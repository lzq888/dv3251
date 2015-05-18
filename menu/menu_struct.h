/******************** (C) COPYRIGHT 2013 BUILDWIN ************************/
#ifndef _MENU_STRUCT_H_
#define _MENU_STRUCT_H_

#include "../config/config.h"



#if 1  		//(LCD_WIDTH >= 320)
	#define MENU_WIDTH  320
	#define MENU_HEIGHT  240
//	#define MENU_WIDTH  220
//	#define MENU_HEIGHT  176
#else 		//((LCD_WIDTH < 320)&&(LCD_WIDTH >= 160))
	#define MENU_WIDTH  160
	#define MENU_HEIGHT  120
#endif

#if (MENU_WIDTH == 320)
#define	FONT_HEIGHT 24
#define MENU_XS					10
#define MENU_YS					5
#define MENU_W                  (320-MENU_XS*2)
#define MENU_H                  (240-MENU_YS*2)
#define MENU_HEAD_HEIGHT		42
#define MENU_ITEM_HEIGHT		40     //Ã¿Ò»ÐÐ²Ëµ¥ÏîµÄ¸ß¶È
#define NUM_PAGE   			    4      //menu items every page
#define MENU_OFFSET_LEVEL_X		8      //µÚ¶þ¼¶²Ëµ¥ÓëµÚÒ»¼¶²Ëµ¥£¨»òÕßµÚÈý¼¶¸úµÚÒ»¼¶£©ÆðÊ¼XÖ®¼äµÄ¼ä¾à£¬³ýÁËÍ¼±êÍâ
#define MENU_ICON_HEIGHT		0x20   //²Ëµ¥ÏîµÄÍ¼±êµÄ¸ß¶È
#define MENU_ICON_WIDTH			0x20   //²Ëµ¥ÏîµÄÍ¼±êµÄ¿í¶È

#define MENU_ITEM1_W		236
#define MENU_ITEM1_H		34
#elif(MENU_WIDTH == 220)
#define	FONT_HEIGHT 24
#define MENU_XS					10
#define MENU_YS					5
#define MENU_W                  (220-MENU_XS*2)
#define MENU_H                  (176-MENU_YS*2)
#define MENU_HEAD_HEIGHT		42
#define MENU_ITEM_HEIGHT		40     //Ã¿Ò»ÐÐ²Ëµ¥ÏîµÄ¸ß¶È
#define NUM_PAGE   			    4      //menu items every page
#define MENU_OFFSET_LEVEL_X		8      //µÚ¶þ¼¶²Ëµ¥ÓëµÚÒ»¼¶²Ëµ¥£¨»òÕßµÚÈý¼¶¸úµÚÒ»¼¶£©ÆðÊ¼XÖ®¼äµÄ¼ä¾à£¬³ýÁËÍ¼±êÍâ
#define MENU_ICON_HEIGHT		0x20   //²Ëµ¥ÏîµÄÍ¼±êµÄ¸ß¶È
#define MENU_ICON_WIDTH			0x20   //²Ëµ¥ÏîµÄÍ¼±êµÄ¿í¶È

#define MENU_ITEM1_W		160
#define MENU_ITEM1_H		34
#elif(MENU_WIDTH == 160)
#define	FONT_HEIGHT 16
#define MENU_XS					5
#define MENU_YS					1
#define MENU_W                  (160-MENU_XS*2)
#define MENU_H                  (120-MENU_YS*2)
#define MENU_HEAD_HEIGHT		22
#define MENU_ITEM_HEIGHT		20     //Ã¿Ò»ÐÐ²Ëµ¥ÏîµÄ¸ß¶È
#define NUM_PAGE   			    4      //menu items every page
#define MENU_OFFSET_LEVEL_X		4      //µÚ¶þ¼¶²Ëµ¥ÓëµÚÒ»¼¶²Ëµ¥£¨»òÕßµÚÈý¼¶¸úµÚÒ»¼¶£©ÆðÊ¼XÖ®¼äµÄ¼ä¾à£¬³ýÁËÍ¼±êÍâ
#define MENU_ICON_HEIGHT		0x10   //²Ëµ¥ÏîµÄÍ¼±êµÄ¸ß¶È
#define MENU_ICON_WIDTH			0x10   //²Ëµ¥ÏîµÄÍ¼±êµÄ¿í¶È

