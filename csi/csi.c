/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : csi.c
* Author             : pengtao_zhang
* Version            : V0904a
* Date               : 09/04/2013
* Description        : This file provides all the csi firmware functions.
***************************************************************************/
//===================================================================
//                                                     	            |
//                       INCLUDE FILES                              |
//                                                                  |
//===================================================================
#include "../header/include.h"

//===================================================================
//                                                     	            |
//                      GLOBAL VARIABLE                             |
//                                                                  |
//===================================================================
u32 u32csi_Dma_Size_H,u32csi_Dma_Size_V;
u32 u32sdr_Buff_Len;
u32 u32MDCnt;
BOOL bMD_StopVideo_Flag;
BOOL bSameSizeFlag;
u32 csi_timeout;
#define CSI_TIMEOUT 	10000000
/*******************************************************************************
* Function Name  : csi_Init
* Description    : initial csi clock
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void csi_Init(void)
{
	deg_Printf("CSI Init\n");
	REG32(CLKCON2) &= ~BIT(26);
	Delay_nopCnt(100);
	REG32(CLKCON2) |= BIT(26);

	REG32(CLKCON0) &= ~BIT(11);    			//csi clk select usb pll
	REG32(CLKCON0) &= ~(BIT(12)|BIT(13));   //csi clk select;00: pll div out;01: pll out without div;
//	REG32(CLKCON0) |= BIT(12);              //10:pix_clk input;11:external crystal oscillator
//	REG32(CLKCON0) |= BIT(13);
	#if ((SEN_USE == SEN_GC0308)||(SEN_USE == SEN_NT99141)||(SEN_USE == SEN_BF3925)||(SEN_USE == SEN_NT99240)||(SEN_USE == SEN_SIV100B))
		REG32(CLKCON0) |= BIT(13);	
	#endif
	CLRB(REG32(PCON0), 23);					//csi Clock Enable
	#if(SYS_CLK	== 120000000)
		#if(SEN_USE == SEN_OV9710)
		REG32(CLKCON1) &= 0x0fffffff;			//csi clk =pll/(2+1)=240/3=80M
		REG32(CLKCON1) |= 3<<28;
		#elif(SEN_USE == SEN_NT99140)
		REG32(CLKCON1) &= 0x0fffffff;			//csi clk =pll/(2+1)=240/3=80M
		REG32(CLKCON1) |= 2<<28;
		#elif(SEN_USE == SEN_NT99141)
		REG32(CLKCON1) &= 0x0fffffff;			//csi clk =pll/(2+1)=240/3=80M
		REG32(CLKCON1) |= 2<<28;
		#elif(SEN_USE == SEN_NT99240)
		REG32(CLKCON1) &= 0x0fffffff;			//csi clk =pll/(2+1)=240/3=80M
		REG32(CLKCON1) |= 2<<28;
		#elif((SEN_USE == SEN_OV7670))
		REG32(CLKCON1) &= 0x0fffffff;			//csi clk =pll/(4+1)=240/5=48M
		REG32(CLKCON1) |= 4<<28;
		#elif((SEN_USE == SEN_SIV121DS))
		REG32(CLKCON1) &= 0x0fffffff;			//csi clk =pll/(4+1)=240/5=48M
		REG32(CLKCON1) |= 4<<28;
		#elif((SEN_USE == SEN_OV7725))
		REG32(CLKCON1) &= 0x0fffffff;			//csi clk =pll/(4+1)=240/5=48M
		REG32(CLKCON1) |= 4<<28;
		#endif
	#elif(SYS_CLK	== 48000000)
	REG32(CLKCON1) &= 0x0fffffff;			//csi clk =pll/(4+1)=240/5=48M
	REG32(CLKCON1) |= 4<<28;
	#endif

	csi_TimeInfo_Init();
	if(sys_ctl.jpeg_video_size == VIDEO_SIZE_640_480) 
	{
		u32csi_Dma_Size_H  = 320;
		u32csi_Dma_Size_V  = 240;
	}
	else if((sys_ctl.jpeg_video_size == VIDEO_SIZE_1280_720) || (sys_ctl.jpeg_video_size == VIDEO_SIZE_1920_1080))
	{

		#if (SEN_USE == SEN_GC0308||SEN_USE == SEN_OV7670||SEN_USE == SEN_SIV121DS||SEN_USE == SEN_OV7725||SEN_USE == SEN_SIV100B)//vga
			u32csi_Dma_Size_H  = 640;
			u32csi_Dma_Size_V  = 480;
		#else						//720p
		    #if(DEFAULT_TVOUT_EN == 1)
			u32csi_Dma_Size_H  = 640;
			u32csi_Dma_Size_V  = 360;
			#else
			u32csi_Dma_Size_H  = 640;
			u32csi_Dma_Size_V  = 360;
			#endif
		#endif
	}
}

/*******************************************************************************
* Function Name  : csi_ParameterSet
* Description    : set csi parameter
* Input          : recordtype: 0:picture; 1:video
*                   u8resType: resolution type
* Output         : None
* Return         : None
*******************************************************************************/
void csi_ParameterSet(u8 recordtype,u8 u8resType)
{	
	if(recordtype == 0)
	{
		if(u8resType == JPEG_SIZE_640_480)
		{
			u32csi_Dma_Size_H  = 320;
			u32csi_Dma_Size_V  = 240;
		}
		else if(u8resType == JPEG_SIZE_1280_720)
		{
			
			#if (SEN_USE == SEN_GC0308||SEN_USE == SEN_OV7670||SEN_USE == SEN_SIV121DS||SEN_USE == SEN_OV7725||SEN_USE == SEN_SIV100B)//vga
				u32csi_Dma_Size_H  = 640;
				u32csi_Dma_Size_V  = 480;
			#else											//720p
				#if(DEFAULT_TVOUT_EN == 1)
				u32csi_Dma_Size_H  = 640;
				u32csi_Dma_Size_V  = 360;
				#else
				u32csi_Dma_Size_H  = 640;
				u32csi_Dma_Size_V  = 360;
				#endif
			#endif

		}
		else if((u8resType == JPEG_SIZE_2560_1440) || (u8resType == JPEG_SIZE_1920_1080))
		{
			u32csi_Dma_Size_H  = 640;
			u32csi_Dma_Size_V  = 360;
		}
		else
		{
			u32csi_Dma_Size_H  = 320;
			u32csi_Dma_Size_V  = 180;
		}
	}
	else
	{
		if(u8resType == VIDEO_SIZE_640_480) 
		{
			u32csi_Dma_Size_H  = 320;
			u32csi_Dma_Size_V  = 240;
		}
		else if((u8resType == VIDEO_SIZE_1280_720) || (u8resType == VIDEO_SIZE_1920_1080))
		{

			#if (SEN_USE == SEN_GC0308||SEN_USE == SEN_OV7670||SEN_USE == SEN_SIV121DS||SEN_USE == SEN_OV7725||SEN_USE == SEN_SIV100B)//vga
				u32csi_Dma_Size_H  = 640;
				u32csi_Dma_Size_V  = 480;
			#else						//720p
				#if(DEFAULT_TVOUT_EN == 1)
				u32csi_Dma_Size_H  = 640;
				u32csi_Dma_Size_V  = 360;
				#else
				u32csi_Dma_Size_H  = 640;
				u32csi_Dma_Size_V  = 360;
				#endif
			#endif

		}
		else
		{
			u32csi_Dma_Size_H  = 320;
			u32csi_Dma_Size_V  = 180;
		}
	}
	u32sdr_Buff_Len  = u32csi_Dma_Size_H*u32csi_Dma_Size_V*2;
	//deg_Printf("Dma_H =%d,Dma_V=%d\n",u32csi_Dma_Size_H,u32csi_Dma_Size_V );
}

