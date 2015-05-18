/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : task_photo.h
* Author             : pengtao_zhang
* Version            : V0225a
* Date               : 02/25/2014  ; mm/dd/yyyy
* Description        : record photo task HEADER FILE.
***************************************************************************/
#ifndef _TASK_PHOTO_H_
#define _TASK_PHOTO_H_

typedef struct {
	u8 photo_sta;         //播放的子状态
	s8 fast_view_time;    //快速预览的时间
	u8 display_update;   //是否需要刷新显示
	u8 sd_flag;          //sd卡状态，用于显示判断
	u32 file_num;        //录像目录下，当前需要新建的文件的序号
}t_photo_trl;

extern t_photo_trl t_photo;
extern BOOL bFastViewFlag;

void task_photo_init(void);
void task_photo_display(void);
void dis_pic_back_sensor(void);
void task_photo_common_even(void);
void task_photo_event(u8 msg);
void task_photo_deal_msg(u8 msg);
void task_photo_exit(void);
void task_photo(void);

#endif