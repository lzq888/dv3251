/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : task_holdMode.h
* Author             : dingping_chen
* Version            : V0225a
* Date               : 11/13/2014  ; mm/dd/yyyy
* Description        : hold mode to save power.
***************************************************************************/
#ifndef _TASK_HOLDMODE_H_
#define _TASK_HOLDMODE_H_

#define HOLD_MODE_COUNT_DEFAULT		(10000/8)	//10 seconds

extern u32 powerSaveFlag;
u32 powerSaveCheck();
void task_holdMode();

#endif
