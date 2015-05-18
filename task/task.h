/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : task.h
* Author             : pengtao_zhang
* Version            : V0225a
* Date               : 02/25/2014  ; mm/dd/yyyy
* Description        : task HEADER FILE.
***************************************************************************/
#ifndef _TASK_H_
#define _TASK_H_
#include "../config/config.h"

//???????????????
enum 
{
#if TASK_RECORD_VIDEO_EN
    TASK_RECORD_VIDEO = 0,
#endif
#if TASK_PHOTO_EN
    TASK_PHOTO,
#endif
#if TASK_PLAY_EN
    TASK_PLAY,
#endif
	TASK_MAX_NUM,
#if TASK_USB_DEVICE_EN
	TASK_USB_DEVICE,
#endif
	TASK_HOLD_MODE,
#if TASK_POWER_OFF_EN
    TASK_POWER_OFF,
#endif
};

typedef struct {
    u8 work_sta;                //ÈÎÎñ×´Ì¬
    u8 work_backup_sta;
	u8 on_recording;            //µ±Ç°ÊÇ·ñÕýÔÚÂ¼Ïñ
    u8 on_playing;              //µ±Ç°ÊÇ·ñÕýÔÚ²¥·ÅÂ¼Ïñ
	u8 on_taking;
    u8 bat_lev;                 //µç³ØµÄ¼¶±ð
    u8 flag_update_bat;         //Ë¢ÐÂµç³ØÏÔÊ¾
    u8 on_lock_mode;		//0: is not lock mode , 1: is on lock mode  
} type_task_ctl;

extern type_task_ctl task_ctl;
extern u8 video_enlager;

void BatVolDisplay(void);
void ZoomNumDisplay(void);
void mode_change(void);
void night_light_ctrl(void);
void DisPlaySDCard(void);
void deal_msg(u8 msg);
void run_task(void);
void task_exit();
void init_task_data();
void DisPlayLowPower(void);
void LockModeDisplay(void);
void task_into_lock_record_video();
u8 task_get_lock_mode_flag();

#endif