#define MENU_ITEM1_W		112
#define MENU_ITEM1_H		20
#endif


//½øÈëµÚÒ»¼¶²Ëµ¥£¬³ýÁË±êÌâ¸úµ×²¿µÄÐÅÏ¢Ö®Íâ£¬¿ªµÄ´°¿ÚµÄ´óÐ¡
#define MENU_LEVEL1_REGION_X              MENU_XS
#define MENU_LEVEL1_REGION_Y              MENU_YS+MENU_HEAD_HEIGHT
#define MENU_LEVEL1_REGION_W		      300
#define MENU_LEVEL1_REGION_H		      160

//½øÈëµÚ¶þ¼¶²Ëµ¥£¬³ýÁË±êÌâ¸úµ×²¿µÄÐÅÏ¢Ö®Íâ£¬¿ªµÄ´°¿ÚµÄ´óÐ¡
#define MENU_LEVEL2_REGION_X              MENU_LEVEL1_REGION_X+MENU_ICON_WIDTH+MENU_OFFSET_LEVEL_X
#define MENU_LEVEL2_REGION_Y              MENU_LEVEL1_REGION_Y
#define MENU_LEVEL2_REGION_W		      MENU_LEVEL1_REGION_W-MENU_ICON_WIDTH-2*MENU_OFFSET_LEVEL_X
#define MENU_LEVEL2_REGION_H		      MENU_LEVEL1_REGION_H

//½øÈëµÚÈý¼¶²Ëµ¥£¬³ýÁË±êÌâ¸úµ×²¿µÄÐÅÏ¢Ö®Íâ£¬¿ªµÄ´°¿ÚµÄ´óÐ¡
#define MENU_LEVEL3_REGION_X              MENU_LEVEL2_REGION_X
#define MENU_LEVEL3_REGION_Y              MENU_LEVEL2_REGION_Y
#define MENU_LEVEL3_REGION_W		      MENU_LEVEL2_REGION_W
#define MENU_LEVEL3_REGION_H		      MENU_LEVEL2_REGION_H

//µÚÒ»¼¶²Ëµ¥ÖÐ£¬µ±Ç°Ñ¡ÖÐµÄ²Ëµ¥Ïî£¬ÐèÒª¸ßÁÁÏÔÊ¾µÄÇøÓò
#define MENU_LEVEL1_HIGHLIGHT_START_X     MENU_XS+4
#define MENU_LEVEL1_HIGHLIGHT_START_Y	  MENU_YS+MENU_HEAD_HEIGHT+3  //+3£¬ÊÇÓÉÓÚÐÐ¸ß¶È40£¬µ«ÊÇ¸ßÁÁµÄ¸ß¶ÈÊÇ34£¬²»ÐèÒªÈ«²¿Çå³ý
#define MENU_LEVEL1_HIGHLIGHT_W		      286
#define MENU_LEVEL1_HIGHLIGHT_H		      34

//µÚ¶þ¼¶²Ëµ¥ÖÐ£¬µ±Ç°Ñ¡ÖÐµÄ²Ëµ¥Ïî£¬ÐèÒª¸ßÁÁÏÔÊ¾µÄÇøÓò
#define MENU_LEVEL2_HIGHLIGHT_START_X     MENU_LEVEL2_REGION_X+4
#define MENU_LEVEL2_HIGHLIGHT_START_Y	  MENU_LEVEL1_HIGHLIGHT_START_Y  //+3£¬ÊÇÓÉÓÚÐÐ¸ß¶È40£¬µ«ÊÇ¸ßÁÁµÄ¸ß¶ÈÊÇ34£¬²»ÐèÒªÈ«²¿Çå³ý
#define MENU_LEVEL2_HIGHLIGHT_W		      236
#define MENU_LEVEL2_HIGHLIGHT_H		      34

