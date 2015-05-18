/******************** (C) COPYRIGHT 2013 BUILDWIN ********************************
* File Name          : menu_display.c
* Author             : tingliu
* Version            : V1018a
* Date               : 10/18/2013
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
MENU_MGROUP menu_mgroup;
MENU_TO_PAGE cur_menu;


/*******************************************************************************
* Function Name  : ClrOSDDisplayFlag
* Description    :
* Input          : n : bit n to be cleared
* Output         : None
* Return         : None
*******************************************************************************/
void ClrOSDDisplayFlag(u8 n)
{
	menu_mgroup.display_update_flag &= ~BIT(n);
}

/*******************************************************************************
* Function Name  : SetOSDDisplayFlag
* Description    :
* Input          : n : bit n to be set
* Output         : None
* Return         : None
*******************************************************************************/
void SetOSDDisplayFlag(u8 n)
{
	menu_mgroup.display_update_flag |= BIT(n);
}

/*******************************************************************************
* Function Name  : GetItemNums
* Description    :
* Input          : x    : current page
                   t    : total page
                   pTemp: character string to display
* Output         : None
* Return         : None
*******************************************************************************/
void GetItemNums(u8 x,u8 t,u8 *pTemp)
{
	u8 i=0,j=0;
	byte2Dec(x,pTemp);
	pTemp[2]='/';
	byte2Dec(t,(u8*)&pTemp[3]);
	pTemp[5]='\0';

	for(;i<6;i++,j++)
	{
		if((i==0||i==3)&&(pTemp[i]=='0'))
			i++;
		pTemp[j] = pTemp[i];
	}
}

/*******************************************************************************
* Function Name  : MenuOsdSdramChange
* Description    : ä¸ä¸çº§èååæ¢æèä¸ä¸åæ¢éä¸­é¡¹çæ¶åï¼åå¨å¦ä¸ä¸ªbufferä¸ä¿®æ¹å¥½
                                                    æ°æ®ï¼ç¶åååæ¢æ¾ç¤ºbufferï¼é¿åå±å¹çåºéªççä¿®æ¹è¿ç¨
* Input          : pOsdInfo   : OSD layer
* Output         : None
* Return         : None
*******************************************************************************/
void MenuOsdSdramChange(OSDInf *pOsdInf)
{
/*	if(pOsdInf->sdramaddr == OSD3_DATA_ADR)
	{
		memcpy__((u8*)OSD3_DATA_ADR_b, (u8*)OSD3_DATA_ADR,pOsdInf->xwidth*pOsdInf->yheight);
		pOsdInf->sdramaddr = OSD3_DATA_ADR_b;
	}
	else
	{
		memcpy__((u8*)OSD3_DATA_ADR, (u8*)OSD3_DATA_ADR_b,pOsdInf->xwidth*pOsdInf->yheight);
		pOsdInf->sdramaddr = OSD3_DATA_ADR;
	}*/
//	REG32(LCDCON45) = menu_mgroup.p_menu_inf->sdramaddr;   //change osd sdram buffer
	lcd_FillPartOsdData(pOsdInf, menu_level_clear_region[menu_mgroup.level].backcolor, menu_level_clear_region[menu_mgroup.level].xs, menu_level_clear_region[menu_mgroup.level].ys,
			menu_level_clear_region[menu_mgroup.level].w, menu_level_clear_region[menu_mgroup.level].h);

 }

