/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : sys.c
* Author             : pengtao_zhang
* Version            : V0801a
* Date               : 08/01/2013  ;  mm/dd/yyyy
* Description        : This file provides all the system firmware functions.
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

/*******************************************************************************
* Function Name  : sys_Init
* Description    : initialize the system
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void sys_Init(void)
{ 
	g_SystemState = SYSTEM_POWER_ON;
	task_ctl.work_sta = TASK_POWER_OFF;				// for not key voice before play music
	REG32(WDT_CFG) = 0x5500; //close wdt
	REG32(SYS_CFG) |= BIT(7);   //JPEG priority > CSI
	pll_Init();
	int_Init();
#if EXTERN_PWR_VDDCORE
	//VDD core使用外部供电时，DVDD设置为1.15V
	REG32(SYS_CON) = 0x932B;	//SPEC request value, before configure LDO_ACON register,should write SYS_CON 0x932B to enable configure
	REG32(LDO_ACON) &= ~(0x3 << 8);//DVDD=1.15V
#endif

	uart_Init();
	deg_Printf("\n uart init ok\n");
	internal_ldo_Init();

	led_Init();
	KeyInit();
	SarAdcinit(APB_CLK/(2*ADC_BAUDRATE) - 1, ADC_CH10_HALFLDO);
	device_init();
	msg_init((u8 *)msg_pool, MSG_DEPTH);
	timer_Init();
	timer_Timer0_Start(); 
	usb_clk_set();
	 
	spi_Init(12000000);
	//spi_param_init(); 
	//deg_Printf("SFID=%x\n",u32spi_SFReadID());
	rtc_Init();
	
	music_init((u32*)AVI_AUDIO_FRAME_BUF_ADDR,0xfff,DAC_SAMPLE_16000,0);
#if SOFT_POWER_ON_OFF
	powerOnCtrlInit();			//if or not power on
#endif

	spi_param_init();
	deg_Printf("\n spi param init ok\n");
#if	(USER_CONFIG!=CONFIG_AX3251_AIRBORNE)
	osd_OsdData_load(RES_OSD_SOURCE);
#endif
#if (SEN_USE != SEN_NO_SENSOR)
	csi_Init(); 
	if( 0 == sensor_Init())
	{
		deg_Printf("\n sensor init ok\n");	
	}
	else
	{
		deg_Printf("\n sensor init err\n");
		g_SystemState = SYSTEM_SENSOR_ERROR;
		#if	(USER_CONFIG==CONFIG_AX3251_AIRBORNE)
		Delay_MS(5000);									//if sensor err , led show 5s
		#endif
	}
	user_show_video_rotate();							//after sensor init , set default setting
#endif	
	G_sensor_init();

	#if (0 == DEFAULT_TVOUT_EN)
		tvout_set_cur_mode(TVOUT_MODE_LCD);		//lcd show ok (ntsc,pal is ok)
	#else
		#if	(USER_CONFIG==CONFIG_AX3251_AIRBORNE)
			tvout_set_cur_mode(TVOUT_MODE_NTSC);
		#else
		    if(0 == sys_ctl.tv_mode)
				tvout_set_cur_mode(TVOUT_MODE_LCD);	 
		    else if(1 == sys_ctl.tv_mode)
		    	{
		    		tvout_set_cur_mode(TVOUT_MODE_LCD);	
				tvout_set_cur_mode(TVOUT_MODE_NTSC);		//lcd show ok (ntsc,pal is ok)
		    	}
			else if(2 == sys_ctl.tv_mode)
			{
				tvout_set_cur_mode(TVOUT_MODE_LCD);	
				tvout_set_cur_mode(TVOUT_MODE_PAL);
			}
		#endif
	#endif

	deg_Printf("TVSetOK\n");
#if (LCD_USE != LCD_NO_DISPLAY)	
	sys_show_jpeg(RES_POWER_ON);
	sys_play_music(RES_POWER_ON_MUSIC);
#endif
	key_voice_init();
#if (LCD_USE != LCD_NO_DISPLAY)	
	FontInit();
#endif
#if(MENU_DISPLAY_USE == MENU_DISPLAY_ENABLE)		
	MenuInit();
#endif
	if(!(device_online&BIT(B_SD_ONLINE)))
	{
		g_SystemState = SYSTEM_CARD_ERROR;
		bSDCardStatus = CARD_OFFLINE;
		deg_Printf("sd offline\n");
	}
	else
	{
		bsd_Close();
		if(!bsd_Init())
		{
			sys_ctl.SD_err_off_flag = 1;
			g_SystemState = SYSTEM_CARD_ERROR;
			deg_Printf("sd init err!!!!!!!!!!\n");
		}
		else
		{
			FRESULT ret = f_mount(&work_fatfs, ROOT_DIR_NAME, 1);		/* Give a work area to the default drive */
			//deg_Printf("pass f_mount ret = 0x%x \n",ret);
		}
	}

	task_ctl.on_lock_mode = 0;			//push lock key will set lock_mode 1
	OSD_changeFlag = 1;
	if(device_online&BIT(B_SD_ONLINE))
	{
		//deg_Printf("system update firmware\n");
		#if (1 == RTC_UPDATA_TIME_FROM_TXT_EN)
		rtc_check_updata_time_from_txt();
		#endif
		sys_update_firmware();			// updata sys form tf destbin.bin file , here must after the update_directory_entry()
		sys_update_FileOrder();
	}
	deg_Printf("system init ok\n");


}