/*******************************************************************************
* Function Name  : csi_Start
* Description    : start csi
* Input          :recordtype 0:picture; 1:video , lcd_set  0: not set lcd, 1 :set lcd
* Output         : None
* Return         : None
*******************************************************************************/
void csi_Start(u8 recordtype,u8 lcd_set)
{
	deg_Printf("csi_Start\n");
	//deg_Printf("videosize=%d,picsize=%d\n",sys_ctl.jpeg_video_size,sys_ctl.jpeg_picture_size);
	//bcsi_FrameEndFlag = 0;
	bMD_Flag = 0;
	bMD_StopVideo_Flag = 0;
	bSameSizeFlag = 0;

	REG32(CSI_DMA_MODE) &= ~BIT(24);			//csi dma disable xjc
	REG32(CSIMODE) &= ~BIT(31);             //csi disable
    Delay_MS(40);
	
	REG32(SOFT_RST) &= ~BIT(1);
	Delay_10US(1);
	REG32(SOFT_RST) |= BIT(1);
	
	bcsi_FrameEndFlag = 0;
    #if(SEN_USE == SEN_OV9710)
		csi_SetDataWidth(10);
	#else
		csi_SetDataWidth(8);
    #endif	
		
	#if((SEN_USE == SEN_OV9710) || (SEN_USE == SEN_NT99140)|| (SEN_USE == SEN_NT99141)|| (SEN_USE == SEN_BF3925)|| (SEN_USE == SEN_NT99240))
		csi_SetInputSize(1280,720);
 	#elif((SEN_USE == SEN_OV7670) || (SEN_USE == SEN_GC0308)||(SEN_USE == SEN_SIV121DS)||(SEN_USE == SEN_OV7725)||(SEN_USE == SEN_SIV100B))
		csi_SetInputSize(640,480);
 	#endif

	REG32(CSI_DMA_MODE) = 0x000c0bf4;
	#if((SEN_USE == SEN_NT99140)||(SEN_USE == SEN_NT99141)||(SEN_USE == SEN_NT99240))
		REG32(CSIMODE) = 0x08100145;
	#elif(SEN_USE == SEN_OV9710)
		REG32(CSIMODE) = 0x08800104;
	#elif(SEN_USE == SEN_BF3925)
		REG32(CSIMODE) = 0x08100145;
	#elif(SEN_USE == SEN_GC0308||SEN_USE == SEN_SIV100B)
		REG32(CSIMODE) = 0x08800145;
	#elif(SEN_USE == SEN_OV7670)
		REG32(CSIMODE) = 0x08800345;
	#elif(SEN_USE == SEN_SIV121DS)
		REG32(CSIMODE) = 0x08800345;
	#elif(SEN_USE == SEN_OV7725)
		REG32(CSIMODE) = 0x08800345;
	#endif
	REG32(CSI_SDR_BASE) |= BIT(31);
	REG32(CSI_SDR_BASE) |= 10<<24;

	REG32(CSI_DMA_MODE) |= BIT(28);   //flush enable
	REG32(CSI_DMA_MODE) |= BIT(29);

	REG32(VIDEO_ENH_MODE) &= ~(BIT(20)|BIT(21));
	REG32(CSIMODE) |=  (BIT(5)|BIT(6));

	lastTimeCount = 1;
	csi_SetTime();
	csi_SetOutputSize(recordtype);
	csi_DmaSet();


	if((task_ctl.work_sta == TASK_PHOTO) && (bFastViewFlag))
	{
		if(1 == lcd_set)
		{
			u32 lcd_con_reg_save = REG32(LCDCON0);
			DIS_OSD1();
			DIS_OSD2();
			DIS_OSD3();
			lcd_set_panel_colour(0,0,0);
			#if(0 == LCD_MCU)
				waittingLcdFrameEnd();
				REG32(LCDCON0) &= ~(BIT(0)|BIT(6)); 
				tvout_Change_display();
				bcsi_FrameEndFlag = 0;
				csi_timeout = 0;
				while(!bcsi_FrameEndFlag && (csi_timeout++ < CSI_TIMEOUT));
				REG32(LCDCON0) = lcd_con_reg_save;
				REG32(LCDCON0) |= (BIT(0)|BIT(6));
			#else
				REG32(LCDCON0) &= ~(BIT(6)); 
				waittingLcdFrameEnd();
				tvout_Change_display();
				bcsi_FrameEndFlag = 0;
				csi_timeout = 0;
				while(!bcsi_FrameEndFlag && (csi_timeout++ < CSI_TIMEOUT));
				waittingLcdFrameEnd();
				REG32(LCDCON0) = lcd_con_reg_save;
				REG32(LCDCON0) |= (BIT(6));
			#endif
			
			if(csi_timeout >= CSI_TIMEOUT)
			{
				deg_Printf("!!!!!!csi_timeout0!!!!!!!\n");
			}
		}
		else
		{
			bcsi_FrameEndFlag = 0;
			csi_timeout = 0;
			while(!bcsi_FrameEndFlag && (csi_timeout++ < CSI_TIMEOUT));
			
			if(csi_timeout >= CSI_TIMEOUT)
			{
				deg_Printf("!!!!!!csi_timeout0!!!!!!!\n");
			}
		}
		
	}
	else 
	{
		if(bPhotoScalFlag | bTaskPlayExit_Flag| bSameSizeFlag)
		{
			//bcsi_FrameEndFlag = 0;
			csi_timeout = 0;
			while(!bcsi_FrameEndFlag && (csi_timeout++ < CSI_TIMEOUT));

			if(csi_timeout >= CSI_TIMEOUT)
			{
				deg_Printf("!!!!!!csi_timeout1!!!!!!!\n");
			}
		}
		else
		{
			//bcsi_FrameEndFlag = 0;
			//while(!bcsi_FrameEndFlag);
			if(1 == lcd_set)
			{
				u32 lcd_con_reg_save = REG32(LCDCON0);
				DIS_OSD1();
				DIS_OSD2();
				DIS_OSD3();
				lcd_set_panel_colour(0,0,0);
				#if(0 == LCD_MCU)
					waittingLcdFrameEnd();
					REG32(LCDCON0) &= ~(BIT(0)|BIT(6)); 
					tvout_Change_display();
					bcsi_FrameEndFlag = 0;
					csi_timeout = 0;
					while(!bcsi_FrameEndFlag && (csi_timeout++ < CSI_TIMEOUT));
					REG32(LCDCON0) = lcd_con_reg_save;
					REG32(LCDCON0) |= (BIT(0)|BIT(6));
				#else
					REG32(LCDCON0) &= ~(BIT(6)); 
					waittingLcdFrameEnd();
					tvout_Change_display();
					bcsi_FrameEndFlag = 0;
					csi_timeout = 0;
					while(!bcsi_FrameEndFlag && (csi_timeout++ < CSI_TIMEOUT));
					waittingLcdFrameEnd();
					REG32(LCDCON0) = lcd_con_reg_save;
					REG32(LCDCON0) |= (BIT(6));
				#endif

				if(csi_timeout >= CSI_TIMEOUT)
				{
					deg_Printf("!!!!!!csi_timeout2!!!!!!!\n");
				}
			}
			else
			{
				bcsi_FrameEndFlag = 0;
				csi_timeout = 0;
				while(!bcsi_FrameEndFlag && (csi_timeout++ < CSI_TIMEOUT));
			
				if(csi_timeout >= CSI_TIMEOUT)
				{
					deg_Printf("!!!!!!csi_timeout2!!!!!!!\n");
				}
			}
		}
	}
	//deg_Printf("csi_Start ok\n");
}

	
	
