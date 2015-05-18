/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : system_conf.h
* Author             : pengtao_zhang
* Version            : V0731a
* Date               : 07/31/2013
* Description        : system parameter config
***************************************************************************/
#ifndef _SYSTEM_CONF_H_
#define _SYSTEM_CONF_H_

#define PLL_CLK		240000000
#define SYS_CLK		120000000
#define APB_CLK		120000000


//========== lcd select ========
#define  LCD_NO_DISPLAY    0
#define  LCD_TDO24THEB2    1		// rgb 
#define  LCD_ILI8961   	   2		// rgb
#define  LCD_3029   	   	 3		//mcu 
#define  LCD_61505   	   	 4		//mcu
#define  LCD_HX8367   	   5		//mcu
#define  LCD_7781   	   	6		//mcu
#define  LCD_HX8312   	 7		//mcu 18bit(882)
#define  LCD_ILI6480		8		//RGB 4.3'(8bit serial)
#define  LCD_3029C		9		//mcu
#define  LCD_61505W		10		//mcu
#define  LCD_9303		11		//mcu
#define  LCD_9312		12		//mcu
#define  LCD_ILI9225		13		//mcu


//========== SENSOR select ========
#define  SEN_NO_SENSOR   0
#define  SEN_GC0308   	1
#define  SEN_NT99140  	2
#define  SEN_OV9710   	3
#define  SEN_OV7670   	4
#define  SEN_NT99141  	5
#define  SEN_BF3925  	6
#define  SEN_SIV121DS   7
#define  SEN_OV7725	   	8
#define  SEN_NT99240	 9
#define  SEN_SIV100B		 10


//========== G_SENSOR select ========
#define  G_SEN_NULL  		0
#define  G_SEN_DMARD07  	1
#define  G_SEN_GMA301A  	2

#define AVI_HEAD_SIZE		0x200			//important
#define VIDEO_MOTION_DETECT_SUPPORT	 1	//0: not support; 1:support motion video detect. must use SDRAM when use this function

//=========fs setting======
#define MIN_FREESECTOR		0x4000				// 0x4000*512 = 8Mbyte


#define EXTERN_PWR_VDDCORE	1					//adopt external LDO to core voltage

#endif
