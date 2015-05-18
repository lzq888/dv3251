//===================================================================
//                       INCLUDE FILES                            
//===================================================================
#include "../header/include.h"



#define DB(fmt,args...)   deg_Printf(fmt,##args)			//debug msg
//#define DB(fmt,args...)										//not debug msg

//===============lcd==============
#define MIRRORMODE  0
#define ROTATEMODE  0
#define DISPLAY_CHANNEL		(0xf)	//osd1ãosd2ãosd3ãvideo enable

#define LCD_INTERFACE_SEL	(3)		//0:8080 1:SPI 2:RGB 3:TV
#define ALPHA_MASK	0xff

u32 enlager_offset_len=0;

void tvout_lcd_en()  
{
	REG32(LCDCON0) |= (1 << 6);
}

void tvout_lcd_disen()  
{
	REG32(LCDCON0) &= ~((1 << 6));
}


//Description: è®¾ç½®åå¾æ¯ä¸è¡æ°æ®çå­èæ°ï¼è¦æ±æ?çåæ°
/*static void tvout_lcd_set_line(u16 span)
{
	  if(span%4==0)
        REG32(LCDCON48) = span;
    else 
		REG32(LCDCON48) = span+2; 
}*/


//=====
//src_x,src_yä¸ºYUV buf çèµ·ç?
//src_w,ä¸ºYUV buf çå®½
//src_h,ä¸ºYUV buf çé«
//YUV bufæ?ç§ï¼1ï¼RGB2YUV ï¼?ï¼æåå¤´è¾åºYUV ,æ ¹æ®å½åYUVçå¤§å°è®¾ç½?

//dst_w,ä¸ºTVOUT è¾åº çå®½
//dst_h,ä¸ºTVOUT è¾åº çé«
//tvout mode æä¸ç§ï¼1ï¼lcd ,2: ntsc ,3:pal  åå«å¯¹åºä¸åæ¨¡å¼çè¾åºå¤§å°è®¾ç½®ã?
//=====
void tvout_display_set(int src_x,int src_y,int src_span, int src_w, int src_h,int dst_w,int dst_h)
{

	u32 w_step = src_w*0x100/dst_w;
	u32 w_remain = src_w*0x100 - dst_w * w_step;
	u32 h_step = src_h*0x100/dst_h;
	u32 h_remain = src_h*0x100 - dst_h * h_step;

	 
	u32 burst = 2;

	if(TVOUT_MODE_LCD == tvout_get_cur_mode())		//lcd
	{
		#if (0 == LCD_MCU)
		//set rgb window
		REG32(LCDCON19) = 0+REG32(LCDCON9);
		REG32(LCDCON20) = 0+REG32(LCDCON13);
		REG32(LCDCON21) = dst_w+REG32(LCDCON9)-1;
		REG32(LCDCON22) = dst_h+REG32(LCDCON13)-1;
		lcd_set_line(src_span*2);						//set line
		#else
		//set mcu window
		REG32(LCDCON19) = 0;
		REG32(LCDCON20) = 0;
		REG32(LCDCON21) = dst_w-1;
		REG32(LCDCON22) = dst_h-1;
		lcd_set_line(src_span*2);						//set line
		#endif
	}
	else											//tvout 
	{
		//set window
		REG32(LCDCON19) = 0;
		REG32(LCDCON20) = 0;
		REG32(LCDCON21) = dst_w;
		REG32(LCDCON22) = dst_h;
		REG32(LCDCON48) = src_span*2;					//set line

	}


	REG32(LCDCON49) = w_step;    //W_step
	REG32(LCDCON50) = w_remain;  //W_remain
	REG32(LCDCON51) = h_step;    //H_step
	REG32(LCDCON52) = h_remain;  //H_remain
	
	REG32(LCDCON53) = dst_w;  //D_w
	REG32(LCDCON54) = dst_h;  //D_h
	REG32(LCDCON55) = src_w;  //S_W
	REG32(LCDCON56) = src_h;  //S_H
	REG32(LCDCON59) |= (burst<<6);

	return;
}

