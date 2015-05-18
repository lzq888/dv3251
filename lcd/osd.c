/******************** (C) COPYRIGHT 2013 BUILDWIN ********************************
* File Name          : osd.c
* Author             :
* Version            :
* Date               : 18/10/2013
* Description        : This file provides all the osd functions.
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
OSDInf OSD3Inf,OSD2Inf,OSD1Inf;
unsigned int gImage_palette[256];
u32 OSD_changeFlag;

void OSDInfInit(void)
{
	OSD1Inf.osd_num = 1;       	//enable global int
	OSD2Inf.osd_num = 2;       	//enable global int
	OSD3Inf.osd_num = 3;       	//enable global int
	
	DIS_OSD1();
	DIS_OSD2();
	DIS_OSD3();
}

/*******************************************************************************
* Function Name  : lcd_UpdateOsdLUT
* Description    : load the osd LUT.
* Input          : osdnum : OSD number
* Output         : None
* Return         : None
*******************************************************************************/
void lcd_UpdateOsdLUT(u8 osdnum,u32 sourceindex)
{
	u32 i, lut_address,temp;

	TABLE_INFO SourceTableHead;
	spi_SFReadData(&SourceTableHead, HeadTableOffset+sourceindex*8, 8);
	if(SourceTableHead.Len > 1024) {
		SourceTableHead.Len = 1024;
		deg_Printf("Len error\n");
	}
	bSFBusy_Flag = 1;
	spi_setCSStatus(0);					//CS LOW
	spi_SendByte(SF_READ_DATA);
	spi_SFSendAddr(HeadTableOffset+SourceTableHead.Addr);
	for(i=0; i<(SourceTableHead.Len/4); i++)
	{
		temp  = u8spi_ReceiveByte()<<24;
		temp += u8spi_ReceiveByte()<<16;
		temp += u8spi_ReceiveByte()<<8;
		temp += u8spi_ReceiveByte();
		gImage_palette[i] = temp;
	}
	spi_setCSStatus(1);					//CS HIGH
	bSFBusy_Flag = 0;

	switch(osdnum)
	{
		case 1:
			DIS_OSD1();
			lut_address = OSD1_LUT_ADR;
			break;
		case 2:
			DIS_OSD2();
			lut_address = OSD2_LUT_ADR;
			break;
		case 3:
			DIS_OSD3();
			lut_address = OSD3_LUT_ADR;
			break;
		default:
			return;
	}

	u32 lcd_con_reg_save = REG32(LCDCON0);
	DIS_OSD1();
	DIS_OSD2();
	DIS_OSD3();
	lcd_set_panel_colour(0,0,0);
	#if(0 == LCD_MCU)
		waittingLcdFrameEnd();
		REG32(LCDCON0) &= ~(BIT(0)|BIT(6));
		for(i=0; i<256; i++)
		{
			REG32(lut_address+i*4) = gImage_palette[i];
		}
		REG32(LCDCON0) = lcd_con_reg_save;
		REG32(LCDCON0) |= (BIT(0)|BIT(6));
	#else
		REG32(LCDCON0) &= ~(BIT(6));
		waittingLcdFrameEnd();
		for(i=0; i<256; i++)
		{
			REG32(lut_address+i*4) = gImage_palette[i];
		}

		waittingLcdFrameEnd();
		REG32(LCDCON0) = lcd_con_reg_save;
		REG32(LCDCON0) |= (BIT(6));
	#endif
}

/*******************************************************************************
* Function Name  : lcd_FillFullOsdData
* Description    : fill all the osd sdram with the same index.
* Input          : pOsdInfo   : OSD layer
                   ColorIndex : color index
* Output         : None
* Return         : None
*******************************************************************************/
void lcd_FillFullOsdData(OSDInf *pOsdInfo, u8 ColorIndex)
{
	my_memset((void *)(pOsdInfo->sdramaddr), ColorIndex, pOsdInfo->xwidth * pOsdInfo->yheight);
}

