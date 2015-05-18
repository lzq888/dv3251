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

#if(LCD_USE == LCD_HX8312)
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


const struct emimode emi_8312 ={
	.red_width = 6,
	.green_width = 6,
	.blue_width = 6,
	.even_rgb_order = ORDER_RGB,
	.odd_rgb_order = ORDER_RGB,

	.shift_width = 8,
	.expand_loc = 0,			//last byte  is bit7 bit6 active ,set it 0, or bit1 bit0 active set it 2
	.expand_width = 6,	
	.datactrl_mode = 1,				
	.cs_oen = 1,
	.wr_inv = 1,						// wr  pin high is idle
	.cs_inv = 1,						// cs pin high is idle 
	.wr_fp = 7,
	.wr_rp = 4,
	.cs_pr = 0x20, 
	.data_en = 0xff,
	.data_inv = 0,						//
	.clkdiv = 8,					//pixel clk
	.pwidth = 320-1,
	.pheight = 240-1,
	.lcd_line_dclks = 320*3-1,
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

static void lcd_write_parameter_18bit(u32 data)
{
	LCD_RS_SET;
	delay_us(1);
	lcd_write_data(((data>>10)&0xff));
	delay_us(1);
	lcd_write_data(((data>>2)&0xff));
	delay_us(1);
	lcd_write_data(data&0x03);
}

static void lcd_WriteReg(u16 cmd,u16 data)
{
	lcd_write_cmd_8bit(cmd);
	lcd_write_cmd_8bit(data);
}


static void lcd_emi_init()
{

	//start oscillation
	lcd_WriteReg(0x59,0x01);
 	lcd_WriteReg(0x60,0x22);
	lcd_WriteReg(0x59,0x00);
 
 	lcd_WriteReg(0x00,0xa0);
 	lcd_WriteReg(0x01,0x10);
  
 	lcd_WriteReg(0x02,0x00);
 	lcd_WriteReg(0x05,0x00);
 	lcd_WriteReg(0x06,0x00);
 	lcd_WriteReg(0x07,0x00);
 	lcd_WriteReg(0x0d,0x00);
 	lcd_WriteReg(0x2B,0x00);
 	lcd_WriteReg(0x9D,0x00);
	lcd_WriteReg(0x1D,0x08);
 	lcd_WriteReg(0x86,0x00);
 	lcd_WriteReg(0x87,0x3F);
 	lcd_WriteReg(0x88,0x02);
 	lcd_WriteReg(0x89,0x05);
 	lcd_WriteReg(0x8D,0x01);
 	lcd_WriteReg(0x8B,0x2b); /////2B  80HZ

 	lcd_WriteReg(0x33,0x01);
 	lcd_WriteReg(0x37,0x01);
 	lcd_WriteReg(0x76,0x00);
 
 	lcd_WriteReg(0x0E,0x00);
 	lcd_WriteReg(0x0F,0x00);
 	lcd_WriteReg(0x10,0x00);
 	lcd_WriteReg(0x11,0x00);
 	lcd_WriteReg(0x12,0x00);
 	lcd_WriteReg(0x13,0x1A);
 	lcd_WriteReg(0x14,0x00);
 	lcd_WriteReg(0x15,0x07);
 	lcd_WriteReg(0x16,0x00);
 	lcd_WriteReg(0x17,0x11);
 	lcd_WriteReg(0x34,0x01);
 	lcd_WriteReg(0x35,0x00);
 	lcd_WriteReg(0x4B,0x00);
 	lcd_WriteReg(0x4C,0x00);
 	lcd_WriteReg(0x4D,0x00);
 	lcd_WriteReg(0x4E,0x00);
 	lcd_WriteReg(0x4F,0x00);
 	lcd_WriteReg(0x50,0x00);

 	lcd_WriteReg(0x42,0x00);
 	lcd_WriteReg(0x43,0x00);
 	lcd_WriteReg(0x44,0x00);
 	lcd_WriteReg(0x45,0x00);
 	lcd_WriteReg(0x46,0xEF);
 	lcd_WriteReg(0x47,0x00);
 	lcd_WriteReg(0x48,0x00);
 	lcd_WriteReg(0x49,0x01);
 	lcd_WriteReg(0x4A,0x3F);

 	lcd_WriteReg(0x2C,0x00);
 	lcd_WriteReg(0x3C,0x00);
 	lcd_WriteReg(0x3D,0x00);
 	lcd_WriteReg(0x3E,0x01);
 	lcd_WriteReg(0x3F,0x3F);
 	lcd_WriteReg(0x40,0x02);
 	lcd_WriteReg(0x41,0x02);
 //////////////////////////////gamma///////////
 
 	lcd_WriteReg(0x8F,0x00);
 	lcd_WriteReg(0x90,0x46);
 	lcd_WriteReg(0x91,0x05);
 	lcd_WriteReg(0x92,0x41);
 	lcd_WriteReg(0x93,0x27);
 	lcd_WriteReg(0x94,0x13);
 	lcd_WriteReg(0x95,0x77);
 	lcd_WriteReg(0x96,0x14);
 	lcd_WriteReg(0x97,0x08);
 	lcd_WriteReg(0x98,0x06);
 	lcd_WriteReg(0x99,0x07);
 	lcd_WriteReg(0x9A,0x08);


//////////////////////////////gamma/////////////
 	lcd_WriteReg(0xC0,0x00);
 	lcd_WriteReg(0xC1,0x01);      //tangjie change 0x01 to 0x00

 	lcd_WriteReg(0x28,0x18);	   	  
 	lcd_WriteReg(0x1A,0x00);	//improve driving cability
 	lcd_WriteReg(0x1C,0x33);
 	lcd_WriteReg(0x55,0x08);
 	lcd_WriteReg(0x24,0x74);
 	lcd_WriteReg(0x25,0x07);

 	lcd_WriteReg(0x19,0x00); ////////////
 	lcd_WriteReg(0x18,0xC1);

 	Delay_MS(15);
 	lcd_WriteReg(0x1E,0x01);
 	lcd_WriteReg(0x18,0xC5);
 	lcd_WriteReg(0x18,0xE5);

 	Delay_MS(60);
 	lcd_WriteReg(0x18,0xF5);
 	Delay_MS(60);

 	lcd_WriteReg(0x1B,0x09);	
 	Delay_MS(15);

 	lcd_WriteReg(0x1F,0x0e);
	lcd_WriteReg(0x20,0x0a);
 	lcd_WriteReg(0x1e,0x81);

 	Delay_MS(15);

 	lcd_WriteReg(0x3b,0x01);
 	Delay_MS(15);

//=======set x========
	lcd_WriteReg(0x45,0x00);
 	lcd_WriteReg(0x46,0xef);

//=======set y========
	lcd_WriteReg(0x47,0x00);
 	lcd_WriteReg(0x48,0x00);
	lcd_WriteReg(0x49,0x01);
 	lcd_WriteReg(0x4a,0x3f);
//===================
 	lcd_WriteReg(0x05,0x14);		//

 	lcd_WriteReg(0x00,0x20);     //change 0x20->0xa0			//0x22 start display
 	

 	lcd_WriteReg(0x42,0x00);        //ram set
 	lcd_WriteReg(0x43,0x00);	  //ram set
 	lcd_WriteReg(0x44,0x00);        //ram set


/*
lcd_WriteReg(0x0001,0x0010); // Start oscillation
lcd_WriteReg(0x0000,0x00A0); // Standby mode cancel
lcd_WriteReg(0x0003,0x0001); // Software reset operation
Delay_MS(10);
lcd_WriteReg(0x0003,0x0000); // Software reset operation cancel
lcd_WriteReg(0x002B,0x0004); // Oscillator frequency adjust setting
lcd_WriteReg(0x0028,0x0018); // DC/DC clock frequency adjust setting
lcd_WriteReg(0x001A,0x0005); // Step up circuit frequency adjust setting
lcd_WriteReg(0x0025,0x0005); // Step up factor in step up circuit 2 setting
lcd_WriteReg(0x0019,0x0000); // VR1 and VR2 regulator factor setting
//############# void Power_on_Set(void) ################//
lcd_WriteReg(0x001C,0x0073); // Step up circuit operating current setting
lcd_WriteReg(0x0024,0x0074); // V18 and VCOM regulator current setting
lcd_WriteReg(0x001E,0x0001); // Extra step up circuit1 operation
lcd_WriteReg(0x0018,0x00C1); // VR1 and VR2 regulator on
Delay_MS(10);
lcd_WriteReg(0x0018,0x00E1); // VCL turn on
lcd_WriteReg(0x0018,0x00F1); // VGH and VGL turn on
Delay_MS(60);
lcd_WriteReg(0x0018,0x00F5); // DDVDH turn on
Delay_MS(60);
lcd_WriteReg(0x001B,0x0009); // VS/VDH turn on and set
Delay_MS(10);
lcd_WriteReg(0x001F,0x0011); // VCOM amplitude voltage setting
lcd_WriteReg(0x0020,0x000E); // VCOMH voltage setting
lcd_WriteReg(0x001E,0x0081); // VCOM operation start
Delay_MS(10);
//############# void Chip_Set (void) ################//
lcd_WriteReg(0x009D,0x0000);
lcd_WriteReg(0x00C0,0x0000);
lcd_WriteReg(0x00C1,0x0000); // BGR bit = ��0�� Note 2
lcd_WriteReg(0x000E,0x0000);
lcd_WriteReg(0x000F,0x0000);
lcd_WriteReg(0x0010,0x0000);
lcd_WriteReg(0x0011,0x0000);
lcd_WriteReg(0x0012,0x0000);
lcd_WriteReg(0x0013,0x0000);
lcd_WriteReg(0x0014,0x0000);
lcd_WriteReg(0x0015,0x0000);
lcd_WriteReg(0x0016,0x0000);
lcd_WriteReg(0x0017,0x0000);
lcd_WriteReg(0x0034,0x0001);
lcd_WriteReg(0x0035,0x0000);
lcd_WriteReg(0x004B,0x0000);
lcd_WriteReg(0x004C,0x0000);
lcd_WriteReg(0x004E,0x0000);
lcd_WriteReg(0x004F,0x0000);
lcd_WriteReg(0x0050,0x0000);
lcd_WriteReg(0x003C,0x0000);
lcd_WriteReg(0x003D,0x0000);
lcd_WriteReg(0x003E,0x0001);
lcd_WriteReg(0x003F,0x003F);
lcd_WriteReg(0x0040,0x0002);
lcd_WriteReg(0x0041,0x0002);
lcd_WriteReg(0x0042,0x0000);
lcd_WriteReg(0x0043,0x0000);
lcd_WriteReg(0x0044,0x0000);
lcd_WriteReg(0x0045,0x0000);
lcd_WriteReg(0x0046,0x00EF);
lcd_WriteReg(0x0047,0x0000);
lcd_WriteReg(0x0048,0x0000);
lcd_WriteReg(0x0049,0x0001);
lcd_WriteReg(0x004A,0x003F);
lcd_WriteReg(0x001D,0x0008); // Gate scan direction setting
lcd_WriteReg(0x0086,0x0000);
lcd_WriteReg(0x0087,0x0030);
lcd_WriteReg(0x0088,0x0002);
lcd_WriteReg(0x0089,0x0005);
lcd_WriteReg(0x008D,0x0001); // Register set-up mode for one line clock number
lcd_WriteReg(0x008B,0x0030); // One line SYSCLK number in one-line scan
lcd_WriteReg(0x0033,0x0001); // N line inversion setting
lcd_WriteReg(0x0037,0x0001); // Scanning method setting
lcd_WriteReg(0x0076,0x0000);
//############# void Gamma_Set(void) ################//
lcd_WriteReg(0x008F,0x0010);
lcd_WriteReg(0x0090,0x0067);
lcd_WriteReg(0x0091,0x0007);
lcd_WriteReg(0x0092,0x0065);
lcd_WriteReg(0x0093,0x0007);
lcd_WriteReg(0x0094,0x0001);
lcd_WriteReg(0x0095,0x0076);
lcd_WriteReg(0x0096,0x0056);
lcd_WriteReg(0x0097,0x0000);
lcd_WriteReg(0x0098,0x0000);
lcd_WriteReg(0x0099,0x0000);
lcd_WriteReg(0x009A,0x0000);
//############# void Display_On(void) ################//
lcd_WriteReg(0x003B,0x0001);
Delay_MS(40);
lcd_WriteReg(0x0000,0x0020);
*/


}

static void lcd_clean_screen(void)
{
	int j, k;  

	for(j=0; j<LCD_HEIGHT; j++)
	{
		for(k=0; k<LCD_WIDTH; k++)
		{
			lcd_write_parameter_18bit(0x00000);
		}
	}

/*
//========color bar ok========
	for(j=0; j<LCD_HEIGHT; j++)
	{
		for(k=0; k<LCD_WIDTH/3; k++)
		{
			lcd_write_parameter_18bit(0x3f000);
		}
		for(k=LCD_WIDTH/3; k<LCD_WIDTH*2/3; k++)
		{
			lcd_write_parameter_18bit(0x00fc0);	
		}
		for(k=LCD_WIDTH*2/3; k<LCD_WIDTH; k++)
		{
			lcd_write_parameter_18bit(0x0003f);
		}
	}
*/
}


void lcd_init(void) 
{
	deg_Printf("lcd_init mcu emi_8312 \n");
	blcd_FrameEnd_Flag = 0;	
	blcd_writeback_Flag = 0;

	PIN_CONF()						//IO down
	
	lcd_emi_timing_init(emi_8312);


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
	return emi_8312.pwidth+1;
}

u32 lcd_get_h()
{
	return emi_8312.pheight+1;
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
