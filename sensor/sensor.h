/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : sensor.h
* Author             : pengtao_zhang
* Version            : V0726a
* Date               : 07/26/2013
* Description        : sensor HEADER FILE.
***************************************************************************/
#ifndef _SENSOR_H_
#define _SENSOR_H_


//================================= 

extern u8 u8SensorwriteID,u8SensorreadID;
extern u8 u8Addrbytnum,u8Databytnum;

void sensor_ClockInit(u32 u32SenClk);
void Sensor_WriteRegister(u8 *pbdata ,u8 u8AddrLength,u8 u8DataLength);
u32 Sensor_ReadRegister(u8 *pbdata ,u8 u8AddrLength,u8 u8DataLength);
void sensor_I2C_port_release(void);

#if(SEN_USE == SEN_GC0308)
    #include  "../sensor/sensor_gc0308.h"
#elif(SEN_USE == SEN_NT99140)
    #include  "../sensor/sensor_nt99140.h"
#elif(SEN_USE == SEN_NT99141)
    #include  "../sensor/sensor_nt99141.h"
#elif(SEN_USE == SEN_OV9710)
    #include  "../sensor/sensor_ov9710.h"
#elif(SEN_USE == SEN_OV7670)
    #include  "../sensor/sensor_ov7670.h"
#elif(SEN_USE == SEN_NT99141)
    #include  "../sensor/sensor_nt99141.h"
#elif(SEN_USE == SEN_BF3925)
    #include  "../sensor/sensor_bf3925.h"
#elif(SEN_USE == SEN_SIV121DS)
    #include  "../sensor/sensor_siv121DS.h"  
#elif(SEN_USE == SEN_OV7725)
    #include  "../sensor/sensor_ov7725.h"
#elif(SEN_USE == SEN_NT99240)
    #include  "../sensor/sensor_nt99240.h"
#elif(SEN_USE == SEN_SIV100B)
    #include  "../sensor/sensor_siv100B.h"
#else 
	......
#endif

#endif
