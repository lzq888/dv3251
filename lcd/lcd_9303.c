/******************** (C) COPYRIGHT 2014 BUILDWIN ************************
* File Name          : lcd_9303.c
* Author             :  
* Version            :  
* Date               : 02/27/2014
* Description        : This file provides all the lcd 9330 EMI firmware functions.
***************************************************************************/
//===================================================================
//                                                     	            |
//                       INCLUDE FILES                              |
//                                                                  |
//===================================================================
#include "../header/include.h"

#if(LCD_USE == LCD_9303)
//===================================================================
//                                                     	            |
//                      GLOBAL VARIABLE                             |
//                                                                  |
//===================================================================

#define PIN_CONF()    REG32(PF_DIR) &= (~0xff7);  REG32(PF) &= (~0xff7);/*REG32(PG_DIR) &= (~0x1fff)*/;

#define	LCD_WR_SET	REG32(PF) |= (1<<0)    	//Ð´Êý¾Ý			 PF0
#define	LCD_WR_CLR	 REG32(PF)  &= ~(1<<0)	  //Ð´Êý¾Ý			 PF0
#define	LCD_CS_SET  REG32(PF)  |= (1<<1)		  //Æ¬Ñ¡¶Ë¿Ú  	 PF1
#define	LCD_CS_CLR  REG32(PF)  &= ~(1<<1)	  //Æ¬Ñ¡¶Ë¿Ú  	 PF1
#define	LCD_RS_CLR	REG32(PF)  &= ~(1<<2) 	//¸´Î»Çå³ý		 PF2
#define	LCD_RS_SET	REG32(PF)  |= (1<<2) 	//¸´Î»Ê¹ÄÜ		 PF2


const struct emimode emi_9303 ={
	.red_width = 5,
	.green_width = 6,
	.blue_width = 5,
	.even_rgb_order = ORDER_RGB,
	.odd_rgb_order = ORDER_RGB,
	.shift_width = 8,
	.expand_loc = 0,
	.expand_width = 0,
	.datactrl_mode = 1,				
	.cs_oen = 1,
	.wr_inv = 1,						// wr  pin down is idle
	.cs_inv = 1,						// cs pin down is idle 
	.wr_fp = 7,
	.wr_rp = 4,
	.cs_pr = 0x10, 
	.data_en = 0xff,
	.data_inv = 0,
	.clkdiv = 8,					//pixel clk
	.pwidth = 320-1,
	.pheight = 240-1,
	.lcd_line_dclks = 320*2-1,
	.rotatemode = ROTATE_NONE,
	.mirror = MIRROR_NONE,
	.yminus16 = 1,
	.interval = 20,
	};

 /*******************************************************************************
* Function Name  : lcd_Init
* Description    : initialize the lcd
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void lcd_write_data(u16 u16data)
{
    REG32(LCDCON18) = u16data;
    while(REG32(LCDCON57)&0x02);	// wait data transfer done
}

static void lcd_write_cmd_8bit(u8 cmd)
{
	LCD_RS_CLR;	
	delay_us(1);
	lcd_write_data(cmd);
	LCD_RS_SET;

}

static void lcd_write_parameter_8bit(u8 data)
{
	LCD_RS_SET;
	delay_us(1);
	lcd_write_data(data);
}

static void lcd_write_cmd_16bit(u16 cmd)
{
	LCD_RS_CLR;	
	delay_us(1);
	lcd_write_data(((cmd>>8)&0xff));
	delay_us(1);
	lcd_write_data(cmd&0xff);
	LCD_RS_SET;
	
}

static void lcd_write_parameter_16bit(u16 data)
{
	LCD_RS_SET;
	delay_us(1);
	lcd_write_data(((data>>8)&0xff));
	delay_us(1);
	lcd_write_data(data&0xff);
}


static void lcd_WriteReg(u16 cmd,u16 data)
{
	lcd_write_cmd_16bit(cmd);
	lcd_write_parameter_16bit(data);
}
static void lcd_emi_init()
{
	lcd_write_cmd_8bit(0x11);
	Delay_MS(120);
	lcd_write_cmd_8bit(0x29);
	Delay_MS(120);
	
	lcd_write_cmd_8bit(0x06); //enter externed command
	lcd_write_cmd_8bit(0x07);
	lcd_write_cmd_8bit(0xb1);
	lcd_write_parameter_8bit(0x00);
	lcd_write_parameter_8bit(0x12);
	lcd_write_cmd_8bit(0xb4);
	lcd_write_parameter_8bit(0x02); //line inversion
	lcd_write_cmd_8bit(0xb6);
	lcd_write_parameter_8bit(0x00); //rev,gs,ss,sm
	lcd_write_parameter_8bit(0xa0);
	lcd_write_parameter_8bit(0x27);
	lcd_write_parameter_8bit(0x00);
	lcd_write_cmd_8bit(0xc0);
	lcd_write_parameter_8bit(0x13); //vrh
	lcd_write_cmd_8bit(0xc1);
	lcd_write_parameter_8bit(0x51); //
	lcd_write_parameter_8bit(0x9d);
	lcd_write_parameter_8bit(0x75);
	lcd_write_cmd_8bit(0xca);
	lcd_write_parameter_8bit(0x21);
	lcd_write_cmd_8bit(0xcb);
	lcd_write_parameter_8bit(0x03); //vc
	lcd_write_cmd_8bit(0xc4);
	lcd_write_parameter_8bit(0x00);

	lcd_write_cmd_8bit(0xc5);
	lcd_write_parameter_8bit(0x03);
	lcd_write_cmd_8bit(0xc6);
	lcd_write_parameter_8bit(0x00);
	lcd_write_cmd_8bit(0xc7);
	lcd_write_parameter_8bit(0x06); //osc
	lcd_write_cmd_8bit(0xc8);
	lcd_write_parameter_8bit(0x34);
	/***************************************/
	//lcd_write_cmd_8bit(0xcc);//tiao wen   max 3f
	//lcd_write_parameter_8bit(0x17); //vcm 0a////cc-1c_cd-17    cc-1b_cd-1f
	//lcd_write_cmd_8bit(0xcd);//se cai
	//lcd_write_parameter_8bit(0x1d); //vdv  1d max 1f
	//lcd_write_parameter_8bit(0x00); //vcm1
	//lcd_write_cmd_8bit(0xcf);
	/*************************************/
