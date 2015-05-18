/******************** (C) COPYRIGHT 2014 BUILDWIN ************************
* File Name          : lcd_61505.c
* Author             :  
* Version            :  
* Date               : 02/27/2014
* Description        : This file provides all the lcd 61505 EMI firmware functions.
***************************************************************************/
//===================================================================
//                                                     	            |
//                       INCLUDE FILES                              |
//                                                                  |
//===================================================================
#include "../header/include.h"

#if(LCD_USE == LCD_61505)
//===================================================================
//                                                     	            |
//                      GLOBAL VARIABLE                             |
//                                                                  |
//===================================================================

#define PIN_CONF()    REG32(PF_DIR) &= (~0xff7); REG32(PF) &= (~0xff7);/*REG32(PG_DIR) &= (~0x1fff)*/;

#define	LCD_WR_SET	REG32(PF) |= (1<<0)    	//写数据			 PF0
#define	LCD_WR_CLR	 REG32(PF)  &= ~(1<<0)	  //写数据			 PF0
#define	LCD_CS_SET  REG32(PF)  |= (1<<1)		  //片选端口  	 PF1
#define	LCD_CS_CLR  REG32(PF)  &= ~(1<<1)	  //片选端口  	 PF1
#define	LCD_RS_CLR	REG32(PF)  &= ~(1<<2) 	//复位清除		 PF2
#define	LCD_RS_SET	REG32(PF)  |= (1<<2) 	//复位使能		 PF2


const struct emimode emi_61505 ={
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
	.wr_inv = 1,						// wr  pin high is idle
	.cs_inv = 1,						// cs pin high is idle 
	.wr_fp = 7,
	.wr_rp = 4,
	.cs_pr = 0x10, 
	.data_en = 0xff,
	.data_inv = 0,						//
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
	lcd_write_data(cmd);
	LCD_RS_SET;
}

