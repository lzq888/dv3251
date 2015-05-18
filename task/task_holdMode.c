/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : task_holdMode.c
* Author             : dingping_chen
* Version            : V0225a
* Date               : 11/13/2014  ;  mm/dd/yyyy
* Description        : This file provides all the record photo functions.
***************************************************************************/
//===================================================================
//                                                     	            |
//                       INCLUDE FILES                              |
//                                                                  |
//===================================================================
#include "../header/include.h"
u32 powerSaveFlag=0;

//===================================================================
//                                                     	            |
//                      GLOBAL VARIABLE                             |
//                                                                  |
//===================================================================
u32 powerSaveCheck()
{
	if(task_ctl.on_playing || 	//video is playing, return
		delResult != FR_OK) {	//delete file procedure is not finished, so shall wait for it	
		reset_powerSaveChk();
		return 0;
	}
	else 
	{
		if(sys_ctl.powerSaveChkCnt != 0 && sys_ctl.powerSaveChkCnt != 0xffffffff) 
		{
			sys_ctl.powerSaveChkCnt--;
			//powerSaveFlag = 0;
			//deg_Printf("-");
			return 0;
		}
		else if(sys_ctl.powerSaveChkCnt == 0xffffffff) 
		{
			powerSaveFlag = 0;
			//deg_Printf("+");
			return 0;
		}
		else
		{
			lcd_set_backlight(0);	//shutdown the lcd backlight
			powerSaveFlag = 1;
			return 0;
		
/*
				lcd_set_backlight(0);	//shutdown the lcd backlight
				skip_key_msg = 1;
				if(powerSaveFlag == 0) {
					deg_Printf("PWR= 1\n");
					powerSaveFlag = 1;
				}
				return 1;


			if( (MENU_IDLE != cur_menu.menu_type) ||			//menu is not idle
				(task_ctl.work_sta == TASK_USB_DEVICE) ||		//task is in USB mode
				((task_ctl.work_sta == TASK_RECORD_VIDEO) && (task_ctl.on_recording)) ) {	//video is recording, so shutdown the lcd backlight
			#if (LCD_USE != LCD_NO_DISPLAY)
				lcd_set_backlight(0);	//shutdown the lcd backlight
				skip_key_msg = 1;
			#endif
				if(powerSaveFlag == 0) {
					deg_Printf("PWR= 1\n");
					powerSaveFlag = 1;
				}
				return 1;
			}
			else {	//enter hold mode
				if(powerSaveFlag == 0) {
					deg_Printf("PWR= 2\n");
					powerSaveFlag = 2;
				}
				return 2;
			}
*/
		}
	}
}