/*******************************************************************************
* Function Name  : MenuOsdSdramRelease
* Description    : ä¸ä¸çº§èååæ¢æèä¸ä¸åæ¢éä¸­é¡¹çæ¶åï¼åå¨å¦ä¸ä¸ªbufferä¸ä¿®æ¹å¥½
                                                    æ°æ®ï¼ç¶åååæ¢æ¾ç¤ºbufferï¼é¿åå±å¹çåºéªççä¿®æ¹è¿ç¨
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MenuOsdSdramRelease(void)
{
	REG32(LCDCON45) = menu_mgroup.p_menu_inf->sdramaddr;   //change osd sdram buffer
}

/*******************************************************************************
* Function Name  : MenuItemDisplay
* Description    : display menu osd picture or string
* Input          : MenuItem   : menu item
                   startx     : start x value
                   starty     : start y value
                   w          : total width for display
                   forecolor  : if dot matrix, forecolor
                   backcolor  : if dot matrix, backcolor
                   flag       : which source to display
* Output         : None
* Return         : None
*******************************************************************************/
void MenuItemDisplay(MENU_ITEM *MenuItem,u16 startx,u16 starty,u16 w,u8 forecolor,u8 backcolor,u8 flag)
{
	if((flag & BIT(MENU_ITEM_HEADER_PIC)) && (MenuItem->type & BIT(6)))//æ¾ç¤ºèåé¡¹çOSDå¾ç
	{
		lcd_UpdateOsdIconData_FromSdram(menu_mgroup.p_menu_inf, MenuItem->act_num,
				startx, starty);
	}

	if((flag & BIT(MENU_ITEM_DOT_MATRIX_PIC)) && (MenuItem->type & BIT(5)))//æ¾ç¤ºèåé¡¹çç¹éµå¾ç
	{
		DotMatrixIconDisplay(MenuItem->icon_addr,startx,starty,forecolor,backcolor);
		startx += MENU_ICON_WIDTH;
		w -= MENU_ICON_WIDTH;
	}

	if((flag & BIT(MENU_ITEM_STRING)) && (MenuItem->type & BIT(4)))//æ¾ç¤ºèåé¡¹çUNICODEå­ç¬¦ä¸?
	{
		u8 align;
		startx += 4;
		w -= 4;
		align = (MenuItem->align & 0x0C)>>2;
		DisplayUnicodeStr(menu_mgroup.p_menu_inf,(u8*)(MenuItem->string_addr->pLanguage[sys_ctl.language]),startx,starty,w,16,forecolor,backcolor,align);
	}
}

/*******************************************************************************
* Function Name  : MenuBackgroundUpdate
* Description    : ä¸ä¸çº§èååæ¢çæ¶åï¼èæ¯å±éæ°å·å¾çæèä¿®æ¹ååæ¥çé¢è?
* Input          : flag      : 0-back to up level
                               1-to next level
* Output         : None
* Return         : None
*******************************************************************************/
void MenuBackgroundUpdate(u8 flag)
{
	if(flag)
	{
		lcd_UpdateOsdIconData_FromSdram(menu_mgroup.p_menu_inf, menu_level_region[menu_mgroup.level].icon,
				menu_level_region[menu_mgroup.level].xs, menu_level_region[menu_mgroup.level].ys);
	}
	else
	{
		lcd_FillPartOsdData(menu_mgroup.p_menu_inf,menu_level_region[menu_mgroup.level].backcolor, menu_level_region[menu_mgroup.level].xs, menu_level_region[menu_mgroup.level].ys,
				menu_level_region[menu_mgroup.level].w, menu_level_region[menu_mgroup.level].h);
	}
}

/*******************************************************************************
* Function Name  : MenuPageUpdate
* Description    : è¿å¥ä¸ä¸çº§èåçæ¶åï¼èåé¡¹çéç½®
* Input          : pMenuPage : menu page
* Output         : None
* Return         : None
*******************************************************************************/
void MenuPageUpdate(MENU_PAGE *pMenuPage)
{
	MENU_MPAGE  *pMP;
	pMP = (MENU_MPAGE *) (&(menu_mgroup.mgr_page));
	if(pMenuPage!=pMP->mpage)
	{
		pMP->mpage = pMenuPage;
		if(pMenuPage->p_menu_item->p_next_menu_page ==NULL)
		{
			if(pMP->mpage->p_menu_item->act_num<=ANL_BEEP_SOUND)
				pMP->index  = *((u8*)&sys_ctl + pMP->mpage->p_menu_item->act_num);
			else
				pMP->index = 0;
			if(pMenuPage->m_roll)
			{
				pMP->page_index = pMP->index - NUM_PAGE;

		        if (pMP->index == 0)
		        {
		        	pMP->page_index = 0;
		        }
		        else if(pMP->index + NUM_PAGE > pMenuPage->total)
		        {
		        	pMP->page_index = (pMenuPage->total > NUM_PAGE) ? pMenuPage->total - NUM_PAGE : 0;
		        }
		        else
		        {
		        	pMP->page_index = pMP->index - 1;
		        }
			}
			else
			{
				pMP->page_index = pMP->index / NUM_PAGE * NUM_PAGE;
			}
		}
		else
		{
			pMP->index = 0;
			pMP->page_index = 0;
		}
	}
}

