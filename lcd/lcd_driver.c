 /******************** (C) COPYRIGHT 2014 BUILDWIN ************************
* File Name          : lcd_driver.c
* Author             :  
* Version            :  
* Date               : 02/27/2014
* Description        : This file provides all the lcd config functions.
***************************************************************************/
//===================================================================
//                                                     	            |
//                       INCLUDE FILES                              |
//                                                                  |
//===================================================================
#include "../header/include.h"

#include "lcd_driver.h"
BOOL volatile blcd_FrameEnd_Flag;		//add for app use it
BOOL volatile blcd_writeback_Flag;
void delay_us(u32 delay_us_cnt)
{
		u32 i, j;
		for (i = 0; i < delay_us_cnt; i++) 
		{
				for (j = 0; j < 50/7; j++) 
				{
					asm ("nop");
				}
		}
}

void delay_ms(u32 delay_ms_cnt) 
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

void lcd_spi_putchar(u8 u8data)
{
    REG32(LCD_DATA) = u8data;
	deg_Printf("lcd_spi_putchar wait spi finish\n");
    while(REG32(LCD_PND)&BIT(BIT_EMI_SPI_BUSY));	// wait data transfer done
	deg_Printf("lcd_spi_putchar wait spi finish ok\n");
}
u8 lcd_spi_getchar(void)
{
    REG32(LCD_DATA) = 0xff;
    while(REG32(LCD_PND)&BIT(BIT_EMI_SPI_BUSY));   
    return REG32(LCD_DATA);
}

void lcd_emi_timing_init(struct emimode p)
{
	REG32(LCD_CFG_RGB) =  BITS(BIT_LCD_CFG_RW, -1+p.red_width)       |
				   BITS(BIT_LCD_CFG_GW, -1+p.green_width)     |
				   BITS(BIT_LCD_CFG_BW, -1+p.blue_width)      |
				   BITS(BIT_LCD_CFG_OO, p.odd_rgb_order)      |
				   BITS(BIT_LCD_CFG_EO, p.even_rgb_order);
	REG32(LCD_CFG_RGB_SHF) = BITS(BIT_RGB_EXPAND_WIDTH, p.expand_width) |
					  BITS(BIT_RGB_EXPAND_LOC, p.expand_loc)     |
					  BITS(BIT_RGB_SHIFT_WIDTH, p.shift_width);		
	REG32(LCD_CFG_DATA_IO) = BITS(BIT_D0_7_OEN, (p.data_en&0xff))       |	// Data 0~7 enabled
					  BITS(BIT_DATA_INV,p.data_inv)              |
					  //BITS(BIT_DATA_DLY,0)                     |	
					  0;
	REG32(LCD_CFG_DATA_HI) = (p.data_en >> 8);  						        			          				       
	REG32(LCD_CFG_EMI) = BITS(BIT_CS_PR, p.cs_pr)           |
				  BITS(BIT_WR_PR, p.wr_rp)           |
				  BITS(BIT_WR_FR, p.wr_fp)           |
				  BITS(BIT_CS_INV, p.cs_inv)         |
				  BITS(BIT_WR_INV, p.wr_inv)         |
				  BITS(BIT_CS_OEN, p.cs_oen)      	 |
				  BITS(BIT_DATACTRL_MODE, p.datactrl_mode);
	REG32(LCD_CFG_CLK_TIM) = BITS(BIT_CLKDIV, p.clkdiv)                          |
					  BITS(BIT_DIV2_DUTY, p.div2_duty);    //LCDCON6
	REG32(LCD_LINE_PIXELS) = p.pwidth;
	REG32(LCD_FRAME_LINES) = p.pheight;	
	REG32(LCD_LINE_DCLKS) = p.lcd_line_dclks;
	REG32(LCD_YUV2RGB) = BIT(BIT_WARP_EN)                        |
				  BITS(BIT_WARP_K, 4)                     |
				  BITS(BIT_ROTATEMODE, p.rotatemode)      |
				  BITS(BIT_MIRROR, p.mirror)              |
				  BITS(BIT_Y_MINUS_0,p.yminus16)          |
				  //BIT(BIT_YCbCr)                        | 
				  0;
	REG32(LCD_DMA_INTERVAL) = p.interval;	
	
	REG32(LCD_CFG) &= ~BIT(BIT_LCD_EN);
	REG32(LCD_CFG) &= ~BITS(BIT_LCD_IF,0x03);
	REG32(LCD_CFG) |= BITS(BIT_LCD_IF, LCD_IF_EMI);                
	REG32(LCD_CFG) |= BIT(BIT_LCD_EN);
	
	//REG32(LCD_CFG) |= BITS(BIT_LCD_IF, LCD_IF_EMI) |
	//		   BIT(BIT_LCD_EN);  
}

