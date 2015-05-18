/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : task_video.h
* Author             : pengtao_zhang
* Version            : V0225a
* Date               : 02/25/2014  ; mm/dd/yyyy
* Description        : record video task HEADER FILE.
***************************************************************************/
#ifndef _TASK_VIDEO_H_
#define _TASK_VIDEO_H_

#define TOTAL_TIME_LEN 8


typedef struct {
	u8 recording_sta;         //录像的子状态；1：正在录； 0：录像未开始
	u8 display_update;   //是否需要刷新显示
	u8 sd_flag;          //sd卡状态，用于显示判断
	u8 DC_record;        //接上DC后，过1~2s后开始录像
	u8 lock_recording_sta;	//lock mode start recording flag
	u32 file_num;        //录像目录下，当前需要新建的文件的序号
}t_record_video_trl;

extern t_record_video_trl t_record_video;
extern u8 TimeInfo_for_record[TIME_INFO_LEN]; 
#if (MENU_WIDTH == 320)
extern u8 Lcd_osd_sys_time[13][176];
#elif (MENU_WIDTH == 220)
extern u8 Lcd_osd_sys_time[13][176];
#else
extern u8 Lcd_osd_sys_time[12][32];
#endif

void task_record_1s_check();
void task_record_set_md_wait();
u8 task_record_get_push_key_stop_flag();
//===flag: 0 is not push key stop. 1 is push key stop=====
void task_record_set_push_key_stop_flag(u8 flag);
void task_video_MD_wait(u8 cnt);
void task_record_video_init(void);
void task_record_start(void);
void task_record_deal_msg(u8 msg);
void task_record_dis_system_time(void);
void task_record_clean_system_time(void);
void task_record_dis_record_time(void);
//void task_record_dis_osd_recording();
void cal_record_time(void);
void  clear_record_dis_time(void);
void task_record_video_display(void);
void MotionDetectDisplay(void);
void task_record_common_even(void);
void task_record_video_event(void);
void task_record_exit(void);
void task_record_video(void);



#endif