/*******************************************************************************
* Function Name  : csi_DmaSet
* Description    : set csi dma
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void csi_DmaSet(void)
{
#if  VIDEO_MOTION_DETECT_SUPPORT

	if(csi_buf_point==1)
	{
		REG32(CSI_SDR_BASE) &= ~(0xffffff);
		REG32(CSI_SDR_BASE) |= ((VIDEO_BASE_SDRAM_ADDR+LCD_VIDEO_SDRAM_SIZE)>>1) & 0xffffff;
	}
	else if(csi_buf_point==2)
	{
		REG32(CSI_SDR_BASE) &= ~(0xffffff);
		REG32(CSI_SDR_BASE) |= ((VIDEO_BASE_SDRAM_ADDR+LCD_VIDEO_SDRAM_SIZE*2)>>1) & 0xffffff;

	}
	else if(csi_buf_point==0)
	{
		REG32(CSI_SDR_BASE) &= ~(0xffffff);
		REG32(CSI_SDR_BASE) |= ((VIDEO_BASE_SDRAM_ADDR)>>1) & 0xffffff;

	}

	//REG32(CSI_SDR_BASE) |= (VIDEO_BASE_SDRAM_ADDR>>1) & 0xffffff;
	REG32(CSI_ISP_BUF) = 0x00000000;
	REG32(CSI_INTR) = 0x7E00;
	csi_MD_Start();
	if(sys_ctl.moving_detect)
	{
		if(task_ctl.work_sta == TASK_RECORD_VIDEO)
			csi_MD_Enable();
		else
			csi_MD_Disable();
	}
	else
	{
		csi_MD_Disable();
	}

	csi_DmaEnable();
#else
	REG32(CSI_DMA_MODE) &= ~BIT(24);
	REG32(CSI_DMA_MODE) &= ~BIT(25);         // select buffer 0 for next CSI frame
	REG32(CSI_INTR) &= ~BIT(14);
	REG32(CSIMODE) |= BIT(31);
#endif
	
}

/*******************************************************************************
* Function Name  : csi_SetDataWidth
* Description    : set data bus width
* Input          : u8DataBusWidth
* Output         : None
* Return         : None
*******************************************************************************/
void csi_SetDataWidth(u8 u8DataBusWidth)
{
	if(u8DataBusWidth == 7)
	{
		REG32(CSI_IMAGE_SIZE) &= 0x0fffffff;
		REG32(CSI_IMAGE_SIZE) |= (0 << 28);
	}
	else if(u8DataBusWidth == 8)
	{
		REG32(CSI_IMAGE_SIZE) &= 0x0fffffff;
		REG32(CSI_IMAGE_SIZE) |= (1 << 28);
	}
	else if(u8DataBusWidth == 9)
	{
		REG32(CSI_IMAGE_SIZE) &= 0x0fffffff;
		REG32(CSI_IMAGE_SIZE) |= (2 << 28);
	}
	else if(u8DataBusWidth == 10)
	{
		REG32(CSI_IMAGE_SIZE) &= 0x0fffffff;
		REG32(CSI_IMAGE_SIZE) |= (3 << 28);
	}
}

