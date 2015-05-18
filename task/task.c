/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : task.c
* Author             : pengtao_zhang
* Version            : V0225a
* Date               : 02/25/2014  ;  mm/dd/yyyy
* Description        : This file provides all the task firmware functions.
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
type_task_ctl task_ctl;
u8 video_enlager=0;

void BatVolDisplay(void)
{
	if(sys_dcin_check() == 1)
	{
		lcd_UpdateOsdIconData_FromSdram(&OSD1Inf, OSD_CHARGE, BAT_ICON_XS, BAT_ICON_YS);
	}
	else
    {	
		if(task_ctl.flag_update_bat == 2)
			lcd_UpdateOsdIconData_FromSdram(&OSD1Inf, OSD_CHARGE, BAT_ICON_XS, BAT_ICON_YS);
		else
			lcd_UpdateOsdIconData_FromSdram(&OSD1Inf, OSD_BAT_0 +task_ctl.bat_lev , BAT_ICON_XS, BAT_ICON_YS);
		//if(!bUSB_Power_Flag)
		//	task_ctl.flag_update_bat = 0;
	}	 
}

void LockModeDisplay(void)
{
	if(task_ctl.on_lock_mode)
	{
		lcd_UpdateOsdIconData_FromSdram(&OSD1Inf, OSD_LOCK_MODE, (TASK_OSD_XS+2*(TASK_ICON_WIDTH+ICON_INTERVAL_SPACE)), TASK_OSD_YS);
	}
	else
	{
		lcd_FillPartOsdData(&OSD1Inf, ALPHA_0X00_COLOR, (TASK_OSD_XS+2*(TASK_ICON_WIDTH+ICON_INTERVAL_SPACE)), TASK_OSD_YS, TASK_ICON_WIDTH, TASK_ICON_HEIGHT);
	}
}

void DisPlayLowPower(void)
{
	lcd_FillPartOsdData(&OSD1Inf, ALPHA_0X00_COLOR, 0, 0, MENU_WIDTH, MENU_HEIGHT);
	DisplayUnicodeStr(&OSD1Inf,(u8 *)(group_low_power[sys_ctl.language]),0,(LCD_HEIGHT-FONT_HEIGHT)/2,LCD_WIDTH,FONT_HEIGHT,OSD_TIME_COLOR, ALPHA_0X00_COLOR,2); 
}

void ZoomNumDisplay(void)
{
	if(task_ctl.work_sta == TASK_PHOTO)
	{
		if((video_enlager<=MAX_ENLAGER_FACTOR) && (video_enlager !=0) &&(t_photo.fast_view_time<0))
			lcd_UpdateOsdIconData_FromSdram(&OSD1Inf, X1+video_enlager, MENU_XS, MENU_HEIGHT-MENU_YS-ZOOM_NUM_Y*TASK_ICON_YSPACE);
		else
			lcd_FillPartOsdData(&OSD1Inf, ALPHA_0X00_COLOR, MENU_XS, MENU_HEIGHT-MENU_YS-ZOOM_NUM_Y*TASK_ICON_YSPACE,ZOOM_NUM_W,ZOOM_NUM_H);
	}
	else
	{
		if((video_enlager<=MAX_ENLAGER_FACTOR) && (video_enlager !=0))
			lcd_UpdateOsdIconData_FromSdram(&OSD1Inf, X1+video_enlager, MENU_XS, MENU_HEIGHT-MENU_YS-ZOOM_NUM_Y*TASK_ICON_YSPACE);
		else
			lcd_FillPartOsdData(&OSD1Inf, ALPHA_0X00_COLOR, MENU_XS, MENU_HEIGHT-MENU_YS-ZOOM_NUM_Y*TASK_ICON_YSPACE,ZOOM_NUM_W,ZOOM_NUM_H);
	}
}