//µÚÈý¼¶²Ëµ¥ÖÐ£¬µ±Ç°Ñ¡ÖÐµÄ²Ëµ¥Ïî£¬ÐèÒª¸ßÁÁÏÔÊ¾µÄÇøÓò
#define MENU_LEVEL3_HIGHLIGHT_START_X     MENU_LEVEL2_HIGHLIGHT_START_X
#define MENU_LEVEL3_HIGHLIGHT_START_Y	  MENU_LEVEL2_HIGHLIGHT_START_Y  //+3£¬ÊÇÓÉÓÚÐÐ¸ß¶È40£¬µ«ÊÇ¸ßÁÁµÄ¸ß¶ÈÊÇ34£¬²»ÐèÒªÈ«²¿Çå³ý
#define MENU_LEVEL3_HIGHLIGHT_W		      MENU_LEVEL2_HIGHLIGHT_W
#define MENU_LEVEL3_HIGHLIGHT_H		      MENU_LEVEL2_HIGHLIGHT_H

//æ é¢æ çç¸å³åé
#define MENU_TITLE_PIC_WIDTH  44                                                  //±êÌâÀ¸Í¼Æ¬µÄ¿í¶È
#define MENU_TITLE_STR_XS     (MENU_TITLE_PIC_WIDTH*2+MENU_XS)                    //±êÌâÀ¸ÎÄ×ÖÆðÊ¼X£¬Òª¼ÓÉÏÁ½¸ö±êÌâÍ¼Æ¬µÄÖµ
#define MENU_TAIL_PAGE_OK_W   40                                                  //×´Ì¬À¸£¬ÏÔÊ¾µ±Ç°Ò³Êý»òÕßOK±êÖ¾µÄ¿í¶È
#define MENU_TAIL_PAGE_OK_X   (MENU_XS+MENU_W-MENU_TAIL_PAGE_OK_W)                //×´Ì¬À¸£¬ÏÔÊ¾µ±Ç°Ò³Êý»òÕßOK±êÖ¾µÄxÖµ
#define MENU_STATUS_BAR_Y     (MENU_YS+MENU_HEAD_HEIGHT+MENU_ITEM_HEIGHT*NUM_PAGE)//×´Ì¬À¸µÄÆðÊ¼YÖµ
#define MENU_STATUS_BAR_H     (MENU_H-MENU_HEAD_HEIGHT-MENU_ITEM_HEIGHT*NUM_PAGE)//×´Ì¬À¸µÄ¸ß¶È

#if (MENU_WIDTH == 320)

#define RES_ATRRIBUTE_1FORMATE_BMP      			0x0
#define RES_ATRRIBUTE_2LANGUAGE_BMP     			0x1
#define RES_ATRRIBUTE_3AUTO_POWEROFF_BMP			0x2
#define RES_ATRRIBUTE_4SCREEN_SAVE_BMP  			0x3
#define RES_ATRRIBUTE_5DEFAULT_BMP      			0x4
#define RES_ATRRIBUTE_6LIGHT_FREQ_BMP   			0x5
#define RES_ATRRIBUTE_7DATE_BMP         			0x6
#define RES_ATRRIBUTE_8VIDEO_ROTATE_BMP 			0x7
#define RES_ATRRIBUTE_9NIGHT_VISION_BMP 			0x8
#define RES_ATRRIBUTE_ATV_BMP           			0x9
#define RES_ATRRIBUTE_BVER_BMP          			0xa
#define RES_ATRRIBUTE_CSETTING_BMP      			0xb


#define RES_BROWSE_1DELETE_BMP          			0xc
#define RES_BROWSE_2PROTECT_BMP         			0xd
#define RES_BROWSE_3PLAYBACK_BMP        			0xe


#define RES_MAIN_DOWN_BMP               			0xf
#define RES_MAIN_MENUBACK_BMP           			0x10
#define RES_MAIN_OK_BMP                 			0x11
#define RES_MAIN_UP_BMP                 			0x12


#define RES_PHOTO_1MP_BMP               			0x13
#define RES_PHOTO_2FAST_VIEW_BMP        			0x14
#define RES_PHOTO_3DTAE_TAG_BMP         			0x15
#define RES_PHOTO_4PHOTO_BMP            			0x16


