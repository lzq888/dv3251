/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : i2c.h
* Author             : pengtao_zhang
* Version            : V0726a
* Date               : 07/26/2013
* Description        : i2c HEADER FILE.
***************************************************************************/
#ifndef _I2C_H_
#define _I2C_H_

//========== I2C select ========
#define I2C_MAP1	1	//select PA0(SCL), PA1(SDA)
#define I2C_MAP2	2	//select PA7(SCL), PA8(SDA)
#define I2C_MAP3	3	//select PG7(SCL), PG8(SDA)
#define I2C_MAP_SW	4	//select software simulate I2C signal,  AX3251_AIRBORNE
#define I2C_MAP_SW2	5	//select software simulate I2C signal,  AX3251_K6000

#define I2C_ACK    (0)
#define I2C_NACK   (1)

extern BOOL bI2CBusy_Flag;

void i2c_Init(u32 u32I2CBaud, u8 u8DevWriteAddr,u8 u8DevReadAddr);
void i2c_SendStart(void);
void i2c_SendStop(void);
u8 u8i2c_ReceiveACK(void);
void i2c_SendByte(u8  u8byI2CSendData);
u8 u8i2c_RecvByte(u8 u8AckFlag);
u8 u8i2c_Read(u8 u8byI2CAddress);
void i2c_Write(u8 u8byI2CAddress,u8 u8byI2CData);

#endif