/*******************************************************************************
* Function Name  : lcd_OsdInit
* Description    : initial the osd hardware and enable the osd.
* Input          : osdnum : OSD number
* Output         : None
* Return         : None
*******************************************************************************/
void lcd_OsdInit(u8 osdnum)
{
	switch(osdnum)
	{
		case 1:
			REG32(LCDCON43) = OSD1Inf.sdramaddr;
			REG32(LCDCON23) = OSD1Inf.xstart + REG32(LCDCON9);
			REG32(LCDCON24) = OSD1Inf.ystart + REG32(LCDCON13);
			REG32(LCDCON25) = OSD1Inf.xstart + OSD1Inf.xwidth + REG32(LCDCON9) - 1;
			REG32(LCDCON26) = OSD1Inf.ystart + OSD1Inf.yheight + REG32(LCDCON13) - 1;
			REG32(LCDCON37) = OSD1Inf.alpha;
			#if (OSDICON_DISPLAY_ENABLE == OSDICON_DISPLAY_USE)
			EN_OSD1();
			#endif
			break;
		case 2:
			REG32(LCDCON44) = OSD2Inf.sdramaddr;
			REG32(LCDCON27) = OSD2Inf.xstart + REG32(LCDCON9);
			REG32(LCDCON28) = OSD2Inf.ystart + REG32(LCDCON13);
			REG32(LCDCON29) = OSD2Inf.xstart + OSD2Inf.xwidth + REG32(LCDCON9) - 1;
			REG32(LCDCON30) = OSD2Inf.ystart + OSD2Inf.yheight + REG32(LCDCON13) - 1;
			REG32(LCDCON38) = OSD2Inf.alpha;
			#if (OSDICON_DISPLAY_ENABLE == OSDICON_DISPLAY_USE)
			EN_OSD2();
			#endif
			break;
		case 3:
			REG32(LCDCON45) = OSD3Inf.sdramaddr;
			REG32(LCDCON31) = OSD3Inf.xstart + REG32(LCDCON9);
			REG32(LCDCON32) = OSD3Inf.ystart + REG32(LCDCON13);
			REG32(LCDCON33) = OSD3Inf.xstart + OSD3Inf.xwidth + REG32(LCDCON9) - 1;
			REG32(LCDCON34) = OSD3Inf.ystart + OSD3Inf.yheight + REG32(LCDCON13) - 1;
			REG32(LCDCON39) = OSD3Inf.alpha;
			#if (OSDICON_DISPLAY_ENABLE == OSDICON_DISPLAY_USE)
			EN_OSD3();
			#endif
			break;
		default:
			break;
	}
}
/*******************************************************************************
* Function Name  : OSDInit
* Description    : initial the osd and start osd
* Input          : pOsdInf    : source struct
                   xstart     : osd start x position of the screen
                   ystart     : osd start y position of the screen
                   xwidth     : the width of the osd layer
                   yheight    : the hight of the osd layer
                   alpha      : when use layer alpha, use this value for layer alpha
                   colorindex : fill all the osd sdram
* Output         : None
* Return         : 1
*******************************************************************************/
u8 OSDInit(OSDInf *pOsdInf,u16 xstart,u16 ystart ,u16 xwidth,u16 yheight,u8 alpha,u8 colorindex)
{
	if(pOsdInf->osd_num > 3 || pOsdInf->osd_num == 0)
	{
		return 0;
	}
	pOsdInf->sdramaddr = OSD1_DATA_ADR +(pOsdInf->osd_num-1)*LCD_OSD_SDRAM_SIZE;
	pOsdInf->xstart = xstart;
	pOsdInf->xwidth = xwidth;
	pOsdInf->ystart = ystart;
	pOsdInf->yheight =yheight;
	pOsdInf->alpha   =alpha;
/*
	waittingLcdFrameEnd();
	switch(pOsdInf->osd_num)
	{
		case 1:
			DIS_OSD1();
			break;
		case 2:
			DIS_OSD2();
			break;
		case 3:
			DIS_OSD3();
			break;
	}
*/
	lcd_UpdateOsdLUT(pOsdInf->osd_num,RES_PALETTE_TAB);
	lcd_FillFullOsdData(pOsdInf,colorindex);
	lcd_OsdInit(pOsdInf->osd_num);

	return 1;
}