#define RES_VIDEO_1MP_BMP               			0x17
#define RES_VIDEO_2DATE_TAG_BMP         			0x18
#define RES_VIDEO_3MOTION_DECTION_BMP   			0x19
#define RES_VIDEO_4LOOP_BMP             			0x1a
#define RES_VIDEO_5VOICE_BMP            			0x1b
#define RES_VIDEO_6G_SENSOR_BMP         			0x1c
#define RES_VIDEO_7VIDEO_BMP            			0x1d

#elif(MENU_WIDTH == 220)

#define RES_ATRRIBUTE_1FORMATE_BMP      			0x0
#define RES_ATRRIBUTE_2LANGUAGE_BMP     			0x1
#define RES_ATRRIBUTE_3AUTO_POWEROFF_BMP			0x2
#define RES_ATRRIBUTE_4SCREEN_SAVE_BMP  			0x3
#define RES_ATRRIBUTE_5DEFAULT_BMP      			0x4
#define RES_ATRRIBUTE_6LIGHT_FREQ_BMP   			0x5
#define RES_ATRRIBUTE_7DATE_BMP         			0x6
#define RES_ATRRIBUTE_8VIDEO_ROTATE_BMP 			0x7
#define RES_ATRRIBUTE_9NIGHT_VISION_BMP 			0x8
#define RES_ATRRIBUTE_ATV_BMP           			0x9
#define RES_ATRRIBUTE_BVER_BMP          			0xa
#define RES_ATRRIBUTE_CSETTING_BMP      			0xb


#define RES_BROWSE_1DELETE_BMP          			0xc
#define RES_BROWSE_2PROTECT_BMP         			0xd
#define RES_BROWSE_3PLAYBACK_BMP        			0xe


#define RES_MAIN_DOWN_BMP               			0xf
#define RES_MAIN_MENUBACK_BMP           			0x10
#define RES_MAIN_OK_BMP                 			0x11
#define RES_MAIN_UP_BMP                 			0x12


#define RES_PHOTO_1MP_BMP               			0x13
#define RES_PHOTO_2FAST_VIEW_BMP        			0x14
#define RES_PHOTO_3DTAE_TAG_BMP         			0x15
#define RES_PHOTO_4PHOTO_BMP            			0x16


#define RES_VIDEO_1MP_BMP               			0x17
#define RES_VIDEO_2DATE_TAG_BMP         			0x18
#define RES_VIDEO_3MOTION_DECTION_BMP   			0x19
#define RES_VIDEO_4LOOP_BMP             			0x1a
#define RES_VIDEO_5VOICE_BMP            			0x1b
#define RES_VIDEO_6G_SENSOR_BMP         			0x1c
#define RES_VIDEO_7VIDEO_BMP            			0x1d

#elif(MENU_WIDTH == 160)

#define RES_ATRRIBUTE_10SETTING_BMP     			0x0
#define RES_ATRRIBUTE_1DATE_BMP         			0x2
#define RES_ATRRIBUTE_2AUTO_POWEROFF_BMP			0x3
#define RES_ATRRIBUTE_3LANGUAGE_BMP     			0x4
#define RES_ATRRIBUTE_4LIGHT_FREQ_BMP   			0x5
#define RES_ATRRIBUTE_5SCREEN_SAVE_BMP  			0x6
#define RES_ATRRIBUTE_6VIDEO_ROTATE_BMP 			0x7
#define RES_ATRRIBUTE_7FORMATE_BMP      			0x8
#define RES_ATRRIBUTE_8DEFAULT_BMP      			0x9
#define RES_ATRRIBUTE_9VER_BMP          			0xa

#define RES_BROWSE_1DELETE_BMP          			0xb
#define RES_BROWSE_2PROTECT_BMP         			0xc
#define RES_BROWSE_3PLAYBACK_BMP        			0xd

#define RES_MAIN_DOWN_BMP               			0x10
#define RES_MAIN_MENUBACK_BMP           			0xe
#define RES_MAIN_OK_BMP                 			0xf
#define RES_MAIN_UP_BMP                 			0x11

#define RES_PHOTO_1MP_BMP               			0x12
#define RES_PHOTO_2FAST_VIEW_BMP        			0x13
#define RES_PHOTO_3DTAE_TAG_BMP         			0x1b
#define RES_PHOTO_4PHOTO_BMP            			0x15


