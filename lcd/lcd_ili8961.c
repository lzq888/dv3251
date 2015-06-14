/******************** (C) COPYRIGHT 2014 BUILDWIN ************************
* File Name          : lcd_s2700l0_g.c
* Author             :  
* Version            :  
* Date               : 02/27/2014
* Description        : This file provides all the lcd s2700l0_g SPI_RGB_2.7 firmware functions.
***************************************************************************/
#include "../header/include.h"

#if(LCD_USE == LCD_ILI8961)
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
const struct spirgbmode spi_ili8961 ={
	.red_width = 8,
	.green_width = 8,
	.blue_width = 8,
	.even_rgb_order = ORDER_RGB,
	.odd_rgb_order = ORDER_GBR,
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
#error "config error"
	.spi_9bit = 0,
	//.spi_baud = SYS_CLK/(2*6000000)-1,
	.spi_baud = SYS_CLK/(2*50000)-1, //yezq

	.vsync_inact_at = 0,
	.vsync_up_neg_edge = 0, 
	.hsync_up_neg_edge = 0,
	.de_up_neg_edge = 0,
	
	.clkdiv = 8,
	.hsrp = 1,
	.vsrp = 1,
	.hspw = 2, 
	.vspw = 2,           
	.hbpd = 72/3, 
	.vbpd = 21,                 
	.hozval  = 960/3,   
	.lineval = 240, 
	.hfpd = 684/3, 
	.vfpd = 2,      

	.rotatemode = ROTATE_NONE,
	.mirror = MIRROR_NONE,
	.yminus16 = 1,
	.interval = 20,
};
#elif ((USER_CONFIG==CONFIG_AX3251_K6000) || ((USER_CONFIG==CONFIG_AX3251_AIRBORNE)))
const struct spirgbmode spi_ili8961 ={
	.red_width = 8,
	.green_width = 8,
	.blue_width = 8,
	.even_rgb_order = ORDER_RGB,
	.odd_rgb_order = ORDER_GBR,
	.shift_width = 8,
	.expand_loc = 0,
	.expand_width = 0,
	//.data_en = 0xf8, yezq
	.data_en = 0xf0,
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
	//.spi_1dw = 0, //yezq
	.spi_1dw = 0,
	.spi_1dw_dir = 0,
	.spi_9biten = 0,
	.spi_9bit = 0,
	//.spi_baud = SYS_CLK/(2*6000000)-1,
	.spi_baud = SYS_CLK/(2*6000000)-1, //yezq

	.vsync_inact_at = 0,
	.vsync_up_neg_edge = 0, 
	.hsync_up_neg_edge = 0,
	.de_up_neg_edge = 0,
	
	.clkdiv = 6,
	.hsrp = 1,
	.vsrp = 1,
	.hspw = 2, 
	.vspw = 2,           
	.hbpd = 72/3, 
	.vbpd = 21,                 
	.hozval  = 960/3,   
	.lineval = 240, 
	.hfpd = 684/3, 
	.vfpd = 2,      

	.rotatemode = ROTATE_NONE,
	.mirror = MIRROR_NONE,
	.yminus16 = 1,
	.interval = 20,
};
#else
	......
