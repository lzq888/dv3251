/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : task_photo.c
* Author             : pengtao_zhang
* Version            : V0225a
* Date               : 02/25/2014  ;  mm/dd/yyyy
* Description        : This file provides all the record photo functions.
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
t_photo_trl t_photo;
BOOL bFastViewFlag = 0;
 
void task_photo_init(void)
{ 
	deg_Printf("task photo init\n");
	csi_Start(1,1);
	if(0 == sys_ctl.tv_mode)
		lcd_set_backlight(1);
	reset_powerSaveChk();
	if((device_online&BIT(B_SD_ONLINE)))		// sd online
	{
		g_SystemState = SYSTEM_IDLE;
	}
	OSDInit(&OSD1Inf,0,0 ,MENU_WIDTH,MENU_HEIGHT,0xff,ALPHA_0X00_COLOR);
	OSD1_useColorAlpha();
	task_record_clean_system_time();
	t_photo.display_update = 1;
	t_photo.sd_flag = 0;
	t_photo.fast_view_time = -1; //»¹Ã»ÓÐÅÄÕÕÆ¬£¬²»ÐèÒªÔ¤ÀÀ
	sd_dis_flag = 0;
	OSD_changeFlag = 1;
}
 
void task_photo_start()
{
	if(FALSE == sd_err_reinit())
	{
		return;
	}

	if(!InitRecordFolder())
		return;

	if(f_get_free_space() < MIN_FREESECTOR)				//card full ,just let led not work. only for airborne
	{
		g_SystemState = SYSTEM_CARD_OVERSPACE;
		deg_Printf("no space \n");
		return ;
	}
	g_stcJpegInfo.RecordType = RECORD_PICTURE;
	g_SystemState = SYSTEM_RECORD_PICTURE;

	if (FR_OK != RecordJPGFile())
	{
		deg_Printf("record jpeg file error !!!\n");
		csi_Stop();
		#if	(USER_CONFIG==CONFIG_AX3251_AIRBORNE)
		#else
		Delay_MS(500);
		#endif
		csi_Start(1,1);
	}
	else
	{
		g_SystemState = SYSTEM_STOP_RECORD_PICTURE;
		deg_Printf("record jpeg file ok\n");

#if	(USER_CONFIG!=CONFIG_AX3251_AIRBORNE)
		music_init((u32*)AVI_AUDIO_FRAME_BUF_ADDR,0xfff,DAC_SAMPLE_16000,0);		//play take photo sound
		sys_play_music(RES_PHOTO_SOUND);
#endif

		if(sys_ctl.fast_view)
		{
			#if (LCD_USE != LCD_NO_DISPLAY)
			bFastViewFlag = 1;
			t_photo.fast_view_time=sys_ctl.fast_view_time;
			f_open(&Fil,(char const *)filename, FA_WRITE | FA_READ);
			PlayPictureFile(&Fil);
			#endif
		}
		else if((sys_ctl.jpeg_picture_size == JPEG_SIZE_1280_720)||(sys_ctl.jpeg_picture_size == JPEG_SIZE_640_480))
		{
			csi_Stop();
			#if	(USER_CONFIG==CONFIG_AX3251_AIRBORNE)
			#else
			Delay_MS(500);
			#endif
			csi_Start(0,1);
		}
	}
	g_SystemState = SYSTEM_STOP_RECORD_PICTURE;
}

void task_photo_dis_system_time()
{
    int i;
    for(i=0; i<TIME_INFO_LEN; i++)
	{                                           //ptr_TimeInfo  //wanted disp timer
		if(TimeInfoCurrent[i]!= TimeInfo_for_record[i])  //TimeInfoBuff //current disp time
		{
			TimeInfo_for_record[i] = TimeInfoCurrent[i];
			if(TimeInfoCurrent[i] == ':')
				lcd_UpdatePartOsdData_SDRAM(&OSD1Inf, (u32)(&(Lcd_osd_sys_time[10][0])), SYS_TIME_XS+NUM_WIDTH*i, SYS_TIME_YS, NUM_WIDTH, NUM_HEIGHT);
			else if(TimeInfoCurrent[i] == '/')
				lcd_UpdatePartOsdData_SDRAM(&OSD1Inf, (u32)(&(Lcd_osd_sys_time[12][0])), SYS_TIME_XS+NUM_WIDTH*i, SYS_TIME_YS, NUM_WIDTH, NUM_HEIGHT);
			else
				lcd_UpdatePartOsdData_SDRAM(&OSD1Inf, (u32)(&(Lcd_osd_sys_time[TimeInfoCurrent[i]-'0'][0])), SYS_TIME_XS+NUM_WIDTH*i, SYS_TIME_YS, NUM_WIDTH, NUM_HEIGHT);
		}
	}
}

