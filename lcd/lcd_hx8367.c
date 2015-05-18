/******************** (C) COPYRIGHT 2014 BUILDWIN ************************
* File Name          : lcd_hx8367.c
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

#if(LCD_USE == LCD_HX8367)
//===================================================================
//                                                     	            |
//                      GLOBAL VARIABLE                             |
//                                                                  |
//===================================================================

#define PIN_CONF()    REG32(PF_DIR) &= (~0xff7);  REG32(PF) &= (~0xff7);/*REG32(PG_DIR) &= (~0x1fff)*/;

#define	LCD_WR_SET	REG32(PF) |= (1<<0)    	//写数据			 PF0
#define	LCD_WR_CLR	 REG32(PF)  &= ~(1<<0)	  //写数据			 PF0
#define	LCD_CS_SET  REG32(PF)  |= (1<<1)		  //片选端口  	 PF1
#define	LCD_CS_CLR  REG32(PF)  &= ~(1<<1)	  //片选端口  	 PF1
#define	LCD_RS_CLR	REG32(PF)  &= ~(1<<2) 	//复位清除		 PF2
#define	LCD_RS_SET	REG32(PF)  |= (1<<2) 	//复位使能		 PF2


const struct emimode emi_hx8367 ={
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


static void lcd_WriteReg(u8 cmd,u8 data)
{
	lcd_write_cmd_8bit(cmd);
	lcd_write_parameter_8bit(data);
}

static void lcd_emi_init()
{

//Driving ability Setting 
lcd_WriteReg(0xEA,0x00);  //PTBA[15:8] 
lcd_WriteReg(0xEB,0x00);  //PTBA[7:0] 
lcd_WriteReg(0xEC,0x3C);  //STBA[15:8] 
lcd_WriteReg(0xED,0xC4);  //STBA[7:0] 
lcd_WriteReg(0xE8,0x48);  //OPON[7:0] 
lcd_WriteReg(0xE9,0x38);  //OPON1[7:0] 
lcd_WriteReg(0xF1,0x01);  //OTPS1B 
lcd_WriteReg(0xF2,0x00);  //GEN[7:0] 
lcd_WriteReg(0x27,0xA3);  // 
lcd_WriteReg(0x2E,0x76);  //GDOFF[7:0] 
lcd_WriteReg(0x60,0x08);  //TE ON 
lcd_WriteReg(0x29,0x01);  //RTN[7:0] 
lcd_WriteReg(0x2B,0x02);  //N_DUM[7:0] 
 
//SET PANEL 
lcd_WriteReg(0x3a,0x55);
//lcd_WriteReg(0x36,0x09);  //SS_P);  lcd_WriteData( GS_P);  lcd_WriteData(REV_P);  lcd_WriteData(BGR_P 
//lcd_WriteReg(0x16,0xD0);
lcd_WriteReg(0x36,0x0d);  //SS_P);  lcd_WriteData( GS_P);  lcd_WriteData(REV_P);  lcd_WriteData(BGR_P 
lcd_WriteReg(0x16,0x30);		//180'
//lcd_WriteReg(0x16,0xf0);		//180'

//Gamma 2.2 Setting     
/*
lcd_WriteReg(0x40,0x00); // 
lcd_WriteReg(0x41,0x01); //   
lcd_WriteReg(0x42,0x01); //   
lcd_WriteReg(0x43,0x12); //   
lcd_WriteReg(0x44,0x10); //   
lcd_WriteReg(0x45,0x24); //   
lcd_WriteReg(0x46,0x05); //   
lcd_WriteReg(0x47,0x5B); //   
lcd_WriteReg(0x48,0x03); //   
lcd_WriteReg(0x49,0x11); //   
lcd_WriteReg(0x4A,0x17); //   
lcd_WriteReg(0x4B,0x18); //   
lcd_WriteReg(0x4C,0x19); //   
 
lcd_WriteReg(0x50,0x1B); //   
lcd_WriteReg(0x51,0x2F); //   
lcd_WriteReg(0x52,0x2D); //   
lcd_WriteReg(0x53,0x3E); //   
lcd_WriteReg(0x54,0x3E); //   
lcd_WriteReg(0x55,0x3F); //   
lcd_WriteReg(0x56,0x30); //   
lcd_WriteReg(0x57,0x6E); //   
lcd_WriteReg(0x58,0x06); //   
lcd_WriteReg(0x59,0x07); //   
lcd_WriteReg(0x5A,0x08); //  APPLICATION NOTE Preliminary V01 
lcd_WriteReg(0x5B,0x0E); //   
lcd_WriteReg(0x5C,0x1C); //   
lcd_WriteReg(0x5D,0xCC); // 
*/
//====gamma good======
lcd_WriteReg(0x40,0x01); // 
lcd_WriteReg(0x41,0x0b); //   
lcd_WriteReg(0x42,0x07); //   
lcd_WriteReg(0x43,0x19); //   
lcd_WriteReg(0x44,0x1a); //   
lcd_WriteReg(0x45,0x24); //   
lcd_WriteReg(0x46,0x07); //   
lcd_WriteReg(0x47,0x66); //   
lcd_WriteReg(0x48,0x08); //   
lcd_WriteReg(0x49,0x0d); //   
lcd_WriteReg(0x4A,0x10); //   
lcd_WriteReg(0x4B,0x12); //   
lcd_WriteReg(0x4C,0x1b); //   
 
lcd_WriteReg(0x50,0x1B); //   
lcd_WriteReg(0x51,0x25); //   
lcd_WriteReg(0x52,0x26); //   
lcd_WriteReg(0x53,0x38); //   
lcd_WriteReg(0x54,0x34); //   
lcd_WriteReg(0x55,0x3e); //   
lcd_WriteReg(0x56,0x19); //   
lcd_WriteReg(0x57,0x78); //   
lcd_WriteReg(0x58,0x04); //   
lcd_WriteReg(0x59,0x0d); //   
lcd_WriteReg(0x5A,0x0f); //  APPLICATION NOTE Preliminary V01 
lcd_WriteReg(0x5B,0x12); //   
lcd_WriteReg(0x5C,0x17); //   
lcd_WriteReg(0x5D,0xCC); // 


//Power Voltage Setting 
lcd_WriteReg(0xE2,0x03);   
lcd_WriteReg(0x1B,0x1D);   
lcd_WriteReg(0x1A,0x01);  //BT (VGH~15V);  lcd_WriteData(VGL~-10V);  lcd_WriteData(DDVDH~5V) 
lcd_WriteReg(0x24,0x37);   
lcd_WriteReg(0x25,0x4F);   
//****VCOM offset** 
//lcd_WriteReg(0x23,0x5A);  //for Flicker adjust //can reload from OTP 
lcd_WriteReg(0x23,0x6a);  //0x6a ok
 
//Power on Setting 
lcd_WriteReg(0x18,0x3A);   
lcd_WriteReg(0x19,0x01);  //OSC_EN='1');  lcd_WriteData( start Osc 
lcd_WriteReg(0x01,0x00);  //DP_STB='0');  lcd_WriteData( out deep sleep 
lcd_WriteReg(0x1F,0x88);// GAS=1);  lcd_WriteData( VOMG=0);  lcd_WriteData( PON=0);  lcd_WriteData( DK=1);  lcd_WriteData( XDK=0);  lcd_WriteData( DVDH_TRI=0);  lcd_WriteData( STB=0 
Delay_MS(5); 
lcd_WriteReg(0x1F,0x80);// GAS=1);  lcd_WriteData( VOMG=0);  lcd_WriteData( PON=0);  lcd_WriteData( DK=0);  lcd_WriteData( XDK=0);  lcd_WriteData( DVDH_TRI=0);  lcd_WriteData( STB=0 
Delay_MS(5); 
lcd_WriteReg(0x1F,0x90);// GAS=1);  lcd_WriteData( VOMG=0);  lcd_WriteData( PON=1);  lcd_WriteData( DK=0);  lcd_WriteData( XDK=0);  lcd_WriteData( DVDH_TRI=0);  lcd_WriteData( STB=0 
Delay_MS(5); 
lcd_WriteReg(0x1F,0xD0);// GAS=1);  lcd_WriteData( VOMG=1);  lcd_WriteData( PON=1);  lcd_WriteData( DK=0);  lcd_WriteData( XDK=0);  lcd_WriteData( DDVDH_TRI=0);  lcd_WriteData( STB=0 
Delay_MS(5); 
 
//262k/65k color selection 
lcd_WriteReg(0x17,0x05);  //default 0x06 262k color // 0x05 65k color//0x03 4k color 
 
//Display ON Setting 
lcd_WriteReg(0x28,0x38);      //GON=1);  lcd_WriteData( DTE=1);  lcd_WriteData( D=10 
Delay_MS(50); 
lcd_WriteReg(0x28,0x3C);      //GON=1);  lcd_WriteData( DTE=1);  lcd_WriteData( D=11 

//Set GRAM Area 

lcd_WriteReg(0x02,0x00); 
lcd_WriteReg(0x03,0x00);  //Column Start 
lcd_WriteReg(0x04,0x01); 
lcd_WriteReg(0x05,0x3F);  //Column End 
 
lcd_WriteReg(0x06,0x00); 
lcd_WriteReg(0x07,0x00);  //Row Start 
lcd_WriteReg(0x08,0x00); 
lcd_WriteReg(0x09,0xEF);  //Row End 
 
lcd_write_cmd_8bit(0x22);


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
}


void lcd_init(void) 
{
	deg_Printf("lcd_init mcu hx8367 \n");
	blcd_FrameEnd_Flag = 0;	
	blcd_writeback_Flag = 0;

	PIN_CONF()

	lcd_emi_timing_init(emi_hx8367);

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
	return emi_hx8367.pwidth+1;
}

u32 lcd_get_h()
{
	return emi_hx8367.pheight+1;
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
