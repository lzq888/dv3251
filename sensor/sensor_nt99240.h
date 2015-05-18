/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : sensor_nt99140.h
* Author             : pengtao_zhang
* Version            : V0826a
* Date               : 08/26/2013
* Description        : sensor nt99140 HEADER FILE.
***************************************************************************/
#ifndef _SENSOR_NT99240_H_
#define _SENSOR_NT99240_H_

/*
#define SENSOR_PIN_CONF()    REG32(PA_DIR) &= ~BIT(5);REG32(PA_DIR) &= ~BIT(6);
#define SENSOR_RESET()       REG32(PA) &= ~BIT(5)
#define SENSOR_NRESET()      REG32(PA) |= BIT(5)
#define SENSOR_POWERDN()     REG32(PA) |= BIT(6)
#define SENSOR_NORMAL()      REG32(PA) &= ~BIT(6)
*/
#define NT99240_I2C_BAUD        (40000)         //400K
#define NT99240_I2C_READ_ADDR   (0x6d)
#define NT99240_I2C_WRITE_ADDR  (0x6c)
#define NT99240_CHIP_ID_ADDR    (0x3000)


u8 sensor_Init(void);
u8 u8sensor_ReadID(void);
void sensor_rotate(u8 flag);

#endif
