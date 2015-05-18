/******************** (C) COPYRIGHT 2013 BUILDWIN ********************************
* File Name          : menu_display.c
* Author             :
* Version            :
* Date               : 18/10/2013
* Description        : This file provides all the main flow of the menu functions.
**********************************************************************************/
//===================================================================
//                                                     	            |
//                       INCLUDE FILES                              |
//                                                                  |
//===================================================================
#include "../header/include.h"


//===================================================================
//                                                     	            |
//                      GLOBAL VARIABLE                             |
//                                                                  |
//===================================================================
FontLibrary FontLib;


/*******************************************************************************
* Function Name  : FontInit
* Description    : initial font.
* Input          :
* Output         : None
* Return         : None
*******************************************************************************/
void FontInit(void)
{	
#if	(USER_CONFIG!=CONFIG_AX3251_AIRBORNE)
	TABLE_INFO SourceTableHead;
	spi_SFReadData(&SourceTableHead, HeadTableOffset+RES_FONT*8, 8);
	spi_SFReadData(&FontLib, HeadTableOffset+SourceTableHead.Addr, 4);
	if(FontLib.NumOfUnicode < 1)
	{
		deg_Printf("no unicode\n");
	}
	deg_Printf("FontLib.NumOfUnicode=0x%x\n",FontLib.NumOfUnicode);
	FontLib.UniAddrOffset = HeadTableOffset+SourceTableHead.Addr+4;
#endif
}

/*******************************************************************************
* Function Name  : GetUnicodeIndex
* Description    : get unicode information.
* Input          : unicode     :
                   pFont       :
* Output         : None
* Return         : None
*******************************************************************************/
void GetUnicodeIndex(u16 unicode,FontIndexInfo *pFont)
{
#if	(USER_CONFIG!=CONFIG_AX3251_AIRBORNE)
	u32 AddrOffset;
	FontSegInfo FontSegInf;
	AddrOffset = FontLib.UniAddrOffset;

    u16 low, mid, high;
    low = 1;
    high = FontLib.NumOfUnicode+1;
    while (1)
    {
        mid = (low + high) / 2;
       spi_SFReadData(&FontSegInf, AddrOffset + (mid - 1) * sizeof(FontSegInf), sizeof(FontSegInf));

        if (unicode < FontSegInf.UnicoValue)
            high = mid -1;
        else if(unicode > FontSegInf.UnicoValue)
            low = mid + 1;
        else
            break;

        if(low > high) {
            //can't find unicode ,find 0x25a1 
        	unicode = 0x25a1;
            low = 1;                        //重新开始查找
            high = FontLib.NumOfUnicode+1;
        }
    }

 //	deg_Printf("FontSegInf.UnicoValue = %x,FontSegInf.StartAddr = %x",FontSegInf.UnicoValue,FontSegInf.StartAddr);
	AddrOffset = FontLib.UniAddrOffset + FontSegInf.StartAddr;
	spi_SFReadData(pFont,AddrOffset,8);
//	deg_Printf("unicode =0x%x, pFont->x=%d,pFont->y=%d,pFont->length=%d",unicode,pFont->x,pFont->y,pFont->length);
	pFont->BaseAddr +=   FontLib.UniAddrOffset ;
#endif
}