void task_photo_display(void)
{
	if(OSD_changeFlag) {
		OSD_changeFlag = 0;
		lcd_UpdateOsdIconData_FromSdram(&OSD1Inf, OSD_PHOTO, TASK_OSD_XS, TASK_OSD_YS);	//æç§æ¨¡å¼å¾æ 
		
		if(sys_ctl.picture_time_info_en)
		{
	    		task_photo_dis_system_time();
		}
	    	else
		{
	    		lcd_FillPartOsdData(&OSD1Inf, ALPHA_0X00_COLOR, SYS_TIME_XS, SYS_TIME_YS, NUM_WIDTH*TIME_INFO_LEN, NUM_HEIGHT);
			task_record_clean_system_time();
		}

//==========night light======
		if(1 == light_sta)		//night
			lcd_UpdateOsdIconData_FromSdram(&OSD1Inf, OSD_NIGHT, TASK_OSD_XS, TASK_OSD_YS+(TASK_ICON_HEIGHT+ICON_INTERVAL_SPACE)*2); 
		else 				//normal
			lcd_UpdateOsdIconData_FromSdram(&OSD1Inf, OSD_NORMAL, TASK_OSD_XS, TASK_OSD_YS+(TASK_ICON_HEIGHT+ICON_INTERVAL_SPACE)*2);  
//=========show night light end==
		
		DisPlaySDCard();
		
		BatVolDisplay();
		LockModeDisplay();
		
		ZoomNumDisplay();	
		lcd_UpdateOsdIconData_FromSdram(&OSD1Inf, OSD_RESA2560x1440+sys_ctl.jpeg_picture_size, MENU_WIDTH-TASK_OSD_XS-(2*TASK_ICON_XSPACE), TASK_OSD_YS+TASK_ICON_YSPACE);
	}
}

void dis_pic_back_sensor(void)
{
	csi_Start(0,1);
	t_photo.fast_view_time = -1;
	bPhotoScalFlag = 0;
	bFastViewFlag = 0;
}

void task_photo_common_even(void)
{
	if(delResult != FR_OK) {
		delResult = f_unlink_removeChain(&delFS, &work_fatfs,&delCLST,1);
		deg_Printf("u");
	}
	if(g_stcJpegInfo.bPowerOffFlag)
	{
		task_ctl.work_sta = TASK_POWER_OFF;
	}
}

void task_photo_event(u8 msg)
{
	task_photo_common_even();
	if(t_photo.photo_sta) {
		if((t_photo.fast_view_time < 0) && (!task_ctl.on_taking))
		{
			deg_Printf("photo_sta start Photo\n");
			t_photo.photo_sta = 0;
			task_ctl.on_taking = 1; 
			#if	(USER_CONFIG==CONFIG_AX3251_AIRBORNE)
			#else
			Delay_MS(300);
			#endif
			task_photo_start();
			task_ctl.on_taking = 0; 
		}	
	}
}


void task_photo_deal_msg(u8 msg)
{
	switch(msg)
	{
	case T_KEY_PLAY | T_KEY_SHORT_UP:
		t_photo.photo_sta = 1;
		/*if((t_photo.fast_view_time < 0) && (!task_ctl.on_taking))
		{
			task_ctl.on_taking = 1; 
			Delay_MS(300);
			task_photo_start();
			task_ctl.on_taking = 0; 
			flush_msg();
		}*/
		break;
	case T_KEY_UP | T_KEY_SHORT_UP:
		if((t_photo.fast_view_time < 0) && (!task_ctl.on_taking))
		{
			video_enlager++;
			if(video_enlager>MAX_ENLAGER_FACTOR)
			{
				video_enlager = MAX_ENLAGER_FACTOR;
			}
			tvout_Change_dis_size(video_enlager,0);
			//t_record_video.display_update = 1;
		}
		break;
	case T_KEY_DOWN | T_KEY_SHORT_UP:
		if((t_photo.fast_view_time < 0) && (!task_ctl.on_taking))
		{
			if(video_enlager>0)
			{
				video_enlager--;
			}
			tvout_Change_dis_size(video_enlager,0);
			//t_record_video.display_update = 1;
		}
		break;
	case T_KEY_MENU | T_KEY_SHORT_UP:
		if(t_photo.fast_view_time > 0)
			dis_pic_back_sensor();
		#if(MENU_DISPLAY_USE == MENU_DISPLAY_ENABLE)
			MenuDisplay(MENU_PHOTO);
		#endif
		task_record_clean_system_time();
		break;
	
	case SYSTEM_1S:
		if(t_photo.fast_view_time>0)
		{
			t_photo.fast_view_time--;
			if(t_photo.fast_view_time<=0)
			{
				dis_pic_back_sensor();
			}
		}
		CalcTimeInfo(TimeInfoCurrent);
		deal_msg(msg);
		break;
		
	default:
		deal_msg(msg);
		break;
	}
}

void task_photo_exit(void)
{
	deg_Printf("task photo exit\n");
}

void task_photo(void)
{
#if (USER_CONFIG == CONFIG_AX3251_AIRBORNE)
	if(SYSTEM_LVD_DETECT == g_SystemState)
	{
		return;
	}
#endif

    task_photo_init();

    while (task_ctl.work_sta == TASK_PHOTO)
    {
	#if (OSDICON_DISPLAY_USE == OSDICON_DISPLAY_ENABLE)
		task_photo_display();
	#endif
        u8 msg = get_msg();
        task_photo_event(msg);
		task_photo_deal_msg(msg);
    }
    task_photo_exit();
}