void lcd_spirgb_timing_init(struct spirgbmode p)
{			
	REG32(LCD_CFG_RGB) = BITS(BIT_LCD_CFG_RW, -1+p.red_width)                  |
				  BITS(BIT_LCD_CFG_GW, -1+p.green_width)                |
				  BITS(BIT_LCD_CFG_BW, -1+p.blue_width)                 | 
				  BITS(BIT_LCD_CFG_OO, p.odd_rgb_order)                 |
				  BITS(BIT_LCD_CFG_EO, p.even_rgb_order);
	REG32(LCD_CFG_RGB_SHF) = BITS(BIT_RGB_EXPAND_WIDTH, p.expand_width)        |
					  BITS(BIT_RGB_EXPAND_LOC, p.expand_loc)            |
					  BITS(BIT_RGB_SHIFT_WIDTH, p.shift_width);
	REG32(LCD_CFG_OUT_CLK) = BITS(BIT_VSYNC_EN, p.vsync_en)               |
					  BITS(BIT_HSYNC_EN, p.hsync_en)               |
					  BITS(BIT_DE_EN, p.de_en)                     |
					  BITS(BIT_DCLK_EN, p.dclk_en)                 |
					  BITS(BIT_VSYNC_INV, p.vsync_inv)             |
					  BITS(BIT_HSYNC_INV, p.hsync_inv)             |
					  BITS(BIT_DE_INV, p.de_inv)                   |
					  BITS(BIT_DCLK_INV, p.dclk_inv);

	REG32(LCD_CFG_DATA_IO) = BITS(BIT_D0_7_OEN, (p.data_en&0xff))         |	// Data 0~7 enabled
					  BITS(BIT_DATA_INV,p.data_inv)                |
						//BITS(BIT_DATA_DLY,0)                     |	
						0;	

	REG32(LCD_CFG_DATA_HI) = (p.data_en >> 8); 

	REG32(LCD_CFG_CLK_TIM) = BITS(BIT_VSYNC_INACT_AT, p.vsync_inact_at)          |
					  BITS(BIT_VSYNC_UP_NEG_EDGE, p.vsync_up_neg_edge)    |
					  BITS(BIT_HSYNC_UP_NEG_EDGE, p.hsync_up_neg_edge)    |
					  BITS(BIT_DE_UP_NEG_EDGE, p.de_up_neg_edge)          |
					  BITS(BIT_CLKDIV, p.clkdiv)                          |
					  BITS(BIT_DIV2_DUTY, p.div2_duty)                    |
					  BITS(BIT_HOLDCLK_EN, p.holdclk_en)                  |
					  BITS(BIT_SLOWDNCLK_EN, p.slowdnclk_en)              |
					  BITS(BIT_SLOWDNCNT_EN, p.slowdncnt_en)              |
					  BITS(BIT_VIDEO_SLOWDN_C_EN, p.video_slowdn_c)       |
					  BITS(BIT_OSD_SLOWDN_C_EN, p.osd_slowdn_c);    //LCDCON6
	REG32(LCD_VS_RISING)   = p.vsrp - 1;          //LCDCON7
	REG32(LCD_HS_RISING)   = p.hsrp - 1;          //LCDCON8
	REG32(LCD_DE_RISING)   = p.hbpd - 1;          //LCDCON9
	REG32(LCD_VS_FALLING)  = p.vspw - 1;          //LCDCON10
	REG32(LCD_HS_FALLING)  = p.hspw - 1;          //LCDCON11
	REG32(LCD_DE_FALLING)  = p.hbpd + p.hozval - 1;        //LCDCON12
	REG32(LCD_DE_START)    = p.vbpd -1;                     //LCDCON13
	REG32(LCD_DE_END)      = p.vbpd + p.lineval - 1;        //LCDCON14 

									  
	REG32(LCD_CFG_EMI) = BITS(BIT_CS_PR, p.cs_pr)           |
				  //BITS(BIT_WR_PR, p.wr_rp)         |
				  //BITS(BIT_WR_FR, p.wr_fp)         |
				  BITS(BIT_CS_INV, p.cs_inv)         |
				  //BITS(BIT_WR_INV, p.wr_inv)       |
				  BITS(BIT_CS_OEN, p.cs_oen)      	 |
				  BITS(BIT_DATACTRL_MODE, p.datactrl_mode);
	REG32(LCD_CFG_SPI) = BITS(BIT_SPI_ID_ST, p.spi_id_st)        |
				  BITS(BIT_SPI_SMP_SEL, p.spi_smp_sel)    |
				  BITS(BIT_SPI_1DW, p.spi_1dw)            |
				  BITS(BIT_SPI_1DW_DIR, p.spi_1dw_dir)    |
				  BITS(BIT_SPI_9BITEN, p.spi_9biten)      |
				  BITS(BIT_SPI_9BIT, p.spi_9bit);	
	REG32(LCD_SPI_BAUD) = BITS(BIT_SPI_BAUD, p.spi_baud);   
	REG32(LCD_LINE_PIXELS) = p.hbpd + p.hozval + p.hfpd - 1;
	REG32(LCD_FRAME_LINES) = p.vbpd + p.lineval + p.vfpd - 1;	
	REG32(LCD_LINE_DCLKS) = (p.hbpd + p.hozval + p.hfpd)*3 - 1;
	REG32(LCD_YUV2RGB) = BIT(BIT_WARP_EN)                        |
				  BITS(BIT_WARP_K, 4)                     |
				  BITS(BIT_ROTATEMODE, p.rotatemode)      |
				  BITS(BIT_MIRROR, p.mirror)              |
				  BITS(BIT_Y_MINUS_0,p.yminus16)          |
				  //BIT(BIT_YCbCr)                        | 
				  0;
	REG32(LCD_DMA_INTERVAL) = p.interval;			

	REG32(LCD_CFG) &= ~BIT(BIT_LCD_EN);
	REG32(LCD_CFG) &= ~BITS(BIT_LCD_IF,0x03);
	REG32(LCD_CFG) |= BITS(BIT_LCD_IF, LCD_IF_SPI);                
	REG32(LCD_CFG) |= BIT(BIT_LCD_EN);
  
	//REG32(LCD_CFG) |= BITS(BIT_LCD_IF, LCD_IF_SPI)|
	//		   BIT(BIT_LCD_EN); 

}