void internal_ldo_Init(void)
{

	//====init sensor io state=====
	REG32(PB_DIR) |= (0x3ffc); 
 	REG32(PB_PU0) &= (~0x3ffc);
	REG32(PB_PD0) |= (0x3ffc);


	//====init lcd io state=========
	#if	(USER_CONFIG==CONFIG_AX3251_K6000)
		#if(1 == LCD_MCU)
		REG32(PF_DIR) &= (~0xff7); REG32(PF) &= (~0xff7);
		#else
		REG32(PF_DIR) &= (~0xffd); REG32(PF) &= (~0xffd);
		#endif
	#else
		#if(1 == LCD_MCU)
		REG32(PF_DIR) &= (~0xff7); REG32(PF) &= (~0xff7);
		#else
		REG32(PF_DIR) &= (~0xffd); REG32(PF) &= (~0xffd);
		#endif
	#endif

	REG32(SYS_CON) = 0x932B;			//SPEC request value
	//====sensor ldo close ======
	REG32(LDO_ACON) &= ~(0xf << 4);
	//====lcd ldo  close ======
	REG32(LDO_ACON) &= ~0xf;  
		
}

void sys_close_ldo_voltage()
{
	REG32(SYS_CON) = 0x932B;	//SPEC request value
	//====sensor ldo close ======
	REG32(LDO_ACON) &= ~(0xf << 4);
	//====lcd ldo  close ======
	REG32(LDO_ACON) &= ~0xf;  
}

