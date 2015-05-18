/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : task_play.c
* Author             : pengtao_zhang
* Version            : V0228a
* Date               : 02/28/2014  ;  mm/dd/yyyy
* Description        : This file provides all the play functions.
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
t_play_trl t_play;
BOOL bTaskPlayExit_Flag=0;
u32 play_file_num;
u32 play_file_total;

void task_play_init(void)
{
	deg_Printf("task play init\n");
	reset_powerSaveChk();
#if	(USER_CONFIG==CONFIG_AX3251_AIRBORNE)
#else
	g_SystemState = SYSTEM_IDLE;
	FRESULT ret;
	u32 scan_num;
	play_file_num = 0;
	play_file_total = 0;
	memset__(&t_play,0,sizeof(t_play_trl));
	sd_dis_flag = 0;
	if(video_enlager)
	{
		video_enlager = 0;
		tvout_Change_dis_size(video_enlager,0);
	}

	if(FALSE == sd_err_reinit())
	{
		return;
	}

	if(!InitRecordFolder())
		return;
	
	if(light_sta)
		CLOSE_NIGHT_LIGHT();
	
	ret = f_scan_files(WORK_DIR_NAME,".JPG|.AVI",&scan_num);


	if(ret != FR_OK) {
		deg_Printf("scan file failed:%d\n",ret);
	}
	//deg_Printf("pass f_scan_files, ret =%d,scan_num = %d\n ",ret,scan_num);
	//play_file_total = scan_num;
	play_file_total = f_get_totalfile_num(0);
	play_file_num = play_file_total-1;
	deg_Printf("file total number =%d\n ",play_file_total);
	if(!play_file_total)
	{
		deg_Printf("no file\n");
		return; 
	}

	//play_file_num = 0;

	csi_Stop();
	OSDInit(&OSD1Inf,0,0 ,MENU_WIDTH,MENU_HEIGHT,0xff,ALPHA_0X00_COLOR);
	OSD1_useColorAlpha();
	if(0 == sys_ctl.tv_mode)
		lcd_set_backlight(1);
	t_play.play_sta = PLAY_STOP;
	OSD_changeFlag = 1;
#endif
}


void task_paly_get_file_num(u8 mode)
{
	switch(mode)
	{
		case PLAY_NEXT_FILE:
			if(play_file_num>0)
				play_file_num--;
			else
				play_file_num = play_file_total-1;
			//deg_Printf("play number =%d\n",play_file_num);	
			break;
		
		case PLAY_PRVE_FILE:
			if(play_file_num<play_file_total-1)
				play_file_num++;
			else
				play_file_num = 0;
			//deg_Printf("play number =%d\n",play_file_num);	
			break;
		default:
			break;
			
	}
}

void task_play_pause_control(void)
{
	if(!task_ctl.on_playing)
	{
		deg_Printf("play...\n");
		Delay_MS(500);
	
		task_ctl.on_playing = 1;
		t_play.pause_flag = 0;
		timer_Timer2_Start();
		audio_dac_init();
		g_stcJpegInfo.iValidFrameCnt = g_stcJpegInfo.i30FrameCnt;
	}
	else
	{
		deg_Printf("pause\n");
		t_play.pause_flag = 1;
		task_ctl.on_playing=0;
		audio_dac_Stop();
		key_voice_init();
	}
}