#define RES_VIDEO_1MP_BMP               			0x12
#define RES_VIDEO_2LOOP_BMP             			0x18
#define RES_VIDEO_3MOTION_DECTION_BMP   			0x19
#define RES_VIDEO_4VOICE_BMP            			0x1a
#define RES_VIDEO_5DATE_TAG_BMP         			0x1b
#define RES_VIDEO_6NIGHT_VISION_BMP     			0x1c
#define RES_VIDEO_7VIDEO_BMP            			0x1d

#endif


//========osd define come from osd resouce tools ========
#define       OSD_1280x1024   	0
#define       OSD_BAT_0       	1
#define       OSD_BAT_1       	2
#define       OSD_BAT_2       	3
#define       OSD_BAT_3       	4
#define       OSD_CHARGE      	5
#define       OSD_COLON       	6
#define       OSD_CROSS       	7
#define       OSD_DOWN_TRIANGLE	8
#define       OSD_LOCK        	9
#define       OSD_LOCK_MODE   	10
#define       OSD_LOOP_VIDEO_AO3	11
#define       OSD_LOOP_VIDEO_BO5	12
#define       OSD_LOOP_VIDEO_C10	13
#define       OSD_MENU_aMenuStatus	14
#define       OSD_MENU_ATTRIBUTE	15
#define       OSD_MENU_BROWSE 	16
#define       OSD_MENU_Menu1B1	17
#define       OSD_MENU_Menu2B 	18
#define       OSD_MENU_MenuItem1S	19
#define       OSD_MENU_MenuItem2S	20
#define       OSD_MENU_PHOTO  	21
#define       OSD_MENU_VIDEO  	22
#define       OSD_MOTION_DECTION_START	23
#define       OSD_MOTION_DECTION_STOP	24
#define       OSD_MUTE        	25
#define       OSD_NIGHT       	26
#define       OSD_NORMAL      	27
#define       OSD_NO_SD_L     	28
#define       OSD_NO_SD_S     	29
#define       OSD_PAUSE       	30
#define       OSD_PHOTO       	31
#define       OSD_PLAY        	32
#define       OSD_RECORD      	33
#define       OSD_RECORDING   	34
#define       OSD_RESA2560x1440	35
#define       OSD_RESB1920x1080	36
#define       OSD_RESC1280x720	37
#define       OSD_RESDVGA     	38
#define       OSD_RESEQVGA    	39
#define       OSD_RESF720x480 	40
#define       OSD_SD_OFFLINE  	41
#define       OSD_SD_ONLINE   	42
#define       OSD_TAKE_PIC    	43
#define       OSD_TASK_PLAY   	44
#define       OSD_UP_TRIANGLE 	45
#define       SD_OFFLINE      	46
#define       X1              	47
#define       X2              	48
#define       X4              	49


#define VIDEO_TITLE 	1
#define VIDEO_RECORDING 2
#define RECORD_VOICE 	5
#define MOVE_DETECT   	6
#define ZOOM_NUM_Y		2

#define BAT_VOL			1
#define RESOLUTION_X	4
#define RESOLUTION_Y	1
#define FILE_NUM		3

#define MAX_ENLAGER_FACTOR		2