void holdModeEnter()
{
	deg_Printf("HoldMode Enter\n");
	REG32(SDR_CFG0) &= ~ BIT(18);
	REG32(SDR_CFG0) |= BIT(17);
	deg_Printf("SDRAM:%x,%x,%x,%x\n",REG32(SDR_CFG0),REG32(SDR_CFG1),REG32(SDR_REFT),REG32(SDR_WBTO));
	//deg_Printf("CLKCON0=%x\n",REG32(CLKCON0));
	//if enter the hold mode , we should shutdown some peripherals to save power 
	//deselect card
	if(bSDCardStatus == CARD_READY) {
		if (!bsd_SelectCard())		//CMD7
		{
			deg_Printf("enter stand-by state fail !!!\n");
			bSDCardStatus = CARD_ONLINE;
		}
		else 
		{
			bSDCardStatus = CARD_STANDBY;
			deg_Printf("enter stand-by state OK\n");
		}
	}
	
	//disable DAC
	audio_amplifier_close();	// mute Power Amplifier
	/*wr_reg(DACCFG, rd_reg(DACCFG)&(~(BIT(0))));	//disable DAC digital filter/delta-sigma modulator 
	REG32(DAC_ACON0) &= ~(BIT(15));	//disable for HP Power
	REG32(DAC_ACON0) &= ~(BIT(13));	//disable for VCM
	REG32(DAC_ACON0) &= ~(BIT(14));	//disable for DAC POWER VDDDAC
	REG32(PCON0)   |= (1<<21);    	//disable dac clock*/

	//disable AGC

	//disable Sensor
	csi_Stop();
	csi_camera_off();
	//REG32(PCON0)   |= (1<<23);    	// disable CSI clock

	//disable LCD
	sys_ctl.powerSaveChkCnt=0;
	lcd_set_backlight(0);	//close backlight
	tvout_lcd_disen();
	//REG32(PCON0)   |= (1<<29);    	// disable LCD clock
	//REG32(PCON0)   |= (1<<22);    	// disable TV clock

	//close sensor LDO and LCD LDO
	sys_close_ldo_voltage();

	//disable Timer
	REG32(PCON0) |= BIT(11);
	//REG32(PCON0) |= BIT(31)|BIT(30)|BIT(28)|BIT(27)|BIT(25)|BIT(21)|BIT(20)|BIT(19)|BIT(17)|BIT(16)|BIT(15)|BIT(14)|BIT(13)|BIT(9)|BIT(8)|BIT(7)|BIT(6)|BIT(5);

	dmac_global_disable();
}
void holdModeExit()
{
	deg_Printf("HoldMode Exit\n");
	REG32(SDR_CFG0) |= BIT(18);
	REG32(SDR_CFG0) &= ~ BIT(17);
	deg_Printf("SDRAM:%x,%x,%x,%x\n",REG32(SDR_CFG0),REG32(SDR_CFG1),REG32(SDR_REFT),REG32(SDR_WBTO));
#if (LCD_USE != LCD_NO_DISPLAY)
	skip_key_msg = 1;
#endif
	powerSaveFlag = 0;
	//disable WDT
	REG32(WDT_CFG) = 0x5520; //close wdt,clear WDT counter
	deg_Printf("WDT=%x\n",REG32(WDT_CFG));
	
	reset_powerSaveChk();
	//enable some peripherals that was disabled before
	//REG32(PCON0) &= ~(BIT(31)|BIT(30)|BIT(28)|BIT(27)|BIT(25)|BIT(21)|BIT(20)|BIT(19)|BIT(17)|BIT(16)|BIT(15)|BIT(14)|BIT(13)|BIT(9)|BIT(8)|BIT(7)|BIT(6)|BIT(5));
	//enable Timer
	timer_Init();

	//open sensor LDO or LCD LDO if we have used sensor or LCD
	internal_ldo_Init();
	deg_Printf("LDO init OK\n");
	

	//enable DAC, open the below code, the system will be dead sometimes
	/*
	REG32(PCON0)   &= ~(1<<21);    	//enable dac clock
	REG32(DAC_ACON0) |= (BIT(15));	//enable for HP Power
	REG32(DAC_ACON0) |= (BIT(13));	//enable for VCM
	REG32(DAC_ACON0) |= (BIT(14));	//enable for DAC POWER VDDDAC
	wr_reg(DACCFG, rd_reg(DACCFG)|(BIT(0)));	//enable DAC digital filter/delta-sigma modulator 
	*/
	//enable AGC

	//enable Sensor
	/*REG32(PCON0)   &= ~(1<<23);    	//enable CSI clock
	csi_camera_on();*/
#if (SEN_USE != SEN_NO_SENSOR)
	csi_Init(); 
	sensor_Init();
	user_show_video_rotate();
	deg_Printf("\n sensor init ok\n");	
#endif
	
	//enable LCD
	/*REG32(PCON0)   &= ~(1<<29);    	//enable LCD clock
	REG32(PCON0)   &= ~(1<<22);    	//enable TV clock
	tvout_lcd_en();*/
	tvout_set_cur_mode(TVOUT_MODE_LCD);		//lcd show ok (ntsc,pal is ok)
	//lcd_set_backlight(1);			//open backlight

	task_ctl.work_sta = task_ctl.work_backup_sta;
}

void holdModeHook()
{
	//deg_Printf("H");
	ScanKey(1);
	led_SetStatus();
	sd_Detect();
	usb20_detect();
}
bool checkWakeUp()
{
	u8 msg;
	msg = get_msg();
	if(msg != NO_KEY && msg != SYSTEM_1S && msg != SYSTEM_500MS) {
	#if (LCD_USE == LCD_NO_DISPLAY)
		put_msg(msg);		//because don't have display, so cannot skip key msg
	#else
		u8 msg_len = MSG_DEPTH;
		do {
			if(msg > (T_KEY_31 | T_KEY_HOLD)) {	//have display, so skip key msg;
				put_msg(msg);
			}
			msg=get_msg();
		}while(msg_len--);
	#endif
		deg_Printf("Hold Wakeup:%x\n",msg);
		return TRUE;
	}
	return FALSE;
}
void task_holdMode()
{
	holdModeEnter();
	while(1){
		REG32(WDT_CFG) = 0x5031;		//WDT timeout is 8ms, and clear WDT counter
		cpu_hold_mode();	//call this function, system will enter hold mode. when WDT wakeup,cpu will exit this function, and continue to run the rest code
		holdModeHook();
		if(checkWakeUp())	//check if we should exit the hold mode
			break;
	}
	holdModeExit();
}
