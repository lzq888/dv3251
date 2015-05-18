/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : config_ax3251_k6000.h
* Author             : dingping_chen
* Version            : V0225a
* Date               : 10/22/2014	;mm/dd/yyyy
* Description        : include file
***************************************************************************/
#ifndef _CONFIG_AX3251_K6000_H_
#define _CONFIG_AX3251_K6000_H_

#define VERSION_NUM  	"V1.3.6"

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
#define LED_REUSE_ADKEY	1

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
#define DEFAULT_TVOUT_EN			1							// 0: close TVOUT output, 1: open TVOUT output
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
 * Module    : Sensor 配置
 *****************************************************************************/ 
#define SENSOR_RESET()  
#define SENSOR_NRESET()   
#define SEN_USE    	 SEN_NT99141
#define G_SEN_USE    G_SEN_GMA301A

//#define I2C_MAP		I2C_MAP2		//I2C select PA7(SCL),PA8(SDA) 
#define I2C_MAP		I2C_MAP_SW2		//I2C select PA9(SCL),PA8(SDA) 

#if (I2C_MAP==I2C_MAP_SW2)
/*
	#define I2C_SCL_PORT_DATA			(REG32(PA))
	#define I2C_SCL_PORT_PU				(REG32(PA_PU0))
	#define I2C_SCL_PORT_PD				(REG32(PA_PD0))
	#define I2C_SCL_PORT_DIR			(REG32(PA_DIR))
	#define I2C_SCL_PORT_BIT			8//9
*/

	#define I2C_SCL_PORT_DATA			(REG32(PG))
	#define I2C_SCL_PORT_PU				(REG32(PG_PU0))
	#define I2C_SCL_PORT_PD				(REG32(PG_PD0))
	#define I2C_SCL_PORT_DIR			(REG32(PG_DIR))
	#define I2C_SCL_PORT_BIT			12

	#define I2C_SDA_PORT_DATA			(REG32(PA))
	#define I2C_SDA_PORT_PU				(REG32(PA_PU0))
	#define I2C_SDA_PORT_PD				(REG32(PA_PD0))
	#define I2C_SDA_PORT_DIR			(REG32(PA_DIR))
	#define I2C_SDA_PORT_BIT			9//8
	
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

/*****************************************************************************
 * Module    : 按键配置
 *****************************************************************************/
#define IO_KEY_TYPE				1
#define AD_KEY_TYPE				2
#define KEY_TYPE	AD_KEY_TYPE

//ADKEY键值表
#define KEY_NUM                        6
/*
//===v1.1=====
#define KEY_ADC                        567,654,738,820,878,946,0xffff
#define KEY_VAL                        T_KEY_DOWN,T_KEY_PLAY,T_KEY_MODE,T_KEY_MENU,T_KEY_UP,T_KEY_LOCK,NO_KEY
*/

//====v1.3=====
#define KEY_ADC                        442,658,744,830,902,982,0xffff//567,654,738,820,878,946,0xffff
#define KEY_VAL                        T_KEY_LOCK,T_KEY_PLAY,T_KEY_MODE,T_KEY_MENU,T_KEY_UP,T_KEY_DOWN,NO_KEY

/*****************************************************************************
 * Module    : 软开关 IO配置
 *****************************************************************************/
#define SOFT_POWER_ON_OFF			1
#if (SOFT_POWER_ON_OFF==1)
	#define POWERKEY_PORT_DATA			(REG32(PA))
	#define POWERKEY_PORT_PU			(REG32(PA_PU0))
	#define POWERKEY_PORT_PD			(REG32(PA_PD0))
	#define POWERKEY_PORT_DIR			(REG32(PA_DIR))
	#define POWERKEY_PORT_BIT			6 
	#define POWERKEY_STATUS()			((POWERKEY_PORT_DATA & (BIT(POWERKEY_PORT_BIT)))>>POWERKEY_PORT_BIT)

	#define POWERON_PORT_DATA			(REG32(PG))
	#define POWERON_PORT_PU				(REG32(PG_PU0))
	#define POWERON_PORT_PD				(REG32(PG_PD0))
	#define POWERON_PORT_DIR			(REG32(PG_DIR))
	#define POWERON_PORT_BIT			7 
	#define POWERON_ENABLE()			(POWERON_PORT_DIR &= ~(BIT(POWERON_PORT_BIT)));(POWERON_PORT_DATA |= (BIT(POWERON_PORT_BIT))) 
	#define POWERON_DISABLE()			(POWERON_PORT_DIR &= ~(BIT(POWERON_PORT_BIT)));(POWERON_PORT_DATA &= ~(BIT(POWERON_PORT_BIT)))