/*******************************************************************************
* Function Name  : int_Init
* Description    : open the IRQ
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void int_Init(void)
{
	REG32(EA) = 0x1;
	asm("msr cpsr_c,#0x5f");      //open global IRQ
	//asm("msr cpsr_c,#0x1f");    //open global FIQ and IRQ
    //asm("msr cpsr_c,#0x9f");    //open global FIQ
}

/*******************************************************************************
* Function Name  : pll_Init
* Description    : initialize the pll
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
#if 0
void pll_Init(void)
{
	REG32(CLKCON0) = (REG32(CLKCON0) & 0xfffffffc) | 3; //system clk select usb pll clk div
	#if(SYS_CLK	== 120000000)
	REG32(CLKCON1) = (REG32(CLKCON1) & 0xffffffe0) | 1; //sys clk=pll/(x+1)=240/(1+1)=120M
	#elif(SYS_CLK == 48000000)
	REG32(CLKCON1) = (REG32(CLKCON1) & 0xffffffe0) | 4; //sys clk=pll/(x+1)=240/(4+1)=48M
	#endif
	REG32(CLKCON0) &= ~BIT(19); 			//AHB disable div
	REG32(CLKCON0) &= ~(BIT(17)|BIT(16)); 	//APB  div 1
	//REG32(CLKCON0) |= BIT(16);
}
#endif

void usb20_detect()
{
	unsigned int tmp = 0;
	
	REG32(USBCFG) |= (1<<17);
	REG32(USBCFG) &= ~((1<<18)|(1<<19));
	REG32(USBCFG) &= ~((1<<21)|(1<<20)); //pull up dm dp
	
	Delay_nopCnt(10);
	
	tmp = REG32(USBCFG);
	tmp = (tmp>>30)&0x03;
	
	if(0x3 != tmp)
	{
		if(device_online&BIT(B_USB_DEV_ONLINE))
			return;
		if (device_insert(DEVICE_PC)) 
		{
			SETB(device_online, B_USB_DEV_ONLINE);
			put_msg(USB_DEVICE_IN);
			deg_Printf("usb device online\n");
		}
	}
	else
	{
		if(!(device_online&BIT(B_USB_DEV_ONLINE)))
			return; 
		if (device_remove(DEVICE_PC)) 
		{
			CLRB(device_online, B_USB_DEV_ONLINE);
			put_msg(USB_DEVICE_CHANG_OUT);
			deg_Printf("usb device offline\n");
		}
	}

}


void pll_Init(void)
{	

	REG32(AUPLL_CFG) &= ~((1<<5)|(1<4));                 //audio_pll select 32k_clk 
	REG32(AUPLL_CFG) |= (1<<3)|(1<<1)|(1<<0);         
	REG32(AUPLL_CFG) |= (1<<7)|(1<<6);                   
	
	u32 i, j;	                                         //wait at least 3ms
	for (i = 0; i < 3 ; i++) 
	{
		for (j = 0; j < 50000/9; j++) 
		{	
			asm("nop");
		}
	}

	REG32(PLL_CFG) |= BIT(7)|BIT(6);                     //upll select aupll_out
	//EA off
	//sdram self fresh on
	/*REG32(SYS_CON)  = 0x932b;
	REG32(SYS_CFG) |= BIT(4);
	while(!(REG32(SYS_CFG)&BIT(16)));*/

	REG32(CLKCON0) &= ~(BIT(1)|BIT(0));                  //sys_clk select rc10m_clk 
	
	#if(SYS_CLK	== 120000000)
	REG32(CLKCON1)  = (REG32(CLKCON1) & 0xffffffe0) | 1; //sys clk=pll/(x+1)=240/(1+1)=120M
	#elif(SYS_CLK	== 48000000)
	REG32(CLKCON1)  = (REG32(CLKCON1) & 0xffffffe0) | 4; //sys clk=pll/(x+1)=240/(4+1)=48M
	#endif
	
	REG32(CLKCON0) &=  ~BIT(4);                          //sys_pll select upll out
	REG32(CLKCON0) |=  BIT(1)|BIT(0);                    //sys_clk select sys_pll out
	
	//sdram self fresh off
	/*REG32(SYS_CON)  = 0x932b;
	REG32(SYS_CFG) &= ~BIT(4);
	while(REG32(SYS_CFG)&BIT(16));*/
	//EA on

	REG32(CLKCON0) &= ~BIT(19); 			//AHB disable div
	REG32(CLKCON0) &= ~(BIT(17)|BIT(16)); 	//APB  div 1  
}
/*******************************************************************************
* Function Name  : sdram_Init
* Description    : initialize the sdram
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void sdram_Init(void)
{
	CLRB(REG32(PCON0), 4);							//sdram Clock Enable Bit

	REG32(PA_DIR) = 0;
	REG32(PD_DIR) = 0;
	REG32(PE_DIR) = BIT(1);

	REG32(PMAP_CFG0) |= 0x01;
//	REG32(SYS_CFG) = 0x01;
	Delay_nopCnt(200);

    REG32(SDR_REFT) = 1000;
	REG32(SDR_CFG1) = 0x03;
    Delay_nopCnt(300);

	REG32(SDR_CFG1) = 0x01;
	REG32(SDR_REFT) = 1000;
	REG32(SDR_REFT) = 1000;
	REG32(SDR_REFT) = 1000;
	REG32(SDR_REFT) = 1000;
	REG32(SDR_REFT) = 1000;
	REG32(SDR_REFT) = 1000;
	REG32(SDR_REFT) = 1000;

	REG32(SDR_REFT) = 375;

	REG32(SDR_CFG1) = 0x02;
//	REG32(SYS_CFG) = 0x00;

    *(volatile unsigned int *)0x20033000;

//	REG32(SYS_CFG) = 0x01;
	REG32(SDR_CFG0) |= 0x0c000a;
	REG32(SDR_CFG0) &= ~BIT(24);
	REG32(SDR_CFG1) = 0x7fc;//REG32(SDR_CFG1) = 0x00;
//	REG32(SDR_WBTO) = 0xF0;
//	REG32(SYS_CFG) = 0x00;
}

/*******************************************************************************
* Function Name  : sdram_ClearPart
* Description    : clear part sdram
* Input          : *dst: sdram start address
                   cnt: clear length
* Output         : None
* Return         : None
*******************************************************************************/
void sdram_ClearBss(u32 *dst, u32 cnt)
{
	while(cnt--)
	{
		*dst++ = 0;
	}
}