/*******************************************************************************
* Function Name  : MenuItemHighlight
* Description    : highlight the selected item
* Input          : Index : current item selected
* Output         : None
* Return         : None
*******************************************************************************/
void MenuItemHighlight(void)
{
	lcd_UpdateOsdIconData_FromSdram(menu_mgroup.p_menu_inf, menu_highlight[menu_mgroup.level].icon,
			menu_highlight[menu_mgroup.level].xs, menu_highlight[menu_mgroup.level].ys + (menu_mgroup.mgr_page.index%NUM_PAGE)*(MENU_ITEM_HEIGHT));
}

/*******************************************************************************
* Function Name  : MenuPageOSDHeaderUpdate
* Description    : update the menu header and tail character and the header picture.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MenuPageOSDHeaderUpdate(void)
{
	MENU_ITEM  *MenuItem;
	u16 startx = 0, starty = 0, itemw = 0;
	u8 flag = 0;
	u8 i;

	if(menu_mgroup.display_update_flag & BIT(MENU_HEARD_DISPLAY_FLAG))//æ¾ç¤ºèåæ å¾æ ?
	{
		MENU_TYPE menu_type;
		menu_type = menu_mgroup.menu_type;

		startx = MENU_XS;
		starty = MENU_YS;
		itemw = MENU_W;
		lcd_FillPartOsdData(menu_mgroup.p_menu_inf,HEAD_STATUS_BACK_COLOR,MENU_XS,MENU_YS,MENU_W,MENU_HEAD_HEIGHT); //clear title content

		for(i = 0; i < 2; i++)
		{
			MenuItem =menu2page[menu_type].p_menu_page->p_menu_item + menu2page[menu_type].p_menu_page->total;  //æ é¢æ¾å¨itemå­ç¬¦ä¸²çæåé¢
			if(i == menu_mgroup.menu_mode)
			{
				flag = BIT(MENU_ITEM_HEADER_PIC);
				MenuItemDisplay(MenuItem,startx,starty+2,itemw,CHARACTER_FORE_COLOR,HEAD_STATUS_BACK_COLOR,flag);
			}
			else
			{
				flag = BIT(MENU_ITEM_DOT_MATRIX_PIC);
				MenuItemDisplay(MenuItem,startx+6,starty+5,itemw,CHARACTER_FORE_COLOR,HEAD_STATUS_BACK_COLOR,flag);
			}

			startx += MENU_TITLE_PIC_WIDTH;     //æ¾ç¤ºçæ é¢æ çå¾æ å®½åº?
			menu_type = menu_list[menu_type].next_menu_type;
		}
		ClrOSDDisplayFlag(MENU_HEARD_DISPLAY_FLAG);
	}
	if((menu_mgroup.display_update_flag & BIT(menu_mgroup.level)) && menu_mgroup.mgr_page.mpage->m_title)//æ¾ç¤ºèåæ å­æ é¢
	{
		MenuItem = menu_mgroup.mgr_page.mpage->p_menu_item + menu_mgroup.mgr_page.mpage->total;
		if(MenuItem->align & 0x05)
		{//åæ¸é¤åèåæ çæå­åå®¹
			lcd_FillPartOsdData(menu_mgroup.p_menu_inf, HEAD_STATUS_BACK_COLOR, MENU_TITLE_STR_XS, MENU_YS, MENU_W-MENU_TITLE_STR_XS, MENU_HEAD_HEIGHT);
			startx = MENU_TITLE_STR_XS;
			starty = MENU_YS+2;
			itemw = MENU_W-MENU_TITLE_STR_XS;
		}
		else if(MenuItem->align & 0x08)
		{
			startx = menu_level_region[menu_mgroup.level].xs;
			starty = menu_level_region[menu_mgroup.level].ys+2; //è®©å­å¨é«åº¦ä¸å±ä¸­æ¾ç¤º
			itemw = menu_level_region[menu_mgroup.level].w-4;   //ç¬¬äºçº§è·ç¬¬ä¸çº§èåï¼æè¾¹æ¡ï¼åå»è¾¹æ¡çå®½åº?
		}
		else
			return;
		flag = BIT(MENU_ITEM_STRING);
		MenuItemDisplay(MenuItem,startx,starty,itemw,CHARACTER_FORE_COLOR,HEAD_STATUS_BACK_COLOR,flag);
		ClrOSDDisplayFlag(menu_mgroup.level);
	}
	if(menu_mgroup.display_update_flag & BIT(6))//æ¾ç¤ºç¶ææ å½åèåé¡µæ°ä»¥åæ»é¡µæ?
	{
		lcd_UpdateOsdIconData_FromSdram(menu_mgroup.p_menu_inf,OSD_MENU_aMenuStatus,MENU_XS,207);
		if(menu_mgroup.level == 0)
		{
			u8 temp[6];
			lcd_FillPartOsdData(menu_mgroup.p_menu_inf, HEAD_STATUS_BACK_COLOR, MENU_TAIL_PAGE_OK_X, MENU_STATUS_BAR_Y,
					MENU_TAIL_PAGE_OK_W, MENU_STATUS_BAR_H);
			GetItemNums((menu_mgroup.mgr_page.page_index+NUM_PAGE)/NUM_PAGE, (menu_mgroup.mgr_page.mpage->total+NUM_PAGE-1)/NUM_PAGE,
					(u8*)&temp);
			DisplayUnicodeStr(menu_mgroup.p_menu_inf, (u8*)&temp, MENU_TAIL_PAGE_OK_X, MENU_STATUS_BAR_Y,
					MENU_TAIL_PAGE_OK_W, FONT_HEIGHT, CHARACTER_FORE_COLOR, HEAD_STATUS_BACK_COLOR,0);
		}
	}

}

/*******************************************************************************
* Function Name  : LoadMenuMPageInfo
* Description    : save or get the menu
* Input          : flag
* Output         : None
* Return         : None
*******************************************************************************/
void LoadMenuMPageInfo(u8 flag)
{
	if(flag)
	{
		menu_mgroup.mgr_group[menu_mgroup.level] = menu_mgroup.mgr_page;
	}
	else
	{
		menu_mgroup.mgr_page = menu_mgroup.mgr_group[menu_mgroup.level];
	}
}