void DisPlaySDCard(void)
{
	if(!(device_online&BIT(B_SD_ONLINE)))
	{
		//if(sd_dis_flag)	
		//	return;
//		lcd_FillPartOsdData(&OSD1Inf, ALPHA_0X00_COLOR, 0, MENU_HEIGHT/2, MENU_ITEM1_W, 2*FONT_HEIGHT);
//		DisplayUnicodeStr(&OSD1Inf,(u8 *)(group_no_card[sys_ctl.language]),0,MENU_HEIGHT/2,MENU_ITEM1_W,FONT_HEIGHT,OSD_TIME_COLOR, ALPHA_0X00_COLOR,2); 
		lcd_UpdateOsdIconData_FromSdram(&OSD1Inf, OSD_SD_OFFLINE, MENU_WIDTH-TASK_OSD_XS-VIDEO_TITLE*TASK_ICON_XSPACE, MENU_HEIGHT-MENU_YS-2*TASK_ICON_HEIGHT-ICON_INTERVAL_SPACE);
		sd_dis_flag=1;
		if((task_ctl.work_sta == TASK_RECORD_VIDEO)||(task_ctl.work_sta == TASK_PHOTO))
		{
			if((sys_ctl.language ==0)||(sys_ctl.language ==1)||(sys_ctl.language ==2)||(sys_ctl.language ==3)||(sys_ctl.language ==5))
			{
				lcd_UpdateOsdIconData_FromSdram_EX(&OSD1Inf, OSD_NO_SD_S, OSD_NO_SD_S_XS, OSD_NO_SD_S_YS);
				DisplayUnicodeStr_ToTempBuf(&OSD1Inf,(u8 *)(group_no_card[sys_ctl.language]),OSD_NO_SD_S_XS,OSD_NO_SD_S_YS,0,8,OSD_NO_SD_S_W,OSD_NO_SD_S_H,OSD_TIME_COLOR, ALPHA_0X00_COLOR,0xf2); 
				lcd_UpdateOsdIconData_FromSdramToOsdBuf(&OSD1Inf, TEMP_OSDICON_ADDR, OSD_NO_SD_S_XS, OSD_NO_SD_S_YS,OSD_NO_SD_S_W,OSD_NO_SD_S_H);
			}
			else
			{
				lcd_UpdateOsdIconData_FromSdram_EX(&OSD1Inf, OSD_NO_SD_L, OSD_NO_SD_L_XS, OSD_NO_SD_L_YS);
				DisplayUnicodeStr_ToTempBuf(&OSD1Inf,(u8 *)(group_no_card[sys_ctl.language]),OSD_NO_SD_L_XS,OSD_NO_SD_L_YS,0,8,OSD_NO_SD_L_W,OSD_NO_SD_L_H,OSD_TIME_COLOR, ALPHA_0X00_COLOR,0xf2); 	
				lcd_UpdateOsdIconData_FromSdramToOsdBuf(&OSD1Inf, TEMP_OSDICON_ADDR, OSD_NO_SD_L_XS, OSD_NO_SD_L_YS,OSD_NO_SD_L_W,OSD_NO_SD_L_H);
			}
		}
	}
	else
	{
		//if(!sd_dis_flag)	
		//	return;

//		lcd_FillPartOsdData(&OSD1Inf, ALPHA_0X00_COLOR, 0, MENU_HEIGHT/2, MENU_ITEM1_W, 2*FONT_HEIGHT);
//		DisplayUnicodeStr(&OSD1Inf,(u8 *)(group_no_card[sys_ctl.language]),0,MENU_HEIGHT/2,MENU_ITEM1_W,FONT_HEIGHT,OSD_TIME_COLOR, ALPHA_0X00_COLOR,2); 
		lcd_UpdateOsdIconData_FromSdram(&OSD1Inf, OSD_SD_ONLINE, MENU_WIDTH-TASK_OSD_XS-VIDEO_TITLE*TASK_ICON_XSPACE, MENU_HEIGHT-MENU_YS-2*TASK_ICON_HEIGHT-ICON_INTERVAL_SPACE);
		sd_dis_flag=0;
		if((task_ctl.work_sta == TASK_RECORD_VIDEO)||(task_ctl.work_sta == TASK_PHOTO))
		{
			if((sys_ctl.language ==0)||(sys_ctl.language ==1)||(sys_ctl.language ==2)||(sys_ctl.language ==3)||(sys_ctl.language ==5))
				lcd_FillPartOsdData(&OSD1Inf, ALPHA_0X00_COLOR,OSD_NO_SD_S_XS, OSD_NO_SD_S_YS,OSD_NO_SD_S_W,OSD_NO_SD_S_H);
			else
				lcd_FillPartOsdData(&OSD1Inf, ALPHA_0X00_COLOR,OSD_NO_SD_L_XS, OSD_NO_SD_L_YS,OSD_NO_SD_L_W,OSD_NO_SD_L_H);
		}
	
	}
	
}

