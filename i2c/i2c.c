/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : i2c.c
* Author             : pengtao_zhang
* Version            : V0726a
* Date               : 07/26/2013 ;mm/dd/yyyy
* Description        : This file provides all the i2c firmware functions.
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
static u8 g_byDevWriteAddr;
static u8 g_byDevReadAddr;
BOOL bI2CBusy_Flag=0;
#define iic_delay() 	Delay_nopCnt(60)	//delay 3us

/*******************************************************************************
* Function Name  : i2c_Init
* Description    : initialize the i2c
* Input          : u32I2CBaud:     i2c baud
                   u8DevWriteAddr: i2c device write ID
                   u8DevReadAddr:  i2c device read ID
* Output         : None
* Return         : None
*******************************************************************************/
void i2c_Init(u32 u32I2CBaud, u8 u8DevWriteAddr,u8 u8DevReadAddr)
{
	bI2CBusy_Flag=1;
#if (I2C_MAP == I2C_MAP1)		//select PA0(SCL), PA1(SDA)
	REG32(PMAP_CFG0)  |= BIT(20);
	REG32(PMAP_CFG0)  &= ~BIT(19);
	REG32(PMAP_CFG0)  &= ~BIT(18);
	REG32(PA) |= 0x0003;     	//bit0,1
	REG32(PA_DIR) |= 0x0003;  	//input
	REG32(PA_PU0)  |= 0x0003; 	//pull up
	REG32(I2C_PRER) = APB_CLK/((5*u32I2CBaud))-1;
	REG32(I2C_CFG) |= BIT(7);      //enable
#elif (I2C_MAP == I2C_MAP2)		//select PA7(SCL), PA8(SDA)
	REG32(PMAP_CFG0)  &= ~BIT(14);//跟SPI复用,disable SPI
	SETB(REG32(PA), 9);					//CS HIGH
	CLRB(REG32(PA_DIR), 9);			    //CS output
	
	REG32(PMAP_CFG0)  &= ~BIT(19);
	REG32(PMAP_CFG0)  |= BIT(18);//PA7 PA8
	REG32(PMAP_CFG0)  |= BIT(20);
	REG32(PA_DIR) |= 0x0180;  	//PA7(SCL),PA8(SDA) input
	REG32(PA)  |= 0x0180; 		//PA9(SPI CS) output high level
	REG32(PA_PU0) |= 0x0180; 
	REG32(PA_PD0) &= ~0x0180; 
	REG32(I2C_PRER) = APB_CLK/((5*u32I2CBaud))-1;
	REG32(I2C_CFG) |= BIT(7);      //enable
#elif (I2C_MAP == I2C_MAP3)		//select PG7(SCL), PG8(SDA)
	REG32(PMAP_CFG0)  |= BIT(20);
	REG32(PMAP_CFG0)  |= BIT(19);
	REG32(PMAP_CFG0)  |= BIT(18);
	REG32(PG) |= 0x0180;     	//bit7,8
	REG32(PG_DIR) |= 0x0180;  	//input
	REG32(PG_PU0)  |= 0x0180; 	//pull up
	REG32(I2C_PRER) = APB_CLK/((5*u32I2CBaud))-1;
	REG32(I2C_CFG) |= BIT(7);      //enable
#elif (I2C_MAP == I2C_MAP_SW)	//select software simulate I2C signal
	#if ((I2C_SCL_PORT_BIT == 12) && (UART_USE == UART1_MAP1))	//I2C and UART is on the same port
		REG32(PMAP_CFG0)  &= ~(1<<7);
	#endif
#elif (I2C_MAP == I2C_MAP_SW2)	//select software simulate I2C signal
	//I2C and SPI0_MAP0 is on the same port
	REG32(PMAP_CFG0)  &= ~(1<<14);		//SPI0_MAP0 not mapping to io
	REG32(PMAP_CFG0)  &= ~(1<<7);	// uart not map to io 
#else 
	......
#endif

    g_byDevWriteAddr = u8DevWriteAddr;
    g_byDevReadAddr = u8DevReadAddr;
	bI2CBusy_Flag=0;
}

/*******************************************************************************
* Function Name  : i2c_SendStart
* Description    : i2c start
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void i2c_SendStart(void)
{
#if ((I2C_MAP == I2C_MAP_SW)||(I2C_MAP == I2C_MAP_SW2))
	I2C_SCL_SDA_OUT();
    I2C_SCL_SDA_HIGH();
    iic_delay();
    I2C_SDA_LOW();
    iic_delay();
    I2C_SCL_LOW();
#else
	REG32(I2C_CMD) = BIT(7);  //generate (repeated) start condition
#endif
}

/*******************************************************************************
* Function Name  : i2c_SendStop
* Description    : i2c stop
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void i2c_SendStop(void)
{
#if ((I2C_MAP == I2C_MAP_SW)||(I2C_MAP == I2C_MAP_SW2))
	I2C_SDA_OUT();
    I2C_SDA_LOW();
    iic_delay();
    I2C_SCL_HIGH();
    iic_delay();
    I2C_SDA_HIGH();
	Delay_10US(50);
#else
	REG32(I2C_CMD) = BIT(6);   // generate stop signal
    Delay_10US(50);
#endif
}

/*******************************************************************************
* Function Name  : u8ReceiveACK
* Description    : received acknowledge from slave
* Input          : None
* Output         : None
* Return         : 1:ack
                   0:nack
*******************************************************************************/
u8 u8i2c_ReceiveACK(void)
{
    u8 u8ack;
#if ((I2C_MAP == I2C_MAP_SW)||(I2C_MAP == I2C_MAP_SW2))
    I2C_SDA_IN();
    iic_delay();
    I2C_SCL_HIGH();
    iic_delay();
    if (!I2C_SDA_IS_HIGH()) {
        //printf("t\n");
        u8ack = true;
    }
	else {
		u8ack = false;
	}
    I2C_SCL_LOW();
   // printf("f\n");	
#else
    u8ack = !(REG32(I2C_STA)&BIT(7));
 /*   if(u8ack)
        deg_Printf("i2c ack\n");
    else
        deg_Printf("i2c Nack\n");
*/
#endif
    return u8ack;
}