/*******************************************************************************
* Function Name  : MenuPagePrev
* Description    : menu back to last level menu
* Input          : pMenuPage
* Output         : None
* Return         : None
*******************************************************************************/
void MenuPagePrev(MENU_PAGE *pMenuPage)
{
	menu_mgroup.level = 0;
	LoadMenuMPageInfo(0);
	MenuUpdate(menu_mgroup.mgr_page.mpage,0);
}

/*******************************************************************************
* Function Name  : MenuPageOSDUpdate
* Description    : update the menu character and the header picture.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MenuPageOSDUpdate(void)
{
	MENU_ITEM  *MenuItem;
	u8 i;
	u8 num;
	u16 x,y;

	MenuItem = (MENU_ITEM *)(menu_mgroup.mgr_page.mpage->p_menu_item)+menu_mgroup.mgr_page.page_index;
	num = menu_mgroup.mgr_page.mpage->total-menu_mgroup.mgr_page.page_index;
	if(num > NUM_PAGE)
		num = NUM_PAGE;
	MenuPageOSDHeaderUpdate();
	MenuItemHighlight();
	for(i = 0 ; i < num; i++)
	{
		u8 selected = (i==menu_mgroup.mgr_page.index%NUM_PAGE)?0:1;
		if(menu_mgroup.level && selected)
			selected = 2; //ç¬¬ä¸çº§èåæªéä¸­çèæ¯è²è·ç¬¬äºçº§èåæªéä¸­çèæ¯è²ä¸å
		x = menu_highlight[menu_mgroup.level].xs+4; //+4,æ¹å¼é«äº®å·¦ä¸è§çä¸è§å½¢è¢«è¦çäº?
		y = menu_highlight[menu_mgroup.level].ys+(MENU_ITEM_HEIGHT)*i+1; //è¿é+1æ¯ä¸ºäºæ¾ç¤ºææä¸çå±ä¸­ï¼å¯æ ¹æ®å®éå¾çè·å±å¹å°ºå¯¸ç¨å¾®ä¿®æ¹
		MenuItemDisplay(MenuItem,x,y,menu_highlight[menu_mgroup.level].w,menu_mgroup.fore_color[selected],menu_mgroup.back_color[selected],0x30);
		MenuItem++;
	}
}

/*******************************************************************************
* Function Name  : MenuUpdate
* Description    :
* Input          : pMenuPage : menu page information details
                   flag      : 0-back to up level
                               1-to next level
* Output         : None
* Return         : None
*******************************************************************************/
void MenuUpdate(MENU_PAGE *pMenuPage,u8 flag)
{
	if(pMenuPage == NULL)
		return;
	SetOSDDisplayFlag(menu_mgroup.level);
	MenuOsdSdramChange(menu_mgroup.p_menu_inf);

	MenuBackgroundUpdate(flag);
	MenuPageUpdate(pMenuPage);

	MenuPageOSDUpdate();
	MenuOsdSdramRelease();
}