#if (MENU_WIDTH == 320)
#define TASK_OSD_XS	   5//10
#define TASK_OSD_YS	   5
#define TASK_ICON_XSPACE		32
#define TASK_ICON_YSPACE		32//16
#define TASK_ICON_WIDTH			32
#define TASK_ICON_HEIGHT		32
#define NUM_WIDTH    11
#define NUM_HEIGHT   16
#define BAT_ICON_XS				(MENU_WIDTH-MENU_XS-BAT_VOL*TASK_ICON_XSPACE)
#define BAT_ICON_YS				(MENU_HEIGHT-MENU_YS-TASK_ICON_YSPACE)
#define ZOOM_NUM_W				20
#define ZOOM_NUM_H				12
#define STR_DISPLAY_YS			110
#define ICON_INTERVAL_SPACE     8
#elif(MENU_WIDTH == 220)
#define TASK_OSD_XS	   5//10
#define TASK_OSD_YS	   5
#define TASK_ICON_XSPACE		32
#define TASK_ICON_YSPACE		32//16
#define TASK_ICON_WIDTH			32
#define TASK_ICON_HEIGHT		32
#define NUM_WIDTH    11
#define NUM_HEIGHT   16
#define BAT_ICON_XS				(MENU_WIDTH-MENU_XS-BAT_VOL*TASK_ICON_XSPACE)
#define BAT_ICON_YS				(MENU_HEIGHT-MENU_YS-TASK_ICON_YSPACE)
#define ZOOM_NUM_W				20
#define ZOOM_NUM_H				12
#define STR_DISPLAY_YS			110
#define ICON_INTERVAL_SPACE     8
#elif(MENU_WIDTH == 160)
#define TASK_OSD_XS	   3
#define TASK_OSD_YS	   1
#define TASK_ICON_XSPACE		18
#define TASK_ICON_YSPACE		10
#define TASK_ICON_WIDTH			16
#define TASK_ICON_HEIGHT		16
#define NUM_WIDTH      4
#define NUM_HEIGHT     8
#define BAT_ICON_XS				(MENU_WIDTH-TASK_OSD_XS-BAT_VOL*TASK_ICON_XSPACE)
#define BAT_ICON_YS				(MENU_HEIGHT-TASK_OSD_YS-8)
#define ZOOM_NUM_W				16
#define ZOOM_NUM_H				10
#define STR_DISPLAY_YS			50
#define ICON_INTERVAL_SPACE     8
#endif

//OSD ICON SYS TIME
#define SYS_TIME_XS	   	(TASK_OSD_XS+TASK_ICON_WIDTH)//(TASK_OSD_XS+TASK_ICON_WIDTH*2)
#define SYS_TIME_YS	  	(MENU_HEIGHT-NUM_HEIGHT-TASK_OSD_YS)

//OSD ICON REC TIME
#define REC_TIME_XS	  	(MENU_WIDTH -NUM_WIDTH*8 -TASK_OSD_XS)//(MENU_WIDTH -NUM_WIDTH*8 -TASK_OSD_XS -VIDEO_RECORDING*TASK_ICON_XSPACE)
#define REC_TIME_YS	  	(TASK_OSD_YS+(MENU_ICON_HEIGHT-NUM_HEIGHT)/2)

#define OSD_NO_SD_L_XS	(TASK_OSD_XS+TASK_ICON_WIDTH*2)
#define OSD_NO_SD_L_YS	(TASK_OSD_YS+TASK_ICON_HEIGHT*3)
#define OSD_NO_SD_L_W	176
#define OSD_NO_SD_L_H    48

#define OSD_NO_SD_S_XS	(TASK_OSD_XS+TASK_ICON_WIDTH*3+ICON_INTERVAL_SPACE)
#define OSD_NO_SD_S_YS	(TASK_OSD_YS+TASK_ICON_HEIGHT*3)
#define OSD_NO_SD_S_W	96
#define OSD_NO_SD_S_H    48

#define SETTING_YEAR   0
#define SETTING_MONTH  1
#define SETTING_DAY    2
#define SETTING_HOUR   3
#define SETTING_MIN    4

typedef enum _ACT_NUM_LIST
{
	ANL_VIDEO_MP		   	   ,
	ANL_LOOP_VIDEO		  	   ,
	ANL_MOTION_DECTECTION  	   ,
	ANL_VIDEO_VOICE			   ,
	ANL_VIDEO_DATE_TAG	       ,
	ANL_NIGHT_LIGHT				,
	ANL_GSENSOR_SENS			,
	ANL_PHOTO_MP	      	   ,
	ANL_FAST_VIEW		   	   ,
	ANL_PHOTO_DATE_TAG			,
	ANL_AUTO_POWER_OFF		   ,
	ANL_LANGUAGE		   	   ,
//	ANL_LIGHT_FREQ	       	   ,
	ANL_SCREEN_SAVE            ,
	ANL_VIDEO_ROTATE		   ,
	ANL_TV	   		   			,
	ANL_BEEP_SOUND		   		,
	ANL_FORMATE		 	   	   ,
	ANL_DEFAULT                ,
	ANL_BROWSE_DELETE_THIS     ,
	ANL_BROWSE_DELETE_ALL	   ,
	ANL_BROWSE_LOCK_THIS     ,
	ANL_BROWSE_UNLOCK_THIS	   ,
	ANL_BROWSE_LOCK_ALL     ,
	ANL_BROWSE_UNLOCK_ALL	   ,
	ANL_DATE_AJUST			   ,
	ANL_VERSION		   		   ,
}ACT_NUM_LIST;

