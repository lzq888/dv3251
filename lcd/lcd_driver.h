#ifndef __LCD_DRIVER_H__
#define __LCD_DRIVER_H__

struct spimode 
{   
	  //LCDCON47
	  u8  rotatemode;
	  u8   mirror; 
	  u8  yminus16; 
	  //LCDCON35
	  u16 pwidth;
	  //LCDCON36
	  u16 pheight;
	  //LCDCON58
	  u32 lcd_line_dclks;
	  //LCDCON1
	  u8  even_rgb_order;
	  u8  odd_rgb_order;
	  u8  red_width;
	  u8  green_width;
	  u8  blue_width;
	  //LCDCON2
	  u8  shift_width;
	  u8  expand_loc;
	  u8  expand_width;
	  //LCDCON15   
	  u8  datactrl_mode;
	  u8  cs_oen;
   // u8  wr_inv;
	  u8  cs_inv;
	 // u8  wr_fp;
	 // u8  wr_rp;
	  u8  cs_pr; 
	  //LCDCON16
     u8 spi_id_st;
     u8 spi_smp_sel;
     u8 spi_1dw;
     u8 spi_1dw_dir;
     u8 spi_9biten;
     u8 spi_9bit;
     // LCDCON 17
     u8  spi_baud;
	//LCDCON60
	u16 interval;
};
struct emimode 
{   
	  //LCDCON47
	  u8  rotatemode;
	  u8   mirror; 
	  u8  yminus16; 
	  //LCDCON35
	  u16 pwidth;
	  //LCDCON36
	  u16 pheight;
	  //LCDCON58
	  u32 lcd_line_dclks;
	  //LCDCON1
	  u8  even_rgb_order;
	  u8  odd_rgb_order;
	  u8  red_width;
	  u8  green_width;
	  u8  blue_width;
	  //LCDCON2
	  u8  shift_width;
	  u8  expand_loc;
	  u8  expand_width;	 
	  
	  //LCDCON4
	  u32 data_en;
		u8  data_inv;
	  //LCDCON6
	  u8  clkdiv;
	  u8  div2_duty;
	  //LCDCON15   
	  u8  datactrl_mode;
	  u8  cs_oen;
    u8  wr_inv;
	  u8  cs_inv;
	  u8  wr_fp;
	  u8  wr_rp;
	  u8  cs_pr;
	//LCDCON60
	u16 interval; 
};    
struct spirgbmode 
{   
	//LCDCON1
	u8  even_rgb_order;
	u8  odd_rgb_order;
	u8  red_width;
	u8  green_width;
	u8  blue_width;
	//LCDCON2
	u8  shift_width;
	u8  expand_loc;
	u8  expand_width;
	//LCDCON3
	u8  vsync_en; 
	u8  hsync_en; 
	u8  de_en;
	u8  dclk_en;
	u8  vsync_inv;
	u8  hsync_inv;
	u8  de_inv;
	u8  dclk_inv;

	//LCDCON4
	u32 data_en;
	u8  data_inv;
	
	//LCDCON6
	u8  vsync_inact_at;
	u8  vsync_up_neg_edge;
	u8  hsync_up_neg_edge;
	u8  de_up_neg_edge;
	u8  clkdiv;
	u8  div2_duty;
	u8  holdclk_en;
	u8  slowdnclk_en;
	u8  slowdncnt_en;
	u8  video_slowdn_c;
	u8  osd_slowdn_c;

	//LCDCON7
	u16 vsrp;
	//LCDCON8
	u16 hsrp;
	//LCDCON10
	u16 vspw;
	//LCDCON11
	u16 hspw;

	//LCDCON15   
	u8  datactrl_mode;
	u8  cs_oen;
	// u8  wr_inv;
	u8  cs_inv;
	// u8  wr_fp;
	// u8  wr_rp;
	u8  cs_pr; 
	//LCDCON16
	u8  spi_id_st;
	u8  spi_smp_sel;
	u8  spi_1dw;
	u8  spi_1dw_dir;
	u8  spi_9biten;
	u8  spi_9bit;
	// LCDCON 17
	u8  spi_baud;
	
	//LCDCON47
	u8  rotatemode;
	u8  mirror; 
	u8  yminus16; 
	//LCDCON35
	u16 hbpd;
	u16 hozval;
	u16 hfpd;
	//LCDCON36
	u16 vbpd;
	u16 lineval; 
	u16 vfpd;
	//LCDCON60
	u16 interval;
};
struct rgbmode 
{   
	//LCDCON1
	u8  even_rgb_order;
	u8  odd_rgb_order;
	u8  red_width;
	u8  green_width;
	u8  blue_width;
	//LCDCON2
	u8  shift_width;
	u8  expand_loc;
	u8  expand_width;
	//LCDCON3
	u8  vsync_en; 
	u8  hsync_en; 
	u8  de_en;
	u8  dclk_en;
	u8  vsync_inv;
	u8  hsync_inv;
	u8  de_inv;
	u8  dclk_inv;

	//LCDCON4
	u32 data_en;
	u8  data_inv;
	
	//LCDCON6
	u8  vsync_inact_at;
	u8  vsync_up_neg_edge;
	u8  hsync_up_neg_edge;
	u8  de_up_neg_edge;
	u8  clkdiv;
	u8  div2_duty;
	u8  holdclk_en;
	u8  slowdnclk_en;
	u8  slowdncnt_en;
	u8  video_slowdn_c;
	u8  osd_slowdn_c;

	//LCDCON7
	u16 vsrp;
	//LCDCON8
	u16 hsrp;

	//LCDCON10
	u16 vspw;
	//LCDCON11
	u16 hspw;

	//LCDCON47
	u8  rotatemode;
	u8  mirror; 
	u8  yminus16; 
	//LCDCON35
	u16 hbpd;
	u16 hozval;
	u16 hfpd;
	//LCDCON36
	u16 vbpd;
	u16 lineval; 
	u16 vfpd;

	/*	//LCDCON15   
	u8  datactrl_mode;
	u8  cs_oen;
	// u8  wr_inv;
	u8  cs_inv;
	// u8  wr_fp;
	// u8  wr_rp;
	u8  cs_pr; 
	//LCDCON16
	u8 spi_id_st;
	u8 spi_smp_sel;
	u8 spi_1dw;
	u8 spi_1dw_dir;
	u8 spi_9biten;
	u8 spi_9bit;
	// LCDCON 17
	u8  spi_baud;*/
	//LCDCON60
	u16 interval;
    
};


void delay_us(u32 delay_us_cnt);

void delay_ms(u32 delay_ms_cnt); 


void lcd_spi_putchar(u8 u8data);

u8 lcd_spi_getchar(void);
#if 0
void lcd_write_data(u16 u16data);

void lcd_spi_timing_init(struct spimode p);
#endif
void lcd_emi_timing_init(struct emimode p);

void lcd_spirgb_timing_init(struct spirgbmode p);

void lcd_rgb_timing_init(struct rgbmode p);

void datactrl_mode_sel();

void spi_to_rgb();
void lcd_Isr(void);
void reset_rgb_data_en(u32 data_en);
void waittingLcdFrameEnd();
#endif 
