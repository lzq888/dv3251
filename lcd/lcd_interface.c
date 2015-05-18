#include "../header/include.h"
#include "lcd_interface.h"

/************************************************************************
 *Description: 设置EMI接口屏osd1层的正常显示

 *Parameters:  stx ，sty ：osd1窗口的左上角的坐标
               gImage_width  ：原图的列数
               gImage_height ：原图的行数
               *gImage_osd   ：原图数据的首地址
               alpha ：透明度
               mode  : 0表示选择osd层的透明度；1表示选择调色板的透明度
 *Return value: 无
*************************************************************************/
void lcd_emi_osd1_display(u16 osd_x, u16 osd_y, u16 gImage_width ,u16 gImage_height,
                     u32 *gImage_osd, u16 alpha, u8 mode) 
{
    save_osd_palette(OSD1_LUT_ADR,(u32 *)(&gImage_palette[0]),alpha);
    save_osd_index((u32)(OFFSET(gImage_osd)),gImage_osd, gImage_width*gImage_height);
    set_osd1_address((u32)(OFFSET(gImage_osd)));
    if(0 == mode)
    {
        save_osd_palette(OSD1_LUT_ADR,(u32 *)(&gImage_palette[0]),0);
        lcd_emi_osd1_set_window(osd_x,osd_y,osd_x+gImage_width,osd_y+gImage_height,alpha,1);
    }   	   
    else
    {
        save_osd_palette(OSD1_LUT_ADR,(u32 *)(&gImage_palette[0]),alpha);
    	  lcd_emi_osd1_set_window(osd_x,osd_y,osd_x+gImage_width,osd_y+gImage_height,0x100,1);   
    }
    	  	
}
/************************************************************************
 *Description: 设置EMI接口屏osd2层的正常显示

 *Parameters:  stx ，sty ：osd2窗口的左上角的坐标
               gImage_width  ：原图的列数
               gImage_height ：原图的行数
               *gImage_osd   ：原图数据的首地址
               alpha ：透明度
               mode  : 0表示选择osd层的透明度；1表示选择调色板的透明度
 *Return value: 无
*************************************************************************/
void lcd_emi_osd2_display(u16 osd_x, u16 osd_y, u16 gImage_width ,u16 gImage_height,
                     u32 *gImage_osd, u16 alpha,u8 mode) 
{
    save_osd_index((u32)(OFFSET(gImage_osd)),gImage_osd, gImage_width*gImage_height);
    set_osd2_address((u32)(OFFSET(gImage_osd)));
    if(0 == mode)
    {
        save_osd_palette(OSD2_LUT_ADR,(u32 *)(&gImage_palette[0]),0);
        lcd_emi_osd2_set_window(osd_x,osd_y,osd_x+gImage_width,osd_y+gImage_height,alpha,1);
    }   	   
    else
    {
        save_osd_palette(OSD2_LUT_ADR,(u32 *)(&gImage_palette[0]),alpha);
    	  lcd_emi_osd2_set_window(osd_x,osd_y,osd_x+gImage_width,osd_y+gImage_height,0x100,1);   
    }    
}
/************************************************************************
 *Description: 设置EMI接口屏osd3层的正常显示

 *Parameters:  stx ，sty ：osd3窗口的左上角的坐标
               gImage_width  ：原图的列数
               gImage_height ：原图的行数
               *gImage_osd   ：原图数据的首地址
               alpha ：透明度
               mode  : 0表示选择osd层的透明度；1表示选择调色板的透明度
 *Return value: 无
*************************************************************************/
void lcd_emi_osd3_display(u16 osd_x, u16 osd_y, u16 gImage_width ,u16 gImage_height,
                     u32 *gImage_osd, u16 alpha, u8 mode) 
{
    save_osd_index((u32)(OFFSET(gImage_osd)),gImage_osd, gImage_width*gImage_height);
    set_osd3_address((u32)(OFFSET(gImage_osd)));
    if(0 == mode)
    {
        save_osd_palette(OSD3_LUT_ADR,(u32 *)(&gImage_palette[0]),0);
        lcd_emi_osd3_set_window(osd_x,osd_y,osd_x+gImage_width,osd_y+gImage_height,alpha,1);
    }   	   
    else
    {
        save_osd_palette(OSD3_LUT_ADR,(u32 *)(&gImage_palette[0]),alpha);
    	  lcd_emi_osd3_set_window(osd_x,osd_y,osd_x+gImage_width,osd_y+gImage_height,0x100,1);   
    }  
}

