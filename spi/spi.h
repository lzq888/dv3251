/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : spi.h
* Author             : pengtao_zhang
* Version            : V0211a
* Date               : 02/11/2014
* Description        : spi HEADER FILE.
***************************************************************************/
#ifndef _SPI_H_
#define _SPI_H_

//SPI flash command define
#define		SF_WRITE_ENABLE	       		0x06
#define		SF_WRITE_DISABLE	   		0x04
#define		SF_READ_STATUS	   			0x05
#define		SF_WRITE_STATUS	   			0x01
#define		SF_READ_DATA	   			0x03				// <= SF_SIZE
#define		SF_WRITE_DATA	   			0x02				// 256 BYTE
#define		SF_ERASE_BLOCK	   			0xD8				// 64K
#define		SF_ERASE_SECTOR	   			0x20				// 4k
#define		SF_READ_ID	       			0x9F				// 3 BYTE
#define		SF_ERASE_CHIP	   			0xC7
#define		SF_POWER_DOWN	   			0xB9
#define		SF_RELEASE_POWER_DOWN	   	0xAB

extern BOOL bSFBusy_Flag;

void spi_Init(u32 u32SPIBaud);
void spi_setCSStatus(u8 status);
void spi_SendByte(u8 u8Data);
u8 u8spi_ReceiveByte(void);
void spi_SFSendAddr(DWORD dwFlashAddr);
u32 u32spi_SFReadID(void);
void spi_SFReadData(void *pDataBuf,DWORD dwFlashAddr, u32 u32DataLen);
void spi_SFWriteEnable(void);
void spi_SFWriteDisable(void);
BOOL spi_SFWaitStatusOK (void);  
BOOL spi_SFWriteData(DWORD dwFlashAddr,void *pDataBuf, u32 u32DataLen);
BOOL spi_SFEraseSector(DWORD dwSectorAddr); 
BOOL spi_SFEraseBlock(DWORD dwSectorAddr);
BOOL spi_SFEraseChip();


///////////////////////////////////len of each table
#define AVIHEAD_TABLE_LEN      (512)
#define JPEG_TABLE_LEN         (0x840)   //2112


#define GC0308INIT_TABLE_LEN   (550)
#define NT99140INIT_TABLE_LEN  (486)
#define OV7670INIT_TABLE_LEN   (468)
#define OV9710INIT_TABLE_LEN   (94)


////////////////////////table head  sequence in spiflash
//ÇëÔÚDaTable.txtÖÐ°´ÈçÏÂË³ÐòÅÅÁÐ¸÷table,ÒòÎªÄ¿Â¼±íµÄË³ÐòÓë³ÌÐòÓÐ¹Ø¡£
#define HeadTableOffset               (0x200)   //offset in spiflash
#include "../res/res.h"


typedef struct _TABLE_INFO
{
	u32 Addr;   //addr of spiflsh
	u32 Len;
}TABLE_INFO;

#endif