/*******************************************************************************
* Function Name  : GetStrFontInfo
* Description    : analyse the UTF-8 and get unicode information.
* Input          : pString     : string
                   pFontGroup  :
* Output         : None
* Return         : None
*******************************************************************************/
void  GetStrFontInfo(u8 *pString,FontGroup *pFontGroup )
{
#if	(USER_CONFIG!=CONFIG_AX3251_AIRBORNE)
	u8 string_flag = 0;
	pFontGroup->handleflag= 0;
	pFontGroup->num = 0;
	pFontGroup->fontx = 0;

	while(*pString !='\0')
	{
		u16 temp;
		u8 a,b;

		temp = *pString++ ;

		if((temp&0xF0)==0xE0)
		{
			a = *pString++ ;
			b = *pString++ ;
			temp =(temp&0x0f)<<12 |(((u16)a)&0x3f)<<6 |(b&0x3f);
		}
		else if((temp&0xE0)==0xC0)
		{
			a = *pString++ ;
			temp =(temp&0x1f)<<6 |(a&0x3f);
		}

		if((temp >0x590) &&  (temp<0x600))		//hebrew handle different, i guess have one hebrew char in string,this string all chars will be hebrew language
		{
			string_flag = LANGUAGE_HEB;
		}

		GetUnicodeIndex(temp, (FontIndexInfo*)(&(pFontGroup->FontInfo[pFontGroup->num])));
		if( (temp ==  0xe31) || ((temp >  0xe33) && (temp < 0xe3b))  || ((temp >  0xe46) && (temp < 0xe4f)) )			//language_thai spac char
		{
			pFontGroup->handleflag |= BIT(pFontGroup->num);
		}
		else
		{
			pFontGroup->fontx += (pFontGroup->FontInfo[pFontGroup->num]).x;
		}
		pFontGroup->num++;
	}


	if(LANGUAGE_HEB == string_flag)		// because hebrew language is from right to left ,so handle it
	{
		FontIndexInfo temp_info;
		int i ;
		for(i = 0;i <pFontGroup->num/2;i++)
		{
			temp_info = pFontGroup->FontInfo[i];
			pFontGroup->FontInfo[i] = pFontGroup->FontInfo[pFontGroup->num-i-1];
			pFontGroup->FontInfo[pFontGroup->num-i-1] = temp_info;
		}
	}
#endif
}

/*******************************************************************************
* Function Name  : UnicodeInfoUpdate
* Description    : display one character.
* Input          : pOSDInf     : osd layer
                   pFont       :
                   xs          : start x
                   ys          : start y
                   forecolor   :
                   backcolor   :
					flag       : 0 :DisplayUnicodeStr; 1:DotMatrixIconDisplay
* Output         : None
* Return         : None
*******************************************************************************/
void UnicodeInfoUpdate(OSDInf *pOsdInfo,FontIndexInfo *pFont,u16 xs,u16 ys,u8 foreColor,u8 backColor,u8 flag,u32 language_handle)
{
#if	(USER_CONFIG!=CONFIG_AX3251_AIRBORNE)
	u16 i=0,j=0;
	u8 *pSdramAddr,*pStartAddr,*pTemp;
	u8 temp[512];

	pTemp =(u8*)temp;

	if(pFont->x==0 ||pFont->y==0)
	{
		return;
	}

	spi_SFReadData(temp, pFont->BaseAddr, pFont->length);

	pStartAddr =(u8 *)(pOsdInfo->sdramaddr)+ ys*pOsdInfo->xwidth + xs;
	pSdramAddr = pStartAddr;

	u8 temp8;
	u8 shift;
	while(pFont->length--)
	{
		temp8 = *pTemp++;
		for(shift=0;shift<8;shift++)
		{
			pSdramAddr =(u8 *)pStartAddr+ i + (j+shift)*pOsdInfo->xwidth;
			if(temp8 &(1<<(shift)))
			{
				if((flag == 0)||(flag == 2))
				{
					if(language_handle)					//just for thai language
					{
						if(shift < (pFont->y/4+1) && (j < 8))		//guess 1/4 pos 
						{
							*pSdramAddr = foreColor ;
						}
					}
					else
					{
						*pSdramAddr = foreColor ;
					}
				}
			}
			else
			{
				if((flag == 1)||(flag == 2))
					*pSdramAddr = backColor;
			}
		}
		i++;
		if(i==pFont->x)
		{
			i = 0;
			j += 8;
		}
	}
#endif
}

