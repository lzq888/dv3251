
#ifndef __LCD_INTERFACE_H__
#define __LCD_INTERFACE_H__

#define OSD1_LUT_ADR  0x10080000
#define OSD2_LUT_ADR  0x10080400
#define OSD3_LUT_ADR  0x10080800


#define OFFSET(X)        X+0x0000A000

void lcd_emi_osd1_display(u16 osd_x, u16 osd_y, u16 gImage_width ,u16 gImage_height,
                     u32 *gImage_osd, u16 alpha, u8 mode); 

void lcd_emi_osd2_display(u16 osd_x, u16 osd_y, u16 gImage_width ,u16 gImage_height,
                     u32 *gImage_osd, u16 alpha, u8 mode); 

void lcd_emi_osd3_display(u16 osd_x, u16 osd_y, u16 gImage_width ,u16 gImage_height,
                     u32 *gImage_osd, u16 alpha, u8 mode);  

void lcd_emi_video_display_normal(u16 video_x, u16 video_y,u16 gImage_width ,u16 gImage_height,
                     u32 *gImage_video);
                     
void lcd_emi_video_display_zoom(u16 video_x,u16 video_y,u16 s_width,u16 s_height,u16 d_width, u16 d_height,
                      u16 w_step,u16 w_remain,u16 h_step,u16 h_remain,u32 *gImage_video);
                      
void lcd_writeback(u32 adr,u16 gImage_width ,u16 gImage_height); 
                     
void lcd_emi_video_display_wbdata(u16 video_x, u16 video_y,u16 gImage_width ,u16 gImage_height,u32 adr);

void lcd_rgb_osd1_display(u16 osd_x, u16 osd_y, u16 gImage_width ,u16 gImage_height,
                     u32 *gImage_osd, u16 alpha, u8 mode); 

void lcd_rgb_osd2_display(u16 osd_x, u16 osd_y, u16 gImage_width ,u16 gImage_height,
                     u32 *gImage_osd, u16 alpha, u8 mode); 

void lcd_rgb_osd3_display(u16 osd_x, u16 osd_y, u16 gImage_width ,u16 gImage_height,
                     u32 *gImage_osd, u16 alpha, u8 mode);  

void lcd_rgb_video_display_normal(u16 video_x, u16 video_y,u16 gImage_width ,u16 gImage_height,
                     u32 *gImage_video);
                     
void lcd_rgb_video_display_zoom(u16 video_x,u16 video_y,u16 s_width,u16 s_height,u16 d_width, u16 d_height,
                      u16 w_step,u16 w_remain,u16 h_step,u16 h_remain,u32 *gImage_video);

void lcd_rgb_video_display_zoomChEnd(u16 video_x,u16 video_y,u16 s_width,u16 s_height,u16 d_width, u16 d_height,
                      u16 w_step,u16 w_remain,u16 h_step,u16 h_remain,u32 *gImage_video);
                     
void lcd_rgb_video_display_wbdata(u16 video_x, u16 video_y,u16 gImage_width ,u16 gImage_height,u32 adr);

void lcd_PostScale_Start(void);
void lcd_PostScale_Stop(void);
                      
#endif