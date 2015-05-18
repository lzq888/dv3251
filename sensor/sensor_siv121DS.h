/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : sensor_siv121DS.h
* Author             : pengtao_zhang
* Version            : V0829a
* Date               : 08/29/2013
* Description        : sensor ov7670 HEADER FILE.
***************************************************************************/
#ifndef _SENSOR_SIV121DS_H_
#define _SENSOR_SIV121DS_H_
/*
#define SENSOR_PIN_CONF()    REG32(PF_DIR) &= ~BIT(1);REG32(PA_DIR) &= ~BIT(6);
#define SENSOR_RESET()       REG32(PF) &= ~BIT(1)
#define SENSOR_NRESET()      REG32(PF) |= BIT(1)
//#define SENSOR_POWERDN()     REG32(PA) |= BIT(6)
//#define SENSOR_NORMAL()      REG32(PA) &= ~BIT(6)
*/
#define SIV121DS_I2C_BAUD        (40000)         //400K
#define SIV121DS_I2C_READ_ADDR   (0x67)
#define SIV121DS_I2C_WRITE_ADDR  (0x66)
#define SIV121DS_CHIP_ID_ADDR    (0x01)

u8 sensor_Init(void);
u8 u8sensor_ReadID(void);

void sensor_rotate(u8 flag);
#endif
