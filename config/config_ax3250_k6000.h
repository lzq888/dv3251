/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : config_ax3250_k6000.h
* Author             : dingping_chen
* Version            : V0225a
* Date               : 10/22/2014	;mm/dd/yyyy
* Description        : include file
***************************************************************************/
#ifndef _CONFIG_AX3250_K6000_H_
#define _CONFIG_AX3250_K6000_H_

#define VERSION_NUM  	"V1.3.4"

/*****************************************************************************
 * Module    : 功能配置
 *****************************************************************************/
#define TASK_RECORD_VIDEO_EN	1
#define TASK_PHOTO_EN			1
#define TASK_PLAY_EN			1
#define TASK_USB_DEVICE_EN		1
#define TASK_POWER_OFF_EN		1

/*****************************************************************************
 * Module    : 系统配置
 *****************************************************************************/
#define HUNTER_IC		HUNTER_128PIN
#define DEBUG_EN		1								//0 : is release    1: is debug
#define LED_REUSE_ADKEY	0

/***************************************************************************
*language define
****************************************************************************/
#define LANGUAGE_CNS		    0						//chinese simple		
#define LANGUAGE_CNT		    1						//chinese taiwan		
#define LANGUAGE_EN		    2						//English				
#define LANGUAGE_RU		    3						//Russian				
#define LANGUAGE_KO		    4						//Korean				
#define LANGUAGE_JA		    5						//Japanese			
#define LANGUAGE_SPA		    6						//Spanish				
#define LANGUAGE_TUR		    7						//Turkey				
#define LANGUAGE_HEB		    8						//Hebrew				
#define LANGUAGE_THA		    9						//Thai				
#define LANGUAGE_PO		    10					//Polish				
#define MAX_LANGUAGE               10

/****************************************************************************
*dc dv setting
****************************************************************************/
#define DEFAULT_LANGUAGE 		LANGUAGE_CNS	
#define DEFAULT_VIDEO_SIZE 	VIDEO_SIZE_1280_720				// take video size
#define DEFAULT_JPEG_SIZE     	JPEG_SIZE_1280_720				// take photo size
#define DEFAULT_JPEG_TIME_EN 		1							// 0: is close , 1 is open
#define DEFAULT_VIDEO_TIME_EN 		1							// 0: is close , 1 is open
#define DEFAULT_CRC_RECORD		1							// 0: close crc record,  1: open crc record
#define DEFAULT_MOVING_DETECT       0							// 0: close moving detect , 1: open moving detect
#define DEFAULT_TVOUT_EN			0							// 0: close TVOUT output, 1: open TVOUT output
#define DEFAULT_TVOUT_CLK_SELECT	0							// 0: select 32768 , 1: select 12m 
#define SD_INS_RESET	0			//when SD card insert, system will reset or not


/****************************************************************************
*dir file  setting
****************************************************************************/
#define ROOT_DIR_NAME		""
#define WORK_DIR_CNT		1
#define WORK_DIR_NAME		"Record"		
#define WORK_DIR_DC_NAME	0					//when videoes and pictures are in the same directory, this macro should be zero
#define WORK_DIR_DV_NAME	0					//when videoes and pictures are in the same directory, this macro should be zero		
#define FIRMWARE_NAME		"Destbin.bin"		//updata firmware file
#define FILEORDER_NAME		"FilOrder.bin"
/*****************************************************************************
 * Module    : 按键配置
 *****************************************************************************/
#define IO_KEY_TYPE				1
#define AD_KEY_TYPE				2
#define KEY_TYPE	IO_KEY_TYPE

/*****************************************************************************
 * Module    : Sensor 配置
 *****************************************************************************/
#define I2C_MAP		I2C_MAP1		//I2C select PA0(SCL),PA1(SDA) 
#define SENSOR_RESET()      
#define SENSOR_NRESET()   
#define SEN_USE 	SEN_OV9710
#define G_SEN_USE    G_SEN_NULL

/*****************************************************************************
 * Module    : 软开关 IO配置
 *****************************************************************************/
#define SOFT_POWER_ON_OFF			1
#if (SOFT_POWER_ON_OFF==1)
	#define POWERKEY_PORT_DATA			(REG32(PA))
	#define POWERKEY_PORT_PU			(REG32(PA_PU0))
	#define POWERKEY_PORT_PD			(REG32(PA_PD0))
	#define POWERKEY_PORT_DIR			(REG32(PA_DIR))
	#define POWERKEY_PORT_BIT			5 
	#define POWERKEY_STATUS()			((POWERKEY_PORT_DATA & (BIT(POWERKEY_PORT_BIT)))>>POWERKEY_PORT_BIT)
#endif

/*****************************************************************************
 * Module    : DCIN IO配置
 *****************************************************************************/
#define DCIN_PORT_DATA			(REG32(PG))
#define DCIN_PORT_PU			(REG32(PG_PU0))
#define DCIN_PORT_PD			(REG32(PG_PD0))
#define DCIN_PORT_DIR			(REG32(PG_DIR))
#define DCIN_PORT_BIT			10

/*****************************************************************************
 * Module    : LED IO配置
 *****************************************************************************/
