/******************** (C) COPYRIGHT 2014 BUILDWIN ************************
* File Name          : lcd_s2700l0_g.c
* Author             :  
* Version            :  
* Date               : 02/27/2014
* Description        : This file provides all the lcd s2700l0_g SPI_RGB_2.7 firmware functions.
***************************************************************************/
#include "../header/include.h"

#if(LCD_USE == LCD_ILI6480)
//===================================================================
//                                                     	            |
//                      GLOBAL VARIABLE                             |
//                                                                  |
//===================================================================

#define lcd_spi_write_command(x)    {1,x} 
#define lcd_spi_write_parameter(x)  {0,x}
#define lcd_delay_ms(x)             {2,x}
#define table_init_end              {9,0}
#if	(USER_CONFIG==CONFIG_AX3250_K6000)
const struct spirgbmode spi_ili6480 ={
	.red_width = 8,
	.green_width = 8,
	.blue_width = 8,
	.even_rgb_order = ORDER_RGB,
	.odd_rgb_order = ORDER_RGB,
	.shift_width = 8,
	.expand_loc = 0,
	.expand_width = 0,
	.data_en = 0xff,
	.data_inv = 0, 

	.vsync_en = 1, 
	.hsync_en = 1, 
	.de_en = 0,
	.dclk_en = 1,
	.vsync_inv = 1,
	.hsync_inv = 1,
	.de_inv = 0,
	.dclk_inv = 0,

	.datactrl_mode = 1,
	.cs_oen = 0,
	/*.cs_inv = 1,*/
	.cs_pr = 8,

	.spi_id_st = 0,
	.spi_smp_sel = 1,
	.spi_1dw = 1,
	.spi_1dw_dir = 0,
	.spi_9biten = 0,
	.spi_9bit = 0,
	.spi_baud = SYS_CLK/(2*6000000)-1,

	.vsync_inact_at = 0,
	.vsync_up_neg_edge = 0, 
	.hsync_up_neg_edge = 0,
	.de_up_neg_edge = 0,
	
	.clkdiv = 4,
	.hsrp = 1,
	.vsrp = 1,
	.hspw = 2, 
	.vspw = 2,           
	.hbpd = 120/3, 
	.vbpd = 8,                 
	.hozval  = 1440/3,   
	.lineval = 272, 
	.hfpd = 168/3, 
	.vfpd = 8,      

	.rotatemode = ROTATE_NONE,
	.mirror = MIRROR_NONE,
	.yminus16 = 1,
	.interval = 20,
};
#elif ((USER_CONFIG==CONFIG_AX3251_K6000) || ((USER_CONFIG==CONFIG_AX3251_AIRBORNE)))
const struct spirgbmode spi_ili6480 ={
	.red_width = 8,
	.green_width = 8,
	.blue_width = 8,
	.even_rgb_order = ORDER_RGB,
	.odd_rgb_order = ORDER_RGB,
	
	.shift_width = 8,
	.expand_loc = 0,
	.expand_width = 0,
	.data_en = 0xf8,
	.data_inv = 0, 

	.vsync_en = 1, 
	.hsync_en = 1, 
	.de_en = 0,
	.dclk_en = 1,
	.vsync_inv = 1,
	.hsync_inv = 1,
	.de_inv = 0,
	.dclk_inv = 0,

	.datactrl_mode = 1,
	.cs_oen = 0,
	/*.cs_inv = 1,*/
	.cs_pr = 8,

	.spi_id_st = 0,
	.spi_smp_sel = 1,
	.spi_1dw = 1,
	.spi_1dw_dir = 0,
	.spi_9biten = 0,
	.spi_9bit = 0,
	.spi_baud = SYS_CLK/(2*6000000)-1,

	.vsync_inact_at = 0,
	.vsync_up_neg_edge = 0, 
	.hsync_up_neg_edge = 0,
	.de_up_neg_edge = 0,
	
	.clkdiv = 4,
	.hsrp = 1,
	.vsrp = 1,
	.hspw = 2, 
	.vspw = 2,           
	.hbpd = 120/3, 
	.vbpd = 8,                 
	.hozval  = 1440/3,   
	.lineval = 272, 
	.hfpd = 168/3, 
	.vfpd = 8,      

	.rotatemode = ROTATE_NONE,
	.mirror = MIRROR_NONE,
	.yminus16 = 1,
	.interval = 20,
};
#else
	......
#endif



void lcd_init(void) 
{
	deg_Printf("lcd_init spi_ili6480\n");
	blcd_FrameEnd_Flag = 0;	
	blcd_writeback_Flag = 0;
	
	PIN_CONF()
	SPI_PIN_CONF()	  	

//====open lcd ldo=====
	REG32(SYS_CON) = 0x932B;	//SPEC request value
	REG32(LDO_ACON) |= 0x4;			// 3.0v
	REG32(LDO_ACON) |= (1<<3);		//lcd ldo enable
	deg_Printf("lcd ldo open \n");
	Delay_MS(100);
//====end open lcd ldo=====

	lcd_spirgb_timing_init(spi_ili6480);


#if (USER_CONFIG==CONFIG_AX3251_K6000)
	reset_rgb_data_en(0xfe);			// data  7bit en  
#endif

	deg_Printf("Reg1=%x,%x,%x,%x,%x\n",REG32(PF_DIR),REG32(PG_DIR),REG32(PMAP_CFG0),REG32(LCD_CFG),REG32(LCD_CFG_EMI));

     	spi_to_rgb(); 
	//REG32(LCDCON0)|=BIT(8)|BIT(13);//XJC
	SetIntSrc(LCD_INT);
	REG32(LCDCON0) |= 1<<10;	
}


//========add for app====

u32 lcd_get_w()
{
	return spi_ili6480.hozval;
}

u32 lcd_get_h()
{
	return spi_ili6480.lineval;
}

void lcd_set_backlight(int flag)
{
//	deg_Printf("set_backlight %d\n",flag);

//=========backlight 2.8v========
	LCDBKL_OUTPUT();
	if(0 == flag)				//close backlight
	{
//		LCDBKL_OPEN();
		LCDBKL_CLOSE();
		
	}
	else						//open backlight
	{
//		LCDBKL_CLOSE();
		LCDBKL_OPEN();
	}

//=========set the backlight  3.3v======
	LCDPWEN_OUTPUT();
#if 0
	if(0 == flag)				//close 
	{
		LCDPWEN_DISABLE();
	}
	else						//open
	{
		LCDPWEN_ENABLE();
	}
#else
	//open forever
	LCDPWEN_ENABLE();	//disable the control of LCD_PWEN, because the voltage not enough
#endif
}


void lcd_Isr(void)
{
	u32 u32lcd_IntFlag;

	u32lcd_IntFlag = REG32(LCDCON57);
	if((u32lcd_IntFlag & BIT(2)) == BIT(2))
	{
		REG32(LCDCON57) = BIT(2);  
		blcd_writeback_Flag = 1;
		//deg_Printf("w ");              	
	}
	if((u32lcd_IntFlag & 0x1) == 0x1)
	{
		REG32(LCDCON57) = 0x1;
		blcd_FrameEnd_Flag = 1;
		//deg_Printf("lcd FE\n");
	}
}

void TFT_LCD_Timing_Initail(void)
{
	lcd_spirgb_timing_init(spi_ili6480);
}


#endif
