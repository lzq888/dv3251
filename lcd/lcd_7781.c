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

#if(LCD_USE == LCD_7781)
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

const struct emimode emi_7781 ={
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
	lcd_WriteReg(0x0001,0x0100);//Output Direct
	lcd_WriteReg(0x0002,0x0700);//Line Inversion
//	#if ( LCD_ROTATION == 270)
//	lcd_WriteReg(0x0003,0x1018);//Entry Mode (65K, BGR)
//	#else
	lcd_WriteReg(0x0003,0x1028);//Entry Mode (65K, BGR)
//	#endif
	lcd_WriteReg(0x0007,0x0121);//Display Control1
	lcd_WriteReg(0x0008,0x0302); //Porch setting
	lcd_WriteReg(0x0009,0x0200);  //Scan Cycle
	lcd_WriteReg(0x000A,0x0000);  //FMARK off
	//-----------------------------------End Display Control setting-----------------------------------------//
	//-------------------------------- Power Control Registers Initial --------------------------------------//
	lcd_WriteReg(0x0010, 0x0790);     //Power Control1
	lcd_WriteReg(0x0011, 0x0005);     //Power Control2
	lcd_WriteReg(0x0012, 0x0000);     //Power Control3
	lcd_WriteReg(0x0013, 0x0000);     //Power Control4
	//---------------------------------End Power Control Registers Initial -------------------------------//
	Delay_MS (100);                                           //Delay 100ms
	//--------------------------------- Power Supply Startup 1 Setting------------------------------------//
	lcd_WriteReg(0x0010, 0x14b0);      //Power Control1
	Delay_MS (50);                      //Delay 50ms
	lcd_WriteReg(0x0011, 0x0337);      //Power Control2
	//--------------------------------- End Power Supply Startup 1 Setting------------------------------//
	Delay_MS (50);                                           //Delay 50ms
	//--------------------------------- Power Supply Startup 2 Setting------------------------------------//


	lcd_WriteReg(0x0012, 0x008b);                    //Power Control3
	lcd_WriteReg(0x0013, 0x1700);                    //Power Control4 对比度
	lcd_WriteReg(0x0029, 0x000b);                    //VCOMH setting //===b21===
//	lcd_WriteReg(0x0029, 0x0025);                    //VCOMH setting //===b13==
//	lcd_WriteReg(0x0029, 0x0020);                    //VCOMH setting //===f6==

	//--------------------------------- End Power Supply Startup 2 Setting------------------------------//
	Delay_MS (50);                                             //Delay 50ms
	//-------------------------------------Gamma Cluster Setting-------------------------------------------//
	lcd_WriteReg(0x0030, 0x0000);
	lcd_WriteReg(0x0031, 0x0207);
	lcd_WriteReg(0x0032, 0x0200);
	lcd_WriteReg(0x0035, 0x0104);
	lcd_WriteReg(0x0036, 0x0004);
	lcd_WriteReg(0x0037, 0x0000);
	lcd_WriteReg(0x0038, 0x0707);
	lcd_WriteReg(0x0039, 0x0207);
	lcd_WriteReg(0x003c, 0x0104);
	lcd_WriteReg(0x003d, 0x0004);
	//---------------------------------------End Gamma Setting---------------------------------------------//
	//----------------------------------Display Windows 240 X 320----------------------------------------//
	lcd_WriteReg(0x0050, 0x0000);                    //Horizontal Address Start Position
	lcd_WriteReg(0x0051, 0x00ef);                   // Horizontal Address End Position
	lcd_WriteReg(0x0052, 0x0000);                    //Vertical Address Start Position
	lcd_WriteReg(0x0053, 0x013f);                   // Vertical Address End Position
	//----------------------------------End Display Windows 240 X 320----------------------------------//
	//-------------------------------------------Frame Rate Setting-------------------------------------------//
	lcd_WriteReg(0x0060, 0xa700);                    //Gate scan control
	lcd_WriteReg(0x0061, 0x0001);                    //Non-display Area setting
	lcd_WriteReg(0x0090, 0x002A);                    //RTNI setting
	//-------------------------------------------END Frame Rate setting------------------------------------//
	lcd_WriteReg(0x0009, 0x0000);                    //Scan Cycle
	lcd_WriteReg(0x002B, 0x0010);
	lcd_WriteReg(0x0007, 0x0133);                    //Display Control1
	Delay_MS (50);                                    //Delay 50ms

	lcd_WriteReg(0x0050 ,0x0000); 		// window horizontal RAM address
	lcd_WriteReg(0x0051,0x00ef); 		// window horizontal RAM address
	lcd_WriteReg(0x0052,0x0000);		//window vertical RAM address
	lcd_WriteReg(0x0053,0x013f);		//window vertical RAM address
	lcd_WriteReg(0x0020,0x0000); 		// GRAM address set
	lcd_WriteReg(0x0021,0x0000);		// GDDRAM address set

	lcd_write_cmd_16bit(0x0022);

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

	lcd_emi_timing_init(emi_7781);


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
	return emi_7781.pwidth+1;
}

u32 lcd_get_h()
{
	return emi_7781.pheight+1;
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
