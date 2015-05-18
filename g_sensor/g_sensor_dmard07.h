/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : g_sensor.h
* Author             : zhipeng_lin
* Version            : V0726a
* Date               : 09/05/2014
* Description        : sensor HEADER FILE.
***************************************************************************/
#ifndef _G_SENSOR_DMARD07_H_
#define _G_SENSOR_DMARD07_H_


#define G_SEN_WRITE_ADDR	0x38
#define G_SEN_READ_ADDR		0x39
#define G_SEN_BAUD          (40000)
#define G_SEN_ID            (0x07)

void Gsen_set_Threshold(u8 threshold);
void G_sensor_init(void);
u8 Gsen_check_lock_flag(void);
void Gsen_Int_Set(void);
#endif