/*
	lcd_write_cmd_8bit(0xcc);//tiao wen   max 3f
	lcd_write_parameter_8bit(0x10); //vcm 0a////cc-1c_cd-17    cc-1b_cd-1f
	lcd_write_cmd_8bit(0xcd);//se cai
	lcd_write_parameter_8bit(0x1f); //vdv  1d max 1f
	lcd_write_cmd_8bit(0xce);
	lcd_write_parameter_8bit(0x00); //vcm1
	lcd_write_cmd_8bit(0x0a);

	lcd_write_parameter_8bit(0x00); //vdv2
	lcd_write_cmd_8bit(0xf9);
	lcd_write_parameter_8bit(0x15);
	lcd_write_parameter_8bit(0x15);
	lcd_write_cmd_8bit(0xf3);
	lcd_write_parameter_8bit(0x0a);
	lcd_write_parameter_8bit(0x02);
	lcd_write_parameter_8bit(0x0a);
	lcd_write_cmd_8bit(0xf6);
	lcd_write_parameter_8bit(0x01);
	lcd_write_parameter_8bit(0x10);
	lcd_write_parameter_8bit(0x00);
	lcd_write_cmd_8bit(0xf2);
	lcd_write_parameter_8bit(0x00);
	
	/*
	lcd_write_cmd_8bit(0xe0); //gmama set
	lcd_write_parameter_8bit(0x70);//70
	lcd_write_cmd_8bit(0xe1);
	lcd_write_parameter_8bit(0x15);
	lcd_write_cmd_8bit(0xe2);
	lcd_write_parameter_8bit(0x77);
	lcd_write_cmd_8bit(0xe3);
	lcd_write_parameter_8bit(0x70);
	lcd_write_cmd_8bit(0xe4);
	lcd_write_parameter_8bit(0x80);
	lcd_write_cmd_8bit(0xe5);
	lcd_write_parameter_8bit(0xe0);
	lcd_write_cmd_8bit(0xe6);
	lcd_write_parameter_8bit(0x00);
	lcd_write_cmd_8bit(0xe7);
	lcd_write_parameter_8bit(0x36);
	lcd_write_cmd_8bit(0xe8);
	lcd_write_parameter_8bit(0x70); //70
	lcd_write_cmd_8bit(0xe9);
	lcd_write_parameter_8bit(0x07);
	lcd_write_cmd_8bit(0xea);
	lcd_write_parameter_8bit(0xc0);
	lcd_write_cmd_8bit(0xeb);
	lcd_write_parameter_8bit(0x80);
*/
	lcd_write_cmd_8bit(0x3a); 
	lcd_write_parameter_8bit(0x55);
	
	//lcd_write_cmd_8bit(0x36);
	//lcd_write_parameter_8bit(0x48);
	
	lcd_write_cmd_8bit(0x36);
	lcd_write_parameter_8bit(0x48);
	
	lcd_write_cmd_8bit(0xfe);
	lcd_write_cmd_8bit(0xef);
	
	lcd_write_cmd_8bit(0xea);
	lcd_write_parameter_8bit(0x3f);
	
	lcd_write_cmd_8bit(0xe6);
	lcd_write_parameter_8bit(0x06);
	
	lcd_write_cmd_8bit(0xe7);
	lcd_write_parameter_8bit(0x3f);
	
	lcd_write_cmd_8bit(0xed);
	lcd_write_parameter_8bit(0x24);
	
	lcd_write_cmd_8bit(0xa4);
	lcd_write_parameter_8bit(0x1d);//12 liang     26 an

	lcd_write_cmd_8bit(0xb4);
	lcd_write_parameter_8bit(0x07);

	lcd_write_cmd_8bit(0xa3);
	lcd_write_parameter_8bit(0x00);
	lcd_write_parameter_8bit(0x40);
	
	lcd_write_cmd_8bit(0xfd);
	lcd_write_parameter_8bit(0x16);
	
	lcd_write_cmd_8bit(0xff);
	lcd_write_parameter_8bit(0x1a);//18
	
	lcd_write_cmd_8bit(0x35);
	lcd_write_parameter_8bit(0x00);
	lcd_write_cmd_8bit(0xf0);
	lcd_write_parameter_8bit(0x00);
	lcd_write_cmd_8bit(0xf1);
	lcd_write_parameter_8bit(0x67);
	lcd_write_cmd_8bit(0xf2);
	lcd_write_parameter_8bit(0x14);
	lcd_write_cmd_8bit(0xf3);
	lcd_write_parameter_8bit(0x47);
	lcd_write_cmd_8bit(0xf4);
	lcd_write_parameter_8bit(0x00);
	lcd_write_cmd_8bit(0xf5);
	lcd_write_parameter_8bit(0x00);
	
	lcd_write_cmd_8bit(0xf7);
	lcd_write_parameter_8bit(0x36);
	lcd_write_cmd_8bit(0xf8);
	lcd_write_parameter_8bit(0x01);
	lcd_write_cmd_8bit(0xf9);
	lcd_write_parameter_8bit(0x77);
	lcd_write_cmd_8bit(0xfa);
	lcd_write_parameter_8bit(0x74);
	lcd_write_cmd_8bit(0xfb);
	lcd_write_parameter_8bit(0x00);
	lcd_write_cmd_8bit(0xfc);
	lcd_write_parameter_8bit(0x00);


	lcd_write_cmd_8bit(0xfa); //exit externed command
	lcd_write_cmd_8bit(0xfb);
	Delay_MS(120); //delay is necessary
	lcd_write_cmd_8bit(0x36);
	//lcd_write_parameter_8bit(0x08);
	lcd_write_parameter_8bit(0x68);
	lcd_write_cmd_8bit(0x3a);
	lcd_write_parameter_8bit(0x05);

	lcd_write_cmd_8bit(0x29);
	
	lcd_write_cmd_8bit(0x2a);
	lcd_write_parameter_8bit(0x00);
	lcd_write_parameter_8bit(0x00);
	lcd_write_parameter_8bit(0x01);
	lcd_write_parameter_8bit(0x3f);

	lcd_write_cmd_8bit(0x2b);
	lcd_write_parameter_8bit(0x00);
	lcd_write_parameter_8bit(0x00);
	lcd_write_parameter_8bit(0x00);
	lcd_write_parameter_8bit(0xef);
	Delay_MS(20); 
	lcd_write_cmd_8bit(0x2c);
}