/*******************************************************************************
* Function Name  : lcd_FillPartOsdData
* Description    : fill the same color index to osd address.
* Input          : pOsdInf    : source struct
                   colorindex : fill all the osd sdram
                   x          : osd start x position of the screen
                   y          : osd start y position of the screen
                   xwidth     : the width of the osd layer
                   yheight    : the hight of the osd layer
* Output         : None
* Return         : None
*******************************************************************************/
void lcd_FillPartOsdData(OSDInf *pOsdInfo, u8 ColorIndex, u16 x, u16 y, u16 xwidth, u16 yheight)
{
	int i, j;
	u8 *a = (u8 *)(pOsdInfo->sdramaddr);

	a += y*pOsdInfo->xwidth + x;
	for(i = 0; i < yheight; i++)
	{
		for(j = 0; j < xwidth; j++)
		{
			*a++ = ColorIndex;
		}
		a += (pOsdInfo->xwidth - xwidth);
	}
}

/*******************************************************************************
* Function Name  : lcd_UpdatePartOsdData
* Description    : update part osd data.
* Input          : pOsdInf    : source struct
*                  source     : the source pointer
*                  sourcenum  : the picture number in the source
                   x          : osd start x position of the screen
                   y          : osd start y position of the screen
* Output         : None
* Return         : None
*******************************************************************************/
void lcd_UpdatePartOsdData(OSDInf *pOsdInfo, u32 sourcenum, u16 x, u16 y)
{
#if	(USER_CONFIG!=CONFIG_AX3251_AIRBORNE)
	int i, j;
	u32 sourceindex = RES_OSD_SOURCE;
	u8 *a = (u8 *)(pOsdInfo->sdramaddr);
//	u8 *pic_source;
	TABLE_INFO SourceTableHead;
	OSDSOURCE_INF OsdSourceHead;
	
	spi_SFReadData(&SourceTableHead, HeadTableOffset+sourceindex*8, 8);
	spi_SFReadData(&OsdSourceHead, HeadTableOffset+SourceTableHead.Addr+sourcenum*12, 12);

	bSFBusy_Flag = 1;
	spi_setCSStatus(0);					//CS LOW
	spi_SendByte(SF_READ_DATA);
	spi_SFSendAddr(HeadTableOffset+SourceTableHead.Addr+OsdSourceHead.dataoffset);
	
	a += y*pOsdInfo->xwidth + x;
	for(i=0; i<OsdSourceHead.yheight; i++)
	{
		for(j=0; j<OsdSourceHead.xwidth; j++)
		{
			*a++ = u8spi_ReceiveByte();
		}
		a += (pOsdInfo->xwidth - OsdSourceHead.xwidth);
	}
	spi_setCSStatus(1);					//CS HIGH
	bSFBusy_Flag = 0;
#endif
}

/*********************************************************************************************************
**  º¯ÊýÃû³Æ£º lcd_UpdatePartOsdData_SDRAM
**  º¯Êý¹¦ÄÜ£º ¸üÐÂ²¿·ÖOSDÊý¾Ý
**  ÊäÈë²ÎÊý£º ¡¾OSDÐÅÏ¢¡¿¡¾SDRAMµØÖ·¡¿¡¾ÆðÊ¼x¡¿¡¾ÆðÊ¼y¡¿¡¾¿í¶È¡¿¡¾¸ß¶È¡¿
*********************************************************************************************************/
void lcd_UpdatePartOsdData_SDRAM(OSDInf *pOsdInfo, u32 sdramaddress, u16 x, u16 y, u16 xwidth, u16 yheight)
{
	int i, j;
	u8 *a = (u8 *)(pOsdInfo->sdramaddr);
	u8 *s = (u8 *)(sdramaddress);

	a += y*pOsdInfo->xwidth + x;
	for(i=0; i<yheight; i++)
	{
		for(j=0; j<xwidth; j++)
		{
			*a++ = *s++;
		}
		a += (pOsdInfo->xwidth - xwidth);
	}
}

void  osd_OsdData_load(u32 sourceindex)
{
	TABLE_INFO SourceTableHead;
	
	spi_SFReadData(&SourceTableHead, HeadTableOffset+sourceindex*8, 8);
	spi_SFReadData((u8 *)OSDICON_BUFF_ADDR, HeadTableOffset+SourceTableHead.Addr, SourceTableHead.Len);
}