#define LED_RED_BLINK                  	1   //是否使用红灯闪烁
#define LED_GREEN_BLINK                 1   //是否使用绿灯闪烁
//夜视灯配置
#define OPEN_NIGHT_LIGHT()   {CLRB(REG32(PG_DIR), 4);SETB(REG32(PG), 4);}			
#define CLOSE_NIGHT_LIGHT()  {CLRB(REG32(PG_DIR), 4);CLRB(REG32(PG), 4);}

//LED_RED
#define LED_RED_INIT()		CLRB(REG32(PF_DIR), 12)
#define LED_RED_ON()      	CLRB(REG32(PF_DIR), 12);SETB(REG32(PF), 12)
#define LED_RED_OFF()     	CLRB(REG32(PF_DIR), 12);CLRB(REG32(PF), 12)
#define LED_RED_TWK()     	CLRB(REG32(PF_DIR), 12);XRLB(REG32(PF), 12)

//LED_GREEN
#define LED_GREEN_INIT()	CLRB(REG32(PG_DIR), 12)
#define LED_GREEN_ON()      CLRB(REG32(PG_DIR), 12);SETB(REG32(PG), 12)
#define LED_GREEN_OFF()     CLRB(REG32(PG_DIR), 12);CLRB(REG32(PG), 12)
#define LED_GREEN_TWK()     CLRB(REG32(PG_DIR), 12);XRLB(REG32(PG), 12)

/*****************************************************************************
 * Module    : LCD配置
 *****************************************************************************/
//LCD型号选择
#define  LCD_USE      LCD_ILI8961	

/*****************************************************************************
 * Module    : MEMU DISPLAY配置
 *****************************************************************************/
//MENU使用选择
#define  MENU_DISPLAY_USE      MENU_DISPLAY_ENABLE	

/*****************************************************************************
 * Module    : OSDICON DISPLAY配置
 *****************************************************************************/
//OSDICON使用选择
#define  OSDICON_DISPLAY_USE   OSDICON_DISPLAY_ENABLE	
//======color setting come from palette pos====
#define ALPHA_0X00_COLOR            0x00			// osd alpha color select from palette pos 

#define OSD_TIME_COLOR  		0xfa			// 0xff0000c0 (abgr)
#define HEAD_STATUS_BACK_COLOR      0xfb
#define CHARACTER_FORE_COLOR        0xFc
#define ALPHA_0X80_COLOR            0xfd
#define SELECT_FORE_COLOR           0xfe
#define SELECT_BACK_COLOR           0xff
#define UNSELECT_LEV1_FORE_COLOR    CHARACTER_FORE_COLOR
#define UNSELECT_LEV1_BACK_COLOR    ALPHA_0X80_COLOR
#define UNSELECT_FORE_COLOR         CHARACTER_FORE_COLOR
#define UNSELECT_BACK_COLOR         ALPHA_0X00_COLOR
//======end color setting come from palette pos====

#if (LCD_USE != LCD_NO_DISPLAY)
	//LCD背光控制
	#define LCDBKL_PORT_DATA	(REG32(PG))
	#define LCDBKL_PORT_PU		(REG32(PG_PU0))
	#define LCDBKL_PORT_PD		(REG32(PG_PD0))
	#define LCDBKL_PORT_DIR		(REG32(PG_DIR))
	#define LCDBKL_PORT_BIT		3
	#define LCDBKL_OUTPUT()		CLRB(LCDBKL_PORT_DIR,LCDBKL_PORT_BIT)
	#define LCDBKL_OPEN()		CLRB(LCDBKL_PORT_DATA,LCDBKL_PORT_BIT)
	#define LCDBKL_CLOSE()		SETB(LCDBKL_PORT_DATA,LCDBKL_PORT_BIT)

	//LCD 3.3V电源控制
	#define LCDPWEN_PORT_DATA 	(REG32(PF))
	#define LCDPWEN_PORT_PU		(REG32(PF_PU0))
	#define LCDPWEN_PORT_PD		(REG32(PF_PD0))
	#define LCDPWEN_PORT_DIR	(REG32(PF_DIR))	
	#define LCDPWEN_PORT_BIT	1
	#define LCDPWEN_OUTPUT()	CLRB(LCDPWEN_PORT_DIR,LCDPWEN_PORT_BIT)
	#define LCDPWEN_ENABLE()	CLRB(LCDPWEN_PORT_DATA,LCDPWEN_PORT_BIT)
	#define LCDPWEN_DISABLE()	SETB(LCDPWEN_PORT_DATA,LCDPWEN_PORT_BIT)

	//LCD信号引脚配置
	//见相关LCD配置头文件
#endif

/*****************************************************************************
 * Module    : 功放Mute配置
 *****************************************************************************/
#define AMP_MUTE_OFF()		CLRB(REG32(PG_DIR), 9);	CLRB(REG32(PG), 9)
#define AMP_MUTE_ON()		CLRB(REG32(PG_DIR), 9);	SETB(REG32(PG), 9)

/*****************************************************************************
 * Module    : SD检测引脚配置
 *****************************************************************************/
#define SD_DETECT_PORT_DATA		(REG32(PA))
#define SD_DETECT_PORT_PU		(REG32(PA_PU0))
#define SD_DETECT_PORT_PD		(REG32(PA_PD0))
#define SD_DETECT_PORT_DIR		(REG32(PA_DIR))
#define SD_DETECT_PORT_IE		(REG32(PA_IE))
#define SD_DETECT_PORT_BIT		9

#endif
