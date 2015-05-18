/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : sensor_ov7670.h
* Author             : pengtao_zhang
* Version            : V0829a
* Date               : 08/29/2013
* Description        : sensor ov7670 HEADER FILE.
***************************************************************************/
#ifndef _SENSOR_OV7670_H_
#define _SENSOR_OV7670_H_
/*
#define SENSOR_PIN_CONF()    REG32(PA_DIR) &= ~BIT(5);REG32(PA_DIR) &= ~BIT(6);
#define SENSOR_RESET()       REG32(PA) &= ~BIT(5)
#define SENSOR_NRESET()      REG32(PA) |= BIT(5)
#define SENSOR_POWERDN()     REG32(PA) |= BIT(6)
#define SENSOR_NORMAL()      REG32(PA) &= ~BIT(6)
*/
#define OV7670_I2C_BAUD        (40000)         //400K
#define OV7670_I2C_READ_ADDR   (0x43)
#define OV7670_I2C_WRITE_ADDR  (0x42)
#define OV7670_CHIP_ID_ADDR    (0x0a)

u8 sensor_Init(void);
u8 u8sensor_ReadID(void);

void sensor_rotate(u8 flag);
#endif