/*
static void tvout_lcd_set_video_address(u32 *video_addr)
{
	REG32(LCDCON46)	= (u32)video_addr;
	return;
}

static void tvlcd_rgb2yuv(u32 *adr,const u32 *gImage_video,u32 gImage_video_width,u32 gImage_video_height)
{
	deg_Printf("lcd_rgb2yuv() start\r\n");
    u32 i,j;
    dma_peri2mem(2, (2<<7)|(1<<11)|(1<<1), (0<<11)|(0<<10), 0x14020030, adr, 2400);
    //uart_putstr("\r\n LCD rgb2yuv..."); 
    REG32(RGB_STATUS) =(1<<1);//0:{RGB} 1:{BGR} 2{GRB} 3:{BRG} 4:{GBR} 5:RBG}  //select RGB mode
    //uart_putstr("\r\n LCD rgb2yuv RGB_STATUS...");
    for(j=0;j<gImage_video_height;j++)
    { 
		for(i=0;i<gImage_video_width;i+=2)
		{
			if(i==gImage_video_width-1)                         //å¦ææ¯ä¸è¡çæåä¸ä¸ªåç´?
			{
				if(j==gImage_video_height-1)                    //å¦ææ¯æåä¸è¡çæåä¸ä¸ªåç´?
					REG32(RGB_DAT) =0x02000000|gImage_video[i+j*gImage_video_width];
				else
					REG32(RGB_DAT) =0x01000000|gImage_video[i+j*gImage_video_width];//å¦ææ¯æåä¸ä¸ªåç´ ä½ä¸æ¯æåä¸è¡?
			} 
			else  
			{
				if(i==gImage_video_width-2)                                   //å¦ææ¯åæ°ç¬¬äºä¸ªåç´?
				{
					if(j==gImage_video_height-1)                              //å¦ææ¯æåä¸è¡çåæ°ç¬¬äºä¸ªåç´?
					{
						REG32(RGB_DAT) =gImage_video[i+j*gImage_video_width]&0xffffff;
						REG32(RGB_DAT) =0x02000000 | gImage_video[i+j*gImage_video_width+1];
					}
					else                                                      //å¦ææ¯åæ°ç¬¬äºä¸ªåç´ ä½ä¸æ¯æåä¸è¡?
					{
						REG32(RGB_DAT) =gImage_video[i+j*gImage_video_width]&0xffffff;
						REG32(RGB_DAT) = 0x01000000| gImage_video[i+j*gImage_video_width+1];
					}
				} 
				else
				{
					REG32(RGB_DAT) =gImage_video[i+j*gImage_video_width]&0xffffff;
					REG32(RGB_DAT) =gImage_video[i+j*gImage_video_width+1]&0xffffff;
				}
			}//end if ;else ; 
			while(!((REG32(RGB_STATUS) & 0x01) == 0x01));  
		} //for---convert one line data
    }     //for---convert whole image data
	deg_Printf("lcd_rgb2yuv() end\r\n");
	return;
}
*/

static void tvout_set_panel(int pwidth,int phigh,int default_red,int default_green,int default_blue)
{

	REG32(LCDCON35) = pwidth;
	REG32(LCDCON36) = phigh;
	REG32(LCDCON40) = default_red;
	REG32(LCDCON41) = default_green;
	REG32(LCDCON42) = default_blue;
	return;
}


//================tvout=============
static u32 tvout_mode = TVOUT_MODE_LCD;	// tvout è¾åºæ¨¡å¼
static u32 tvout_w = 0;					// tvout è¾åºæ¨¡å¼çå®½
static u32 tvout_h = 0;					// tvout è¾åºæ¨¡å¼çå®½


static void tvout_mdelay(u32 nms)
{
	int i,j;
	for(i = 0;i < nms;i++)
	{
		for(j = 0;j < 10000;j++)
		{
			asm("nop");
		}
	}
}


//return:TVOUT_MODE_LCD,TVOUT_MODE_NTSC,TVOUT_MODE_PAL
u32 tvout_get_cur_mode()
{
	return tvout_mode;
}

u32 tvout_get_w()
{
	return tvout_w;
}

u32 tvout_get_h()
{
	return tvout_h;
}

