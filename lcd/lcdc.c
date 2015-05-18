#include "../header/include.h"


/************************************************************************
 *Description: 设置EMI屏接口的画板底色

 *Parameters:  default_red ： 红色，取值0-255
               default_green ： 绿色 取值0-255
               default_blue  ： 蓝色 取值0-255

 *Return value: 无
*************************************************************************/
void lcd_set_panel_colour(u16 default_red, u16 default_green,u16 default_blue) {
				     
	REG32(LCDCON40) = default_red;		 
	REG32(LCDCON41) = default_green;
	REG32(LCDCON42) = default_blue;
}

/************************************************************************
 *Description: 设置osd 1层图片数据的索引地址

 *Parameters:  osd1_addr ：osd1数据存放的首地址

 *Return value: 无
*************************************************************************/
void set_osd1_address(u32 osd1_addr)
{
	  REG32(LCDCON43) = osd1_addr;
}
/************************************************************************
 *Description: 设置osd 2层图片数据的索引地址

 *Parameters:  osd2_addr ：osd2数据存放的首地址

 *Return value: 无
*************************************************************************/
void set_osd2_address(u32 osd2_addr)
{
	  REG32(LCDCON44) = osd2_addr;
}
/************************************************************************
 *Description: 设置osd 3层图片数据的索引地址

 *Parameters:  osd3_addr ：osd3数据存放的首地址

 *Return value: 无
*************************************************************************/
void set_osd3_address(u32 osd3_addr)
{
	  REG32(LCDCON45) = osd3_addr;
}
/************************************************************************
 *Description: 设置video层图片数据的索引地址

 *Parameters:  video_addr ：video数据存放的首地址

 *Return value: 无
*************************************************************************/
void  set_video_address(u32 video_addr)
{	  
	  REG32(LCDCON46) = video_addr;
}

/************************************************************************
 *Description: 将RGB数据转换成YUV并存放到给定的地址

 *Parameters:  u32adr ：video数据存放的首地址
               *gImage_video ：video数据的数组首地址
               gImage_video_width ：video数据的列数
               gImage_video_height ：video数据的行数

 *Return value: 无
*************************************************************************/ 
void lcd_rgb2yuv(u32 u32adr,u32 *gImage_video,u32 gImage_video_width,u32 gImage_video_height)
{
    u32 i,j;
    dma_peri2mem(2, (2<<7)|(1<<11)|(1<<1), (0<<11)|(0<<10), 0x14020030, u32adr, 2400);
    REG32(RGB_STATUS) =(1<<1);//0:{RGB} 1:{BGR} 2{GRB} 3:{BRG} 4:{GBR} 5:RBG}  //select RGB mode
    for(j=0;j<gImage_video_height;j++)
    {
       for(i=0;i<gImage_video_width;i+=2)
       {
           if(i==gImage_video_width-1)                                     //如果是一行的最后一个像素
           {
             if(j==gImage_video_height-1)                                  //如果是最后一行的最后一个像素
             REG32(RGB_DAT) =0x02000000|gImage_video[i+j*gImage_video_width];
             else
             REG32(RGB_DAT) =0x01000000|gImage_video[i+j*gImage_video_width];     //如果是最后一个像素但不是最后一行
           }
           else 
             if(i==gImage_video_width-2)                                   //如果是倒数第二个像素
                 if(j==gImage_video_height-1)                              //如果是最后一行的倒数第二个像素
                 {
                  REG32(RGB_DAT) =gImage_video[i+j*gImage_video_width]&0xffffff;
                  REG32(RGB_DAT) =0x02000000 | gImage_video[i+j*gImage_video_width+1];
                 }
                 else                                                      //如果是倒数第二个像素但不是最后一行
                 {
                  REG32(RGB_DAT) =gImage_video[i+j*gImage_video_width]&0xffffff;
                  REG32(RGB_DAT) = 0x01000000| gImage_video[i+j*gImage_video_width+1];
                 }
              else
               {
                 REG32(RGB_DAT) =gImage_video[i+j*gImage_video_width]&0xffffff;
                 REG32(RGB_DAT) =gImage_video[i+j*gImage_video_width+1]&0xffffff;
               }
           while(!((REG32(RGB_STATUS) & 0x01) == 0x01));     
       } 
    }         
}