typedef enum _menu_act_type
{
	MENU_ACT_NEXT,				// Õ¹¿ªÏÂÒ»¼¶²Ëµ¥
	MENU_ACT_PREV,				// ·µ»ØÉÏÒ»¼¶²Ëµ¥
	MENU_ACT_FUNC,				// Ö´ÐÐÏìÓ¦º¯Êý
	MENU_ACT_EXIT,				// ÍË³öËùÓÐ²Ëµ¥
} MENU_ACT_TYPE;

typedef struct _ACT_LIST
{
	ACT_NUM_LIST act_num;
	void (*pActFunc)(u8);
}ACT_LIST;

typedef enum _menu_type
{
	MENU_IDLE,
	MENU_VIDEO,
	MENU_PHOTO,
	MENU_BROWSE,
	MENU_ATTRIBUTE
} MENU_TYPE;

typedef struct _MENU_LIST
{
	MENU_TYPE menu_type;
	MENU_TYPE next_menu_type;
}MENU_LIST;

typedef struct _MENU_TO_PAGE
{
	MENU_TYPE menu_type;
	struct _menu_page *p_menu_page;
}MENU_TO_PAGE;

typedef struct _item_string
{
	u8 const *pLanguage[MAX_LANGUAGE+1];
} ITEM_STRING;

typedef struct _menu_item
{
	u8 type;								// ²Ëµ¥ÀàÐÍ
	u8 align;
	u8 act_num;								// ²Ëµ¥¶ÔÓ¦ÏìÓ¦¹¦ÄÜº¯ÊýµÄ±àºÅ
	u8 icon_addr;							// Í¼±ê×ÊÔ´µØÖ·?
	ITEM_STRING *string_addr;						// ×Ö·û´®×ÊÔ´µØÖ·?
	struct _menu_page  *p_next_menu_page;			// Ö¸ÏòÏÂÒ»¼¶²Ëµ¥µÄÈë¿Ú
} MENU_ITEM;

typedef struct _menu_page
{
	u8  total;				// ²Ëµ¥Ïî×ÜÊý
	u8 	m_title;			// ÊÇ·ñÓÐ²Ëµ¥Í·
	u8  m_roll;				// ¹ö¶¯²Ëµ¥»¹ÊÇ·­Ò³²Ëµ¥
	MENU_ITEM  *p_menu_item;		// Ö¸Ïò²Ëµ¥ÏîÁÐ±í
	struct _menu_page *p_prev_menu_page;	// Ö¸ÏòÉÏÒ»¼¶²Ëµ¥µÄÈë¿Ú
} MENU_PAGE;

//use another osd layer to highlight the chose item
typedef struct _menu_background_highlight
{
	u8  icon;
	u8  backcolor;
	u16 xs;
	u16 ys;
	u16 w;
	u16 h;
}MENU_BACKGROUND_HIGHLIGHT;

typedef struct _menu_size
{
	u16 xs;
	u16 ys;
	u16 w;
	u16 h;
}MENU_SIZE;

//ÉÏÏÂ¼¶²Ëµ¥ÇÐ»»µÄÊ±ºò£¬ÖØÐÂË¢²Ëµ¥ÇøÓò»òÕß·½¿ò
typedef struct _menu_region_size
{
	u8  icon;           //ÓÐµÄÊ±ºòÊÇË¢Í¼Æ¬
	u8  backcolor;      //ÓÐµÄÊ±ºòÊÇÕû¸öÇøÓòË¢Ò»ÖÖÑÕÉ«
	u16 xs;
	u16 ys;
	u16 w;
	u16 h;
}MENU_REGION_SIZE;

