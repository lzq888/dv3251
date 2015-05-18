/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : config_ax3251_airborne.h
* Author             : dingping_chen
* Version            : V0225a
* Date               : 10/28/2014	;mm/dd/yyyy
* Description        : include file
***************************************************************************/
#ifndef _CONFIG_AX3251_AIRBORNE_H_
#define _CONFIG_AX3251_AIRBORNE_H_

#define VERSION_NUM  	"V2.0"

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
#define HUNTER_IC		HUNTER_64PIN
#define DEBUG_EN		1							//0 : is release    1: is debug
#define LED_REUSE_ADKEY	0

/*****************************************************************************
 * Module    : 按键配置
 *****************************************************************************/
#define IO_KEY_TYPE				1
#define AD_KEY_TYPE				2
#define KEY_TYPE				IO_KEY_TYPE

#define KEY_NUM					1	//1

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
#define DEFAULT_JPEG_TIME_EN 		0							// 0: is close , 1 is open
#define DEFAULT_VIDEO_TIME_EN 		0							// 0: is close , 1 is open
#define DEFAULT_CRC_RECORD		0							// 0: close crc record,  1: open crc record
#define DEFAULT_MOVING_DETECT       0							// 0: close moving detect , 1: open moving detect
#define DEFAULT_VIDEO_REC_TIME	(40*60)						// second , if > def will stop video rec
#define DEFAULT_TVOUT_EN			1							// 0: close TVOUT output, 1: open TVOUT output
#define DEFAULT_TVOUT_CLK_SELECT	0							// 0: select 32768 , 1: select 12m 
#define RTC_UPDATA_TIME_FROM_TXT_EN		0					//0 : no use txt file set rtc time , 1: use it

#define SD_INS_RESET	1			//when SD card insert, system will reset or not
#define AD_CHECK_BAT_EN			1							// 0: havn't ad check bat,  1 have ad check bat
//VDD 100k  ad_point   100k GND
//VDD    adcval
// 4.2v 	646
// 4.0v    618
// 3.7v	575
// 3.4v    515
// 3.1v    478
// 2.9v    435
// 2.7v    409
// 2.5v    381
// 2.3v    342
#define AD_CHECK_BAT_LOW_VOL		478							//bat 3.1v is low power 

/****************************************************************************
*dir file  setting
****************************************************************************/
#define ROOT_DIR_NAME		""
#define WORK_DIR_CNT		2
#define WORK_DIR_NAME		0					//when videoes and pictures are in the different directory, this macro should be zero	
#define WORK_DIR_DC_NAME	"IMAGE/DCIMG"
#define WORK_DIR_DV_NAME	"VIDEO/DVREC"	
#define FIRMWARE_NAME		"Destbin.bin"		//updata firmware file
#define FILEORDER_NAME		"FilOrder.bin"


/*****************************************************************************
 * Module    : Sensor 配置
 *****************************************************************************/
#define I2C_MAP		I2C_MAP_SW			//select software simulate I2C signal

#define SENSOR_RESET()       REG32(PF) &= ~BIT(5);REG32(PF_DIR) &= ~BIT(5)
#define SENSOR_NRESET()      REG32(PF) |= BIT(5);REG32(PF_DIR) &= ~BIT(5)

#if (I2C_MAP==I2C_MAP_SW)
	#define I2C_SCL_PORT_DATA			(REG32(PG))
	#define I2C_SCL_PORT_PU				(REG32(PG_PU0))
	#define I2C_SCL_PORT_PD				(REG32(PG_PD0))
	#define I2C_SCL_PORT_DIR			(REG32(PG_DIR))
	#define I2C_SCL_PORT_BIT			12
	
	#define I2C_SDA_PORT_DATA			(REG32(PG))
	#define I2C_SDA_PORT_PU				(REG32(PG_PU0))
	#define I2C_SDA_PORT_PD				(REG32(PG_PD0))
	#define I2C_SDA_PORT_DIR			(REG32(PG_DIR))
	#define I2C_SDA_PORT_BIT			4
	
	#define I2C_SCL_SDA_OUT()			I2C_SCL_PORT_DIR &= ~(BIT(I2C_SCL_PORT_BIT));I2C_SDA_PORT_DIR &= ~(BIT(I2C_SDA_PORT_BIT))
	#define I2C_SDA_IN()				I2C_SDA_PORT_PU|=(BIT(I2C_SDA_PORT_BIT));I2C_SDA_PORT_DIR |= (BIT(I2C_SDA_PORT_BIT))
	#define I2C_SDA_OUT()				I2C_SDA_PORT_PU&=~(BIT(I2C_SDA_PORT_BIT));I2C_SDA_PORT_DIR &= ~(BIT(I2C_SDA_PORT_BIT))
	#define I2C_SCL_SDA_HIGH()			I2C_SCL_PORT_DATA|=BIT(I2C_SCL_PORT_BIT);I2C_SDA_PORT_DATA|=BIT(I2C_SDA_PORT_BIT)
	#define I2C_SDA_HIGH()				I2C_SDA_PORT_DATA |= BIT(I2C_SDA_PORT_BIT)
	#define I2C_SDA_LOW()				I2C_SDA_PORT_DATA &= ~(BIT(I2C_SDA_PORT_BIT))
	#define I2C_SCL_HIGH()				I2C_SCL_PORT_DATA|=BIT(I2C_SCL_PORT_BIT)
	#define I2C_SCL_LOW()				I2C_SCL_PORT_DATA &= ~(BIT(I2C_SCL_PORT_BIT))
	#define I2C_SDA_IS_HIGH()			(I2C_SDA_PORT_DATA & BIT(I2C_SDA_PORT_BIT))