void task_play_deal_msg(void)
{
    u8 msg = get_msg();
	switch(msg)
	{
	case T_KEY_PLAY | T_KEY_SHORT_UP:
#if 0
		if(!fs_api.file_mode)//jpg file
			break;
#endif

		if((filename[14] =='J')&&(filename[15] =='P')&&(filename[16] =='G'))
		{
			
		}
		else
		{
			task_play_pause_control();
			t_play.play_sta = PLAY_VIDEO;
		}

		break;
	case T_KEY_MENU | T_KEY_SHORT_UP:
		if(task_ctl.work_sta == TASK_PLAY)
		{
			if(task_ctl.on_playing)
				task_play_pause_control();
			
			#if(MENU_DISPLAY_USE == MENU_DISPLAY_ENABLE)
			MenuDisplay(MENU_BROWSE);
			#endif

			if(t_play.pause_flag)
				task_play_pause_control();
		}
		else
			#if(MENU_DISPLAY_USE == MENU_DISPLAY_ENABLE)
			MenuDisplay(MENU_BROWSE);
			#endif
		break;
		
	case T_KEY_DOWN | T_KEY_SHORT_UP:
		task_paly_get_file_num(PLAY_NEXT_FILE);
		t_play.play_sta = PLAY_VIDEO;
		t_play.pause_flag = 0;
		break;
		
	case T_KEY_UP | T_KEY_SHORT_UP:
		task_paly_get_file_num(PLAY_PRVE_FILE);
		t_play.play_sta = PLAY_VIDEO;
		t_play.pause_flag = 0;
		break;
	
	default:
		deal_msg(msg);
		break;
	}

}

void task_play_Next(void)
{
	if(t_play.play_sta == PLAY_VIDEO)
		t_play.play_sta = PLAY_EXIT;
	else 
		t_play.play_sta = PLAY_PHOTO;
}

void task_play_start(void)
{
#if	(USER_CONFIG==CONFIG_AX3251_AIRBORNE)
#else
	FRESULT ret;
	u32 scan_num;
	u32 cur_num;
	if(FALSE == sd_err_reinit())
	{
		return;
	}
	ret = f_scan_files(WORK_DIR_NAME,".JPG|.AVI",&scan_num);
	//deg_Printf("pass f_scan_files, ret =%d,scan_num = %d\n ",ret,scan_num);
	//play_file_total = scan_num;
	play_file_total = f_get_totalfile_num(0);
	deg_Printf("play_file_total =%d\n ",play_file_total);
	
	if(play_file_total > 0)
	{
		//f_exchangesort_file(play_file_total);
		memcpy__(filename, "Record/", 7);
		deg_Printf("play_file_num =%d\n ",play_file_num);
		//char *ptr = f_get_scan_file_name(play_file_num,play_file_total);
		char *ptr = f_get_file_name(play_file_num,play_file_total);
		deg_Printf("get file name = %s\n",ptr);
		cur_num = (ptr[3]-'0')*100+(ptr[4]-'0')*10+(ptr[5]-'0');
		if('L' == ptr[0])
		{
			t_play.file_lock_flag = 1;
		}
		else
		{
			t_play.file_lock_flag = 0;
		}
		//deg_Printf("cur_num = %d\n",cur_num);
		memcpy__(filename+7, ptr, 13);
		//deg_Printf("filename = %s\n",filename);
	}
	else
	{
		return;
	}

	filename[10]='0'+ ((cur_num/100)%10);
	filename[11]='0'+ ((cur_num/10)%10);
	filename[12]='0'+ (cur_num%10);
	deg_Printf("fopen %s\n",filename);
	ret =  f_open(&Fil,(char const *)filename, FA_READ);
	if(ret != FR_OK) {
		deg_Printf("open file failed:%d\n",ret);
	}
	//deg_Printf("pass f_open, ret =%d\n ",ret);

	if((filename[14] =='A')&&(filename[15] =='V')&&(filename[16] =='I'))
	{
		PlayVideoFile(&Fil);
		f_close(&Fil);
		sd_WaitSdStopTran();
		t_play.play_sta = PLAY_VIDEO;
	}
	else if((filename[14] =='J')&&(filename[15] =='P')&&(filename[16] =='G'))
	{
		t_play.play_sta = PLAY_PHOTO;
		PlayPictureFile(&Fil);
		f_close(&Fil);
		sd_WaitSdStopTran();

		t_play.play_sta = PLAY_STOP;

	}

	task_ctl.on_playing = 0;
#endif
	deg_Printf("play finish\n");
}