static void tvout_lcd_clk_cfg()			// resume to lcd clk
{
	//default setting
		REG32(VDAC_CFG) |= 0x1b;
		REG32(PLL_INT_N) |= 0x8;
		REG32(PLL_FRAC_N) |= 0x0;
		//REG32(PLL_CFG) |= 0xc3;
		REG32(CLKCON2) |= 0x901a;
		//REG32(CLKCON1) |= 0x4;
		//REG32(CLKCON0) |= 0xf;
}

static void tvout_clk_cfg()				//set for tvout clk
{

		REG32(VDAC_CFG) |= (1<<6)|(1<<7);
		//VDAC_CFG &= ~(1<<3);
		REG32(VDAC_CFG) &= ~(0b11<<4);

//======set clk && sel clk=======
//=======32k========ok
#if (0 == DEFAULT_TVOUT_CLK_SELECT)
	    REG32(CLKCON2) |= (1<<15);
		tvout_mdelay(300);
	    REG32(PLL_CFG) &= ~(1<<5)|(1<<4);
	    REG32(PLL_CFG) |= (1<<3);//|(3<<0);
	    REG32(PLL_CFG) &= ~(1<<2);
	    REG32(PLL_CFG) |= (1<<11)|(1<<8);
	    REG32(PLL_INT_N) = 6591;
	    REG32(PLL_FRAC_N) = 52223;
	    REG32(PLL_CFG) |= (1<<13);
		tvout_mdelay(10);
	    REG32(CLKCON1) |= (3<<12); //32k
#elif (1 == DEFAULT_TVOUT_CLK_SELECT)

	//=========osc_12m===========very good
//		REG32(CLKCON2) |= (1<<7);
		REG32(CLKCON2) |= (1<<8)|(1<<7);		//here will be ok
		tvout_mdelay(300);
		REG32(PLL_CFG) &= ~(1<<5);
		REG32(PLL_CFG) |= (1<<4);
		REG32(CLKCON0) |= (1<<24);	
		REG32(PLL_CFG) |= (1<<3);
		REG32(PLL_CFG) |= (1<<11)|(1<<8);
		REG32(PLL_CFG) &= ~((1<<2)|(1<<1)|(1<<0));
		REG32(PLL_INT_N) = 13;
		REG32(PLL_FRAC_N) = 32767;//32855:è¯¥åæ°æååä¹ä¸çè¯¯å·?
		REG32(PLL_CFG) |= (1<<13);
		tvout_mdelay(10);
		REG32(CLKCON1) |= (2<<12);//12M osc
#endif

	//========RC_11_94M==========,not good
/*
		REG32(PLL_CFG) &= ~(1<<4);
		REG32(PLL_CFG) |= (1<<5);
		REG32(CLKCON0) |= (1<<24);	
		REG32(PLL_CFG) |= (1<<3);
		REG32(PLL_CFG) |= (1<<11)|(1<<8);
		REG32(PLL_CFG) &= ~((1<<2)|(1<<1)|(1<<0));
		REG32(PLL_INT_N) = 14;
		REG32(PLL_FRAC_N) = 52955;
		REG32(PLL_CFG) |= (1<<13);
		tvout_mdelay(10);
		REG32(CLKCON1) |= (2<<12);	//11.94M RC
*/
	//========USB_11_42M=========not good
/*
		REG32(PLL_CFG) &= ~(1<<5);
		REG32(PLL_CFG) |= (1<<4);
		REG32(CLKCON0) &= ~(1<<24);	
		REG32(PLL_CFG) |= (1<<3);
		REG32(PLL_CFG) |= (1<<11)|(1<<8);
		REG32(PLL_CFG) &= ~((1<<2)|(1<<1)|(1<<0));
		REG32(PLL_INT_N) = 14;
		REG32(PLL_FRAC_N) = 9892;
		REG32(PLL_CFG) |= (1<<13);
		tvout_mdelay(10);
		REG32(CLKCON1) |= (2<<12);	//11.42M RC
*/

}

static void tv_write_reg(u8 addr, u8 d)
{

   REG32(CVE2_REGADDR) = addr;
   REG32(CVE2_REGDIN) = d;
   REG32(CVE2_REGCTL) |= 0x01;
   while(REG32(CVE2_REGCTL));
}
/*
static u8 tv_read_reg(u8 addr)
{

   u8 temp;
   REG32(CVE2_REGADDR) = addr;
   REG32(CVE2_REGCTL) |= 0x02;
   while(REG32(CVE2_REGCTL));
   temp = REG32(CVE2_REGDOUT);
   return temp;

}*/

