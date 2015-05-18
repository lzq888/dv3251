/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : gsensor.c
* Author             : zhipen_lin
* Version            : V0726a
* Date               : 09/05/2014
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
BOOL bGsensor_Lock = FALSE;
u8 Gsensor_ID;

#if (G_SEN_NULL != G_SEN_USE)

/*******************************************************************************
* Function Name  : GSensor_WriteRegister
* Description    : write sensor register
* Input          : *pbdata :sensor register addr and data
                   u8AddrLength:sensor register addr length
                   u8DataLength:sensor register data length
* Output         : None
* Return         : None
*******************************************************************************/
void GSensor_WriteRegister(u8 *pbdata ,u8 u8AddrLength,u8 u8DataLength)
{

	u8 i;
	bI2CBusy_Flag=1;
	i2c_SendStart();
	i2c_SendByte(G_SEN_WRITE_ADDR);
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
* Function Name  : GSensor_WriteRegister
* Description    : read sensor register
* Input          : *pbdata :sensor register addr
                   u8AddrLength:sensor register addr length
                   u8DataLength:sensor register data length
* Output         : None
* Return         : u32i2cReadResult:the result from sensor register
*******************************************************************************/
u32 GSensor_ReadRegister(u8 *pbdata ,u8 u8AddrLength,u8 u8DataLength)
{

	u8 i;
    u32 u32i2cReadResult=0;
	bI2CBusy_Flag=1;
    i2c_SendStart();
	i2c_SendByte(G_SEN_WRITE_ADDR);
	u8i2c_ReceiveACK();
    for(i=0;i<u8AddrLength;i++)
    {
		i2c_SendByte(pbdata[i]);
		u8i2c_ReceiveACK();
    }
    i2c_SendStop();
    i2c_SendStart();
    i2c_SendByte(G_SEN_READ_ADDR);
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
 
void Gsen_Scan(u8 u8IntervalCnt)
{

	static u32 u32Gsen_Scan_Cnt = 0;
	static u8 u8Gsen_Check_Cnt = 0;
	if(Gsensor_ID != G_SEN_ID)
	{
		return;
	}
	if(sys_ctl.Gsensor_senstivity != 0)
	{
		u32Gsen_Scan_Cnt++;
		if(u32Gsen_Scan_Cnt%u8IntervalCnt == 0)
		{
			if(Gsen_check_lock_flag())
			{
				u8Gsen_Check_Cnt++;
				if(u8Gsen_Check_Cnt >= 1)
				{
					u8Gsen_Check_Cnt = 0;
					bGsensor_Lock = TRUE;
					//deg_Printf("G lock\n");
				}
			}
			else
			{
				u8Gsen_Check_Cnt = 0;
			}
		}
	}
}
 
 
BOOL Gsen_Detect_IntPort(void)
{
	BOOL bRes = FALSE;
	if (!CHKB(GSEN_DETECT_PORT_DATA, GSEN_DETECT_PORT_BIT))
	{
		bRes = TRUE;
		Gsen_Int_Set();
	}
	return bRes;

} 
 
void Gsen_Check_Int(u32 u32IntervalCnt)
{

	static u32 u32Gsen_Scan_Cnt = 0;
	static u8 u8Gsen_Check_Cnt = 0;
	if(Gsensor_ID != G_SEN_ID)
	{
		return;
	}
	if(sys_ctl.Gsensor_senstivity != 0)
	{
		u32Gsen_Scan_Cnt++;
		if(u32Gsen_Scan_Cnt%u32IntervalCnt == 0)
		{
			if(Gsen_Detect_IntPort())
			{
				u8Gsen_Check_Cnt++;
				if(u8Gsen_Check_Cnt >= 1)
				{
					u8Gsen_Check_Cnt = 0;
					bGsensor_Lock = TRUE;
					deg_Printf("G lock\n");
				}
			}
			else
			{
				u8Gsen_Check_Cnt = 0;
			}
		}
	}
}

#endif