void task_play_event(void)
{
	if(delResult != FR_OK) {
		delResult = f_unlink_removeChain(&delFS, &work_fatfs,&delCLST,1);
		deg_Printf("u");
	}
	if((!play_file_total) 
		|| (bSDCardStatus!=CARD_READY))	//in the playing, SD card pull out, so change mode
	{
		mode_change();
		return; 
	}
	if((t_play.play_sta == PLAY_VIDEO) || (t_play.play_sta == PLAY_PHOTO))
	{
		g_SystemState = SYSTEM_PLAY_VIDEO;
		task_play_start();
	}

	//=====for updata play_file_total =======
	if(t_play.play_sta == PLAY_STOP)	
	{
		u32 scan_num;
		f_scan_files(WORK_DIR_NAME,".JPG|.AVI",&scan_num);
		play_file_total = f_get_totalfile_num(0);
	}
	//=====end updata play_file_total======
}

void task_play_display(void)
{
	if(OSD_changeFlag) {
		OSD_changeFlag = 0;

		if(!task_ctl.on_playing)
		{
			lcd_UpdateOsdIconData_FromSdram(&OSD1Inf, OSD_PLAY, MENU_WIDTH-TASK_OSD_XS-TASK_ICON_XSPACE*2, TASK_OSD_YS);
		}
		else
		{
			lcd_UpdateOsdIconData_FromSdram(&OSD1Inf, OSD_PAUSE, MENU_WIDTH-TASK_OSD_XS-TASK_ICON_XSPACE*2, TASK_OSD_YS);	
		}

		if(t_play.file_lock_flag)
		{
			lcd_UpdateOsdIconData_FromSdram(&OSD1Inf, OSD_LOCK,  MENU_WIDTH-TASK_OSD_XS-VIDEO_TITLE*TASK_ICON_XSPACE, TASK_OSD_YS+TASK_ICON_HEIGHT+40);	/* 显示文件加锁图标 */
		}
		else
		{
			lcd_FillPartOsdData(&OSD1Inf, ALPHA_0X00_COLOR,  MENU_WIDTH-TASK_OSD_XS-VIDEO_TITLE*TASK_ICON_XSPACE, TASK_OSD_YS+TASK_ICON_HEIGHT+40, 32, 32);	/* 清除文件加锁图标 */
		}

		DisplayUnicodeStr_EXT(&OSD1Inf,(u8 *)(filename+7),32,MENU_HEIGHT-TASK_ICON_HEIGHT,0,0,MENU_ITEM1_W,FONT_HEIGHT,OSD_TIME_COLOR, ALPHA_0X00_COLOR,0xf2);
		BatVolDisplay();
		DisPlaySDCard(); 
	}
}

void task_play_exit(void)
{
	bTaskPlayExit_Flag = 1;	
	u32 lcd_con_reg_save = REG32(LCDCON0);
	DIS_OSD1();
	DIS_OSD2();
	DIS_OSD3();
	lcd_set_panel_colour(0,0,0);
	REG32(LCDCON0) &= ~(BIT(6));
	waittingLcdFrameEnd();
	csi_Start(1,0);
	tvout_display_set(0,0,u32csi_Dma_Size_H,u32csi_Dma_Size_H,u32csi_Dma_Size_V,tvout_get_w(),tvout_get_h());	
	waittingLcdFrameEnd();
	REG32(LCDCON0) = lcd_con_reg_save;
	DIS_OSD1();
	REG32(LCDCON0) |= (BIT(6));
	
	bTaskPlayExit_Flag = 0;
	t_play.play_sta = PLAY_STOP;
	if(light_sta)
		OPEN_NIGHT_LIGHT();
}

void task_play(void)
{
    task_play_init();

	//sd offline or no to play
	if((!play_file_total)||(!(device_online&BIT(B_SD_ONLINE))))
	{
		mode_change();
		return; 
	}
	task_ctl.on_playing = 0;
	t_play.pause_flag = 0;
	t_play.play_sta = PLAY_VIDEO;
	deg_Printf("play Init OK\n");
    while (task_ctl.work_sta == TASK_PLAY)
    {
		task_play_event();
		task_play_deal_msg();
		#if (OSDICON_DISPLAY_USE == OSDICON_DISPLAY_ENABLE)
		task_play_display();
		#endif
    }
    task_play_exit();

}


