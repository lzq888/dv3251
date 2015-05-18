/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : sensor_nt99140.h
* Author             : pengtao_zhang
* Version            : V0826a
* Date               : 08/26/2013
* Description        : sensor nt99140 HEADER FILE.
***************************************************************************/
#ifndef _SENSOR_NT99141_H_
#define _SENSOR_NT99141_H_


#define NT99141_I2C_BAUD        (40000)         //400K
#define NT99141_I2C_READ_ADDR   (0x55)
#define NT99141_I2C_WRITE_ADDR  (0x54)
#define NT99141_CHIP_ID_ADDR    (0x3000)


u8 sensor_Init(void);
u8 u8sensor_ReadID(void);
void sensor_rotate(u8 flag);

#endif