/*******************************************************************************
* Function Name  : MenuCommonEvent
* Description    : deal with the common event
* Input          : msg : msg to deal
* Output         : None
* Return         : None
*******************************************************************************/
void MenuCommonEvent(u8 msg)
{
	if(msg == (T_KEY_MENU | T_KEY_SHORT_UP))
	{
		if(menu_mgroup.level==0)
		{
			menu_mgroup.menu_mode ++;
			if(menu_mgroup.menu_mode==1)
			{
				SetOSDDisplayFlag(MENU_HEARD_DISPLAY_FLAG);
				SetCurMenuType(MENU_ATTRIBUTE);
			}
			else
				SetCurMenuType(MENU_IDLE);
		}
		else
		{
			MenuPagePrev(menu_mgroup.mgr_page.mpage->p_prev_menu_page);
		}
	}
//	else
//	{
//		deal_msg(msg);
//	}
}

/*******************************************************************************
* Function Name  : MenuItemUp
* Description    :
* Input          : pMP : MENU_MPAGE
* Output         : None
* Return         : None
*******************************************************************************/
void MenuItemUp(MENU_MPAGE  *pMP)
{
    if (pMP->index == 0)
    {
    	pMP->index = pMP->mpage->total-1;
        if (pMP->mpage->m_roll) {
        	pMP->page_index = (pMP->index  > NUM_PAGE) ?pMP->mpage->total - NUM_PAGE : 0;
        } else {
        	pMP->page_index = (pMP->index / NUM_PAGE) * NUM_PAGE;
        }
    }
    else
    {
    	pMP->index--;
        if (pMP->index < pMP->page_index) {
            if (pMP->mpage->m_roll) {
            	pMP->page_index--;
            } else {
            	pMP->page_index -= NUM_PAGE;
            }
        }
    }

	MenuOsdSdramChange(menu_mgroup.p_menu_inf);
	
	if (menu_mgroup.level) {	/* fix 'submenu' bug, 2014-4-25 */
		MenuBackgroundUpdate(1);		
	}
	
	MenuPageOSDUpdate();
	MenuOsdSdramRelease();
}

/*******************************************************************************
* Function Name  : MenuItemDown
* Description    :
* Input          : pMP : MENU_MPAGE
* Output         : None
* Return         : None
*******************************************************************************/
void MenuItemDown(MENU_MPAGE  *pMP)
{
	pMP->index++;
    if (pMP->index - pMP->page_index >= NUM_PAGE) {
        if (pMP->mpage->m_roll) {
        	pMP->page_index++;
        } else {
        	pMP->page_index += NUM_PAGE;
        }
    }
    if (pMP->index == pMP->mpage->total) {
    	pMP->index = 0;
    	pMP->page_index = 0;
    }

	MenuOsdSdramChange(menu_mgroup.p_menu_inf);
	
	if (menu_mgroup.level) {	/* fix 'submenu' bug, 2014-4-25 */
		MenuBackgroundUpdate(1);		
	}
	
	MenuPageOSDUpdate();
	MenuOsdSdramRelease();
}