/*******************************************************************************
* Function Name  : csi_SetInputSize
* Description    : set csi input resolution
* Input          : u16Hsize:width;u16Vsize:height
* Output         : None
* Return         : None
*******************************************************************************/
void csi_SetInputSize(u16 u16Hsize,u16 u16Vsize)
{
	REG32(CSI_IMAGE_SIZE) &= 0xf0000000;
	REG32(CSI_IMAGE_SIZE) |= (u16Vsize<<16) | u16Hsize;
}

/*******************************************************************************
* Function Name  : csi_SetOutputSize
* Description    : set csi output resolution
* Input          : recordtype: 0:picture;1:video
* Output         : None
* Return         : None
*******************************************************************************/
void csi_SetOutputSize(u8 recordtype)
{
	static u32 u32csi_Dma_Size_H_Pre= 0;
	static u32 u32csi_Dma_Size_V_Pre = 0;

	if(recordtype)
		csi_SetScaler(recordtype,sys_ctl.jpeg_video_size);
	else
		csi_SetScaler(recordtype,sys_ctl.jpeg_picture_size);

	csi_SetOutMode(recordtype);
	if(recordtype)
		csi_ParameterSet(recordtype,sys_ctl.jpeg_video_size);
	else
		csi_ParameterSet(recordtype,sys_ctl.jpeg_picture_size);

	if((u32csi_Dma_Size_H_Pre == u32csi_Dma_Size_H) && (u32csi_Dma_Size_V_Pre == u32csi_Dma_Size_V))
	{
		bSameSizeFlag = 1;
		return;
	}
	else
	{
		u32csi_Dma_Size_H_Pre = u32csi_Dma_Size_H;
		u32csi_Dma_Size_V_Pre = u32csi_Dma_Size_V;
		u32sdr_Buff_Len  = u32csi_Dma_Size_H*u32csi_Dma_Size_V*2;
	}	
}