#endif

/*****************************************************************************
 * Module    : DCIN IO配置
 *****************************************************************************/
#define DCIN_PORT_DATA			(REG32(PG))
#define DCIN_PORT_PU			(REG32(PG_PU0))
#define DCIN_PORT_PD			(REG32(PG_PD0))
#define DCIN_PORT_DIR			(REG32(PG_DIR))
#define DCIN_PORT_BIT			12

/*****************************************************************************
 * Module    : LED IO配置
 *****************************************************************************/
#define LED_RED_BLINK                  	1   //是否使用红灯闪烁
#define LED_GREEN_BLINK                 0   //是否使用绿灯闪烁


//LED_RED
#define LED_RED_INIT()		CLRB(REG32(PA_DIR), 5)
#define LED_RED_ON()      	SETB(REG32(PA), 5)
#define LED_RED_OFF()     	CLRB(REG32(PA), 5)
#define LED_RED_TWK()     	XRLB(REG32(PA), 5)

//LED_GREEN
#define LED_GREEN_INIT()		
#define LED_GREEN_ON()      
#define LED_GREEN_OFF()     
#define LED_GREEN_TWK()     

/*****************************************************************************
 * Module    : LCD配置
 *****************************************************************************/
//LCD型号选择
#define  LCD_USE      LCD_ILI8961

#if ((LCD_3029 == LCD_USE)||(LCD_3029C == LCD_USE)||(LCD_61505 == LCD_USE)||(LCD_61505W == LCD_USE)||(LCD_HX8367 == LCD_USE)||(LCD_7781 == LCD_USE)||(LCD_HX8312== LCD_USE)||(LCD_9303== LCD_USE)||(LCD_9312== LCD_USE)||(LCD_ILI9225== LCD_USE))	
//mcu 
#define OPEN_NIGHT_LIGHT()   {CLRB(REG32(PF_DIR), 3);SETB(REG32(PF), 3);}	
#define CLOSE_NIGHT_LIGHT()  {CLRB(REG32(PF_DIR), 3);CLRB(REG32(PF), 3);}
#else		
//rgb
#define OPEN_NIGHT_LIGHT()   {CLRB(REG32(PF_DIR), 1);SETB(REG32(PF), 1);}	
#define CLOSE_NIGHT_LIGHT()  {CLRB(REG32(PF_DIR), 1);CLRB(REG32(PF), 1);}
#endif

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
	#define LCDBKL_OUTPUT()		{CLRB(LCDBKL_PORT_DIR,LCDBKL_PORT_BIT);SETB(REG32(PG_DIR),6);}	// for saveful , set PG6 input (because they are together)
	#define LCDBKL_OPEN()		SETB(LCDBKL_PORT_DATA,LCDBKL_PORT_BIT)
	#define LCDBKL_CLOSE()		CLRB(LCDBKL_PORT_DATA,LCDBKL_PORT_BIT)

	//LCD 3.3V电源控制
	#define LCDPWEN_PORT_DATA 	
	#define LCDPWEN_PORT_PU		
	#define LCDPWEN_PORT_PD		
	#define LCDPWEN_PORT_DIR	
	#define LCDPWEN_PORT_BIT
	#define LCDPWEN_OUTPUT()	
	#define LCDPWEN_ENABLE()	
	#define LCDPWEN_DISABLE()	

	//LCD信号引脚配置
	//见相关LCD配置头文件
#endif

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
#define SD_DETECT_PORT_BIT		7//9

/*****************************************************************************
 * Module    : Gsen INT检测引脚配置
 *****************************************************************************/
#define GSEN_DETECT_PORT_DATA		(REG32(PG))
#define GSEN_DETECT_PORT_PU			(REG32(PG_PU0))
#define GSEN_DETECT_PORT_PD			(REG32(PG_PD0))
#define GSEN_DETECT_PORT_DIR		(REG32(PG_DIR))
#define GSEN_DETECT_PORT_IE			(REG32(PG_IE))
#define GSEN_DETECT_PORT_BIT		4

#endif