/*******************************************************************************
* Function Name  : UnicodeInfoUpdate_EX
* Description    : read one character data to SDRAM.
* Input          : pOSDInf     : osd layer
                   pFont       :
                   xs          : start x
                   ys          : start y
                   forecolor   :
                   backcolor   :
					flag       : 0 :DisplayUnicodeStr; 1:DotMatrixIconDisplay
* Output         : None
* Return         : None
*******************************************************************************/
void UnicodeInfoUpdate_EX(OSDInf *pOsdInfo,FontIndexInfo *pFont,u16 startx,u16 starty,u16 xs,u16 ys,u16 w,u16 h,u8 foreColor,u8 backColor,u8 flag,u32 language_handle)
{
#if	(USER_CONFIG!=CONFIG_AX3251_AIRBORNE)
	u16 i=0,j=0;
	u8 *pSdramAddr,*pStartAddr,*pTemp;
	u8 temp[512];
	u8 *t = (u8 *)(TEMP_OSDICON_ADDR);

	pTemp =(u8*)temp;

	if(pFont->x==0 ||pFont->y==0)
	{
		return;
	}

	xs -= startx;
	ys -= starty;

	spi_SFReadData(temp, pFont->BaseAddr, pFont->length);
	pStartAddr = (u8 *)(TEMP_OSDICON_ADDR)+ ys*w + xs;
	pSdramAddr = pStartAddr;

	u8 temp8;
	u8 shift;
	while(pFont->length--)
	{
		temp8 = *pTemp++;
		for(shift=0;shift<8;shift++)
		{
			//pSdramAddr =(u8 *)pStartAddr+ i + (j+shift)*pOsdInfo->xwidth;
			pSdramAddr =(u8 *)pStartAddr+ i + (j+shift)*w;
			if(temp8 &(1<<(shift)))
			{
				if((flag == 0)||(flag == 2))
				{
					if(language_handle)					//just for thai language
					{
						if(shift < (pFont->y/4 +1)&& (j < 8))		//just draw head and foot
						{
							*pSdramAddr = foreColor ;
						}
					}
					else
					{
						*pSdramAddr = foreColor ;
					}
				}

			}
			else
			{
				if((flag == 1)||(flag == 2))
					*pSdramAddr = backColor;
			}
		}
		i++;
		if(i==pFont->x)
		{
			i = 0;
			j += 8;
		}
	}
#endif
}

/*******************************************************************************
* Function Name  : DisplayUnicodeStr
* Description    : display the unicode string.
* Input          : pOSDInf     : osd layer
                   pString     : string
                   startx      : start x
                   starty      : start y
                   w           :
                   h           :
                   forecolor   :
                   backcolor   :
                   align       :   1 is right align,   2 is center align . other value is left align
* Output         : None
* Return         : None
*******************************************************************************/
void DisplayUnicodeStr(OSDInf *pOSDInf,u8 *pString,u16 startx,u16 starty,u16 w,u16 h,u8 forecolor, u8 backcolor,u8 align)
{
#if	(USER_CONFIG!=CONFIG_AX3251_AIRBORNE)
	FontGroup  font_group;
	u16 tempx,tempsx,tempw;
	u16 width;
	u8 i;
	GetStrFontInfo(pString,(FontGroup *)&font_group);
	#if (MENU_WIDTH == 320)
	starty += 4;
	#elif(MENU_WIDTH == 160)
	
	#endif
	if(w > font_group.fontx)
	{
		tempw = font_group.fontx;
	}
	else
		tempw = w;


	if(align ==1)
	{
		tempx =startx+w-tempw;
	}
	else if((align == 2)||(align == 4))
	{
		tempx =startx+(w-tempw)/2;
	}
	else
		tempx = startx;

	tempsx = tempx;
	width = w+startx;

	for(i=0; i<font_group.num; i++)
	{
		if((tempx+(font_group.FontInfo[i]).x -4 > width))
		{
			starty += h;
			tempx = tempsx;
		}
		if((align ==3)||(align ==4))
			UnicodeInfoUpdate(pOSDInf,&(font_group.FontInfo[i]),tempx,starty,forecolor,backcolor,2,(font_group.handleflag & BIT(i)));
		else
			UnicodeInfoUpdate(pOSDInf,&(font_group.FontInfo[i]),tempx,starty,forecolor,backcolor,0,(font_group.handleflag & BIT(i)));

		if((font_group.handleflag & BIT(i+1)) && (i+1 <font_group.num))			//for language thai spac handle
		{
		}
		else
		{
			tempx+=(font_group.FontInfo[i]).x;
		}
	}
//	deg_Printf("total tmpx %d!!!\r\n", tempx);
#endif
}