static void tv_write_dac_reg(u8 addr,u32 data)
{
//	CVE2_CTL = (1<<31)|(addr<<24)|data;
	REG32(CVE2_CTL) = (1<<31)|(addr<<24)|data;

}

//todo:implement in the future
/*void tv_read_dac_reg(u8 addr)
{
//	REG32(CVE2_CTL) = (0<<31) | (addr);
}
*/
static void tv_enable()		//open tvout 
{
	tv_write_dac_reg(TVDAC_CTRL,0x141);
}

void tv_disable(void)		//close tvout
{
	REG32(VDAC_CFG) &= ~(1<<7);
}

/*static void tvout_reg_printf()
{
	int i;
	for(i = 0;i <= 77;i++)
	{
		DB("tvreg%d = 0x%x\n",i,tv_read_reg(i));
	}
	
	for(i = 0;i <= 59;i++)
	{
		DB("REG32(LCDCON%d) = 0x%x \n",i,REG32(LCDCON0+i*0x4));
	}
	
	DB("REG32(VDAC_CFG) = 0x%x \n",REG32(VDAC_CFG));
	DB("REG32(PLL_INT_N) = 0x%x \n",REG32(PLL_INT_N));
	DB("REG32(PLL_FRAC_N) = 0x%x \n",REG32(PLL_FRAC_N));
	DB("REG32(PLL_CFG) = 0x%x \n",REG32(PLL_CFG));
	DB("REG32(CLKCON2) = 0x%x \n",REG32(CLKCON2));
	DB("REG32(CLKCON1) = 0x%x \n",REG32(CLKCON1));
	DB("REG32(CLKCON0) = 0x%x \n",REG32(CLKCON0));
	DB("REG32(PCON0) = 0x%x \n",REG32(PCON0));
}*/

static void tvout_ntsc_reg_init()
{
	//default set all reg

		tv_write_reg(0,0x21);
		tv_write_reg(1,0xf0);
		tv_write_reg(2,0x7c);
		tv_write_reg(3,0x1f);
		tv_write_reg(4,0x0);
		tv_write_reg(5,0x0);
		tv_write_reg(6,0x9);
		tv_write_reg(7,0x0);
		tv_write_reg(8,0x7e);
		tv_write_reg(9,0x44);
		
		tv_write_reg(10,0x76);
		tv_write_reg(11,0x3b);
		tv_write_reg(12,0x0);
		tv_write_reg(13,0x0);
		tv_write_reg(14,0x46);
		tv_write_reg(15,0x2);
		tv_write_reg(16,0x3c);
		tv_write_reg(17,0x0);
		tv_write_reg(18,0x17);
		tv_write_reg(19,0x21);
		
		tv_write_reg(20,0x1b);
		tv_write_reg(21,0x1b);
		tv_write_reg(22,0x24);
		tv_write_reg(23,0x83);
		tv_write_reg(24,0x1);
		tv_write_reg(25,0x3e);
		tv_write_reg(26,0xf);
		tv_write_reg(27,0xf);
		tv_write_reg(28,0x60);
		tv_write_reg(29,0x5);
		
		tv_write_reg(30,0xc8);
		tv_write_reg(31,0x0);
		tv_write_reg(32,0x89);
		tv_write_reg(33,0x4);
		tv_write_reg(34,0x89);
		tv_write_reg(35,0x1);
		tv_write_reg(36,0x2);
		tv_write_reg(37,0x0);
		tv_write_reg(38,0xa);
		tv_write_reg(39,0x5);

		tv_write_reg(40,0x0);
		tv_write_reg(41,0x16);
		tv_write_reg(42,0xff);
		tv_write_reg(43,0x3);
		tv_write_reg(44,0x20);
		tv_write_reg(45,0xf);
		tv_write_reg(46,0x78);
		tv_write_reg(47,0x0);
		tv_write_reg(48,0x0);
		tv_write_reg(49,0xb4);

		tv_write_reg(50,0x0);
		tv_write_reg(51,0x16);
		tv_write_reg(52,0x2);
		tv_write_reg(53,0x48);
		tv_write_reg(54,0x0);
		tv_write_reg(55,0xa3);
		tv_write_reg(56,0xc8);
		tv_write_reg(57,0x15);
		tv_write_reg(58,0x5);
		tv_write_reg(59,0x15);

		tv_write_reg(60,0x4a);
		tv_write_reg(61,0x0);
		tv_write_reg(62,0x1);
		tv_write_reg(63,0x20);
		tv_write_reg(64,0x7);
		tv_write_reg(65,0x2f);
		tv_write_reg(66,0x7);
		tv_write_reg(67,0x0);
		tv_write_reg(68,0x0);
		tv_write_reg(69,0x0);
		
		tv_write_reg(70,0x0);
		tv_write_reg(71,0x0);
		tv_write_reg(72,0x0);
		tv_write_reg(73,0x0);
		tv_write_reg(74,0x0);
		tv_write_reg(75,0xff);
		tv_write_reg(76,0x3);

}

