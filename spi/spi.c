/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : spi.c
* Author             : pengtao_zhang
* Version            : V0211a
* Date               : 02/11/2013 ;mm/dd/yyyy
* Description        : This file provides all the spi firmware functions.
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
BOOL bSFBusy_Flag=0;

void spi_Init(u32 u32SPIBaud)
{
	bSFBusy_Flag = 1;
	CLRB(REG32(PCON0), 13);						//SPI clock enable
	REG32(PMAP_CFG0) |= BIT(14);				//SPI0 MAP0
	REG32(SPI0_BAUD) = APB_CLK/(2*u32SPIBaud) - 1;
	REG32(SPI0_CFG) |= BIT(4) | BIT(1) | BIT(0);
	spi_setCSStatus(1);					//CS HIGH
	CLRB(REG32(PA_DIR), 7);
	CLRB(REG32(PA_DIR), 9);	
	bSFBusy_Flag = 0;	
}

void spi_setCSStatus(u8 status)
{
	if(status) {
		SETB(REG32(PA), 9);					//CS HIGH
	}
	else {
		Delay_nopCnt(200);					//because SPI CS pin and SD DECT pin is multiplexed, so need delay to let  CS stable 
		CLRB(REG32(PA), 9);					//CS LOW
	}
}

void spi_SendByte(u8 u8Data)
{
	REG32(SPI0_CFG) &= ~BIT(5);  				//TX
	REG32(SPI0_BUF) = u8Data;
	while((REG32(SPI0_CFG)&0x80) ==0);
}

u8 u8spi_ReceiveByte(void)
{
	REG32(SPI0_CFG) |= BIT(5);  				//RX
	REG32(SPI0_BUF) = 0xff;
	while((REG32(SPI0_CFG)&0x80) ==0);
	return REG32(SPI0_BUF);
}

void spi_SFSendAddr(DWORD dwFlashAddr)
{
	spi_SendByte((dwFlashAddr>>16)&0xff);
	spi_SendByte((dwFlashAddr>>8 )&0xff);
	spi_SendByte((dwFlashAddr    )&0xff);
}

u32 u32spi_SFReadID(void)
{
	u8 u8SFID[3];
	u32 u32Result=0;

	bSFBusy_Flag = 1;
	spi_setCSStatus(0);					//CS LOW
	spi_SendByte(SF_READ_ID);
	u8SFID[2] = u8spi_ReceiveByte();
	u8SFID[1] = u8spi_ReceiveByte();
	u8SFID[0] = u8spi_ReceiveByte();
	spi_setCSStatus(1);					//CS HIGH
	u32Result = (u8SFID[2]<<16) | (u8SFID[1]<<8) | u8SFID[0];
	bSFBusy_Flag = 0;
	return u32Result;
}

void spi_SFReadData(void *pDataBuf,DWORD dwFlashAddr, u32 u32DataLen)
{
	u8 *pSFReadBuf = (u8 *)pDataBuf;

	bSFBusy_Flag = 1;
	spi_setCSStatus(0);					//CS LOW
	spi_SendByte(SF_READ_DATA);
	spi_SFSendAddr(dwFlashAddr);
	while(u32DataLen--)
	{
		*pSFReadBuf++ = u8spi_ReceiveByte();
	}
	spi_setCSStatus(1);					//CS HIGH
	bSFBusy_Flag = 0;
}
void spi_SFWriteEnable(void)
{	
	bSFBusy_Flag = 1;
	spi_setCSStatus(0);					//CS LOW
    spi_SendByte(SF_WRITE_ENABLE);
    spi_setCSStatus(1);					//CS HIGH	
	bSFBusy_Flag = 0;
}
void spi_SFWriteDisable(void) 
{
	bSFBusy_Flag = 1;
    spi_setCSStatus(0);					//CS LOW
    spi_SendByte(SF_WRITE_DISABLE);
    spi_setCSStatus(1);					//CS HIGH	
	bSFBusy_Flag = 0;
}
BOOL spi_SFWaitStatusOK (void) 
{
	int iTOCnt = 0;
	bSFBusy_Flag = 1;
    spi_setCSStatus(0);					//CS LOW
    spi_SendByte(SF_READ_STATUS);
	while (u8spi_ReceiveByte()&1)
	{
		if (iTOCnt++ > 8000*2000)		//2s
		{
			spi_setCSStatus(1);			//CS HIGH
			bSFBusy_Flag = 0;
			return FALSE;
		}
	}
    spi_setCSStatus(1);					//CS HIGH
	bSFBusy_Flag = 0;
	return TRUE;	
}

BOOL spi_SFWriteData(DWORD dwFlashAddr,void *pDataBuf, u32 u32DataLen)
{
	u8 *pSFWriteBuff = (u8 *)pDataBuf;
	
	spi_SFWriteEnable();
	bSFBusy_Flag = 1;
	spi_setCSStatus(0);					//CS LOW
	spi_SendByte(SF_WRITE_DATA);
	spi_SFSendAddr(dwFlashAddr);
	while (u32DataLen--)
	{
		spi_SendByte(*pSFWriteBuff++);
	}
	spi_setCSStatus(1);					//CS HIGH	
	bSFBusy_Flag = 0;

    if (!spi_SFWaitStatusOK())
	{
    	return FALSE;
	}

    return TRUE;
}

BOOL spi_SFEraseSector(DWORD dwSectorAddr)
{
	spi_SFWriteEnable();
	bSFBusy_Flag = 1;
	spi_setCSStatus(0);					//CS LOW
	spi_SendByte(SF_ERASE_SECTOR);
	spi_SFSendAddr(dwSectorAddr);
	spi_setCSStatus(1);					//CS HIGH	
	bSFBusy_Flag = 0;
    if (!spi_SFWaitStatusOK())
	{
    	return FALSE;
	}
    return TRUE;
}
BOOL spi_SFEraseBlock(DWORD dwSectorAddr)
{
	spi_SFWriteEnable();
	bSFBusy_Flag = 1;
	spi_setCSStatus(0);					//CS LOW
	spi_SendByte(SF_ERASE_BLOCK);
	spi_SFSendAddr(dwSectorAddr);
	spi_setCSStatus(1);					//CS HIGH	
	bSFBusy_Flag = 0;
    if (!spi_SFWaitStatusOK())
	{
    	return FALSE;
	}
    return TRUE;
}
BOOL spi_SFEraseChip()
{
	spi_SFWriteEnable();
	bSFBusy_Flag = 1;
	spi_setCSStatus(0);					//CS LOW
	spi_SendByte(SF_ERASE_CHIP);
	spi_setCSStatus(1);					//CS HIGH	
	bSFBusy_Flag = 0;
    if (!spi_SFWaitStatusOK())
	{
		my_printf("spi_SFEraseChip fail !!!");
    	return FALSE;
	}
    return TRUE;
}