void mode_change(void)
{
	deg_Printf("mode change\n");
	task_ctl.work_sta++;
	if(task_ctl.work_sta >= TASK_MAX_NUM)
		task_ctl.work_sta = 0;

	//if(cur_menu.menu_type!=MENU_IDLE)
	//	SetCurMenuType(MENU_IDLE);
}

void night_light_ctrl(void)
{
//	if(sys_ctl.video_night_light)
//	{
		if(light_sta==1)
		{
			CLOSE_NIGHT_LIGHT();
			light_sta = 0;
		}
		else
		{
			OPEN_NIGHT_LIGHT() ;
			light_sta = 1;
		}
//	}
}


//所有任务的公共消息处理函数°
void deal_msg(u8 msg)
{
    switch (msg)
    {
		case T_KEY_POWER | T_KEY_SHORT_UP:
		    if(task_ctl.on_playing)
				break;
			if(task_ctl.work_sta != TASK_USB_DEVICE)		//usb mode not open night light
			{
				deg_Printf("night_light_ctrl \n");
				night_light_ctrl();
			}
			break;
		case T_KEY_POWER|T_KEY_LONG:
			task_exit();
			deg_Printf("long pressed power key\n");
			break;
		case T_KEY_MODE | T_KEY_SHORT_UP:
			if(((task_ctl.work_sta == TASK_PHOTO)&&(t_photo.fast_view_time > 0))||(task_ctl.on_playing))
			{
				break;
			}
			else if((g_SystemState != SYSTEM_RECORD_VIDEO) && (t_play.play_sta != PLAY_VIDEO || task_ctl.on_playing ==0)&&(MENU_IDLE == cur_menu.menu_type))
			{
				mode_change();
			}
			break;
		case USB_DEVICE_IN:
			if (TASK_USB_DEVICE != task_ctl.work_sta)
			{
				task_ctl.work_backup_sta = task_ctl.work_sta;
			}
			task_ctl.work_sta = TASK_USB_DEVICE;
			break;
		case USB_DEVICE_CHANG_OUT:
//			task_ctl.work_sta = task_ctl.work_backup_sta;
			task_ctl.work_sta = TASK_POWER_OFF;				//out usb go to power off
			deg_Printf("USB_DEVICE_CHANG_OUT,task_ctl.work_sta = 0x%x\n",task_ctl.work_sta);
			break;
		case SDMMC_CHANGE_IN:

			break;
		case SDMMC_CHANGE_OUT:
			break;
		
		case T_KEY_AIRBORNE_PHOTO:
			deg_Printf("T_KEY_AIRBORNE_PHOTO\n");
			if(task_ctl.work_sta != TASK_PHOTO && TASK_USB_DEVICE != task_ctl.work_sta) {
				task_ctl.work_sta = TASK_PHOTO;
			}
			t_photo.photo_sta = 1;
			break;
			
		case T_KEY_AIRBORNE_PHOTO | T_KEY_SHORT_UP:
		case T_KEY_AIRBORNE_PHOTO | T_KEY_LONG_UP:
			break;
		
		case T_KEY_AIRBORNE_VIDEO:
			break;
			
		case T_KEY_AIRBORNE_VIDEO | T_KEY_SHORT_UP:
		case T_KEY_AIRBORNE_VIDEO | T_KEY_LONG_UP:
//			deg_Printf("T_KEY_AIRBORNE_VIDEO UP\n");
			if(task_ctl.work_sta != TASK_RECORD_VIDEO && TASK_USB_DEVICE != task_ctl.work_sta) {
				task_ctl.work_sta = TASK_RECORD_VIDEO;
			}
			t_record_video.recording_sta = 1;
			break;
			
		case T_KEY_AIRBORNE_CTRL | T_KEY_SHORT_UP:
			if(task_ctl.work_sta != TASK_PHOTO  && TASK_USB_DEVICE != task_ctl.work_sta) {
				task_ctl.work_sta = TASK_PHOTO;
			}
			t_photo.photo_sta = 1;
			break;
		case T_KEY_AIRBORNE_CTRL | T_KEY_LONG_UP:
			if(task_ctl.work_sta != TASK_RECORD_VIDEO  && TASK_USB_DEVICE != task_ctl.work_sta) {
				task_ctl.work_sta = TASK_RECORD_VIDEO;
			}
			t_record_video.recording_sta = 1;
			break;
		case SYSTEM_500MS:
			//OSD_changeFlag = 1;
			break;
		case SYSTEM_1S:
			if(powerSaveFlag == 2)	//the condition of hold mode is valid, so system enter the hold mode on the next time
			{
				task_ctl.work_backup_sta = task_ctl.work_sta;
				task_ctl.work_sta = TASK_HOLD_MODE;
			}
			break;
		default:
			break;
    }
}