void lcd_rgb_timing_init(struct rgbmode p)
{			
	REG32(LCD_CFG_RGB) =  BITS(BIT_LCD_CFG_RW, -1+p.red_width)       |
				   BITS(BIT_LCD_CFG_GW, -1+p.green_width)     |
				   BITS(BIT_LCD_CFG_BW, -1+p.blue_width)      |
				   BITS(BIT_LCD_CFG_OO, p.odd_rgb_order)      |
				   BITS(BIT_LCD_CFG_EO, p.even_rgb_order);
	REG32(LCD_CFG_RGB_SHF) =	BITS(BIT_RGB_EXPAND_WIDTH, p.expand_width) |
						BITS(BIT_RGB_EXPAND_LOC, p.expand_loc)     |
						BITS(BIT_RGB_SHIFT_WIDTH, p.shift_width);
	REG32(LCD_CFG_OUT_CLK) = BITS(BIT_VSYNC_EN, p.vsync_en)       |
					  BITS(BIT_HSYNC_EN, p.hsync_en)       |
					  BITS(BIT_DE_EN, p.de_en)             |
					  BITS(BIT_DCLK_EN, p.dclk_en)         |
					  BITS(BIT_VSYNC_INV, p.vsync_inv)     |
					  BITS(BIT_HSYNC_INV, p.hsync_inv)     |
					  BITS(BIT_DE_INV, p.de_inv)           |
					  BITS(BIT_DCLK_INV, p.dclk_inv);
				  
	REG32(LCD_CFG_DATA_IO) =	BITS(BIT_D0_7_OEN, (p.data_en&0xff)) |	// Data 0~7 enabled
						BITS(BIT_DATA_INV,p.data_inv)        |
						//BITS(BIT_DATA_DLY,0)               |	
							0;	
    REG32(LCD_CFG_DATA_HI) = (p.data_en >> 8); 
    
    REG32(LCD_CFG_CLK_TIM) = BITS(BIT_VSYNC_INACT_AT, p.vsync_inact_at)          |
					  BITS(BIT_VSYNC_UP_NEG_EDGE, p.vsync_up_neg_edge)    |
					  BITS(BIT_HSYNC_UP_NEG_EDGE, p.hsync_up_neg_edge)    |
					  BITS(BIT_DE_UP_NEG_EDGE, p.de_up_neg_edge)          |
					  BITS(BIT_CLKDIV, p.clkdiv)                          |
					  BITS(BIT_DIV2_DUTY, p.div2_duty)                    |
					  BITS(BIT_HOLDCLK_EN, p.holdclk_en)                  |
					  BITS(BIT_SLOWDNCLK_EN, p.slowdnclk_en)              |
					  BITS(BIT_SLOWDNCNT_EN, p.slowdncnt_en)              |
					  BITS(BIT_VIDEO_SLOWDN_C_EN, p.video_slowdn_c)       |
					  BITS(BIT_OSD_SLOWDN_C_EN, p.osd_slowdn_c);    //LCDCON6
    REG32(LCD_VS_RISING)   = p.vsrp - 1;          //LCDCON7
    REG32(LCD_HS_RISING)   = p.hsrp - 1;          //LCDCON8
    REG32(LCD_DE_RISING)   = p.hbpd - 1;          //LCDCON9
    REG32(LCD_VS_FALLING)  = p.vspw - 1;          //LCDCON10
    REG32(LCD_HS_FALLING)  = p.hspw - 1;          //LCDCON11
    REG32(LCD_DE_FALLING)  = p.hbpd + p.hozval - 1;        //LCDCON12
    REG32(LCD_DE_START)    = p.vbpd -1;                     //LCDCON13
    REG32(LCD_DE_END)      = p.vbpd + p.lineval - 1;        //LCDCON14 
		
	REG32(LCD_LINE_PIXELS) = p.hbpd + p.hozval + p.hfpd - 1;
	REG32(LCD_FRAME_LINES) = p.vbpd + p.lineval + p.vfpd - 1;	
	REG32(LCD_LINE_DCLKS) =  p.hbpd + p.hozval + p.hfpd - 1;
    REG32(LCD_YUV2RGB) =	BIT(BIT_WARP_EN)                        |
					BITS(BIT_WARP_K, 4)                     |
					BITS(BIT_ROTATEMODE, p.rotatemode)      |
					BITS(BIT_MIRROR, p.mirror)              |
					BITS(BIT_Y_MINUS_0,p.yminus16)          |
					//BIT(BIT_YCbCr)                        | 
						  0;
	REG32(LCD_DMA_INTERVAL) = p.interval;	
	
	REG32(LCD_CFG) &= ~BIT(BIT_LCD_EN);
	REG32(LCD_CFG) &= ~BITS(BIT_LCD_IF,0x03);
	REG32(LCD_CFG) |= BITS(BIT_LCD_IF, LCD_IF_RGB);                
	REG32(LCD_CFG) |= BIT(BIT_LCD_EN);
	//REG32(LCD_CFG) |= BITS(BIT_LCD_IF, LCD_IF_RGB)                |
	//		   BIT(BIT_LCD_EN); 

}
void datactrl_mode_sel()
{
	REG32(LCD_CFG) &= ~BIT(BIT_LCD_EN);
	REG32(LCD_CFG_EMI) &= ~BITS(BIT_DATACTRL_MODE, 1);
	REG32(LCD_CFG) |= BIT(BIT_LCD_EN);  
}
void spi_to_rgb()
{
	REG32(LCD_CFG) &= ~BIT(BIT_LCD_EN);
	REG32(LCD_CFG) = BITS(BIT_LCD_IF, LCD_IF_RGB);
	REG32(LCD_CFG) |= BIT(BIT_LCD_EN);  
}

void reset_rgb_data_en(u32 data_en)
{
    REG32(LCD_CFG_DATA_IO) =	BITS(BIT_D0_7_OEN, (data_en&0xff)) |	// Data 0~7 enabled
						BITS(BIT_DATA_INV,0)        |
							0;	
    REG32(LCD_CFG_DATA_HI) = (data_en >> 8); 
}

void waittingLcdFrameEnd()
{
#if  (USER_CONFIG==CONFIG_AX3251_AIRBORNE)
	u32 timeout = 200000;
	blcd_FrameEnd_Flag = 0;
	while ((blcd_FrameEnd_Flag == 0) && --timeout );
	
#else
	u32 timeout = 0xffffff;
	blcd_FrameEnd_Flag = 0;
	while (blcd_FrameEnd_Flag == 0 && --timeout );
	if(timeout == 0)
		deg_Printf("waittingLcdFrame Timeout\n");
#endif
}