static void lcd_write_parameter_8bit(u8 data)
{
	LCD_RS_SET;
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

//=========61505U==========

	lcd_WriteReg(0x0007,0x0000);		 //display control:GON=DTE=D1-0=0
	lcd_WriteReg(0x0010,0x0000);  		 //sleep mode:slp=0;
	lcd_WriteReg(0x0012,0x0000);		//power control 3:pon=0

	lcd_WriteReg(0x0000,0x0000);    	//transfer synchronization
	lcd_WriteReg(0x0000,0x0000);
	lcd_WriteReg(0x0000,0x0000);
	lcd_WriteReg(0x0000,0x0000);
	lcd_WriteReg(0x00a4,0x0001);		 //oscillation control
	Delay_MS(60); 			 	//_delay_ms 60 ms

	lcd_WriteReg(0x0001,0x0100); 		//driver output control
	lcd_WriteReg(0x0002,0x0700); 		// drive  waveform control
	lcd_WriteReg(0x0003,0x1028); 		//entry mode
	lcd_WriteReg(0x0008,0x0808);		// display control  0x0404
	lcd_WriteReg(0x000a,0x0000);		//display control 4
	lcd_WriteReg(0x000c,0x0001);		//external display interface control2
	lcd_WriteReg(0x000d,0x0001); 		//frame marker control
	lcd_WriteReg(0x0060,0x2700);	// driver output control
	lcd_WriteReg(0x0061,0x0001); 		// base image display control
	lcd_WriteReg(0x006A,0x0000);		// base image display control
	lcd_WriteReg(0x0090 ,0x0010); 		// panel interface control 1
	lcd_WriteReg(0x0092,0x0000);		// panel interface control 2
	lcd_WriteReg(0x0093,0x0001);		// panel interface control 3


	//set gamma value
	lcd_WriteReg(0x0030,0x0303);		// Gamma control (1)
	lcd_WriteReg(0x0031,0x0303); 		// Gamma control (2)
	lcd_WriteReg(0x0032,0x0303);   		// Gamma control (3)
	lcd_WriteReg(0x0033,0x0303);  		// Gamma control (4)
	lcd_WriteReg(0x0034,0x0404);		// Gamma control (5)
	lcd_WriteReg(0x0035,0x0404);	// Gamma control (6)
	lcd_WriteReg(0x0036,0x0404); 		// Gamma control (7)
	lcd_WriteReg(0x0037,0x0303); 		// Gamma control (8)
	lcd_WriteReg(0x0038,0x0303);	// Gamma control (9)
	lcd_WriteReg(0x0039,0x0303); 		// Gamma control (10)
	lcd_WriteReg(0x003a,0x0303); 		// Gamma control (11)
	lcd_WriteReg(0x003b,0x0303); 		// Gamma control (12)
	lcd_WriteReg(0x003c,0x0404);		// Gamma control (13)
	lcd_WriteReg(0x003d,0x0303); 		// Gamma control (14)
	lcd_WriteReg(0x0000,0x0100);
	lcd_WriteReg(0x0000,0x0100);
       lcd_WriteReg(0x0000 ,0x0100);

       // power on
	lcd_WriteReg(0x0007,0x0001);		 //display control:GON=DTE=D1-0=0
	lcd_WriteReg(0x0017,0x0001);		//power control 6:
	lcd_WriteReg(0x0019,0x0000); 		//power control
	lcd_WriteReg(0x0010,0x17b0);		//power control 1
	lcd_WriteReg(0x0011,0x0006);		//power control 2
	lcd_WriteReg(0x0012,0x0118); 		//power control 3  0x0118
	lcd_WriteReg(0x0013 ,0x1b00); 		//power control 4  0x1b00

	//set  vdv3-0
	lcd_WriteReg(0x0029,0x0010);		//power control 7:
	lcd_WriteReg(0x002a,0x008c); 		// set vcomh

	lcd_WriteReg(0x0012,0x0138);		//power control 3
	Delay_MS(120);
	lcd_WriteReg(0x0050 ,0x0000); 		// window horizontal RAM address
	lcd_WriteReg(0x0051,0x00ef); 		// window horizontal RAM address
	lcd_WriteReg(0x0052,0x0000);		//window vertical RAM address
	lcd_WriteReg(0x0053,0x013f);		//window vertical RAM address
	lcd_WriteReg(0x0020,0x0000); 		// GRAM address set
	lcd_WriteReg(0x0021,0x0000);		// GDDRAM address set
	lcd_WriteReg(0x0007,0x0021); 		// Display control on
	Delay_MS(60);
	lcd_WriteReg(0x0010,0x10b0); 		//power control 1
	lcd_WriteReg(0x0011,0x0000); 		//power control 2
	Delay_MS(60);
	lcd_WriteReg(0x0007,0x0061);		// Display control on
	Delay_MS(60);
	lcd_WriteReg(0x0007,0x0173); 		//	Display control on
	Delay_MS(120);

	lcd_write_cmd_16bit(0x0022);


//========61505W======
/*
	lcd_WriteReg(0x00A4,0x0001);
	Delay_MS(2);
	lcd_WriteReg(0x0010,0x0000);
	lcd_WriteReg(0x0011,0x0007);
	lcd_WriteReg(0x0012,0x0000);
	lcd_WriteReg(0x0013,0x0000);
	Delay_MS(200);
	lcd_WriteReg(0x0010,0x0430);
	lcd_WriteReg(0x0011,0x0237);
	Delay_MS(50);
	lcd_WriteReg(0x0012,0x01BC);
	Delay_MS(50);
	lcd_WriteReg(0x0013,0x0f00);
	//lcd_WriteReg(0x002A,0x0080);
	//lcd_WriteReg(0x0029,0x0054);

	lcd_WriteReg(0x0029,0x0030);		//0x30 ok
	lcd_WriteReg(0x002A,0x0080);

	Delay_MS(50);
	lcd_WriteReg(0x0000,0x0001);
	lcd_WriteReg(0x0001,0x0000);
	lcd_WriteReg(0x0002,0x0700);

	lcd_WriteReg(0x0003,0x1038);		// 0' or 180'

	lcd_WriteReg(0x0004,0x0000);
	lcd_WriteReg(0x0008,0x0808);
	lcd_WriteReg(0x0009,0x0000);
	lcd_WriteReg(0x000A,0x0008);
	lcd_WriteReg(0x000C,0x0000);
	lcd_WriteReg(0x000D,0x0000);
	lcd_WriteReg(0x000E,0x0030);
	lcd_WriteReg(0x000F,0x0000);

	lcd_WriteReg(0x0030,0x0200);
	lcd_WriteReg(0x0031,0x360A);
	lcd_WriteReg(0x0032,0x0603);
	lcd_WriteReg(0x0033,0x0405);
	lcd_WriteReg(0x0034,0x0000);
	lcd_WriteReg(0x0035,0x0200);
	lcd_WriteReg(0x0036,0x360A);
	lcd_WriteReg(0x0037,0x0603);
	lcd_WriteReg(0x0038,0x0405);
	lcd_WriteReg(0x0039,0x0000);

	lcd_WriteReg(0x0050,0x0000);
	lcd_WriteReg(0x0051,0x00EF);
	lcd_WriteReg(0x0052,0x0000);
	lcd_WriteReg(0x0053,0x013F);

	lcd_WriteReg(0x0060,0x2700);
	lcd_WriteReg(0x0061,0x0001);
	lcd_WriteReg(0x006A,0x0000);

	lcd_WriteReg(0x0090,0x0016);
	lcd_WriteReg(0x0091,0x0006);
	lcd_WriteReg(0x0092,0x0400);
	lcd_WriteReg(0x0093,0x0404);
	lcd_WriteReg(0x0093,0x0004);

	lcd_WriteReg(0x0050 ,0x0000); 		// window horizontal RAM address
	lcd_WriteReg(0x0051,0x00ef); 		// window horizontal RAM address
	lcd_WriteReg(0x0052,0x0000);		//window vertical RAM address
	lcd_WriteReg(0x0053,0x013f);		//window vertical RAM address
//	lcd_WriteReg(0x0020,0x0000); 		// GRAM address set
//	lcd_WriteReg(0x0021,0x0000);		// GDDRAM address set
	lcd_WriteReg(0x0020,0x0000); 		// GRAM address set
	lcd_WriteReg(0x0021,0x0001);		// GDDRAM address set

	lcd_WriteReg(0x0007,0x0001);
	Delay_MS(10);
	lcd_WriteReg(0x0007,0x0061);
	lcd_WriteReg(0x0007,0x0173);

	lcd_write_cmd_16bit(0x0022);
*/

}

static void lcd_clean_screen(void)
{
	int j, k;  

	for(j=0; j<LCD_HEIGHT; j++)
	{
		for(k=0; k<LCD_WIDTH; k++)
		{
			lcd_write_parameter_16bit(0x0000);	
		}
	}
}


void lcd_init(void) 
{
	deg_Printf("lcd_init mcu 61505 \n");
	blcd_FrameEnd_Flag = 0;	
	blcd_writeback_Flag = 0;

	PIN_CONF()						//IO down
	lcd_emi_timing_init(emi_61505);

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
	

}


//========add for app====

u32 lcd_get_w()
{
	return emi_61505.pwidth+1;
}

u32 lcd_get_h()
{
	return emi_61505.pheight+1;
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