typedef struct _menu_mgr
{
	MENU_PAGE *mpage;
	u8 index;						// µ±Ç°²Ëµ¥Ñ¡ÖÐµÄÏî(¾ø¶ÔÖµ£¬²»ÊÇÏà¶ÔÖµ)
	u8 page_index;					// µ±Ç°²Ëµ¥ËùÔÚÒ³µÄµÚÒ»Ïî
} MENU_MPAGE;

typedef struct _menu_group
{
	MENU_MPAGE mgr_page;			// Ò³¹ÜÀíÆ÷
	MENU_MPAGE mgr_group[4];		// ×é¹ÜÀíÆ÷
	u8  menu_mode;
	MENU_TYPE menu_type;		// Ö¸Ïò²Ëµ¥ÏîÁÐ±í
	u8  level;
	u8  display_update_flag;
	u8  lcd_update_enable;
	OSDInf *p_menu_inf;
	OSDInf *p_menuf_inf;
	u8 back_color[3];				// ±³¾°É« [0]£º²Ëµ¥Ñ¡ÖÐ  [1]£ºµÚÒ»¼¶²Ëµ¥²Ëµ¥Î´Ñ¡ÖÐ [2]£ºÆäËû¼¶²Ëµ¥²Ëµ¥Î´Ñ¡ÖÐ
	u8 fore_color[3];				// Ç°¾°É« [0]£º²Ëµ¥Ñ¡ÖÐ  [1]£ºµÚÒ»¼¶²Ëµ¥²Ëµ¥Î´Ñ¡ÖÐ [2]£ºÆäËû¼¶²Ëµ¥²Ëµ¥Î´Ñ¡ÖÐ
} MENU_MGROUP;

typedef struct _TIME_SETTING_DISPLAY
{
	OSDInf *pOSDInf;
	u8 timepString[5];
	u16 startx;
	u16 starty;
	u16 w;
	u16 h;
	u8 forecolor; 
	u8 backcolor;
	u8 align;
} TIME_SETTING_DISPLAY;


typedef void (*user_set)(u8);
extern MENU_MGROUP menu_mgroup;
extern MENU_TO_PAGE cur_menu;
extern MENU_PAGE const video_menu;
extern MENU_PAGE const photo_menu;
extern MENU_PAGE const attribute_menu;
extern MENU_PAGE const browse_menu;

extern MENU_PAGE const power_off_menu;
extern MENU_PAGE const language_menu;
extern MENU_PAGE const lightsource_menu;
extern MENU_PAGE const sleep_time_menu;
extern MENU_PAGE const photo_rotate_menu;
extern MENU_PAGE const formate_menu;
extern MENU_PAGE const default_menu;
extern MENU_PAGE const version_menu;

extern MENU_PAGE const video_resolution_menu;
extern MENU_PAGE const video_loop_menu;
extern MENU_PAGE const motion_detection_menu;
extern MENU_PAGE const video_vioce_menu;
extern MENU_PAGE const video_date_menu;
extern MENU_PAGE const video_night_menu;

extern MENU_PAGE const photo_resolution_menu;
extern MENU_PAGE const photo_slide_menu;
extern MENU_PAGE const photo_date_menu;

extern MENU_PAGE const browse_delete_menu;
extern MENU_PAGE const browse_protect_menu;
//extern MENU_SIZE const menu_layer_size[];
extern MENU_BACKGROUND_HIGHLIGHT const menu_level_region[];
extern MENU_BACKGROUND_HIGHLIGHT const menu_highlight[];
extern MENU_BACKGROUND_HIGHLIGHT const menu_level_clear_region[];
extern ACT_LIST  const act_list[];
extern MENU_LIST const menu_list[];
extern const MENU_TO_PAGE menu2page[];
extern const u8  menu_frame_background[];
extern const u8  menu_item_background[];

//=====show tips====
extern char const *group_no_card[];
extern char const *group_format_sd_ing[];
extern char const *group_format_sd_succeed[];
extern char const *group_format_sd_fail[];
extern char const *group_low_power[];
//lock
extern char const *group_file_lock[];
//delete
extern char const *group_file_delete[];
//======
extern const ITEM_STRING attribute_page_string6;		//data set 

#endif