/*******************************************************************************
* Function Name  : csi_SetOutMode
* Description    : set csi ouput mode
* Input          : 0:picture; 1:video
* Output         : None
* Return         : None
*******************************************************************************/
void csi_SetOutMode(u8 recordtype)
{
	REG32(CSI_OUT_MODE) = (0<<29) | (((((u32)TimerInfoPixelBuf)>>2)&0x3ffff) << 8) | (0<<7) | (0<<2) | 0;	
	if(recordtype == 0)
	{
		#if((SEN_USE == SEN_OV7670) || (SEN_USE == SEN_GC0308)||(SEN_USE == SEN_SIV121DS)||(SEN_USE == SEN_OV7725)||(SEN_USE == SEN_SIV100B))	
			if(sys_ctl.jpeg_picture_size == JPEG_SIZE_640_480)
				REG32(CSI_OUT_MODE) |= (1<<30) | (1<<28) | (0<<27) | (0<<26) | (1<<5);			//bit(26) :0 :select origin image , 1: select csi_scale output image
			else if(sys_ctl.jpeg_picture_size == JPEG_SIZE_1280_720)
				REG32(CSI_OUT_MODE) |= (1<<30) | (1<<28) | (0<<27) | (0<<26) | (0<<5);			//bit(5) :0: no scale , 1: scale 1/2  , 2: scale 1/4  , 3:  scale  1/8
			else if((sys_ctl.jpeg_picture_size == JPEG_SIZE_1920_1080)||(sys_ctl.jpeg_picture_size == JPEG_SIZE_2560_1440))
				REG32(CSI_OUT_MODE) |= (1<<30) | (1<<28) | (0<<27) | (1<<26) | (1<<5);
		#elif((SEN_USE == SEN_OV9710) || (SEN_USE == SEN_NT99140) || (SEN_USE == SEN_NT99141)|| (SEN_USE == SEN_BF3925)|| (SEN_USE == SEN_NT99240))	
			if(sys_ctl.jpeg_picture_size == JPEG_SIZE_1280_720)
				#if	(USER_CONFIG==CONFIG_AX3251_AIRBORNE)
					REG32(CSI_OUT_MODE) |= (1<<30) | (1<<28) | (0<<27) | (0<<26) | (1<<5);
				#else
				    #if(DEFAULT_TVOUT_EN == 1)
					REG32(CSI_OUT_MODE) |= (1<<30) | (1<<28) | (0<<27) | (0<<26) | (1<<5);
					#else
					REG32(CSI_OUT_MODE) |= (1<<30) | (1<<28) | (0<<27) | (0<<26) | (1<<5);
					#endif
				#endif
			else if(sys_ctl.jpeg_picture_size == JPEG_SIZE_640_480)
				REG32(CSI_OUT_MODE) |= (1<<30) | (1<<28) | (0<<27) | (1<<26) | (1<<5);	
			else if((sys_ctl.jpeg_picture_size == JPEG_SIZE_1920_1080)||(sys_ctl.jpeg_picture_size == JPEG_SIZE_2560_1440))
				REG32(CSI_OUT_MODE) |= (1<<30) | (1<<28) | (0<<27) | (1<<26) | (1<<5);	
		#endif
	}
	else
	{
		#if((SEN_USE == SEN_OV7670) || (SEN_USE == SEN_GC0308)||(SEN_USE == SEN_SIV121DS)||(SEN_USE == SEN_OV7725)||(SEN_USE == SEN_SIV100B))	
		if(sys_ctl.jpeg_video_size == VIDEO_SIZE_640_480)
				REG32(CSI_OUT_MODE) |= (1<<30) | (1<<28) | (0<<27) | (0<<26) | (1<<5);	
		if((sys_ctl.jpeg_video_size == VIDEO_SIZE_1280_720) || (sys_ctl.jpeg_video_size == VIDEO_SIZE_1920_1080))
				REG32(CSI_OUT_MODE) |= (1<<30) | (1<<28) | (0<<27) | (0<<26) | (0<<5);
		#elif((SEN_USE == SEN_OV9710) || (SEN_USE == SEN_NT99140) || (SEN_USE == SEN_NT99141)|| (SEN_USE == SEN_BF3925)|| (SEN_USE == SEN_NT99240))	
		if((sys_ctl.jpeg_video_size == VIDEO_SIZE_1280_720) || (sys_ctl.jpeg_video_size == VIDEO_SIZE_1920_1080))
			#if	(USER_CONFIG==CONFIG_AX3251_AIRBORNE)
				REG32(CSI_OUT_MODE) |= (1<<30) | (1<<28) | (0<<27) | (0<<26) | (1<<5);
			#else
				#if(DEFAULT_TVOUT_EN == 1)
				REG32(CSI_OUT_MODE) |= (1<<30) | (1<<28) | (0<<27) | (0<<26) | (1<<5);
				#else
				REG32(CSI_OUT_MODE) |= (1<<30) | (1<<28) | (0<<27) | (0<<26) | (1<<5);
				#endif
			#endif
		else if(sys_ctl.jpeg_video_size == VIDEO_SIZE_640_480)
				REG32(CSI_OUT_MODE) |= (1<<30) | (1<<28) | (0<<27) | (1<<26) | (1<<5);		
		#endif
	}
}