/*******************************************************************************
* Function Name  : MenuAct
* Description    :
* Input          : act_num  :
                   index    :
* Output         : None
* Return         : None
*******************************************************************************/
u8 MenuAct(u8 act_num,u8 index)
{
	if(act_list[act_num].pActFunc!=NULL&&act_num<=ANL_DATE_AJUST)
		act_list[act_num].pActFunc(index);
	return 0;
}

/*******************************************************************************
* Function Name  : MenuHandle
* Description    :
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MenuHandle(void)
{
	u8 type;
	MENU_ITEM  *MenuItem;
	MenuItem = (MENU_ITEM *)(menu_mgroup.mgr_page.mpage->p_menu_item)+menu_mgroup.mgr_page.index;
	type = MenuItem->type&0x03;
	LoadMenuMPageInfo(1);
	switch(type)
	{
		case MENU_ACT_NEXT:
			menu_mgroup.level++;
			MenuUpdate(MenuItem->p_next_menu_page,1);
			break;

		case MENU_ACT_PREV:
			menu_mgroup.level = 0;
			LoadMenuMPageInfo(0);
			MenuUpdate(menu_mgroup.mgr_page.mpage,0);
			break;

		case MENU_ACT_FUNC:
			MenuAct(MenuItem->act_num,menu_mgroup.mgr_page.index);
			if(cur_menu.menu_type!=MENU_IDLE)
			{
				menu_mgroup.level = 0;
				LoadMenuMPageInfo(0);
				MenuUpdate(menu_mgroup.mgr_page.mpage,0);
			}
			break;

		case MENU_ACT_EXIT:
			SetCurMenuType(MENU_IDLE);
			break;

		default:
			break;
	}
}

/*******************************************************************************
* Function Name  : MenuOSDInit
* Description    : reinitial the OSD1 and OSD3,clear the OSD, use color alpha.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MenuOSDInit(void)
{

	OSDInit(menu_mgroup.p_menu_inf, 0, 0,MENU_WIDTH, MENU_HEIGHT, 0x80, ALPHA_0X00_COLOR);
	OSD3_useColorAlpha();

	OSDInit(&OSD1Inf,0,0 ,MENU_WIDTH,MENU_HEIGHT,0xff,ALPHA_0X00_COLOR);
	OSD1_useColorAlpha();
}

/*******************************************************************************
* Function Name  : MenuInit
* Description    : power on, set the menu default struct value
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MenuInit(void)
{
	//FontInit();
	zeromem((u8*)&menu_mgroup, sizeof(MENU_MGROUP));
	menu_mgroup.lcd_update_enable = 1;
	menu_mgroup.p_menu_inf  = &OSD3Inf;
//	menu_mgroup.p_menuf_inf = &OSD1Inf;
	menu_mgroup.fore_color[0] = SELECT_FORE_COLOR;//éä¸­çèåé¡¹åæ¯è?
	menu_mgroup.back_color[0] = SELECT_BACK_COLOR;//éä¸­çèåé¡¹èæ¯è?
	menu_mgroup.fore_color[1] = UNSELECT_LEV1_FORE_COLOR; //æªéä¸­çç¬¬ä¸çº§èååæ¯è²
	menu_mgroup.back_color[1] = UNSELECT_LEV1_BACK_COLOR; //æªéä¸­çç¬¬ä¸çº§èåèæ¯è²
	menu_mgroup.fore_color[2] = UNSELECT_FORE_COLOR; //æªéä¸­çç¬¬ä¸çº§èååæ¯è²
	menu_mgroup.back_color[2] = UNSELECT_BACK_COLOR; //æªéä¸­çç¬¬ä¸çº§èåèæ¯è²
	cur_menu.menu_type = MENU_IDLE;  //åå§åä¸ºç©ºé²ç¶æ?
	//MenuOSDInit();
	sd_dis_flag = 0;
}

/*******************************************************************************
* Function Name  : SetCurMenuType
* Description    : set current menu type
* Input          : menu_typeï¼æç§æ¨¡å¼ä¸çèåï¼åå«ä¸ºå½åï¼æç§ï¼åæ¾ï¼è®¾ç½®ï¼?
* Output         : None
* Return         : None
*******************************************************************************/
void SetCurMenuType(MENU_TYPE menu_type)
{
	if(menu_type >MENU_ATTRIBUTE||cur_menu.menu_type ==menu_type)
		return;
	cur_menu.menu_type = menu_type;
	cur_menu.p_menu_page = menu2page[menu_type].p_menu_page;
}