void init_task_data(void)
{
	memset__(&task_ctl, 0, sizeof(task_ctl));
}

void run_task(void)
{
	g_stcJpegInfo.bLowPowerFlag = 0;
	t_record_video.lock_recording_sta = 0;		//lock mode recording sta flag init
	task_ctl.on_taking = 0;
	task_ctl.on_playing = 0;					//init the playing 
	task_ctl.on_recording = 0;					//init the on_recording
	task_ctl.bat_lev = 0;						//init the bat level
	task_ctl.work_sta = TASK_RECORD_VIDEO;  //é»è®¤è¿å¥å½åæ¨¡å¼
	g_stcJpegInfo.bPowerOffFlag = FALSE;

	if(device_online & BIT(B_USB_DEV_ONLINE))
	{
		task_ctl.work_backup_sta = task_ctl.work_sta; 
		task_ctl.work_sta = TASK_USB_DEVICE;
	}

	#if	(USER_CONFIG==CONFIG_AX3251_AIRBORNE)
	#else
	sys_dcin_start_flag_init();				//
	#endif
	
	while (task_ctl.work_sta != TASK_POWER_OFF)
	{
        switch (task_ctl.work_sta) 
		{
        case TASK_RECORD_VIDEO:
            task_record_video();
            break;
        case TASK_PHOTO:
            task_photo();
            break;
		#if (LCD_USE != LCD_NO_DISPLAY)		
        case TASK_PLAY:
            task_play();
            break;
		#endif	
		case TASK_USB_DEVICE:
			task_usb_device();
			break;
		case TASK_HOLD_MODE:
			task_holdMode();
			break;
        default:
            break;
        }
	}

}

void task_exit()
{
	if(task_ctl.work_sta != TASK_USB_DEVICE)		//because usb input ,can't power off
	{
		cur_menu.menu_type = MENU_IDLE;			//exit menu
		task_ctl.work_sta = TASK_POWER_OFF;		// break task ,and power off
		g_stcJpegInfo.bPowerOffFlag = 1;	//break record,and play,and power off
		deg_Printf("task_exit() \n");
	}
}

void task_into_lock_record_video()
{
	if(task_ctl.work_sta != TASK_USB_DEVICE && task_ctl.work_sta != TASK_RECORD_VIDEO && task_ctl.work_sta != TASK_POWER_OFF)
	{
		task_ctl.work_sta = TASK_RECORD_VIDEO;		//into record video
		if(!task_ctl.on_recording)						
		{
			t_record_video.lock_recording_sta = 1;			//start recording
		}
		if(task_ctl.on_playing)							//pause playying
		{
			task_play_pause_control();
		}
		deg_Printf("lock mode and recording video\n");
	}
	else		//task video
	{
		if(!task_ctl.on_recording)						
		{
			t_record_video.recording_sta = 1;			//start recording
		}
	}

	cur_menu.menu_type = MENU_IDLE;				//exit menu
	task_ctl.on_lock_mode = 1;
}

u8 task_get_lock_mode_flag()
{
	return task_ctl.on_lock_mode;
}


