
#ifndef _LCDC_H_
#define _LCDC_H_

#include "../header/include.h"

void lcd_set_panel_colour(u16 default_red, u16 default_green,u16 default_blue); 

void set_osd1_address(u32 osd1_addr);

void set_osd2_address(u32 osd2_addr);

void set_osd3_address(u32 osd3_addr);

void  set_video_address(u32 video_addr);

void lcd_rgb2yuv(u32 u32adr,u32 *gImage_video,u32 gImage_video_width,u32 gImage_video_height);
void lcd_rgb2yuvChEnd(u32 u32adr,u32 *gImage_video,u32 gImage_video_width,u32 gImage_video_height);

void lcd_emi_video_set_window(u16 stx, u16 sty, u16 endx, u16 endy);

void lcd_rgb_video_set_window(u16 stx, u16 sty, u16 endx, u16 endy);

void lcd_set_line(u16 span);

void lcd_emi_video_normal(u16 stx,u16 sty, 
                       u16 s_width, u16 s_height,u16 burst);

void lcd_emi_video_zoom(u16 stx,u16 sty, u16 s_width, u16 s_height,
                               u16 d_width, u16 d_height,
                               u16 w_step,u16 w_remain,u16 h_step,u16 h_remain,u16 burst);

void lcd_emi_video_display_part(int stx,int sty, 
                       int s_width, int s_height,int d_width, int d_height,int burst);

void lcd_rgb_video_normal(u16 stx,u16 sty, 
                       u16 s_width, u16 s_height,u16 burst);

void lcd_rgb_video_zoom(u16 stx,u16 sty, u16 s_width, u16 s_height,
                               u16 d_width, u16 d_height,
                               u16 w_step,u16 w_remain,u16 h_step,u16 h_remain,u16 burst);

void save_osd_palette(u32 u32adr,u32 *gImage_palette, u8 alpha);

void save_osd_index(u32 u32adr,u32 *gImage_osd, u32 gImage_osd_area);

void lcd_emi_osd1_set_window(u16 stx, u16 sty, u16 endx, u16 endy, u16 alpha, u16 burst);

void lcd_emi_osd2_set_window(u16 stx, u16 sty, u16 endx, u16 endy, u16 alpha, u16 burst);

void lcd_emi_osd3_set_window(u16 stx, u16 sty, u16 endx, u16 endy, u16 alpha, u16 burst); 

void lcd_rgb_osd1_set_window(u16 stx, u16 sty, u16 endx, u16 endy, u16 alpha, u16 burst); 

void lcd_rgb_osd2_set_window(u16 stx, u16 sty, u16 endx, u16 endy, u16 alpha, u16 burst); 

void lcd_rgb_osd3_set_window(u16 stx, u16 sty, u16 endx, u16 endy, u16 alpha, u16 burst); 

void video(u16 stx,u16 sty, u16 endx, u16 endy,u16 span,u16 s_w,u16 s_h,u16 d_w,u16 d_h,
          u16 w_step,u16 w_remain,u16 h_step,u16 h_remain,u16 burst);


#endif
