/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : sensor_ov9710.h
* Author             : pengtao_zhang
* Version            : V1110a
* Date               : 11/10/2013
* Description        : sensor bf3925 HEADER FILE.
***************************************************************************/
#ifndef _SENSOR_BF3925_H_
#define _SENSOR_BF3925_H_

/*
#define SENSOR_PIN_CONF()    REG32(PA_DIR) &= ~BIT(5);REG32(PA_DIR) &= ~BIT(6);
#define SENSOR_RESET()       REG32(PA) &= ~BIT(5)
#define SENSOR_NRESET()      REG32(PA) |= BIT(5)
#define SENSOR_POWERDN()     REG32(PA) |= BIT(6)
#define SENSOR_NORMAL()      REG32(PA) &= ~BIT(6)
*/
#define BF3925_I2C_BAUD        (40000)         //400K
#define BF3925_I2C_READ_ADDR   (0xdd)
#define BF3925_I2C_WRITE_ADDR  (0xdc)
#define BF3925_CHIP_ID_ADDR    (0xfc)


u8 sensor_Init(void);
u8 u8sensor_ReadID(void);
void sensor_rotate(u8 flag);
#endif
