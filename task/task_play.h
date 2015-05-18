/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : task_play.h
* Author             : pengtao_zhang
* Version            : V0228a
* Date               : 02/28/2014  ; mm/dd/yyyy
* Description        : play task HEADER FILE.
***************************************************************************/
#ifndef _TASK_PLAY_H_
#define _TASK_PLAY_H_

enum {
	PLAY_PHOTO,
	PLAY_VIDEO,
	PLAY_MENU,
	PLAY_STOP,
	PLAY_EXIT
};

enum 
{
	PLAY_NEXT_FILE,
	PLAY_PRVE_FILE,
	PLAY_CUR_FILE
};


typedef struct {
	u8 play_sta;         //播放的子状态
	u8 display_update;   //是否需要刷新显示
	u8 pause_flag;       //暂停标志
	u8 sd_flag;          //sd卡状态，用于显示判断
	u8 file_lock_flag;		//0 : cur file is unlocked , 1 :cur file is locked
}t_play_trl;

extern t_play_trl t_play;
extern BOOL bTaskPlayExit_Flag;
extern u32 play_file_num;

void task_play_init(void);
void task_play_deal_msg(void);
void task_play_Next(void);
void task_play_start(void);
void task_play_event(void);
void task_play_display(void);
void task_play_exit(void);
void task_play(void);
void delete_current_file(void);
void delete_all_file(void);
void lock_current_file(void);
void unlock_current_file(void);
void lock_all_file(void);
void unlock_all_file(void);
void task_play_pause_control(void);

#endif