/*******************************************************************************
* Function Name  : i2c_SendByte
* Description    : i2c send one byte data
* Input          : u8byI2CSendData: data
* Output         : None
* Return         : None
*******************************************************************************/
void i2c_SendByte(u8  u8byI2CSendData)
{
#if ((I2C_MAP == I2C_MAP_SW)||(I2C_MAP == I2C_MAP_SW2))
	u32 i;
    I2C_SDA_OUT();
    for (i=8; i!=0; i--) {
        if (u8byI2CSendData & BIT(7)) {
            I2C_SDA_HIGH();
        } else {
            I2C_SDA_LOW();
        }
        iic_delay();
        I2C_SCL_HIGH();
        iic_delay();
        I2C_SCL_LOW();
        u8byI2CSendData <<= 1;
    }
#else
    REG32(I2C_TX) = u8byI2CSendData;
    REG32(I2C_CMD) |= BIT(4);             //Write to  slave
    while( BIT_CK_1(REG32(I2C_STA),1) );//BIT(1) = 1 when transferring data
#endif
}

/*******************************************************************************
* Function Name  : u8i2c_RecvByte
* Description    : i2c receive one byte data
* Input          : u8AckFlag: when a receiver,send ack or ack
                   0:ack
                   1:nack
* Output         : None
* Return         : u8byRecvData: received data
*******************************************************************************/
u8 u8i2c_RecvByte(u8 u8AckFlag)
{
	u8 u8byRecvData = 0;
#if ((I2C_MAP == I2C_MAP_SW)||(I2C_MAP == I2C_MAP_SW2))
	u8 i;
    I2C_SDA_IN();
    for (i=8; i!=0; i--) {
        iic_delay();
        I2C_SCL_HIGH();
        iic_delay();
        u8byRecvData <<= 1;
        if (I2C_SDA_IS_HIGH()) {
            u8byRecvData |= BIT(0);
        }
        I2C_SCL_LOW();
    }
	if(I2C_NACK == u8AckFlag)
	{
		I2C_SDA_OUT();
		I2C_SDA_HIGH();
		iic_delay();
		I2C_SCL_HIGH();
		iic_delay();
		I2C_SCL_LOW();
	}
	else
	{
		I2C_SDA_OUT();
		I2C_SDA_LOW();
		iic_delay();
		I2C_SCL_HIGH();
		iic_delay();
		I2C_SCL_LOW();
	}
#else
	if(I2C_NACK == u8AckFlag)    //after read from slave, send NACK
	{
	    REG32(I2C_CMD) |= BIT(3)|BIT(5);   //
    }
	else   ////after read from slave, send ACK
	{
	   REG32(I2C_CMD) |= BIT(5);
	}
	while( BIT_CK_1(REG32(I2C_STA),1) );//BIT(1) = 1 when transferring data
	u8byRecvData = (u8)REG32(I2C_RCV);
#endif
    return u8byRecvData;
}

/*******************************************************************************
* Function Name  : u8i2c_Read
* Description    : i2c read data
* Input          : u8byI2CAddress: read data from this address
* Output         : None
* Return         : u8byI2CReadResult: received data from this address
*******************************************************************************/
u8 u8i2c_Read(u8 u8byI2CAddress)
{
    u8  u8byI2CReadResult;
	bI2CBusy_Flag=1;
    i2c_SendStart();
	i2c_SendByte(g_byDevWriteAddr);
	u8i2c_ReceiveACK();
    i2c_SendByte(u8byI2CAddress);
    u8i2c_ReceiveACK();
    i2c_SendStop();
    i2c_SendStart();
    i2c_SendByte(g_byDevReadAddr);
    u8i2c_ReceiveACK();
    u8byI2CReadResult = u8i2c_RecvByte(I2C_NACK);  //NO_ACK
    i2c_SendStop();
	bI2CBusy_Flag=0;
    return  u8byI2CReadResult;
}

/*******************************************************************************
* Function Name  : i2c_Write
* Description    : i2c write data
* Input          : u8byI2CAddress: write data to this address
                   u8byI2CData: data
* Output         : None
* Return         : None
*******************************************************************************/
void i2c_Write(u8 u8byI2CAddress,u8 u8byI2CData)
{
	bI2CBusy_Flag=1;
    i2c_SendStart();
	i2c_SendByte(g_byDevWriteAddr);
	u8i2c_ReceiveACK();
    i2c_SendByte(u8byI2CAddress);
    u8i2c_ReceiveACK();
    i2c_SendByte(u8byI2CData);
    u8i2c_ReceiveACK();
    i2c_SendStop();
	bI2CBusy_Flag=0;
}