/*******************************************************************************
* Function Name  : MenuExit
* Description    : exit menu
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MenuExit(void)
{
	deg_Printf("Exit Menu\n");
	
	waittingLcdFrameEnd();
	DIS_OSD3();
	DIS_OSD1();
//	lcd_FillFullOsdData(menu_mgroup.p_menuf_inf,ALPHA_0X00_COLOR);
	lcd_FillFullOsdData(menu_mgroup.p_menu_inf,ALPHA_0X00_COLOR);
	EN_OSD1();
	//EN_OSD3();
	sd_dis_flag = 0;
//	menu_mgroup.lcd_update_enable = 1;
}

/*******************************************************************************
* Function Name  : MenuDisplay
* Description    : main flow of the menu(èåä¸»æµç¨?
* Input          : menu_typeï¼æç§æ¨¡å¼ä¸çèåï¼åå«ä¸ºå½åï¼æç§ï¼åæ¾ï¼
* Output         : None
* Return         : None
*******************************************************************************/
void MenuDisplay(MENU_TYPE menu_type)
{
	if(menu_type > MENU_ATTRIBUTE || cur_menu.menu_type == menu_type)
		return;
    deg_Printf("Start Menu\n");
	cur_menu.menu_type = menu_type;
	cur_menu.p_menu_page = menu2page[menu_type].p_menu_page;
	MenuOSDInit();
	menu_mgroup.menu_type = cur_menu.menu_type;
	menu_mgroup.menu_mode = 0;
	menu_mgroup.display_update_flag = 0xff;  //update all the items
	if(cur_menu.menu_type != MENU_BROWSE)
		menu_mgroup.lcd_update_enable = 1;
	else
		menu_mgroup.lcd_update_enable = 0;
	menu_mgroup.level = 0;

	while(cur_menu.menu_type != MENU_IDLE)
	{
		u8 menu_type;
		zeromem((u8*)&menu_mgroup,5*sizeof(MENU_MPAGE));
		lcd_UpdateOsdIconData_FromSdram(menu_mgroup.p_menu_inf, menu_level_region[0].icon, 0, 0);
		MenuUpdate(cur_menu.p_menu_page,0);
		menu_type = cur_menu.menu_type;
		while(menu_type == cur_menu.menu_type)
		{
			u8 msg = get_msg() ;

			switch(msg)
			{
				case T_KEY_PLAY | T_KEY_SHORT_UP:
					MenuHandle();
					break;

				case T_KEY_UP | T_KEY_SHORT_UP:
					MenuItemUp(&(menu_mgroup.mgr_page));
					break;

				case T_KEY_DOWN | T_KEY_SHORT_UP:
					MenuItemDown(&(menu_mgroup.mgr_page));
					break;

				default:
					MenuCommonEvent(msg);
					break;
			}

//			if(task_ctl.work_sta == TASK_POWER_OFF)
//				SetCurMenuType(MENU_IDLE);

			if(MENU_IDLE == cur_menu.menu_type)
				break;
//			if(menu_mgroup.lcd_update_enable == 0 && (menu_mgroup.display_update_flag&BIT(LCD_UPDATE_FLAG)))
//			{
//				ClrOSDDisplayFlag(LCD_UPDATE_FLAG);
//				REG32(LCD_CON)&=~BIT(9);
//			}
		}
	}
	MenuExit();
}