/*******************************************************************************
* Function Name  : bss_clear
* Description    : clear bss
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void bss_clear(void)
{
	sdram_ClearBss(&__bss_start,((u32)(&__bss_end) - (u32)(&__bss_start))/4);
}

void umod_test(void)
{
#if 1
	u32 x;
	u8 y;
	x= REG32(PA);
	y=REG32(PB);
	if(x%y)
		REG32(PA)=0;
#endif
}

void sys_dcin_init()
{
	SETB(DCIN_PORT_DIR, DCIN_PORT_BIT);			//set it input
	CLRB(DCIN_PORT_PU, DCIN_PORT_BIT);			//not pull up
	CLRB(DCIN_PORT_PD, DCIN_PORT_BIT);			//not pull down
}

void sys_dcin_set_up()
{
	CLRB(DCIN_PORT_DIR, DCIN_PORT_BIT);		//set it output
	SETB(DCIN_PORT_DATA, DCIN_PORT_BIT);		
	SETB(DCIN_PORT_PU, DCIN_PORT_BIT);		//pull up
	CLRB(DCIN_PORT_PD, DCIN_PORT_BIT);		//not pull down
}

void sys_dcin_set_down()
{
#if	((USER_CONFIG==CONFIG_AX3251_K6000) && (UART_USE == UART1_MAP1))
	REG32(PMAP_CFG0)  &= ~(1<<7);
#endif	
	CLRB(DCIN_PORT_DIR, DCIN_PORT_BIT);		//set it output
	CLRB(DCIN_PORT_DATA, DCIN_PORT_BIT);
	CLRB(DCIN_PORT_PU, DCIN_PORT_BIT);		//not pull up
	SETB(DCIN_PORT_PD, DCIN_PORT_BIT);		//pull down
}

/*******************************************************************************
* Function Name  : sys_dcin_check
* Description    : check powerkey station
* Input          : None
* Output         : None
* Return         : 2: dc check is not valid, 1: dc is on, 0: dc is out
*******************************************************************************/
u32 sys_dcin_check()
{
	u32 tmpPorta = 0;
//	u8 i;
	//deg_Printf("CHK");
	if((bI2CBusy_Flag == 0)&&(bSFBusy_Flag == 0))
	{
		 #if(USER_CONFIG == CONFIG_AX3251_K6000)
		 i2c_SendStop(); 
		 #endif
	#if	((USER_CONFIG==CONFIG_AX3251_K6000) && (UART_USE == UART1_MAP1))
		if(0 == (REG32(PMAP_CFG0)  & (1<<7)))		//uart use to normal io, not map to uart io will return
		{
			return 1;		//default dc in
		}
		REG32(PMAP_CFG0)  &= ~(1<<7);			//set not map to uart io
	#endif	
		CLRB(DCIN_PORT_DATA,DCIN_PORT_BIT);	
		CLRB(DCIN_PORT_DIR, DCIN_PORT_BIT);			//set it output

		SETB(DCIN_PORT_DIR, DCIN_PORT_BIT);			//set it input
		CLRB(DCIN_PORT_PU, DCIN_PORT_BIT);			//not pull up
		CLRB(DCIN_PORT_PD, DCIN_PORT_BIT);			//not pull down
		Delay_nopCnt(20);
		tmpPorta=(DCIN_PORT_DATA & BIT(DCIN_PORT_BIT));
	#if	((USER_CONFIG==CONFIG_AX3251_K6000) && (UART_USE == UART1_MAP1))
		REG32(PMAP_CFG0)  |= (1<<7);					//map to uart io ,so can print msg
		CLRB(DCIN_PORT_DIR, DCIN_PORT_BIT);			//set it output
		//uart_PutChar(0x00);							//避免串口打印输出乱码
	#endif
		//deg_Printf("DCDC=%x\n",tmpPorta);
	}
	return tmpPorta>>DCIN_PORT_BIT;
}