static void tvout_pal_reg_init()
{
		//config chroma freq
		tv_write_reg(0,0x2A);
		tv_write_reg(1,0x09);
		tv_write_reg(2,0x8A);
		tv_write_reg(3,0xCB);
		//for test
		if (0)
		{
			//chroma bw
			tv_write_reg(7,0);//
			//cb_gain cr_gain  //å½ä¸¤èé½ä¸ºé¶æ¶ï¼è²åº¦ä¿¡å·ä¸ºé¶å³é»ç?
			tv_write_reg(32,0x00);
			tv_write_reg(34,0x00);
		}


		//config chroma phase
		tv_write_reg(4,0x00);
		//tv_write_reg(37,90);

		//config black level
		tv_write_reg(14,0x3f);
		tv_write_reg(15,0x00);

		//config blank level
		tv_write_reg(16,0x3f);
		tv_write_reg(17,0x00);

		//config vbi blank level
		tv_write_reg(60,0x3f);
		tv_write_reg(61,0x00);

		//sync base level
		tv_write_reg(53,0x10);//16

		if (PAL_DEFINITION) 
		{
			DB("PAL_DEFINITION	702*576 \r\n");
			//config active pixel number. NTSC=1440; PAL = 1404.	
			tv_write_reg(49,0xAF);
			tv_write_reg(50,0x4);
		}
		else
		{
			DB("PAL_DEFINITION	720*576 \r\n");
			//the defaut setting is 1440/2=720
			//config active pixel number. NTSC=1440; PAL = 1404.	
		}

		//config line number 625=0x9c*4+0x01; 576=625-24.5*2(å¥å¶åºçè¡æ¶é?
		tv_write_reg(23,0x9c);  
		tv_write_reg(24,0x01); 

		//first video line //
		tv_write_reg(51,22);

		//Horizontal sync pulse width
		tv_write_reg(8,63*2);//  63 point

		//config burst width
		tv_write_reg(9,31*2);//31 point	
		//config breez width
		tv_write_reg(41,12*2);//12 point
		
		//	éç½®row10è¦èèrow41årow9ï¼row*2 = row41 + row9 + 11 + Pï¼Pä¸ºä½é?
		if (PAL_DEFINITION) 
		{
			//config back porch width
			tv_write_reg(10,79*2);
		}
		else
		{
			//config back porch width
			tv_write_reg(10,59*2);
		}
		//config front porch width
		tv_write_reg(44,20*2);//20 point

		//change the peek2peek value of the burst signal
		//pal, CB burst amp
		tv_write_reg(11,0x2a);
		//pal, CR burst amp
		tv_write_reg(12,0x2a);
 
		//cb\crçååå³ç³»ï¼éè¦ä¸LCDCç¸å palæ¨¡å¼(é»è®¤æ¯NTSC) å¥å¶åºæ å¿ä½(æ¹åè²åæ­¥ä¿¡å·çç¸ä½ãè§é¢æåãp199)
		//enable pal, sys625_50 , cphase_rst(2b),vsync5
		tv_write_reg(52,0x5f);//0x5b:æ¯ä¸¤è¡éè½½ä¸æ¬¡ï¼å¤´é¨å è¡ä¼æå?0x5f:11bä¸éè½?
}


//=====arg type: 0 is lcd,  1 is tv_ntsc  ,2 is tv_pal====