/************************************************************************
 *Description: 设置EMI接口屏video层的正常显示

 *Parameters:  stx ，sty ：video窗口的左上角的坐标
               gImage_width  ：原图的列数
               gImage_height ：原图的行数
               *gImage_osd   ：原图数据的首地址

 *Return value: 无
*************************************************************************/
void lcd_emi_video_display_normal(u16 video_x, u16 video_y,u16 gImage_width ,u16 gImage_height,
                     u32 *gImage_video)
{
    lcd_rgb2yuv((u32)(OFFSET(gImage_video)),gImage_video,gImage_width,gImage_height);
    set_video_address((u32)(OFFSET(gImage_video)));
    lcd_emi_video_normal(video_x,video_y,gImage_width,gImage_height,1);
}
/************************************************************************
 *Description: 设置EMI接口屏video层的正常显示

 *Parameters:  stx ，sty ：video窗口的左上角的坐标
               s_width  ：原图的列数
               s_height ：原图的行数
               d_width  ：缩放后图片的列数
               d_height ：缩放后图片的行数
               w_step : 宽度步进整数部分, W_step=原图宽度*0x100/缩放后图宽度
               w_remain : 宽度步进小数部分, W_remain=原图宽度*0x100-缩放后图宽度*W_step
               h_step : 高度步进整数部分, H_step=原图高度*0x100/缩放后图高度
               h_remain : 高度步进小数部分, H_remain=原图高度*0x100-缩放后图高度*H_step
               *gImage_video   ：原图数据的首地址

 *Return value: 无
*************************************************************************/
void lcd_emi_video_display_zoom(u16 video_x,u16 video_y,u16 s_width,u16 s_height,u16 d_width, u16 d_height,
                      u16 w_step,u16 w_remain,u16 h_step,u16 h_remain,u32 *gImage_video)
{
    lcd_rgb2yuv((u32)(OFFSET(gImage_video)),gImage_video,s_width,s_height);
    set_video_address((u32)(OFFSET(gImage_video)));
    lcd_emi_video_zoom(video_x, video_y, s_width, s_height, d_width, d_height,
                               w_step, w_remain, h_step, h_remain, 1);
}
/************************************************************************
 *Description: 回写数据

 *Parameters:  adr   ：回写数据存放的首地址
               gImage_width  ：原图的列数
               gImage_height ：原图的行数

 *Return value: 无
*************************************************************************/
void lcd_writeback(u32 adr,u16 gImage_width ,u16 gImage_height)
 {
 	  u32 i;
	 	for(i=0; i<=(gImage_height/8); i++)   //若不够整除，多回写的8行可以存放余下的数据
    {		
    	  REG32(LCDCON61) = adr+(gImage_width*8/2)*4*i;	
    	  REG32(LCDCON0)  |= (1<<14);            //kick start	
		    while((REG32(LCDCON57)&(1<<2))==0);		//waiting writeback pending	    
		    REG32(LCDCON57) |= 0x4;                //clear writeback pending
	  } 
    REG32(LCDCON0) &= ~(1 << 7);              //clear writeback_en bit
    REG32(LCDCON0) &= ~(1 << 6);              //clear video_en bit  
}
/************************************************************************
 *Description: 设置EMI接口屏video层的回写显示

 *Parameters:  stx ，sty ：video窗口的左上角的坐标
               gImage_width  ：原图的列数
               gImage_height ：原图的行数
               adr   ：回写数据存放的首地址

 *Return value: 无
*************************************************************************/
void lcd_emi_video_display_wbdata(u16 video_x, u16 video_y,u16 gImage_width ,u16 gImage_height,u32 adr)
{ 
	  REG32(LCDCON0) &= ~(1 << 6);             //clear video_en bit
	  while((REG32(LCDCON57)&(1<<0))==0);      //waiting 1 frame pending	
    set_video_address(adr);
    lcd_emi_video_normal(video_x,video_y,gImage_width,gImage_height,1);
    REG32(LCDCON0) |= (1 << 6);              //set video_en bit
	REG32(LCDCON57) |= 1;                    //clear 1 frame pending
}
/************************************************************************
 *Description: 设置RGB接口屏osd1层的正常显示

 *Parameters:  stx ，sty ：osd1窗口的左上角的坐标
               gImage_width  ：原图的列数
               gImage_height ：原图的行数
               *gImage_osd   ：原图数据的首地址
               alpha ：透明度
               mode  : 0表示选择osd层的透明度；1表示选择调色板的透明度
 *Return value: 无
*************************************************************************/
void lcd_rgb_osd1_display(u16 osd_x, u16 osd_y, u16 gImage_width ,u16 gImage_height,
                     u32 *gImage_osd, u16 alpha, u8 mode) 
{
    save_osd_palette(OSD1_LUT_ADR,(u32 *)&gImage_palette[0],alpha);
    //uart_putword(gImage_osd); uart_putword(" ");
    save_osd_index((u32)(OFFSET(gImage_osd)),gImage_osd, gImage_width*gImage_height);
    set_osd1_address((u32)(OFFSET(gImage_osd)));
    if(0 == mode)
    {
        save_osd_palette(OSD1_LUT_ADR,(u32 *)&gImage_palette[0],0);
        lcd_rgb_osd1_set_window(osd_x,osd_y,osd_x+gImage_width,osd_y+gImage_height,alpha,1);
    }   	   
    else
    {
        save_osd_palette(OSD1_LUT_ADR,(u32 *)&gImage_palette[0],alpha);
    	  lcd_rgb_osd1_set_window(osd_x,osd_y,osd_x+gImage_width,osd_y+gImage_height,0x100,1);   
    }
    	  	
}
/************************************************************************
 *Description: 设置RGB接口屏osd2层的正常显示

 *Parameters:  stx ，sty ：osd2窗口的左上角的坐标
               gImage_width  ：原图的列数
               gImage_height ：原图的行数
               *gImage_osd   ：原图数据的首地址
               alpha ：透明度
               mode  : 0表示选择osd层的透明度；1表示选择调色板的透明度
 *Return value: 无
*************************************************************************/
void lcd_rgb_osd2_display(u16 osd_x, u16 osd_y, u16 gImage_width ,u16 gImage_height,
                     u32 *gImage_osd, u16 alpha,u8 mode) 
{
    save_osd_index((u32)(OFFSET(gImage_osd)),gImage_osd, gImage_width*gImage_height);
    set_osd2_address((u32)(OFFSET(gImage_osd)));
    if(0 == mode)
    {
        save_osd_palette(OSD2_LUT_ADR,(u32 *)&gImage_palette[0],0);
        lcd_rgb_osd2_set_window(osd_x,osd_y,osd_x+gImage_width,osd_y+gImage_height,alpha,1);
    }   	   
    else
    {
        save_osd_palette(OSD2_LUT_ADR,(u32 *)&gImage_palette[0],alpha);
		lcd_rgb_osd2_set_window(osd_x,osd_y,osd_x+gImage_width,osd_y+gImage_height,0x100,1);   
    }    
}
/************************************************************************
 *Description: 设置RGB接口屏osd3层的正常显示

 *Parameters:  stx ，sty ：osd3窗口的左上角的坐标
               gImage_width  ：原图的列数
               gImage_height ：原图的行数
               *gImage_osd   ：原图数据的首地址
               alpha ：透明度
               mode  : 0表示选择osd层的透明度；1表示选择调色板的透明度
 *Return value: 无
*************************************************************************/
void lcd_rgb_osd3_display(u16 osd_x, u16 osd_y, u16 gImage_width ,u16 gImage_height,
                     u32 *gImage_osd, u16 alpha, u8 mode) 
{
    save_osd_index((u32)(OFFSET(gImage_osd)),gImage_osd, gImage_width*gImage_height);
    set_osd3_address((u32)(OFFSET(gImage_osd)));
    if(0 == mode)
    {
        save_osd_palette(OSD3_LUT_ADR,(u32 *)&gImage_palette[0],0);
        lcd_rgb_osd3_set_window(osd_x,osd_y,osd_x+gImage_width,osd_y+gImage_height,alpha,1);
    }   	   
    else
    {
        save_osd_palette(OSD3_LUT_ADR,(u32 *)&gImage_palette[0],alpha);
    	  lcd_rgb_osd3_set_window(osd_x,osd_y,osd_x+gImage_width,osd_y+gImage_height,0x100,1);   
    }  
}