static void lcd_clean_screen(void)
{
	int j, k;

	for(j=0; j<LCD_HEIGHT; j++)
	{
		for(k=0; k<LCD_WIDTH; k++)
		{
			lcd_write_parameter_8bit(0x00);	
			lcd_write_parameter_8bit(0x00);
			
		}
	}
	//while(1);
}

void lcd_init(void) 
{
	deg_Printf("lcd_init mcu 9303 \n");
	blcd_FrameEnd_Flag = 0;	
	blcd_writeback_Flag = 0;
	PIN_CONF()

	lcd_emi_timing_init(emi_9303);

//====open lcd ldo=====
	REG32(SYS_CON) = 0x932B;	//SPEC request value
	REG32(LDO_ACON) |= 0x4;			// 3.0v
	REG32(LDO_ACON) |= (1<<3);		//lcd ldo enable
	deg_Printf("lcd ldo open \n");
	Delay_MS(100);
//====end open lcd ldo=====
	
	lcd_emi_init();

	lcd_clean_screen();

//	lcd_set_backlight(1);
//	while(1);


	LCD_WR_SET;
    	datactrl_mode_sel();

	SetIntSrc(LCD_INT);
	REG32(LCDCON0) |= 1<<10;	

	deg_Printf("pass emi lcd init \n");
 
}



//========add for app====

u32 lcd_get_w()
{
	return emi_9303.pwidth+1;
}

u32 lcd_get_h()
{
	return emi_9303.pheight+1;
}

void lcd_set_backlight(int flag)
{
	deg_Printf("set_backlight %d\n",flag);

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

//	Delay_MS(1000);

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



#endif