void tvout_set_cur_mode(u8 type)
{
	lcd_set_backlight(0);	//close backlight
	tvout_lcd_disen();
	REG32(PCON0)   &= ~(1<<29);    	// enable LCD clock
	REG32(PCON0)   &= ~(1<<22);    	// enable TV clock
	if(TVOUT_MODE_LCD == type)
	{
		DB("tvout is lcd \n");
		tv_disable();
		
		tvout_mode = TVOUT_MODE_LCD;
		tvout_w = lcd_get_w();
		tvout_h = lcd_get_h();
		DB("tvout_w =%d,tvout_h = %d \n",tvout_w,tvout_h);
		
		tvout_lcd_clk_cfg();	//init clk

		REG32(LCDCON0) &= ~((1<<9)|(1 << 7)|(1 << 6) | (1 << 5) |(1 << 4)|(1 << 3)|(LCD_INTERFACE_SEL<<1)|(1<<0));			//disabled
		lcd_set_panel_colour(0,0,0);
		lcd_init();	

//		REG32(LCDCON0) |= (0 << 8)|(1 << 6) |(1 << 0);							//video_en,osd3_en,osd2_en,osd1_en,lcd_en
		//=======after set clk=====
		tvout_lcd_disen();
		waittingLcdFrameEnd();
		set_video_address(VIDEO_BASE_SDRAM_ADDR);		
		tvout_display_set(0,0,u32csi_Dma_Size_H,u32csi_Dma_Size_H,u32csi_Dma_Size_V,tvout_get_w(),tvout_get_h());
		waittingLcdFrameEnd();
		tvout_lcd_en();
//		REG32(LCDCON0) &= ~BIT(7);	//write back disable

		
		//lcd_set_backlight(1);	//open backlight

	}
	else if(TVOUT_MODE_NTSC == type)
	{
		DB("tvout is ntsc \n");
		tvout_mode = TVOUT_MODE_NTSC;
		tvout_w = 720;
		tvout_h = 480;
		DB("tvout_w =%d,tvout_h = %d \n",tvout_w,tvout_h);
		
		tvout_clk_cfg();			//tvout clk set
		tvout_ntsc_reg_init();		//ntsc reg init
		SetIntSrc(LCD_INT);			//open lcd int 
		REG32(LCDCON0) |= 1<<10;	
		
		tvout_set_panel(tvout_get_w()-1,tvout_get_h()-1,0,0,250);

		tvout_display_set(0,0,u32csi_Dma_Size_H,u32csi_Dma_Size_H,u32csi_Dma_Size_V,tvout_get_w(),tvout_get_h());
	
		
		REG32(LCDCON47)	= (0<<0)//warped distance enable
					| (4<<1)//warped distance (4 recommended)
					| (ROTATEMODE<<4)//rotate mode 0\1 disable\180
					| (MIRRORMODE<<5)//mirror mode 0\1\2\3 disable\up_and_down\left_and_right\up_and_down_left_and_right
				    | (1<<8);
		REG32(LCDCON0)		|=	(0<<0)	//[0]:		lcd enable
					|	(LCD_INTERFACE_SEL<<1)	//[2:1]:	TV out
					|	(DISPLAY_CHANNEL<<3)//[3:6]:	osd1ãosd2ãosd3ãvideo enable
					|	(1<<9); //[9]: odd_and_even line first 0/1 even/odd
		
		tvout_lcd_en();
		tv_enable();
		Delay_MS(100);		// let tvout work steady

	}
	else
	{
		DB("tvout is pal \n");
		tvout_mode = TVOUT_MODE_PAL;
		if(0 == PAL_DEFINITION)
		{
			tvout_w = 720;
			tvout_h = 576;
		}
		else
		{
			tvout_w = 702;
			tvout_h = 576;
		}
		DB("tvout_w =%d,tvout_h = %d \n",tvout_w,tvout_h);
		tvout_clk_cfg();			//tvout clk set
		tvout_pal_reg_init();		//pal reg init

		SetIntSrc(LCD_INT);			//open lcd int
		REG32(LCDCON0) |= 1<<10;	
		
		tvout_set_panel(tvout_get_w()-1,tvout_get_h()-1,0,0,250);

		tvout_display_set(0,0,u32csi_Dma_Size_H,u32csi_Dma_Size_H,u32csi_Dma_Size_V,tvout_get_w(),tvout_get_h());

		REG32(LCDCON47)	=	(0<<0)//warped distance enable
					|	(4<<1)//warped distance (4 recommended)
					|	(ROTATEMODE<<4)//rotate mode 0\1 disable\180
					|	(MIRRORMODE<<5)//mirror mode 0\1\2\3 disable\up_and_down\left_and_right\up_and_down_left_and_right
					| (1<<8);
		REG32(LCDCON0)		|=	(0<<0)	//[0]:		lcd enable
					|	(LCD_INTERFACE_SEL<<1)	//[2:1]:	TV out
					|	(DISPLAY_CHANNEL<<3)//[3:6]:	osd1ãosd2ãosd3ãvideo enable
					|	(0<<9) //[9]: odd_and_even line first 0/1 even/odd
					|	(0<<10)//one frame display finish pending interrupt 
					|	(0<<11)//write back 8line finish pending interrupt
					|	(0<<12);//video or osd buffer empty pending interrupt
		REG32(LCDCON0) &= ~((1 << 9) );	//[9]: odd_and_even line first 0/1 even/odd
		
		tvout_lcd_en();
		tv_enable();
		Delay_MS(100);		// let tvout work steady
		
	}
	
	OSDInfInit();
//	tvout_reg_printf();

}