/************************************************************************
 *Description: 设置RGB接口屏video层的正常显示

 *Parameters:  stx ，sty ：video窗口的左上角的坐标
               gImage_width  ：原图的列数
               gImage_height ：原图的行数
               *gImage_osd   ：原图数据的首地址

 *Return value: 无
*************************************************************************/
void lcd_rgb_video_display_normal(u16 video_x, u16 video_y,u16 gImage_width ,u16 gImage_height,
                     u32 *gImage_video)
{
    lcd_rgb2yuv((u32)(OFFSET(gImage_video)),gImage_video,gImage_width,gImage_height);
    set_video_address((u32)(OFFSET(gImage_video)));
    lcd_rgb_video_normal(video_x,video_y,gImage_width,gImage_height,1);
}
/************************************************************************
 *Description: 设置RGB接口屏video层的正常显示

 *Parameters:  stx ，sty ：video窗口的左上角的坐标
               s_width  ：原图的列数
               s_height ：原图的行数
               d_width  ：缩放后图片的列数
               d_height ：缩放后图片的行数
               w_step : 宽度步进整数部分, W_step=原图宽度*0x100/缩放后图宽度
               w_remain : 宽度步进小数部分, W_remain=原图宽度*0x100-缩放后图宽度*W_step
               h_step : 高度步进整数部分, H_step=原图高度*0x100/缩放后图高度
               h_remain : 高度步进小数部分, H_remain=原图高度*0x100-缩放后图高度*H_step
               *gImage_video   ：原图数据的首地址

 *Return value: 无
*************************************************************************/
void lcd_rgb_video_display_zoom(u16 video_x,u16 video_y,u16 s_width,u16 s_height,u16 d_width, u16 d_height,
                      u16 w_step,u16 w_remain,u16 h_step,u16 h_remain,u32 *gImage_video)
{
    lcd_rgb2yuv((u32)(OFFSET(gImage_video)),gImage_video,s_width,s_height);
//    uart_putstr("\r\n    *****************************1" );
    set_video_address((u32)(OFFSET(gImage_video)));
//    uart_putstr("\r\n    *****************************2" );
    lcd_rgb_video_zoom(video_x, video_y, s_width, s_height, d_width, d_height,
                               w_step, w_remain, h_step, h_remain, 1);
}