/*******************************************************************************
* Function Name  : csi_SetScaler
* Description    : set csi scaler parameter
* Input          : u8resType: resolution type
 Input          : recordtype: 0:picture; 1:video
* Output         : None
* Return         : None
*******************************************************************************/
void csi_SetScaler(u8 recordtype,u8 u8resType)
{
	u8  u8Vscale_Padding,u8Hscale_Padding,u8Scale_Rate,u8Scale_En,u8Vscale_Fix,u8Hscale_Fix;
	u16 u16Vscale_Point,u16Hscale_Point,u16Scale_Height,u16Scale_Width;

	if(0 == recordtype)
	{

		//-------------scaler set----------------
		u8Scale_En       = 0;
		#if((SEN_USE == SEN_OV7670) || (SEN_USE == SEN_GC0308)||(SEN_USE == SEN_SIV121DS)||(SEN_USE == SEN_OV7725)||(SEN_USE == SEN_SIV100B))
		if((u8resType == JPEG_SIZE_640_480))
		{
			return;
		}
	    	else if( (u8resType == JPEG_SIZE_1280_720)||(u8resType == JPEG_SIZE_1920_1080)||(u8resType == JPEG_SIZE_2560_1440))
		{
		   u8Vscale_Padding = 1;
		   u8Hscale_Padding = 1;
		   u8Scale_Rate     = 0;
		   u8Scale_En       = 1;

		   u8Vscale_Fix     = 0;
		   u16Vscale_Point  = 682;
		   u8Hscale_Fix     = 0;
		   u16Hscale_Point  = 512;

		   u16Scale_Height  = 720;
		   u16Scale_Width   = 1280;
		}
		 #elif((SEN_USE == SEN_OV9710) || (SEN_USE == SEN_NT99140) || (SEN_USE == SEN_NT99141)|| (SEN_USE == SEN_BF3925)|| (SEN_USE == SEN_NT99240))
		 if((u8resType == JPEG_SIZE_1280_720)||(u8resType == JPEG_SIZE_1920_1080)||(u8resType == JPEG_SIZE_2560_1440))
		 {
			 return;
		 }
		 else if((u8resType == JPEG_SIZE_640_480))
	    	{
		   u8Vscale_Padding = 1;
		   u8Hscale_Padding = 1;
		   u8Scale_Rate     = 0;
		   u8Scale_En       = 1;

		   u8Vscale_Fix     = 1;
		   u16Vscale_Point  = 512;
		   u8Hscale_Fix     = 2;
		   u16Hscale_Point  = 0;

		   u16Scale_Height  = 480;
		   u16Scale_Width   = 640;
		 }
		  #endif
	}
	else
	{

		//-------------scaler set----------------
		u8Scale_En       = 0;
		#if((SEN_USE == SEN_OV7670) || (SEN_USE == SEN_GC0308)||(SEN_USE == SEN_SIV121DS)||(SEN_USE == SEN_OV7725)||(SEN_USE == SEN_SIV100B))
		if((u8resType == VIDEO_SIZE_640_480))
		{
			return;
		}
	    else if((u8resType == VIDEO_SIZE_1280_720)||(u8resType == VIDEO_SIZE_1920_1080) )
		{
		   u8Vscale_Padding = 1;
		   u8Hscale_Padding = 1;
		   u8Scale_Rate     = 0;
		   u8Scale_En       = 1;

		   u8Vscale_Fix     = 0;
		   u16Vscale_Point  = 682;
		   u8Hscale_Fix     = 0;
		   u16Hscale_Point  = 512;

		   u16Scale_Height  = 720;
		   u16Scale_Width   = 1280;
		}
		 #elif((SEN_USE == SEN_OV9710) || (SEN_USE == SEN_NT99140) || (SEN_USE == SEN_NT99141)|| (SEN_USE == SEN_BF3925)|| (SEN_USE == SEN_NT99240))
		 if((u8resType == VIDEO_SIZE_1280_720)||(u8resType == VIDEO_SIZE_1920_1080))
		 {
			 return;
		 }
		 else if((u8resType == VIDEO_SIZE_640_480))
	    {
		   u8Vscale_Padding = 1;
		   u8Hscale_Padding = 1;
		   u8Scale_Rate     = 0;
		   u8Scale_En       = 1;

		   u8Vscale_Fix     = 1;
		   u16Vscale_Point  = 512;
		   u8Hscale_Fix     = 2;
		   u16Hscale_Point  = 0;

		   u16Scale_Height  = 480;
		   u16Scale_Width   = 640;
		 }
		  #endif
	}

	
   REG32(CSI_SCALER_PARA0) = ((63<<8) |(u8Vscale_Padding << 4) | (u8Hscale_Padding << 3) | (u8Scale_Rate << 1) |(u8Scale_En));
   REG32(CSI_SCALER_PARA1) = ((u8Vscale_Fix << 26) | (u16Vscale_Point << 16) | (u8Hscale_Fix << 10) | (u16Hscale_Point));
   REG32(CSI_SCALER_PARA2) = ((u16Scale_Height << 16) | (u16Scale_Width));
}