/*******************************************************************************
* Function Name  : DotMatrixIconDisplay
* Description    : display Dot Matrix icon.
* Input          : icon_addr   :
                   x           : start x
                   y           : start y
                   forecolor   :
                   backcolor   :
                   align       :
* Output         : None
* Return         : None
*******************************************************************************/
void DotMatrixIconDisplay(u8 icon_addr,u16 x,u16 y,u8 forecolor,u8 backcolor)
{
#if	(USER_CONFIG!=CONFIG_AX3251_AIRBORNE)
	TABLE_INFO SourceTableHead;
	ICON_FILE_HEAD  icon_head;
	IconIndexInfo Icon;

	spi_SFReadData(&SourceTableHead, HeadTableOffset+RES_DOT_MATRIX*8, 8);
    spi_SFReadData(&icon_head, HeadTableOffset+SourceTableHead.Addr+(icon_addr)*sizeof(ICON_FILE_HEAD)+4, sizeof(ICON_FILE_HEAD));
    Icon.x = icon_head.x;
    Icon.y = icon_head.y;
    Icon.BaseAddr = HeadTableOffset+SourceTableHead.Addr + icon_head.addr;
    Icon.length = icon_head.length;
    UnicodeInfoUpdate(menu_mgroup.p_menu_inf,&Icon,x,y,backcolor,forecolor,1,0);
#endif
}


/*******************************************************************************
* Function Name  : DisplayUnicodeStr
* Description    : display the unicode string.
* Input          : pOSDInf     : osd layer
                   pString     : string
                   startx      : start x
                   starty      : start y
                   w           :
                   h           :
                   forecolor   :
                   backcolor   :
                   align       :   1 is right align,   2 is center align . other value is left align
* Output         : None
* Return         : None
*******************************************************************************/
void DisplayUnicodeStr_ToTempBuf(OSDInf *pOSDInf,u8 *pString,u16 startx,u16 starty,u16 offset_x,u16 offset_y,u16 w,u16 h,u8 forecolor, u8 backcolor,u8 align)
{
#if	(USER_CONFIG!=CONFIG_AX3251_AIRBORNE)
	FontGroup  font_group;
	u16 tempx,tempsx,tempw;
	u16 width;
	u8 i;
	GetStrFontInfo(pString,(FontGroup *)&font_group);
	#if (MENU_WIDTH == 320)
	starty += 4;
	#elif(MENU_WIDTH == 160)
	
	#endif

	if(w > font_group.fontx)
	{
		tempw = font_group.fontx;
	}
	else
		tempw = w;

	if((align&0x0f) ==1)
	{
		tempx =startx+w-tempw;
	}
	else if(((align&0x0f) == 2)||((align&0x0f) == 4))
	{
		tempx =startx+(w-tempw)/2;
	}
	else
		tempx = startx;

	tempsx = tempx;
	width = w+startx;

	for(i=0; i<font_group.num; i++)
	{
		if((tempx+(font_group.FontInfo[i]).x -4 > width))
		{
			starty += h;
			tempx = tempsx;
		}
		if((align>>4)&0x0f == 0xf)
		{
			UnicodeInfoUpdate_EX(pOSDInf,&(font_group.FontInfo[i]),startx-offset_x,starty-offset_y,tempx,starty,w,h,forecolor,backcolor,0,(font_group.handleflag & BIT(i)));
		}
		else
		{
			if((align&0x0f ==3)||(align&0x0f ==4))
				UnicodeInfoUpdate(pOSDInf,&(font_group.FontInfo[i]),tempx,starty,forecolor,backcolor,2,(font_group.handleflag & BIT(i)));
			else
				UnicodeInfoUpdate(pOSDInf,&(font_group.FontInfo[i]),tempx,starty,forecolor,backcolor,0,(font_group.handleflag & BIT(i)));
		}

		if((font_group.handleflag & BIT(i+1)) && (i+1 <font_group.num))
		{
		}
		else
		{
			tempx+=(font_group.FontInfo[i]).x;
		}
	}
//	deg_Printf("total tmpx %d!!!\r\n", tempx);
#endif

}

void DisplayUnicodeStr_EXT(OSDInf *pOSDInf,u8 *pString,u16 startx,u16 starty,u16 offset_x,u16 offset_y,u16 w,u16 h,u8 forecolor, u8 backcolor,u8 align)
{
#if	(USER_CONFIG!=CONFIG_AX3251_AIRBORNE)
	lcd_Clean_TempOsdBuf(TEMP_OSDICON_ADDR,w,h);
	DisplayUnicodeStr_ToTempBuf(pOSDInf,pString,startx,starty,offset_x,offset_y,w,h,forecolor, backcolor,align);
	lcd_UpdateOsdIconData_FromSdramToOsdBuf(&OSD1Inf, TEMP_OSDICON_ADDR, startx,starty,w,h);
#endif

}