void lcd_rgb_video_display_zoomChEnd(u16 video_x,u16 video_y,u16 s_width,u16 s_height,u16 d_width, u16 d_height,
                      u16 w_step,u16 w_remain,u16 h_step,u16 h_remain,u32 *gImage_video)
{
    lcd_rgb2yuvChEnd((u32)(OFFSET(gImage_video)),gImage_video,s_width,s_height);
//    uart_putstr("\r\n    *****************************1" );
    set_video_address((u32)(OFFSET(gImage_video)));
//    uart_putstr("\r\n    *****************************2" );
    lcd_rgb_video_zoom(video_x, video_y, s_width, s_height, d_width, d_height,
                               w_step, w_remain, h_step, h_remain, 1);
}


/************************************************************************
 *Description: 设置RGB接口屏video层的回写显示

 *Parameters:  stx ，sty ：video窗口的左上角的坐标
               gImage_width  ：原图的列数
               gImage_height ：原图的行数
               adr   ：回写数据存放的首地址

 *Return value: 无
*************************************************************************/
void lcd_rgb_video_display_wbdata(u16 video_x, u16 video_y,u16 gImage_width ,u16 gImage_height,u32 adr)
{ 
	  REG32(LCDCON0) &= ~(1 << 6);             //clear video_en bit
	  REG32(LCDCON57) |= 1;	 
	  while((REG32(LCDCON57)&(1<<0))==0);      //waiting 1 frame pending	
    set_video_address(adr);
    lcd_rgb_video_normal(video_x,video_y,gImage_width,gImage_height,1);
    REG32(LCDCON0) |= (1 << 6);              //set video_en bit
	  //LCDCON57 |= 1;                    //clear 1 frame pending
}

