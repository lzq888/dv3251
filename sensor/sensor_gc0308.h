/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : sensor_gc0308.h
* Author             : pengtao_zhang
* Version            : V0726a
* Date               : 07/26/2013
* Description        : sensor gc0308 HEADER FILE.
***************************************************************************/
#ifndef _SENSOR_GC0308_H_
#define _SENSOR_GC0308_H_
/*
#define SENSOR_PIN_CONF()    REG32(PA_DIR) &= ~BIT(5);REG32(PA_DIR) &= ~BIT(6);
#define SENSOR_RESET()       REG32(PA) &= ~BIT(5)
#define SENSOR_NRESET()      REG32(PA) |= BIT(5)
#define SENSOR_POWERDN()     REG32(PA) |= BIT(6)
#define SENSOR_NORMAL()      REG32(PA) &= ~BIT(6)
*/
#define GC0308_I2C_BAUD        (100000)         //400K
#define GC0308_I2C_READ_ADDR   (0x43)
#define GC0308_I2C_WRITE_ADDR  (0x42)
#define GC0308_CHIP_ID_ADDR    (0x00)


u8 sensor_Init(void);
u8 u8sensor_ReadID(void);
void sensor_rotate(u8 flag);
#endif