#endif

	
u16 table_init[50][2]=
{


//======backup ok need good========
	lcd_spi_write_command(0x055f),
	lcd_delay_ms(5),	
	lcd_spi_write_command(0x051f),
	lcd_delay_ms(10),	
	lcd_spi_write_command(0x055f),
	lcd_delay_ms(50),
	lcd_spi_write_command(0x2b01),
	lcd_spi_write_command(0x000b), 			//vcom ac	
	lcd_spi_write_command(0x019f),			//vcom dc
	lcd_spi_write_command(0x040b),
	lcd_spi_write_command(0x1604),
	lcd_spi_write_command(0x0614),
	lcd_spi_write_command(0x0745),



/*
//=====not good=====
	lcd_spi_write_command(0x055f),
	lcd_delay_ms(5),	
	lcd_spi_write_command(0x051f),
	lcd_delay_ms(10),	
	lcd_spi_write_command(0x055f),
	lcd_delay_ms(50),
	lcd_spi_write_command(0x055e),
	lcd_spi_write_command(0x2b01),
	lcd_spi_write_command(0x000b), 			//vcom ac	
	lcd_spi_write_command(0x019b),			//vcom dc
	lcd_spi_write_command(0x0b81),
	lcd_spi_write_command(0x0695),
	lcd_spi_write_command(0x0746),
	lcd_spi_write_command(0x1600),

	lcd_spi_write_command(0x1777),
	lcd_spi_write_command(0x1877),
	lcd_spi_write_command(0x1933),
	lcd_spi_write_command(0x1a43),
	
	lcd_spi_write_command(0x9580),
	lcd_spi_write_command(0xaf04),
	lcd_spi_write_command(0xa522),
	lcd_spi_write_command(0xa612),
	lcd_spi_write_command(0xa706),
*/



/*
//====ÁèÑô=====
lcd_spi_write_command(0x055F),//WJL
lcd_delay_ms(10),
lcd_spi_write_command(0x051F),//WJL
lcd_delay_ms(10),

lcd_spi_write_command(0x055F),//WJL
lcd_delay_ms(50),

lcd_spi_write_command(0x000b),
lcd_spi_write_command(0x019f),
lcd_spi_write_command(0x0340),

lcd_spi_write_command(0x040b),//0x0408 Flip

lcd_spi_write_command(0x055C),
lcd_spi_write_command(0x0614),
lcd_spi_write_command(0x0745),
lcd_spi_write_command(0x0800),
lcd_spi_write_command(0x0B00),
lcd_spi_write_command(0x0C06),
lcd_spi_write_command(0x0D40),
lcd_spi_write_command(0x0E40),
lcd_spi_write_command(0x0F40),
lcd_spi_write_command(0x1040),
lcd_spi_write_command(0x1140),

lcd_spi_write_command(0x1604),// WJL

lcd_spi_write_command(0x17DF),

lcd_spi_write_command(0x1823),
lcd_spi_write_command(0x1304),

lcd_spi_write_command(0x1931),
lcd_spi_write_command(0x1A25),
lcd_spi_write_command(0x1B03),
lcd_spi_write_command(0x2F61),
lcd_spi_write_command(0x5500),
lcd_spi_write_command(0x5A03),
lcd_spi_write_command(0x6A23),
lcd_spi_write_command(0x6F04),
lcd_delay_ms(10),

lcd_spi_write_command(0x2B01),
*/


	table_init_end 
};

void lcd_spi_sendcmd(u16 cmd)
{
	REG32(PF) |= (1<<LCD_SPI_CS_PIN);
	delay_ms(1);
	REG32(PF) &= ~(1<<LCD_SPI_CS_PIN);
	lcd_spi_putchar((cmd >> 8) & 0xff);
	lcd_spi_putchar(cmd & 0xff);
	REG32(PF) |= (1<<LCD_SPI_CS_PIN);	
}


void delay(u32 delay_ms_cnt) 
{
	u32 i, j;	
	for (i = 0; i < delay_ms_cnt; i++) 
	{
		for (j = 0; j < 50000/9; j++) 
		{	
			asm("nop");
		}
	}
}

void lcd_spi_init(u16 *p)
{

	while(9 != *p)
	{   
		if(2==*p)
		{
			delay(*(p++));
		}
		else
		{   
			p++;
			lcd_spi_sendcmd(*p);	      
		}
		p++;
	}
}

#ifdef SPI_TRANSFER
int spi_send(unsigned char *buf, int len)
{
	REG32(PF) |= (1<<LCD_SPI_CS_PIN);
	delay_ms(1);
	REG32(PF) &= ~(1<<LCD_SPI_CS_PIN);
	delay_ms(5);
	while(len-- > 0) {
		lcd_spi_putchar(*buf++);
	}
	delay_ms(5);
	REG32(PF) |= (1<<LCD_SPI_CS_PIN);	

	return 0;
}

int spi_recv(unsigned char *buf, int len)
{
	//REG32(PF) |= (1<<LCD_SPI_CS_PIN);
	//delay_ms(1);
	REG32(PF) &= ~(1<<LCD_SPI_CS_PIN);
	while(len-- > 0) {
		*buf++ = lcd_spi_getchar();
	}
	REG32(PF) |= (1<<LCD_SPI_CS_PIN);	

	return 0;
}
#endif

void lcd_init(void) 
{
	deg_Printf("lcd_init spi_ili8961 \n");
	blcd_FrameEnd_Flag = 0;	
	blcd_writeback_Flag = 0;
	
	PIN_CONF()
	SPI_PIN_CONF()	  	
	REG32(PF) |= (1<<LCD_SPI_CS_PIN);	


//====open lcd ldo=====
	REG32(SYS_CON) = 0x932B;	//SPEC request value
	REG32(LDO_ACON) |= 0x4;			// 3.0v
	REG32(LDO_ACON) |= (1<<3);		//lcd ldo enable
	deg_Printf("lcd ldo open \n");
	Delay_MS(100);
//====end open lcd ldo=====

	lcd_spirgb_timing_init(spi_ili8961);

#ifdef SPI_TRANSFER
	return;
#endif
    	lcd_spi_init(&table_init[0][0]);	
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
	return spi_ili8961.hozval;
}

u32 lcd_get_h()
{
	return spi_ili8961.lineval;
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
	lcd_spirgb_timing_init(spi_ili8961);
}


#endif
