/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : g_sensor.h
* Author             : zhipeng_lin
* Version            : V0726a
* Date               : 09/05/2014
* Description        : sensor HEADER FILE.
***************************************************************************/
#ifndef _G_SENSOR_H_
#define _G_SENSOR_H_

extern BOOL bGsensor_Lock;
extern u8 Gsensor_ID;

void GSensor_WriteRegister(u8 *pbdata ,u8 u8AddrLength,u8 u8DataLength);
u32 GSensor_ReadRegister(u8 *pbdata ,u8 u8AddrLength,u8 u8DataLength);
void Gsen_Scan(u8 u8IntervalCnt);
BOOL Gsen_Detect_IntPort(void);
void Gsen_Check_Int(u32 u32IntervalCnt);

#if (G_SEN_USE == G_SEN_NULL)
    #include  "../g_sensor/g_sensor_null.h"
#elif(G_SEN_USE == G_SEN_DMARD07)
    #include  "../g_sensor/g_sensor_dmard07.h"
#elif(G_SEN_USE == G_SEN_GMA301A)
    #include  "../g_sensor/g_sensor_gma301a.h"
#else 
	......
#endif

#endif