/*void video3_display(u32 adr,u16 video_x, u16 video_y)
{
    lcd_rgb2yuv(adr,gImage_video3,gImage_video3_width,gImage_video3_height);
    set_video_address(adr);    
    lcd_emi_video_display_normal(video_x,video_y,gImage_video3_width,gImage_video3_height,1);
}
    
*/	


void lcd_PostScale_Start(void)
{
	u32 lcd_con_reg_save = REG32(LCDCON0);
	DIS_OSD1();
	DIS_OSD2();
	DIS_OSD3();
	lcd_set_panel_colour(0,0,0);
	#if(0 == LCD_MCU)
		waittingLcdFrameEnd();
		REG32(LCDCON0) &= ~(BIT(0) |BIT(6) |BIT(11));
		
		REG32(LCDCON46) = VIDEO_BASE_SDRAM_ADDR;
		if (sys_ctl.jpeg_picture_size == JPEG_SIZE_2560_1440)
			tvout_display_set(0,0,u32csi_Dma_Size_H,u32csi_Dma_Size_H,u32csi_Dma_Size_V,JPEG_SCALE_SIZE_H,JPEG_SCALE_SIZE_V);
		else if (sys_ctl.jpeg_picture_size == JPEG_SIZE_1920_1080)
			tvout_display_set(0,0,u32csi_Dma_Size_H,u32csi_Dma_Size_H,u32csi_Dma_Size_V,1920,1080);
		
		REG32(LCDCON0) = lcd_con_reg_save;
		REG32(LCDCON0) |= BIT(7);	//write back enable
		REG32(LCDCON0) |= (BIT(0) |BIT(6) | BIT(11));
	#else
		REG32(LCDCON0) &= ~(BIT(6) |BIT(11));
		waittingLcdFrameEnd();

		REG32(LCDCON46) = VIDEO_BASE_SDRAM_ADDR;
		if (sys_ctl.jpeg_picture_size == JPEG_SIZE_2560_1440)
			tvout_display_set(0,0,u32csi_Dma_Size_H,u32csi_Dma_Size_H,u32csi_Dma_Size_V,JPEG_SCALE_SIZE_H,JPEG_SCALE_SIZE_V);
		else if (sys_ctl.jpeg_picture_size == JPEG_SIZE_1920_1080)
			tvout_display_set(0,0,u32csi_Dma_Size_H,u32csi_Dma_Size_H,u32csi_Dma_Size_V,1920,1080);
		
		waittingLcdFrameEnd();
		REG32(LCDCON0) = lcd_con_reg_save;
		REG32(LCDCON0) |= BIT(7);	//write back enable
		REG32(LCDCON0) |= (BIT(6) | BIT(11));
	#endif

}


void lcd_PostScale_Stop(void)
{
	u32 lcd_con_reg_save = REG32(LCDCON0);
	DIS_OSD1();
	DIS_OSD2();
	DIS_OSD3();
	lcd_set_panel_colour(0,0,0);
	#if(0 == LCD_MCU)
		waittingLcdFrameEnd();
		REG32(LCDCON0) &= ~(BIT(0) |BIT(6) | BIT(11)); 
		csi_Start(0,0);
		tvout_Change_display();
		REG32(LCDCON0) = lcd_con_reg_save;
		EN_OSD1();
		REG32(LCDCON0) &= ~BIT(7);	//write back disable
		REG32(LCDCON0) |= (BIT(0) |BIT(6));
	#else
		REG32(LCDCON0) &= ~(BIT(6) | BIT(11)); 
		waittingLcdFrameEnd();
		csi_Start(0,0);
		DIS_OSD1();
		DIS_OSD2();
		DIS_OSD3();
		lcd_set_panel_colour(0,0,0);
		REG32(LCDCON0) &= ~BIT(6) ;
		waittingLcdFrameEnd();
		tvout_Change_display();
		REG32(LCDCON0) = lcd_con_reg_save;
		EN_OSD1();
		REG32(LCDCON0) &= ~BIT(7);	//write back disable
		REG32(LCDCON0) |= (BIT(6));
	#endif

}





