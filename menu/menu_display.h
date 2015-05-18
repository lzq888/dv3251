/******************** (C) COPYRIGHT 2013 BUILDWIN ************************/
#ifndef _MENU_DISPLAY_H_
#define _MENU_DISPLAY_H_

#define MENU_DISPLAY_DISABLE	0
#define MENU_DISPLAY_ENABLE		1


//一个字节的不同bit表示需要更新不同的内容，用于大致判断要刷哪一个大部分
//#define LCD_UPDATE_FLAG		7
#define MENU_ITEMS_UPDATE_FLAG     6    //显示状态栏当前菜单页数以及总页数
#define MENU_HEARD_DISPLAY_FLAG    5    //显示菜单标题栏图标或者菜单项图标
//#define MENU_TAIL_DISPLAY_FLAG   4
//BIT0 ~ BIT3 表示不同的菜单级是否要显示菜单标题

//一个字节的不同bit表示需要更新不同的内容，用于子函数中细化要刷的部分
#define MENU_ITEM_HEADER_PIC        6  //显示菜单标题栏的标题图片(非点阵)
#define MENU_ITEM_DOT_MATRIX_PIC    5  //显示菜单标题栏或者菜单项的点阵图片
#define MENU_ITEM_STRING            4  //显示标题或者菜单项的点阵字符串

extern MENU_MGROUP menu_mgroup;
extern MENU_TO_PAGE cur_menu;

void MenuInit(void);
void ClrOSDDisplayFlag(u8 n);
void SetOSDDisplayFlag(u8 n);
void MenuOsdSdramChange(OSDInf *pOsdInf);
void MenuOsdSdramRelease(void);
void MenuBackgroundUpdate(u8 flag);
void MenuItemHighlight(void);
void MenuPageOSDHeaderUpdate(void);
void MenuPageOSDUpdate(void);
void MenuItemDisplay(MENU_ITEM *MenuItem,u16 startx,u16 starty,u16 w,u8 forecolor,u8 backcolor,u8 flag);
void MenuUpdate(MENU_PAGE *pMenuPage,u8 flag);
void SetCurMenuType(MENU_TYPE menu_type);
void LoadMenuMPageInfo(u8 flag);
void MenuPagePrev(MENU_PAGE *pMenuPage);
void MenuItemUp(MENU_MPAGE  *pMP);
void MenuItemDown(MENU_MPAGE  *pMP);
void MenuHandle(void);
u8 MenuAct(u8 act_num,u8 index);
void MenuExit(void);
void MenuDisplay(MENU_TYPE menu_type);


#endif
