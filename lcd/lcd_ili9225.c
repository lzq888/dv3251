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

#if(LCD_USE == LCD_ILI9225)
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


const struct emimode emi_ili9225 ={
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
	.pwidth = 220-1,
	.pheight = 176-1,
	.lcd_line_dclks = 220*2-1,
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

//=========ili9225==========
//VCC=VCI=2.8V

lcd_WriteReg(0x10, 0x0000); // Set SAP,DSTB,STB
lcd_WriteReg(0x11, 0x0000); // Set APON,PON,AON,VCI1EN,VC
lcd_WriteReg(0x12, 0x0000); // Set BT,DC1,DC2,DC3
lcd_WriteReg(0x13, 0x0000); // Set GVDD
lcd_WriteReg(0x14, 0x0000); // Set VCOMH/VCOML voltage
Delay_MS(40); // Delay 20 ms

// Please follow this power on sequence
lcd_WriteReg(0x11, 0x0018); // Set APON,PON,AON,VCI1EN,VC
lcd_WriteReg(0x12, 0x6121); // Set BT,DC1,DC2,DC3
lcd_WriteReg(0x13, 0x006F); // Set GVDD
lcd_WriteReg(0x14, 0x495F); // Set VCOMH/VCOML voltage
lcd_WriteReg(0x10, 0x0800); // Set SAP,DSTB,STB
Delay_MS(10); // Delay 10 ms
lcd_WriteReg(0x11, 0x103B); // Set APON,PON,AON,VCI1EN,VC
Delay_MS(50); // Delay 30 ms

lcd_WriteReg(0x01, 0x011C); // set the display line number and display direction
lcd_WriteReg(0x02, 0x0100); // set 1 line inversion
lcd_WriteReg(0x03, 0x1028); // set GRAM write direction and BGR=1.
lcd_WriteReg(0x07, 0x0000); // Display off
lcd_WriteReg(0x08, 0x0808); // set the back porch and front porch
lcd_WriteReg(0x0B, 0x1100); // set the clocks number per line
lcd_WriteReg(0x0C, 0x0000); // CPU interface
lcd_WriteReg(0x0F, 0x0D01); // Set Osc
lcd_WriteReg(0x15, 0x0020); // Set VCI recycling
lcd_WriteReg(0x20, 0x00AF); // RAM Address
//lcd_WriteReg(0x20, 0x0000); // RAM Address
lcd_WriteReg(0x21, 0x0000); // RAM Address

//------------------------ Set GRAM area --------------------------------//
lcd_WriteReg(0x30, 0x0000); 
lcd_WriteReg(0x31, 0x00DB); 
lcd_WriteReg(0x32, 0x0000); 
lcd_WriteReg(0x33, 0x0000); 
lcd_WriteReg(0x34, 0x00DB); 
lcd_WriteReg(0x35, 0x0000); 
lcd_WriteReg(0x36, 0x00AF); 
lcd_WriteReg(0x37, 0x0000); 
lcd_WriteReg(0x38, 0x00DB); 
lcd_WriteReg(0x39, 0x0000); 

// ---------- Adjust the Gamma 2.2 Curve -------------------//
lcd_WriteReg(0x50, 0x0000); 
lcd_WriteReg(0x51, 0x0808); 
lcd_WriteReg(0x52, 0x080A); 
lcd_WriteReg(0x53, 0x000A); 
lcd_WriteReg(0x54, 0x0A08); 
lcd_WriteReg(0x55, 0x0808); 
lcd_WriteReg(0x56, 0x0000); 
lcd_WriteReg(0x57, 0x0A00); 
lcd_WriteReg(0x58, 0x0710); 
lcd_WriteReg(0x59, 0x0710); 

lcd_WriteReg(0x07, 0x0012); 
Delay_MS(50); // Delay 50 ms
lcd_WriteReg(0x07, 0x1017); 

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
	deg_Printf("lcd_init mcu ili9225 \n");
	blcd_FrameEnd_Flag = 0;	
	blcd_writeback_Flag = 0;

	PIN_CONF()						//IO down
	lcd_emi_timing_init(emi_ili9225);

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
	return emi_ili9225.pwidth+1;
}

u32 lcd_get_h()
{
	return emi_ili9225.pheight+1;
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