/*******************************************************************************
* Function Name  : lcd_UpdatePartOsdData
* Description    : update  osd icon data from sdram.
* Input          : pOsdInf    : source struct
*                  sourceindex : the icon index in spi
*                  sourcenum  : the icon number in the source
                   x          : osd start x position of the screen
                   y          : osd start y position of the screen
* Output         : None
* Return         : None
*******************************************************************************/
void lcd_UpdateOsdIconData_FromSdram(OSDInf *pOsdInfo,u32 sourcenum, u16 x, u16 y)
{
#if	(USER_CONFIG!=CONFIG_AX3251_AIRBORNE)
	int i, j;
	u32 sourceindex = RES_OSD_SOURCE;
	OSDSOURCE_INF OsdSourceHead;
	u8 *a = (u8 *)(pOsdInfo->sdramaddr);
	u8 *s = (u8 *)(OSDICON_BUFF_ADDR);
	u32 *sh = (u32 *)(OSDICON_BUFF_ADDR+sourcenum*12);
	
	OsdSourceHead.xwidth  = sh[0];
	OsdSourceHead.yheight = sh[1];
	OsdSourceHead.dataoffset = sh[2];
	
	s += OsdSourceHead.dataoffset;
	a += y*pOsdInfo->xwidth + x;
	for(i=0; i<OsdSourceHead.yheight; i++)
	{
		for(j=0; j<OsdSourceHead.xwidth; j++)
		{
			*a++ = *s++;
		}
		a += (pOsdInfo->xwidth - OsdSourceHead.xwidth);
	}
#endif
}

/*******************************************************************************
* Function Name  : lcd_UpdatePartOsdData
* Description    : update  osd icon data from sdram.
* Input          : pOsdInf    : source struct
*                  sourceindex : the icon index in spi
*                  sourcenum  : the icon number in the source
                   x          : osd start x position of the screen
                   y          : osd start y position of the screen
* Output         : None
* Return         : None
*******************************************************************************/
void lcd_UpdateOsdIconData_FromSdram_EX(OSDInf *pOsdInfo,u32 sourcenum, u16 x, u16 y)
{
#if	(USER_CONFIG!=CONFIG_AX3251_AIRBORNE)
	int i, j;
	u32 sourceindex = RES_OSD_SOURCE;
	OSDSOURCE_INF OsdSourceHead;
	u8 *a = (u8 *)(pOsdInfo->sdramaddr);
	u8 *t = (u8 *)(TEMP_OSDICON_ADDR);
	u8 *s = (u8 *)(OSDICON_BUFF_ADDR);
	u32 *sh = (u32 *)(OSDICON_BUFF_ADDR+sourcenum*12);
	
	OsdSourceHead.xwidth  = sh[0];
	OsdSourceHead.yheight = sh[1];
	OsdSourceHead.dataoffset = sh[2];
	
	s += OsdSourceHead.dataoffset;
	for(i=0; i<OsdSourceHead.yheight; i++)
	{
		for(j=0; j<OsdSourceHead.xwidth; j++)
		{
			*t++ = *s++;
		}
	}
#endif
}

/*******************************************************************************
* Function Name  : lcd_UpdatePartOsdData
* Description    : update  osd icon data from sdram to OSDBUF.
* Input          : pOsdInf    : source struct
*                  sourceindex : the icon index in spi
*                  SdramAddr  : the icon data source
                   x          : osd start x position of the screen
                   y          : osd start y position of the screen
				   w		  : OSD source width
				   h		  : OSD source height
				    * 
* Output         : None
* Return         : None
*******************************************************************************/
void lcd_UpdateOsdIconData_FromSdramToOsdBuf(OSDInf *pOsdInfo,u32 SdramAddr, u16 x, u16 y,u16 w,u16 h)
{
	int i, j;
	u8 *a = (u8 *)(pOsdInfo->sdramaddr);
	u8 *t = (u8 *)(SdramAddr);

	a += y*pOsdInfo->xwidth + x;
	for(i=0; i<h; i++)
	{
		for(j=0; j<w; j++)
		{
			*a++ = *t++;
		}
		a += (pOsdInfo->xwidth - w);
	}
}

void lcd_Clean_TempOsdBuf(u32 addr, u16 w, u16 h)
{
	u16 i,j;
	u8 *t = (u8 *)addr;
	
	for(i=0; i<h; i++)
	{
		for(j=0; j<w; j++)
		{
			*t++ = 0;
		}
	}
}