#if 1
void lcd_rgb2yuvChEnd(u32 u32adr,u32 *gImage_video,u32 gImage_video_width,u32 gImage_video_height)
{
    u32 i,j;
    dma_peri2mem(2, (2<<7)|(1<<11)|(1<<1), (0<<11)|(0<<10), 0x14020030, u32adr, 2400);
    REG32(RGB_STATUS) =(1<<1);//0:{RGB} 1:{BGR} 2{GRB} 3:{BRG} 4:{GBR} 5:RBG}  //select RGB mode
    for(j=0;j<gImage_video_height;j++)
    {
       for(i=0;i<gImage_video_width;i+=2)
       {
           if(i==gImage_video_width-1)                                     //如果是一行的最后一个像素
           {
             if(j==gImage_video_height-1)                                  //如果是最后一行的最后一个像素
             REG32(RGB_DAT) =0x02000000|XCHDWORD(gImage_video[i+j*gImage_video_width]);
             else
             REG32(RGB_DAT) =0x01000000|XCHDWORD(gImage_video[i+j*gImage_video_width]);     //如果是最后一个像素但不是最后一行
           }
           else 
             if(i==gImage_video_width-2)                                   //如果是倒数第二个像素
                 if(j==gImage_video_height-1)                              //如果是最后一行的倒数第二个像素
                 {
                  REG32(RGB_DAT) =XCHDWORD(gImage_video[i+j*gImage_video_width])&0xffffff;
                  REG32(RGB_DAT) =0x02000000 | XCHDWORD(gImage_video[i+j*gImage_video_width+1]);
                 }
                 else                                                      //如果是倒数第二个像素但不是最后一行
                 {
                  REG32(RGB_DAT) =XCHDWORD(gImage_video[i+j*gImage_video_width])&0xffffff;
                  REG32(RGB_DAT) = 0x01000000| XCHDWORD(gImage_video[i+j*gImage_video_width+1]);
                 }
              else
               {
                 REG32(RGB_DAT) =XCHDWORD(gImage_video[i+j*gImage_video_width])&0xffffff;
                 REG32(RGB_DAT) =XCHDWORD(gImage_video[i+j*gImage_video_width+1])&0xffffff;
               }
           while(!((REG32(RGB_STATUS) & 0x01) == 0x01));     
       } 
    }         
}
#endif
/************************************************************************
 *Description: 设置EMI接口屏video窗口

 *Parameters:  stx ，sty ：video窗口的左上角的坐标
               endx ，endy ：video窗口的右下角的坐标              

 *Return value: 无
*************************************************************************/
void lcd_emi_video_set_window(u16 stx, u16 sty, u16 endx, u16 endy)
{
	 REG32(LCDCON19) = stx;
	 REG32(LCDCON20) = sty;
	 REG32(LCDCON21) = endx - 1;
	 REG32(LCDCON22) = endy - 1;
}
/************************************************************************
 *Description: 设置RGB接口屏video窗口

 *Parameters:  stx ，sty ：video窗口的左上角的坐标
               endx ，endy ：video窗口的右下角的坐标              

 *Return value: 无
*************************************************************************/
void lcd_rgb_video_set_window(u16 stx, u16 sty, u16 endx, u16 endy)
{
	 REG32(LCDCON19) = stx + REG32(LCDCON9);
	 REG32(LCDCON20) = sty + REG32(LCDCON13);
	 REG32(LCDCON21) = endx + REG32(LCDCON9) - 1;
	 REG32(LCDCON22) = endy + REG32(LCDCON13) - 1;
}
/************************************************************************
 *Description: 设置原图每一行数据的字节数，要求是4的倍数

 *Parameters:  span ：数据跨度              

 *Return value: 无
*************************************************************************/
void lcd_set_line(u16 span)
{
	  if(span%4==0)
        REG32(LCDCON48) = span;
    else 
    	REG32(LCDCON48) = span+2; 
}
/************************************************************************
 *Description: 设置EMI接口屏video窗口的正常显示

 *Parameters:  stx ，sty ：video窗口的左上角的坐标
               s_width  ：原图的列数
               s_height ：原图的行数
               burst ：video每次收到DMA请求从SDRAM取出的数据个数

 *Return value: 无
*************************************************************************/
void lcd_emi_video_normal(u16 stx,u16 sty, 
                       u16 s_width, u16 s_height,u16 burst)
{
    lcd_emi_video_set_window(stx,sty,stx+s_width, sty+s_height);
	  
    lcd_set_line(s_width*2);

    REG32(LCDCON49) = 0x100;    //W_srep 宽度步进整数部分, W_step=原图宽度*0x100/缩放后图宽度
    REG32(LCDCON50) = 0;        //W_remain 宽度步进小数部分, W_remain=原图宽度*0x100-缩放后图宽度*W_step
    REG32(LCDCON51) = 0x100;    //H_step 高度步进整数部分, H_step=原图高度*0x100/缩放后图高度
    REG32(LCDCON52) = 0;        //H_remain 高度步进小数部分, H_remain=原图高度*0x100-缩放后图高度*H_step
    REG32(LCDCON53) = s_width;  //D_w
    REG32(LCDCON54) = s_height; //D_h   
    REG32(LCDCON55) = s_width;  //S_W
    REG32(LCDCON56) = s_height; //S_H
    
    REG32(LCDCON59) |= (burst<<6); // bit[7:6]  
}
/************************************************************************
 *Description: 设置EMI接口屏video窗口的缩放显示

 *Parameters:  stx ，sty ：osd2窗口的左上角的坐标
               s_width ：原图的列数
               s_height ：原图的行数
               d_width ：缩放后图片的列数
               d_height ：缩放后图片的行数
               w_step : 宽度步进整数部分, W_step=原图宽度*0x100/缩放后图宽度
               w_remain : 宽度步进小数部分, W_remain=原图宽度*0x100-缩放后图宽度*W_step
               h_step : 高度步进整数部分, H_step=原图高度*0x100/缩放后图高度
               h_remain : 高度步进小数部分, H_remain=原图高度*0x100-缩放后图高度*H_step
               burst ：video每次收到DMA请求从SDRAM取出的数据个数

 *Return value: 无
*************************************************************************/
void lcd_emi_video_zoom(u16 stx,u16 sty, u16 s_width, u16 s_height,
                               u16 d_width, u16 d_height,
                               u16 w_step,u16 w_remain,u16 h_step,u16 h_remain,u16 burst)
{
    lcd_emi_video_set_window(stx,sty,stx+d_width, sty+d_height);
	  
    lcd_set_line(s_width*2);
    
    REG32(LCDCON49) = w_step;    //W_srep 
    REG32(LCDCON50) = w_remain;  //W_remain 
    REG32(LCDCON51) = h_step;    //H_step 
    REG32(LCDCON52) = h_remain;  //H_remain 
    REG32(LCDCON53) = d_width;   //D_w
    REG32(LCDCON54) = d_height;  //D_h 
    REG32(LCDCON55) = s_width;   //S_W
    REG32(LCDCON56) = s_height;  //S_H
    
    REG32(LCDCON59) |= (burst<<6);  // bit[7:6]  	
}
/************************************************************************
 *Description: 设置EMI接口屏video窗口的部分显示

 *Parameters:  stx ，sty ：osd2窗口的左上角的坐标
               s_width ：原图的列数
               s_height ：原图的行数
               d_width ：缩放后图片的列数
               d_height ：缩放后图片的行数
               w_step : 宽度步进整数部分, W_step=原图宽度*0x100/缩放后图宽度
               w_remain : 宽度步进小数部分, W_remain=原图宽度*0x100-缩放后图宽度*W_step
               h_step : 高度步进整数部分, H_step=原图高度*0x100/缩放后图高度
               h_remain : 高度步进小数部分, H_remain=原图高度*0x100-缩放后图高度*H_step
               burst ：video每次收到DMA请求从SDRAM取出的数据个数

 *Return value: 无
*************************************************************************/
void lcd_emi_video_display_part(int stx,int sty, 
                       int s_width, int s_height,int d_width, int d_height,int burst)
{
	  lcd_emi_video_set_window(stx,sty,stx+d_width, sty+d_height);
	  
    lcd_set_line(s_width*2);
    
    REG32(LCDCON49) = 0x100;    //W_srep
    REG32(LCDCON50) = 0;        //W_remain
    REG32(LCDCON51) = 0x100;    //H_step
    REG32(LCDCON52) = 0;        //H_remain
    REG32(LCDCON53) = d_width;  //D_w
    REG32(LCDCON54) = d_height; //D_h   
    REG32(LCDCON55) = s_width;  //S_W
    REG32(LCDCON56) = s_height; //S_H
     
    REG32(LCDCON59) |= (burst<<6);   
}
/************************************************************************
 *Description: 设置RGB接口屏video窗口的正常显示

 *Parameters:  stx ，sty ：osd2窗口的左上角的坐标
               s_width ：原图的列数
               s_height ：原图的行数
               burst ：video每次收到DMA请求从SDRAM取出的数据个数

 *Return value: 无
*************************************************************************/
void lcd_rgb_video_normal(u16 stx,u16 sty, 
                       u16 s_width, u16 s_height,u16 burst)
{
    lcd_rgb_video_set_window(stx,sty,stx+s_width, sty+s_height);
	  
    lcd_set_line(s_width*2);

    REG32(LCDCON49) = 0x100;    //W_srep 宽度步进整数部分, W_step=原图宽度*0x100/缩放后图宽度
    REG32(LCDCON50) = 0;        //W_remain 宽度步进小数部分, W_remain=原图宽度*0x100-缩放后图宽度*W_step
    REG32(LCDCON51) = 0x100;    //H_step 高度步进整数部分, H_step=原图高度*0x100/缩放后图高度
    REG32(LCDCON52) = 0;        //H_remain 高度步进小数部分, H_remain=原图高度*0x100-缩放后图高度*H_step
    REG32(LCDCON53) = s_width;  //D_w
    REG32(LCDCON54) = s_height; //D_h   
    REG32(LCDCON55) = s_width;  //S_W
    REG32(LCDCON56) = s_height; //S_H
    
    REG32(LCDCON59) |= (burst<<6); // bit[7:6]  
}
/************************************************************************
 *Description: 设置RGB接口屏video窗口的缩放显示

 *Parameters:  stx ，sty ：osd2窗口的左上角的坐标
               s_width ：原图的列数
               s_height ：原图的行数
               d_width ：缩放后图片的列数
               d_height ：缩放后图片的行数
               w_step : 宽度步进整数部分, W_step=原图宽度*0x100/缩放后图宽度
               w_remain : 宽度步进小数部分, W_remain=原图宽度*0x100-缩放后图宽度*W_step
               h_step : 高度步进整数部分, H_step=原图高度*0x100/缩放后图高度
               h_remain : 高度步进小数部分, H_remain=原图高度*0x100-缩放后图高度*H_step
               burst ：video每次收到DMA请求从SDRAM取出的数据个数

 *Return value: 无
*************************************************************************/
void lcd_rgb_video_zoom(u16 stx,u16 sty, u16 s_width, u16 s_height,
                               u16 d_width, u16 d_height,
                               u16 w_step,u16 w_remain,u16 h_step,u16 h_remain,u16 burst)
{
    lcd_rgb_video_set_window(stx,sty,stx+d_width, sty+d_height);
	  
    lcd_set_line(s_width*2);
    
    REG32(LCDCON49) = w_step;    //W_srep 
    REG32(LCDCON50) = w_remain;  //W_remain 
    REG32(LCDCON51) = h_step;    //H_step 
    REG32(LCDCON52) = h_remain;  //H_remain 
    REG32(LCDCON53) = d_width;   //D_w
    REG32(LCDCON54) = d_height;  //D_h 
    REG32(LCDCON55) = s_width;   //S_W
    REG32(LCDCON56) = s_height;  //S_H
    
    REG32(LCDCON59) |= (burst<<6);  // bit[7:6]  	
}
/************************************************************************
 *Description: 设置RGB接口屏video窗口的缩放显示

 *Parameters:  stx ，sty ：osd2窗口的左上角的坐标
               s_width ：原图的列数
               s_height ：原图的行数
               d_width ：缩放后图片的列数
               d_height ：缩放后图片的行数
               w_step : 宽度步进整数部分, W_step=原图宽度*0x100/缩放后图宽度
               w_remain : 宽度步进小数部分, W_remain=原图宽度*0x100-缩放后图宽度*W_step
               h_step : 高度步进整数部分, H_step=原图高度*0x100/缩放后图高度
               h_remain : 高度步进小数部分, H_remain=原图高度*0x100-缩放后图高度*H_step
               burst ：video每次收到DMA请求从SDRAM取出的数据个数

 *Return value: 无
*************************************************************************/
/*void lcd_rgb_video_part(u16 stx,u16 sty, u16 s_width, u16 s_height,
                               u16 d_width, u16 d_height,
                               u16 w_step,u16 w_remain,u16 h_step,u16 h_remain,u16 burst)
{
    lcd_rgb_video_set_window(stx,sty,stx+d_width, sty+d_height);
	  
    lcd_set_line(s_width*2);
    
    LCDCON49 = w_step;    //W_srep 
    LCDCON50 = w_remain;  //W_remain 
    LCDCON51 = h_step;    //H_step 
    LCDCON52 = h_remain;  //H_remain 
    LCDCON53 = d_width;   //D_w
    LCDCON54 = d_height;  //D_h 
    LCDCON55 = s_width;   //S_W
    LCDCON56 = s_height;  //S_H
    
    LCDCON59 |= (burst<<6);  // bit[7:6]  	
}*/
/************************************************************************
 *Description: 将osd的调色板数据存放到给定的地址

 *Parameters: u32adr ： 数据存放的首地址,
              *gImage_palette ：调试板数据的数组首地址
              alpha ：调色板的透明度

 *Return value: 无
*************************************************************************/
void save_osd_palette(u32 u32adr,u32 *gImage_palette, u8 alpha)
{
	  u32 *pt,i;
    for(i=0; i<0x100; i++) 
		{			
				pt = (u32 *)(u32adr + i*4);
				*pt = (alpha<<24)|gImage_palette[i];		 		
		} 			
}
/************************************************************************
 *Description: 将osd的索引数据存放到给定的地址

 *Parameters: u32adr ： 数据存放的首地址,
              *gImage_osd ：索引数据的数组首地址
              gImage_osd_area ：索引数据的总数

 *Return value: 无
*************************************************************************/
void save_osd_index(u32 u32adr,u32 *gImage_osd, u32 gImage_osd_area)
{
	  u32 *pt,i;
    for(i=0; i<gImage_osd_area; i++) 
		{			
				pt = (u32 *)(u32adr + i*4);
				*pt = gImage_osd[i];		 		
		} 			
}
/************************************************************************
 *Description: 设置EMI接口屏osd1窗口

 *Parameters:  stx ，sty ：osd1窗口的左上角的坐标
               endx ，endy ：osd1窗口的右下角的坐标
               alpha ：osd1窗口的透明度，取值在0——255
               burst ：osd1每次收到DMA请求从SDRAM取出的数据个数

 *Return value: 无
*************************************************************************/
void lcd_emi_osd1_set_window(u16 stx, u16 sty, u16 endx, u16 endy, u16 alpha, u16 burst) 
{
	REG32(LCDCON23) = stx ;	   
	REG32(LCDCON24) = sty ;	 
	REG32(LCDCON25) = endx - 1;
	REG32(LCDCON26) = endy - 1;
	REG32(LCDCON37) = alpha;
	REG32(LCDCON59) |= (burst<<0);		// bit[1:0]
}
/************************************************************************
 *Description: 设置EMI接口屏osd2窗口

 *Parameters:  stx ，sty ：osd2窗口的左上角的坐标
               endx ，endy ：osd2窗口的右下角的坐标
               alpha ：osd2窗口的透明度，取值在0——255
               burst ：osd2每次收到DMA请求从SDRAM取出的数据个数

 *Return value: 无
*************************************************************************/
void lcd_emi_osd2_set_window(u16 stx, u16 sty, u16 endx, u16 endy, u16 alpha, u16 burst) 
{
	REG32(LCDCON27) = stx;
	REG32(LCDCON28) = sty;
	REG32(LCDCON29) = endx - 1;
	REG32(LCDCON30) = endy - 1;
	REG32(LCDCON38) = alpha;
	REG32(LCDCON59) |= (burst<<2);		// bit[3:2]
}
/************************************************************************
 *Description: 设置EMI接口屏osd3窗口

 *Parameters:  stx ，sty ：osd3窗口的左上角的坐标
               endx ，endy ：osd3窗口的右下角的坐标
               alpha ：osd3窗口的透明度，取值在0——255
               burst ：osd3每次收到DMA请求从SDRAM取出的数据个数

 *Return value: 无
*************************************************************************/
void lcd_emi_osd3_set_window(u16 stx, u16 sty, u16 endx, u16 endy, u16 alpha, u16 burst) 
{
	REG32(LCDCON31) = stx;
	REG32(LCDCON32) = sty;
	REG32(LCDCON33) = endx - 1;
	REG32(LCDCON34) = endy - 1;
	REG32(LCDCON39) = alpha;
	REG32(LCDCON59) |= (burst<<4);		// bit[5:4]
} 
/************************************************************************
 *Description: 设置RGB接口屏osd1窗口

 *Parameters:  stx ，sty ：osd1窗口的左上角的坐标
               endx ，endy ：osd1窗口的右下角的坐标
               alpha ：osd1窗口的透明度，取值在0——255
               burst ：osd1每次收到DMA请求从SDRAM取出的数据个数

 *Return value: 无
*************************************************************************/
void lcd_rgb_osd1_set_window(u16 stx, u16 sty, u16 endx, u16 endy, u16 alpha, u16 burst) 
{
	REG32(LCDCON23) = stx + REG32(LCDCON9);	  // DE 有效起始像素
	REG32(LCDCON24) = sty + REG32(LCDCON13);	// DE 有效起始行
	REG32(LCDCON25) = endx + REG32(LCDCON9) - 1;
	REG32(LCDCON26) = endy + REG32(LCDCON13) - 1;//
	REG32(LCDCON37) = alpha;
	REG32(LCDCON59) |= (burst<<0);		// bit[1:0]
}
/************************************************************************
 *Description: 设置RGB接口屏osd2窗口

 *Parameters:  stx ，sty ：osd2窗口的左上角的坐标
               endx ，endy ：osd2窗口的右下角的坐标
               alpha ：osd2窗口的透明度，取值在0——255
               burst ：osd2每次收到DMA请求从SDRAM取出的数据个数

 *Return value: 无
*************************************************************************/
void lcd_rgb_osd2_set_window(u16 stx, u16 sty, u16 endx, u16 endy, u16 alpha, u16 burst) 
{
	REG32(LCDCON27) = stx + REG32(LCDCON9);
	REG32(LCDCON28) = sty + REG32(LCDCON13);
	REG32(LCDCON29) = endx + REG32(LCDCON9) - 1;
	REG32(LCDCON30) = endy + REG32(LCDCON13) - 1;
	REG32(LCDCON38) = alpha;
	REG32(LCDCON59) |= (burst<<2);		// bit[3:2]
}
/************************************************************************
 *Description: 设置RGB接口屏osd3窗口

 *Parameters:  stx ，sty ：osd3窗口的左上角的坐标
               endx ，endy ：osd3窗口的右下角的坐标
               alpha ：osd3窗口的透明度，取值在0——255
               burst ：osd3每次收到DMA请求从SDRAM取出的数据个数

 *Return value: 无
*************************************************************************/
void lcd_rgb_osd3_set_window(u16 stx, u16 sty, u16 endx, u16 endy, u16 alpha, u16 burst) 
{
	REG32(LCDCON31) = stx + REG32(LCDCON9);
	REG32(LCDCON32) = sty + REG32(LCDCON13);
	REG32(LCDCON33) = endx + REG32(LCDCON9) - 1;
	REG32(LCDCON34) = endy + REG32(LCDCON13) - 1;
	REG32(LCDCON39) = alpha;
	REG32(LCDCON59) |= (burst<<4);		// bit[5:4]
} 
/************************************************************************
 *Description: 设置RGB接口屏video窗口的缩放显示

 *Parameters:  stx ，sty ：video窗口的左上角的坐标
               endx ，endy ：video窗口的右下角的坐标
               span ：数据跨度 
               s_w ：原图的列数
               s_h ：原图的行数
               d_w ：缩放后图片的列数
               d_h ：缩放后图片的行数
               w_step : 宽度步进整数部分, W_step=原图宽度*0x100/缩放后图宽度
               w_remain : 宽度步进小数部分, W_remain=原图宽度*0x100-缩放后图宽度*W_step
               h_step : 高度步进整数部分, H_step=原图高度*0x100/缩放后图高度
               h_remain : 高度步进小数部分, H_remain=原图高度*0x100-缩放后图高度*H_step
               burst ：video每次收到DMA请求从SDRAM取出的数据个数

 *Return value: 无
*************************************************************************/
void video(u16 stx,u16 sty, u16 endx, u16 endy,u16 span,u16 s_w,u16 s_h,u16 d_w,u16 d_h,
          u16 w_step,u16 w_remain,u16 h_step,u16 h_remain,u16 burst)
{
	 REG32(LCDCON19) = stx;
	 REG32(LCDCON20) = sty;
	 REG32(LCDCON21) = endx;
	 REG32(LCDCON22) = endy;

   REG32(LCDCON48) = span;
   REG32(LCDCON49) = w_step;    //W_srep
   REG32(LCDCON50) = w_remain;  //W_remain
   REG32(LCDCON51) = h_step;    //H_step
   REG32(LCDCON52) = h_remain;  //H_remain
   REG32(LCDCON53) = d_w;  //D_w
   REG32(LCDCON54) = d_h;  //D_h
   REG32(LCDCON55) = s_w;  //S_W
   REG32(LCDCON56) = s_h;  //S_H
   REG32(LCDCON59) |= (burst<<6);
}