#if (VIDEO_MOTION_DETECT_SUPPORT)
/*******************************************************************************
* Function Name  : csi_DmaEnable
* Description    : set csi dma
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void csi_DmaEnable(void)
{

	REG32(CSI_DMA_MODE) &= ~(0x3fffff);
	REG32(CSI_DMA_MODE) |= 0xffff;
	//REG32(CSI_DMA_MODE) |= BIT(26);
	REG32(CSI_DMA_MODE) |= BIT(27);
	REG32(CSI_DMA_MODE) &= ~BIT(25);         // select buffer 0 for next CSI frame
	REG32(CSI_DMA_MODE) |= BIT(24);			//csi dma enable

	REG32(CSI_INTR) &= ~(0x1ff);
	REG32(CSI_INTR) |= BIT(14);			   //enable all csi interrupt
	SetIntSrc(CSI_INT);
	REG32(CSIMODE) |= BIT(31);             //csi enable
}

void csi_MD_Start(void)
{
	REG32(MOTION_DETECT_PARA0) = (0<<31) | (0<<30) | (0<<29) | (2<<27) | (1<<26) | (3<<24) | ((VIDEO_BASE_SDRAM_ADDR>>2)& 0x00ffffff);
	REG32(MOTION_DETECT_PARA1) = ((u32csi_Dma_Size_H*u32csi_Dma_Size_V)<<12) | u32csi_Dma_Size_H;
	REG32(MOTION_DETECT_PARA2) = ((0x200)<<12) | u32csi_Dma_Size_H;
	REG32(MOTION_DETECT_PARA3) = (0<<12) | u32csi_Dma_Size_V;
	REG32(MOTION_DETECT_PARA4) = (1<<28) | (0<<24) | (u32csi_Dma_Size_H<<12) | u32csi_Dma_Size_V;
	REG32(CSI_P_SIZE_FRA) |= (0<<24) | (0x16<<16);
	csi_MD_Enable();
}

void csi_MD_Enable(void)
{
	REG32(MOTION_DETECT_PARA0) |= BIT(31);
}

void csi_MD_Disable(void)
{
	REG32(MOTION_DETECT_PARA0) &= ~BIT(31);
}


/*******************************************************************************
* Function Name  : csi_CheckMD
* Description    : check MD stop record video flag
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void csi_CheckMD(void)
{
	if(sys_ctl.moving_detect)
	{
		u32MDCnt++;
		if(bMD_Flag == 0)
		{
			if(u32MDCnt > MD_STOP_VIDEO_S*100)
			{
				u32MDCnt = 0;
				bMD_StopVideo_Flag = 1;
			}
		}
		else
		{
			u32MDCnt = 0;
		}
	}
}
#endif

/*******************************************************************************
* Function Name  : csi_Stop
* Description    : stop csi
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void csi_Stop(void)
{
	deg_Printf("csi_Stop\n");
	REG32(CSI_DMA_MODE) &= ~BIT(24);		//csi dma enable
	ClrIntSrc(CSI_INT);
	REG32(CSIMODE) &= ~BIT(31);     		//csi disable
}

/*******************************************************************************
* Function Name  : csi_Enable
* Description    : enable csi,csi dma,csi isr
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void csi_Enable(void)
{
	REG32(CSI_SDR_BASE) &= ~(0xffffff);
	REG32(CSI_SDR_BASE) |= ((VIDEO_BASE_SDRAM_ADDR)>>1) & 0xffffff;
	REG32(CSI_DMA_MODE) |= BIT(24);		//csi dma enable
	SetIntSrc(CSI_INT);
	REG32(CSIMODE) |= BIT(31);     		//csi enable
}

/*******************************************************************************
* Function Name  : csi_InserTimeInfo
* Description    : High resolution photo shoot,add time info
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void csi_InserTimeInfo(void)
{
	u32 i,j,k;
	u32 u32Temp;
	u32 m=0;
	u8 *YUYVBuff = (u8 *)(VIDEO_BASE_SDRAM_ADDR+640*2*4);

	for(j=0;j<TIME_FONT_H;j++)
	{
		for(i=0;i<TIME_INFO_LEN;i++)
		{
			u32Temp = TimerInfoPixelBuf[j*TIME_INFO_LEN+i];
			for(k=0;k<32;k++)
			{
				if(k%2==0)
				{
					if(u32Temp & (1<<k))
					{
						YUYVBuff[j*1280+i*64+2*m] = TIME_INFO_Y;
						YUYVBuff[j*1280+i*64+2*m+1] = TIME_INFO_U;
					}
				}
				else
				{
					if(u32Temp & (1<<k))
					{
						YUYVBuff[j*1280+i*64+2*m] = TIME_INFO_Y;
						YUYVBuff[j*1280+i*64+2*m+1] = TIME_INFO_V;
					}
				}
				m++;
			}
			m=0;
		}
	}
}



void csi_camera_init(void)
{
	bcsi_FrameEndFlag = 0;
	bMD_Flag = 0;
	bMD_StopVideo_Flag = 0;


	REG32(CSI_DMA_MODE) &= ~BIT(24);			//csi dma disable xjc
	REG32(CSIMODE) &= ~BIT(31);             //csi disable
    Delay_MS(40);
	REG32(SOFT_RST) &= ~BIT(1);
	Delay_10US(1);
	REG32(SOFT_RST) |= BIT(1);

    #if(SEN_USE == SEN_OV9710)
		csi_SetDataWidth(10);
	#else
		csi_SetDataWidth(8);
    #endif	
		
	#if((SEN_USE == SEN_OV9710) || (SEN_USE == SEN_NT99140) || (SEN_USE == SEN_NT99141)|| (SEN_USE == SEN_BF3925) || (SEN_USE == SEN_NT99240))
		csi_SetInputSize(1280,720);
 	#elif((SEN_USE == SEN_OV7670) || (SEN_USE == SEN_GC0308)||(SEN_USE == SEN_SIV121DS)||(SEN_USE == SEN_OV7725)||(SEN_USE == SEN_SIV100B))
		csi_SetInputSize(640,480);
 	#endif

	REG32(CSI_DMA_MODE) = 0x000c0bf4;
    	#if((SEN_USE == SEN_NT99140) || (SEN_USE == SEN_NT99141) || (SEN_USE == SEN_NT99240)  )
		REG32(CSIMODE) = 0x08100145;
	#elif(SEN_USE == SEN_OV9710)
		REG32(CSIMODE) = 0x08800104;//0x08800104;
	#elif(SEN_USE == SEN_BF3925)
//		REG32(CSIMODE) = 0x08100104;//0x08800104;
		REG32(CSIMODE) = 0x08100145;
	#elif(SEN_USE == SEN_GC0308||(SEN_USE == SEN_SIV100B))
		REG32(CSIMODE) = 0x08800145;
	#elif(SEN_USE == SEN_OV7670)
		REG32(CSIMODE) = 0x08800345;
	#elif(SEN_USE == SEN_SIV121DS)
		REG32(CSIMODE) = 0x08800345;
	#elif(SEN_USE == SEN_OV7725)
		REG32(CSIMODE) = 0x08800345;
	#endif


	REG32(VIDEO_ENH_MODE) &= ~(BIT(20)|BIT(21));
	REG32(CSIMODE) |=  (BIT(5)|BIT(6));
	
	//REG32(CSI_SDR_BASE) |= BIT(31);
	//REG32(CSI_SDR_BASE) |= 10<<24;

	//REG32(CSI_DMA_MODE) |= BIT(28);   //flush enable
	//REG32(CSI_DMA_MODE) |= BIT(29);

	//lastTimeCount = 1;
	//csi_SetTime();

	//csi_SetOutputSize(recordtype);
	//csi_DmaSet();

{
	u8  u8Vscale_Padding,u8Hscale_Padding,u8Scale_Rate,u8Scale_En,u8Vscale_Fix,u8Hscale_Fix;
	u16 u16Vscale_Point,u16Hscale_Point,u16Scale_Height,u16Scale_Width;
	
	#if((SEN_USE == SEN_OV7670) || (SEN_USE == SEN_GC0308)||(SEN_USE == SEN_SIV121DS)||(SEN_USE == SEN_OV7725)||(SEN_USE == SEN_SIV100B))

		REG32(CSI_OUT_MODE) |= (1<<30) | (1<<28) | (0<<27) | (0<<26) | (1<<5);	
	#else
	u8Vscale_Padding = 1;
	u8Hscale_Padding = 1;
	u8Scale_Rate     = 0;
	u8Scale_En       = 1;

	u8Vscale_Fix     = 1;
	u16Vscale_Point  = 512;
	u8Hscale_Fix     = 2;
	u16Hscale_Point  = 0;

	u16Scale_Height  = 480;
	u16Scale_Width   = 640;
	
   REG32(CSI_SCALER_PARA0) = ((63<<8) |(u8Vscale_Padding << 4) | (u8Hscale_Padding << 3) | (u8Scale_Rate << 1) |(u8Scale_En));
   REG32(CSI_SCALER_PARA1) = ((u8Vscale_Fix << 26) | (u16Vscale_Point << 16) | (u8Hscale_Fix << 10) | (u16Hscale_Point));
   REG32(CSI_SCALER_PARA2) = ((u16Scale_Height << 16) | (u16Scale_Width));	

		REG32(CSI_OUT_MODE) = (1<<30) | (0<<29) | (1<<28) | (0<<27) | (1<<26)| (0<<7) | (0<<5) | (0<<2) | 0;

 	#endif
}
	
	REG32(CSI_SDR_BASE) |= (VIDEO_BASE_SDRAM_ADDR>>1) & 0xffffff;
	REG32(CSI_ISP_BUF) = ((CSI_BUF0 << 16) | CSI_BUF1);//LLZ
	REG32(CSI_INTR) = 0x7E00;

	//csi_DmaEnable();
	REG32(CSI_DMA_MODE) &= ~(0x3fffff);
	REG32(CSI_DMA_MODE) |= 0xffff;
#if 1
#define HEADSIZE 12
//#define PACKETSIZE (3072-20)//3072-12 not 32 æ´æ°å?
#define PACKETSIZE (2988)

	REG32(CSI_DMA_MODE) &= ~(0x3fffff);
	REG32(CSI_DMA_MODE) |= ((PACKETSIZE-HEADSIZE)/2);//packet size set//3k
	REG32(CSI_DMA_MODE) |= ((HEADSIZE/2)<<16);//header size set//12bytes
#endif

	REG32(CSI_DMA_MODE) |= BIT(27);
	REG32(CSI_DMA_MODE) &= ~BIT(26);
	REG32(CSI_DMA_MODE) &= ~BIT(25);         // select buffer 0 for next CSI frame

	REG32(CSI_DMA_MODE) |= BIT(24);			//csi dma enable

	REG32(CSI_INTR) &= ~(0x1ff);
	REG32(CSI_INTR) |= BIT(14);			   //enable all csi interrupt

	
	REG32(CSI_SDR_BASE) |= BIT(31);
	REG32(CSI_SDR_BASE) |= 10<<24;
	
}


void csi_camera_on(void)
{
	SetIntSrc(CSI_INT);
	REG32(CSIMODE) |= BIT(31);             //csi enable
	REG32(CSI_DMA_MODE) |= BIT(24);			//csi dma enable	
}

void csi_camera_off(void)
{
	REG32(CSI_DMA_MODE) &= ~BIT(24);			//csi dma dis enable
	ClrIntSrc(CSI_INT);
	REG32(CSIMODE) &= ~BIT(31);     //csi disable
	
}