static u8 dcin_start_flag;			//for check 
void sys_dcin_start_flag_init()
{
	u32 i ;
	u32 dcin_cnt = 0;
	for(i = 0;i < 30;i++)
	{
		if(sys_dcin_check() == 1)
		{
			dcin_cnt++;
			delay_ms(1);
		}
	}

	if(dcin_cnt>= 28)
	{
		dcin_start_flag = 1;			//for start recording
	}

}

u8 sys_dcin_get_start_flag()		//check if dcin start ,0: no  , 1 yes
{
	return dcin_start_flag;
}

void sys_dcin_set_start_flag(u8 flag)//check if dcin start ,0: no  , 1 yes
{
	dcin_start_flag = flag;
}

//=========end dc_in handle======

/*******************************************************************************
* Function Name  : jpeg_enc_InitTab
* Description    : initialize jpeg table
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void jpeg_enc_InitTab(void)
{
//	u32 i;
    u8* dataPtr;
	TABLE_INFO JpegTableHead;
	
	spi_SFReadData(&JpegTableHead,HeadTableOffset+RES_JPEG_TAB*8,8);
	if(JpegTableHead.Len != JPEG_TABLE_LEN)
    {
    	deg("JpegTableHead.Len err!!!\n");
    }
	dataPtr = (u8 *)0x10010000;
	spi_SFReadData(dataPtr,HeadTableOffset+JpegTableHead.Addr, 0x400);
	dataPtr = (u8 *)0x10020000;
	spi_SFReadData(dataPtr,HeadTableOffset+JpegTableHead.Addr+0x400, 0x440);

	jpeg_enc_InitQualTab(0);  //compression ratio:0=1x; 1=2x; 2=4x;3=8x
}

void sys_show_jpeg(u8 image_index)
{

	u32 jpeg_w,jpeg_h;
	TABLE_INFO SourceTableHead;
	u8 u8JpegScal;
	u32 u32DisBuf_Addr;

	if(RES_POWER_ON != image_index)
	{
		csi_Stop();
	}
	deg_Printf("ReadStart\n");
	spi_SFReadData(&SourceTableHead, HeadTableOffset+image_index*8, 8);
	spi_SFReadData((u8 *)JPEG_BUFFER_START_ADDRESS, HeadTableOffset+SourceTableHead.Addr, SourceTableHead.Len);
	deg_Printf("ReadFinish\n");
//======show======

	u32DisBuf_Addr = REG32(LCDCON46) + DISPLAY_SIZE;
	if(u32DisBuf_Addr >= (DISPLAY_ADDR + DISPLAY_SIZE*3))
		u32DisBuf_Addr = DISPLAY_ADDR;
		
	mjpdec_Start((u8 *)JPEG_BUFFER_START_ADDRESS,(u8 *)u32DisBuf_Addr);

	while(jpdec_flag==0);
	deg_Printf("jpeg dec  finish\n");
	jpeg_w = (REG32(JPSIZE)>>16) & 0xffff;										// get jpeg w h
	jpeg_h = REG32(JPSIZE) & 0xffff;
	u8JpegScal = (REG32(JPCON2)>>6) & 0x3;
	if((u8JpegScal==0)||(u8JpegScal==1))
		u8JpegScal = 1;
	else if(u8JpegScal==2)
		u8JpegScal = 2;
	else if(u8JpegScal==3)
		u8JpegScal = 4;
//	deg_Printf("jpeg_w = 0x%x\n",jpeg_w);
//	deg_Printf("jpeg_h = 0x%x\n",jpeg_h);
//	deg_Printf("jpeg_scal = 0x%x\n",u8JpegScal);


	u32 lcd_con_reg_save = REG32(LCDCON0);
	DIS_OSD1();
	DIS_OSD2();
	DIS_OSD3();
	lcd_set_panel_colour(0,0,0);
	REG32(LCDCON0) &= ~(BIT(6));
	waittingLcdFrameEnd();
	REG32(LCDCON46) = u32DisBuf_Addr;
	tvout_display_set(0,0,jpeg_w/u8JpegScal,jpeg_w/u8JpegScal,jpeg_h/u8JpegScal,tvout_get_w(),tvout_get_h());		// sometimes will show no good,just do it again for test
	waittingLcdFrameEnd();
	REG32(LCDCON0) = lcd_con_reg_save;
	REG32(LCDCON0) |= BIT(6);
//	deg_Printf("pass show logo\n");
	Delay_MS(100);
	if(0 == sys_ctl.tv_mode)
		lcd_set_backlight(1);

}

void sys_play_music(u8 music_index)
{
#if	(USER_CONFIG!=CONFIG_AX3251_AIRBORNE)
//======play music=====
	u16 volume = 0;
 	TABLE_INFO SourceTableHead;
	spi_SFReadData(&SourceTableHead, HeadTableOffset+music_index*8, 8);
	spi_SFReadData((u8 *)JPEG_BUFFER_START_ADDRESS, HeadTableOffset+SourceTableHead.Addr, SourceTableHead.Len);

	deg_Printf("music Len = 0x%x \n",SourceTableHead.Len);
	if(music_index == RES_POWER_ON_MUSIC)
	{
		volume = 0xfff;
	}
	else
	{
		volume = 0xfff;
	}
	deg_Printf("volume = 0x%x \n",volume);
	//music_init((u32*)__TEMP_BUFF_BEG,volume,DAC_SAMPLE_16000);
	music_play((u8*)JPEG_BUFFER_START_ADDRESS,SourceTableHead.Len);

//======end play music==
#endif
}
#if SOFT_POWER_ON_OFF
void powerOnCtrlInit()
{
	u8 temp[2] = {0};
	rtc_ReadRam(temp,5,2);					// 0~3  for rtc time
	if(0x32==temp[0] && 0x50==temp[1]  )
	{
		sys_power_on();
	}
	else	
	{
		temp[0] = 0x32;
		temp[1] = 0x50;
		rtc_WriteRam(temp,5,2);				//write first rtc work flag
		/*if(0 == sys_dcin_check())					//first bat power into , power off
		{
			deg_Printf("first bat into \n");
			sys_power_off(1);
		}
		else */
		{
			sys_power_on();
		}
	}

}

