/******************** (C) COPYRIGHT 2014 BUILDWIN ************************
* File Name          : lcd_tdo24theb2.c
* Author             :  
* Version            :  
* Date               : 02/27/2014
* Description        : This file provides all the lcd tdo24theb2 SPI_RGB_2.4 firmware functions.
***************************************************************************/
//===================================================================
//                                                     	            |
//                       INCLUDE FILES                              |
//                                                                  |
//===================================================================
#include "../header/include.h"

#if(LCD_USE == LCD_TDO24THEB2)
//===================================================================
//                                                     	            |
//                      GLOBAL VARIABLE                             |
//                                                                  |
//===================================================================

#define lcd_spi_write_command(x)    {1,x} 
#define lcd_spi_write_parameter(x)  {0,x}
#define lcd_delay_ms(x)             {2,x}
#define table_init_end              {9,0}

const struct spirgbmode spi_tdo24theb2 ={
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
	.dclk_inv = 1,

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
	
	.clkdiv = 12,
	.hsrp = 1,
	.vsrp = 1,
	.hspw = 2, 
	.vspw = 2,           
	.hbpd = 99/3,  
	.vbpd = 15,                 
	.hozval  = 480/3,         
	.lineval = 240, 
	.hfpd = 83/3,
	.vfpd = 8,      

	.rotatemode = ROTATE_NONE,
	.mirror = MIRROR_NONE,
	.yminus16 = 1,
	.interval = 40,
	};
	
u16 table_init[10][2]=
{
	lcd_spi_write_command(0x080a),
	lcd_spi_write_command(0x0c01),
	lcd_spi_write_command(0x100f),
	lcd_spi_write_command(0x1c28),
	lcd_spi_write_command(0x2420),

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



void lcd_init(void) 
{
	deg_Printf("lcd_init lcd_tdo24theb2 \n");
	blcd_FrameEnd_Flag = 0;	
	blcd_writeback_Flag = 0;
	
	PIN_CONF()
	LCD_SPI_PMAP1()
	SPI_PIN_CONF()	  

//====open lcd ldo=====
	REG32(SYS_CON) = 0x932B;	//SPEC request value
	REG32(LDO_ACON) |= 0x4;			// 3.0v
	REG32(LDO_ACON) |= (1<<3);		//lcd ldo enable
	deg_Printf("lcd ldo open \n");
	Delay_MS(100);
	
    lcd_spirgb_timing_init(spi_tdo24theb2);
    lcd_spi_init(&table_init[0][0]);	
    spi_to_rgb();

	//REG32(LCDCON0)|=BIT(8)|BIT(13);//XJC
	SetIntSrc(LCD_INT);
	REG32(LCDCON0) |= 1<<10;	
}


//========add for app====

u32 lcd_get_w()
{
	return spi_tdo24theb2.hozval;
}

u32 lcd_get_h()
{
	return spi_tdo24theb2.lineval;
}

void lcd_set_backlight(int flag)
{
	//deg_Printf("set_backlight %d\n",flag);
	REG32(PG_DIR) &= ~(1<<3);
	if(0 == flag)				//close 
	{
		REG32(PG) |= (1<<3);
	}
	else						//open
	{
		REG32(PG) &= ~(1<<3);
	}
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
	lcd_spirgb_timing_init(spi_tdo24theb2);
}


 
#endif