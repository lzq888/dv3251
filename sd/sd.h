/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : sd.h
* Author             : pengtao_zhang
* Version            : V0809a
* Date               : 08/09/2013
* Description        : SD HEADER FILE.
***************************************************************************/
#ifndef _SD_H_
#define _SD_H_

#define SD_CLK 		20000000		//
#define SD_HS_CLK	30000000

#define SD_SAMPLE_EDGE  0   //0:fall; 1:rise
#define	FWS(FunctionWithSD)							{if(!FunctionWithSD) return FALSE;}

typedef enum
{
    NOT_SD,
    SD_10,
    SD_20_NC,
    SD_20_HC,
    MMC
}SD_VER;

typedef enum
{
    SD_FREE,
    SD_READ,
    SD_WRITE,
 //   SD_ABEND,
    SD_OFFLINE
}CARD_STATE;

typedef struct
{
    DWORD   	dwRCA;
    SD_VER		eVer;
    DWORD   	dwCap;

    DWORD   	dwNextLBA;
    CARD_STATE	eCardState;

}SD_INFO;

enum
{
    CARD_OFFLINE = 0,
    CARD_ONLINE,
    CARD_READY,
    CARD_STANDBY,
};


extern SD_INFO g_stcSDInfo;
extern volatile int bSDCardStatus;

BOOL bsd_Init(void);
void InitSDCard(void);
void sd_Wait74Clk(void);
BOOL bsd_Reset(void);
BOOL bsd_GetVer(void);
BOOL bsd_SetFunc(BYTE *pDataBuf);
DWORD dwsd_GetRspVar(void);
BOOL bsd_GetAllCID(void);
BOOL bsd_GetCID(void);
BOOL bsd_GetRCA(void);
BOOL bsd_DealWithRCA(void);
BOOL bsd_GetCSD(void);
DWORD dwsd_GetSDCap(void);
BOOL bsd_SelectCard(void);
BOOL bsd_SetBlockLen(void);
BOOL bsd_SetBusWidth(BOOL bBusWidthType);
BOOL bsd_IsTranState(void);
BOOL bsd_SendCMD(BYTE byCMDIndex, DWORD dwArgument);
BOOL bsd_Send_CMD(BYTE byCMDIndex, DWORD dwArgument);
BOOL bsd_Send_ACMD(BYTE byCMDIndex, DWORD dwArgument);
BOOL bsd_SetMMCRCA(void);
BOOL bsd_WaitDAT0High(void);
BOOL bsd_StopTran(void);
BOOL bsd_Close(void);
void sd_StartDataKick(int iDMAddr, BOOL bRWMode, int cnt);
BOOL bsd_WaitDataPending(void);
BOOL bsd_UpdateSDData(BYTE *pDataBuf, DWORD dwLBA, DWORD dwLBANum, BOOL bRWMode);
BOOL bsd_write(BYTE *pDataBuf, DWORD dwLBA, DWORD dwLBANum);
BOOL bsd_read(BYTE *pDataBuf, DWORD dwLBA, DWORD dwLBANum);
void sd_WaitSdStopTran(void);
BOOL bsd_DetectIO(void);
void sd_CheckOffline(void);
void sd_Detect(void);
BOOL sd_err_reinit(void);
#endif
