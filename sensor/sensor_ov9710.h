/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : sensor_ov9710.h
* Author             : pengtao_zhang
* Version            : V0827a
* Date               : 08/27/2013
* Description        : sensor ov9710 HEADER FILE.
***************************************************************************/
#ifndef _SENSOR_OV9710_H_
#define _SENSOR_OV9710_H_

/*
#define SENSOR_PIN_CONF()    REG32(PA_DIR) &= ~BIT(5);REG32(PA_DIR) &= ~BIT(6);
#define SENSOR_RESET()       REG32(PA) &= ~BIT(5)
#define SENSOR_NRESET()      REG32(PA) |= BIT(5)
#define SENSOR_POWERDN()     REG32(PA) |= BIT(6)
#define SENSOR_NORMAL()      REG32(PA) &= ~BIT(6)
*/
#define OV9710_I2C_BAUD        (40000)         //400K
#define OV9710_I2C_READ_ADDR   (0x61)
#define OV9710_I2C_WRITE_ADDR  (0x60)
#define OV9710_CHIP_ID_ADDR    (0x0A)


u8 sensor_Init(void);
u8 u8sensor_ReadID(void);
void sensor_rotate(u8 flag);

#endif