void tvout_Set_Dis_Offset(u32 offset_x,u32 offset_y,u32 src_span)
{
	enlager_offset_len = (src_span*offset_y + offset_x)*2;
	//REG32(LCDCON46) = VIDEO_BASE_SDRAM_ADDR+enlager_offset_len;	
}

void tvout_Change_dis_size(u8 factor, bool updateFlag)
{
	static u8 u8pre_factor = 0;
	u32 tmpLCDcon46 = 0;
	u32 lcd_con_reg_save;
	if(!updateFlag)
	{
		if(u8pre_factor != factor)
			u8pre_factor = factor;
		else
			return;
	}
		
	switch(factor)
	{

		case 0:
			lcd_con_reg_save = REG32(LCDCON0);
			DIS_OSD1();
			DIS_OSD2();
			DIS_OSD3();
			lcd_set_panel_colour(0,0,0);
			#if(0 == LCD_MCU)
				waittingLcdFrameEnd();
				REG32(LCDCON0) &= ~(BIT(0)|BIT(6));
				tmpLCDcon46 = REG32(LCDCON46);
				tvout_Set_Dis_Offset(0,0,u32csi_Dma_Size_H);
				while (tmpLCDcon46 == REG32(LCDCON46));
				tvout_display_set(0,0,u32csi_Dma_Size_H,u32csi_Dma_Size_H,u32csi_Dma_Size_V,tvout_get_w(),tvout_get_h());	
				REG32(LCDCON0) = lcd_con_reg_save;
				REG32(LCDCON0) |= (BIT(0)|BIT(6));
			#else
				REG32(LCDCON0) &= ~(BIT(6));
				waittingLcdFrameEnd();
				tmpLCDcon46 = REG32(LCDCON46);
				tvout_Set_Dis_Offset(0,0,u32csi_Dma_Size_H);
				while (tmpLCDcon46 == REG32(LCDCON46));
				tvout_display_set(0,0,u32csi_Dma_Size_H,u32csi_Dma_Size_H,u32csi_Dma_Size_V,tvout_get_w(),tvout_get_h());	
				waittingLcdFrameEnd();
				REG32(LCDCON0) = lcd_con_reg_save;
				REG32(LCDCON0) |= (BIT(6));
			#endif
		break;
		case 1:
			lcd_con_reg_save = REG32(LCDCON0);
			DIS_OSD1();
			DIS_OSD2();
			DIS_OSD3();
			lcd_set_panel_colour(0,0,0);
			#if(0 == LCD_MCU)
				waittingLcdFrameEnd();
				REG32(LCDCON0) &= ~(BIT(0)|BIT(6));
				tmpLCDcon46 = REG32(LCDCON46);
				tvout_Set_Dis_Offset(u32csi_Dma_Size_H/4,u32csi_Dma_Size_V/4,u32csi_Dma_Size_H);
				while (tmpLCDcon46 == REG32(LCDCON46));
				tvout_display_set(0,0,u32csi_Dma_Size_H,u32csi_Dma_Size_H/2,u32csi_Dma_Size_V/2,tvout_get_w(),tvout_get_h());	
				REG32(LCDCON0) = lcd_con_reg_save;
				REG32(LCDCON0) |= (BIT(0)|BIT(6));
			#else
				REG32(LCDCON0) &= ~(BIT(6));
				waittingLcdFrameEnd();
				tmpLCDcon46 = REG32(LCDCON46);
				tvout_Set_Dis_Offset(u32csi_Dma_Size_H/4,u32csi_Dma_Size_V/4,u32csi_Dma_Size_H);
				while (tmpLCDcon46 == REG32(LCDCON46));
				tvout_display_set(0,0,u32csi_Dma_Size_H,u32csi_Dma_Size_H/2,u32csi_Dma_Size_V/2,tvout_get_w(),tvout_get_h());	
				waittingLcdFrameEnd();
				REG32(LCDCON0) = lcd_con_reg_save;
				REG32(LCDCON0) |= (BIT(6));
			#endif
			
		break;
		case 2:
			lcd_con_reg_save = REG32(LCDCON0);
			DIS_OSD1();
			DIS_OSD2();
			DIS_OSD3();
			lcd_set_panel_colour(0,0,0);
			#if(0 == LCD_MCU)
				waittingLcdFrameEnd();
				REG32(LCDCON0) &= ~(BIT(0)|BIT(6));
				tmpLCDcon46 = REG32(LCDCON46);
				tvout_Set_Dis_Offset(u32csi_Dma_Size_H*3/8,u32csi_Dma_Size_V*3/8,u32csi_Dma_Size_H);
				while (tmpLCDcon46 == REG32(LCDCON46));
				tvout_display_set(0,0,u32csi_Dma_Size_H,u32csi_Dma_Size_H/4,u32csi_Dma_Size_V/4,tvout_get_w(),tvout_get_h());	
				REG32(LCDCON0) = lcd_con_reg_save;
				REG32(LCDCON0) |= (BIT(0)|BIT(6));
			#else
				REG32(LCDCON0) &= ~(BIT(6));
				waittingLcdFrameEnd();
				tmpLCDcon46 = REG32(LCDCON46);
				tvout_Set_Dis_Offset(u32csi_Dma_Size_H*3/8,u32csi_Dma_Size_V*3/8,u32csi_Dma_Size_H);
				while (tmpLCDcon46 == REG32(LCDCON46));
				tvout_display_set(0,0,u32csi_Dma_Size_H,u32csi_Dma_Size_H/4,u32csi_Dma_Size_V/4,tvout_get_w(),tvout_get_h());	
				waittingLcdFrameEnd();
				REG32(LCDCON0) = lcd_con_reg_save;
				REG32(LCDCON0) |= (BIT(6));
			#endif
		break;
		default:
			break;


	}
}

void tvout_Change_display(void)
{
	if(0 == video_enlager)
	{
		tvout_Set_Dis_Offset(0,0,u32csi_Dma_Size_H);
		tvout_display_set(0,0,u32csi_Dma_Size_H,u32csi_Dma_Size_H,u32csi_Dma_Size_V,tvout_get_w(),tvout_get_h());	
	}
	else if(1 == video_enlager)
	{
		tvout_Set_Dis_Offset(u32csi_Dma_Size_H/4,u32csi_Dma_Size_V/4,u32csi_Dma_Size_H);
		tvout_display_set(0,0,u32csi_Dma_Size_H,u32csi_Dma_Size_H/2,u32csi_Dma_Size_V/2,tvout_get_w(),tvout_get_h());	
	}
	else if(2 == video_enlager)
	{
		tvout_Set_Dis_Offset(u32csi_Dma_Size_H*3/8,u32csi_Dma_Size_V*3/8,u32csi_Dma_Size_H);
		tvout_display_set(0,0,u32csi_Dma_Size_H,u32csi_Dma_Size_H/4,u32csi_Dma_Size_V/4,tvout_get_w(),tvout_get_h());	
	}
}