void sys_power_on()
{
	deg_Printf("sys_power_on\n");
#if	(USER_CONFIG==CONFIG_AX3251_K6000)
	POWERON_ENABLE();
#elif (USER_CONFIG==CONFIG_AX3250_K6000)
	rtc_set_wko_up();
#else
	......
#endif
}

//====flag : 0 is show logo play music,  1 is direct power off=======
void sys_power_off(u8 flag)
{
	deg_Printf("sys_power_off\n");
	u32 dc_check_cnt = 0;
	u32 i = 0;

	bsd_Close();
	
	g_SystemState = SYSTEM_POWER_OFF;
	if(0 == flag)
	{
		sys_show_jpeg(RES_POWER_OFF);
		if(g_stcJpegInfo.bLowPowerFlag)
		{
			deg_Printf("low power!!!\n");
			EN_OSD1();
			DIS_OSD3();
			DisPlayLowPower();
			Delay_MS(1500);
		}
		else
		{
			DIS_OSD1();
			DIS_OSD3();
		}
		music_init((u32*)AVI_AUDIO_FRAME_BUF_ADDR,0xfff,DAC_SAMPLE_16000,1);
		sys_play_music(RES_POWER_OFF_MUSIC);
		
		if((1 == sys_ctl.tv_mode)||(2 == sys_ctl.tv_mode))
			tv_disable();
	}

	CLOSE_NIGHT_LIGHT();				//close night light
#if (LCD_USE != LCD_NO_DISPLAY)
	lcd_set_backlight(0);					//close back lignt
#endif
	audio_amplifier_close();				//close amplifier
    

	while(i < 50)
	{
		i++;
		if(sys_dcin_check() == 1)
		{
			dc_check_cnt++;
			Delay_MS(2);
		}
	}

	if(dc_check_cnt > 45)		//dc in
	{
		deg_Printf("dcin !\n");
		u32 keypower_pushcnt = 0;
		u32 dc_out_cnt = 0;					
		while(key_powerkey_check());		//until the power key up

		while(keypower_pushcnt < 100)			//if power key push again just go to reset
		{
			if(key_powerkey_check())
			{
				keypower_pushcnt++;
				if(keypower_pushcnt > 80)			// user power on 
				{
					deg_Printf("poweron restart sys\n");
					sys_wdt_reset();				//reset sys
					Delay_MS(1000);				//enough time for reset
				}
			}
			else
			{
				keypower_pushcnt = 0;
			}

			if(sys_dcin_check()==0)			//check dc
			{
				dc_out_cnt++;
				if(dc_out_cnt > 50)				//check dc out will power off
				{
					deg_Printf("dc out power off\n");
					Delay_MS(50);
					break;						
				}
			}
			else
			{
				dc_out_cnt = 0;
			}
			Delay_MS(1);
		}

	}
	sys_close_ldo_voltage();				//close sensor lcd ldo

	while(1) {
		sys_dcin_set_down();
		Delay_MS(50);
#if	(USER_CONFIG==CONFIG_AX3251_K6000)
		POWERON_DISABLE();
#elif (USER_CONFIG==CONFIG_AX3250_K6000)
		rtc_set_wko_down();
#else
		......
#endif	
		delay_ms(1000);
	}
}
#endif