#endif	

#define SEN_USE    	SEN_NT99141
#define G_SEN_USE    G_SEN_NULL

/*****************************************************************************
 * Module    : 软开关 IO配置
 *****************************************************************************/
#define SOFT_POWER_ON_OFF			0

/*****************************************************************************
 * Module    : DCIN IO配置
 *****************************************************************************/
#define DCIN_PORT_DATA			(REG32(PF))
#define DCIN_PORT_PU			(REG32(PF_PU0))
#define DCIN_PORT_PD			(REG32(PF_PD0))
#define DCIN_PORT_DIR			(REG32(PF_DIR))
#define DCIN_PORT_BIT			4

/*****************************************************************************
 * Module    : LED IO配置
 *****************************************************************************/
#define LED_RED_BLINK                  	1   //是否使用红灯闪烁
#define LED_GREEN_BLINK                 1   //是否使用绿灯闪烁
//夜视灯配置
#define OPEN_NIGHT_LIGHT()   {CLRB(REG32(PF_DIR), 1);SETB(REG32(PF), 1);}			
#define CLOSE_NIGHT_LIGHT()  {CLRB(REG32(PF_DIR), 1);CLRB(REG32(PF), 1);}

//LED_RED
#if LED_RED_BLINK
#define LED_RED_INIT()		CLRB(REG32(PF_DIR), 1)
#define LED_RED_ON()      	CLRB(REG32(PF_DIR), 1);SETB(REG32(PF), 1)
#define LED_RED_OFF()     	CLRB(REG32(PF_DIR), 1);CLRB(REG32(PF), 1)
#define LED_RED_TWK()     	CLRB(REG32(PF_DIR), 1);XRLB(REG32(PF), 1)
#endif

//LED_GREEN
#if LED_GREEN_BLINK
/*
#define LED_GREEN_INIT()	CLRB(REG32(PF_DIR), 0)
#define LED_GREEN_ON()      CLRB(REG32(PF_DIR), 0);SETB(REG32(PF), 0)
#define LED_GREEN_OFF()     CLRB(REG32(PF_DIR), 0);CLRB(REG32(PF), 0)
#define LED_GREEN_TWK()     CLRB(REG32(PF_DIR), 0);XRLB(REG32(PF), 0)
*/
#define LED_GREEN_INIT()	CLRB(REG32(PF_DIR), 6)
#define LED_GREEN_ON()      CLRB(REG32(PF_DIR), 6);SETB(REG32(PF), 6)
#define LED_GREEN_OFF()     CLRB(REG32(PF_DIR), 6);CLRB(REG32(PF), 6)
#define LED_GREEN_TWK()     CLRB(REG32(PF_DIR), 6);XRLB(REG32(PF), 6)
#endif

/*****************************************************************************
 * Module    : LCD配置
 *****************************************************************************/
//LCD型号选择
#define  LCD_USE      LCD_NO_DISPLAY	

/*****************************************************************************
 * Module    : MEMU DISPLAY配置
 *****************************************************************************/
//MENU使用选择
#define  MENU_DISPLAY_USE      MENU_DISPLAY_DISABLE	

/*****************************************************************************
 * Module    : OSDICON DISPLAY配置
 *****************************************************************************/
//OSDICON使用选择
#define  OSDICON_DISPLAY_USE   OSDICON_DISPLAY_DISABLE	

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

/*****************************************************************************
 * Module    : 功放Mute配置
 *****************************************************************************/
#define AMP_MUTE_OFF()		CLRB(REG32(PG_DIR), 8);	CLRB(REG32(PG), 8)
#define AMP_MUTE_ON()		CLRB(REG32(PG_DIR), 8);	SETB(REG32(PG), 8)


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
