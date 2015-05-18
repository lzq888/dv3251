/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : sensor.c
* Author             : pengtao_zhang
* Version            : V0726a
* Date               : 07/26/2013
* Description        : This file provides all the sensor  firmware functions.
***************************************************************************/
//===================================================================
//                                                     	            |
//                       INCLUDE FILES                              |
//                                                                  |
//===================================================================
#include "../header/include.h"

//===================================================================
//                                                     	            |
//                      GLOBAL VARIABLE                             |
//                                                                  |
//===================================================================

u8 u8SensorwriteID,u8SensorreadID;
u8 u8Addrbytnum,u8Databytnum;

/*******************************************************************************
* Function Name  : sensor_ClockInit
* Description    : set sensor clock
* Input          : u32SenClk: senclk frequency
* Output         : None
* Return         : None
*******************************************************************************/
void sensor_ClockInit(u32 u32SenClk)
{
	u32 u32SenCLk_div;
	
	REG32(CLKCON2) &= ~BIT(26);
	Delay_nopCnt(100);
	REG32(CLKCON2) |= BIT(26);
	
	//REG32(LDO_ACON) &= 0xf8f;
	//REG32(LDO_ACON) |= 7<<4;   //sensor ldo 3.3V

	REG32(PB_DIR) &= ~BIT(10);     //sen_mclk output
	REG32(PMAP_CFG0)  |= BIT(17);  //sen_mclk map enable
	REG32(PMAP_CFG0)  &= ~BIT(16);
	REG32(CLKCON2) |= BIT(25);
	REG32(CLKCON2) &= ~BIT(24);
	
	u32SenCLk_div = PLL_CLK/u32SenClk - 1;
	REG32(CLKCON1) &= 0xf03fffff ;
	REG32(CLKCON1) |= u32SenCLk_div<<22;  //senclk =pll/(div+1)
}

/*******************************************************************************
* Function Name  : Sensor_WriteRegister
* Description    : write sensor register
* Input          : *pbdata :sensor register addr and data
                   u8AddrLength:sensor register addr length
                   u8DataLength:sensor register data length
* Output         : None
* Return         : None
*******************************************************************************/
void Sensor_WriteRegister(u8 *pbdata ,u8 u8AddrLength,u8 u8DataLength)
{
	u8 i;

	bI2CBusy_Flag=1;
	i2c_SendStart();
	i2c_SendByte(u8SensorwriteID);
	u8i2c_ReceiveACK();
	for(i=0;i<u8AddrLength;i++)
	{
		i2c_SendByte(pbdata[i]);
		u8i2c_ReceiveACK();
	}
	for(i=u8AddrLength;i<(u8AddrLength+u8DataLength);i++)
	{
		i2c_SendByte(pbdata[i]);
		u8i2c_ReceiveACK();
	}
	i2c_SendStop();
	bI2CBusy_Flag=0;
}

/*******************************************************************************
* Function Name  : Sensor_ReadRegister
* Description    : read sensor register
* Input          : *pbdata :sensor register addr
                   u8AddrLength:sensor register addr length
                   u8DataLength:sensor register data length
* Output         : None
* Return         : u32i2cReadResult:the result from sensor register
*******************************************************************************/
u32 Sensor_ReadRegister(u8 *pbdata ,u8 u8AddrLength,u8 u8DataLength)
{
	u8 i;
    u32 u32i2cReadResult=0;

	bI2CBusy_Flag=1;
    i2c_SendStart();
	i2c_SendByte(u8SensorwriteID);
	u8i2c_ReceiveACK();
    for(i=0;i<u8AddrLength;i++)
    {
		i2c_SendByte(pbdata[i]);
		u8i2c_ReceiveACK();
    }
    i2c_SendStop();
    i2c_SendStart();
    i2c_SendByte(u8SensorreadID);
	u8i2c_ReceiveACK();
	for(i=u8AddrLength;i<(u8AddrLength+u8DataLength-1);i++)
	{
	    pbdata[i] = u8i2c_RecvByte(I2C_ACK);
	    u8i2c_ReceiveACK();
	}
	pbdata[u8AddrLength+u8DataLength-1] = u8i2c_RecvByte(I2C_NACK);
	i2c_SendStop();
	for(i=0;i<u8DataLength;i++)
	{
		u32i2cReadResult |= pbdata[i+u8AddrLength]<<((u8DataLength-1-i)*8);
	}
	bI2CBusy_Flag=0;
	return u32i2cReadResult;
}


void sensor_I2C_port_release(void)
{
	bI2CBusy_Flag=1;
#if (I2C_MAP == I2C_MAP2)		//select PA7(SCL), PA8(SDA)
	REG32(PA_PU0) &= ~(0x0180);
	REG32(PMAP_CFG0)  &= ~BIT(20);//ä¸SPIå¤ç¨ï¼disable IIC,
	spi_Init(12000000);
	deg_Printf("IIC Disable\n");
#elif (I2C_MAP == I2C_MAP_SW)
	#if ((I2C_SCL_PORT_BIT == 12) && (UART_USE == UART1_MAP1))	//I2C and UART is on the same port
		REG32(PMAP_CFG0)  |= (1<<7);
		REG32(PG_DIR) &= ~(1<<12);
	#endif
#elif (I2C_MAP == I2C_MAP_SW2)
	  //I2C and SPI0_MAP0 is on the same port
		REG32(PMAP_CFG0)  |= (1<<14);
		spi_setCSStatus(1);      	//SPI_CS HIGH
		CLRB(REG32(PA_DIR), 9);			    //SPI_CS output

	//=====uart not map to io====
	REG32(PMAP_CFG0)  |= (1<<7);

#endif	
	bI2CBusy_Flag=0;
}