void sys_wdt_reset()
{
	deg_Printf("wdt reset\n");
	REG32(WDT_CFG) = 0x0039; //wdt reset
	deg_Printf("waiting reset\n");
	while(1);
}


//======system updata from tf card======
void sys_update_firmware(void)
{

	u8 *pTempbuf = (u8 *)AVI_INDEX_DEST_BUFF_ADDR;
	u32 spi_flash_addr=0;
	u32 writed;
	u32 writed_size = 0;

//	deg_Printf("sys_update_firmware\n");
	if (f_open(&Fil, FIRMWARE_NAME, FA_READ| FA_OPEN_EXISTING) == FR_OK) 
	{
		deg_Printf("open file ok:fsize = 0x%x\n",Fil.fsize);
		//sys_show_jpeg(UPDATE_LOGO_INDEX);
		//if(spi_SFEraseChip())
		{

			//deg_Printf("flash eraze ok,SPI_PARAM_LEN = %d\n",SPI_PARAM_LEN);
			deg_Printf("Start write firmware:");
			while(f_read(&Fil, pTempbuf, 512, (uint *)(&writed))==FR_OK)
			{
//				deg_Printf("%x%x%x%x\n",*(pTempbuf)&0xff,*(pTempbuf+1)&0xff,*(pTempbuf+2)&0xff,*(pTempbuf+3)&0xff);
//				deg_Printf("%x%x%x%x\n",*(pTempbuf+4)&0xff,*(pTempbuf+5)&0xff,*(pTempbuf+6)&0xff,*(pTempbuf+7)&0xff);
				if((spi_flash_addr&0xFFF) == 0) {
					if(!spi_SFEraseSector(spi_flash_addr)) {
						deg_Printf("SectorErase Fail on addr:%x\n",spi_flash_addr);
						break;
					}
					else {
						deg_Printf("*");
					}
				}
				spi_SFWriteData(spi_flash_addr,(u8 *)pTempbuf,SPI_PARAM_LEN);
				spi_flash_addr +=SPI_PARAM_LEN;
				spi_SFWriteData(spi_flash_addr,(u8 *)pTempbuf+SPI_PARAM_LEN,SPI_PARAM_LEN);
				spi_flash_addr +=SPI_PARAM_LEN;
				
				writed_size+= 512;
				if(writed_size >= Fil.fsize)
				{
					deg_Printf("writed_size = 0x%x,writed = 0x%x\n",writed_size,writed);
					break;
				}
			}
			deg_Printf("write firmware ok\n");
		}
		f_close(&Fil);
		deg_Printf("updata finish\n");

		#if	(USER_CONFIG==CONFIG_AX3251_AIRBORNE)
			led_Init();
			g_SystemState = SYSTEM_CARD_UPDATA_SUCCESS;
			Delay_MS(8000);
		#endif
		//sys_show_jpeg(UPDATE_OK_LOGO_INDEX);
//		while(1);
	}
	sd_WaitSdStopTran();	//in order to save power

}

