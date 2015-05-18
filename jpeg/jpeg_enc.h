/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : jpeg_enc.h
* Author             : pengtao_zhang
* Version            : V0814a
* Date               : 08/14/2013
* Description        : jpeg encode HEADER FILE.
***************************************************************************/
#ifndef _JPEG_ENC_H_
#define _JPEG_ENC_H_

#define video_buf_size 172800
#define audio_buf_size 16000


typedef enum
{
   RECORD_VIDEO,
   RECORD_AUDIO,
   RECORD_PICTURE
}RECORD_TYPE;

typedef struct
{
	u32		dwRecordType;//0:pic ; 1:video
	u32		dwAudiobufSize;//4K->video,16K->voice
	BOOL 	bIndexBufFull;
	BOOL 	bExIndexBufFull;
	BOOL 	bIndexBufFlag;		//FALSE:__TEMP_BUFF; TRUE:dwExIndexBuf

	u32		dwFrameEndBlock;			//index buf write after this chuck block.
	DWORD 	*dwpIndexBuf;
	DWORD	dwIndexLen;
	DWORD 	dwIndexWrLen;
	DWORD	dwChunkLen;

	BYTE	*pJpegFillBuf;
	BYTE	*pFSWriteBuf;
	BYTE 	*pFrameStartAddr;
	int		iJpegFillBufCnt;
	int		iFSWriteBufCnt;
	int 	iJpegBuffSize;
	int 	i30FrameCnt;
	int     i30FrameCnt_diff;
	int		iValidFrameCnt;
	int		iJpeg10MSCnt;
	BOOL 	bTimeOverFlag;
	BOOL 	bFileOverFlag;
	BOOL 	bSpaceOverFlag;
	BOOL	bPowerOffFlag;
	BOOL	bLowPowerFlag;
	BOOL    bVideoAutoRecordFlag;  //spycam Vedio auto record and save flag
	BOOL    bAudioAutoRecordFlag;  //spycam Audio auto record and save flag
	BOOL 	bRewritePicture;
	RECORD_TYPE   RecordType;

	u32		u32AudioDataReady;
	u32		dwFrameEndBlockAudio;////audio buf write after this chuck block.
	BYTE	*pAudioDataBuf;
	int		iAudioFillBufCnt;
	int		iAudioFSWriteBufCnt;

	int		iJpegLineBufDone;
	int		iJpegFrameFillCnt;
	int		iJpegFrameWriteCnt;
	int		iJpegFrameSize;
}JPEG_INFO;


extern volatile JPEG_INFO g_stcJpegInfo;
//extern DWORD dwExIndexBuf[256];
extern volatile gp_fifo auido_sd_locat_fifo;
extern volatile gp_fifo JpegFrame_locat_fifo;

void jpeg_enc_Init(void);
void jpeg_enc_InitTab(void);
void jpeg_enc_InitQualTab(u8 u8Qual);
void jpeg_enc_Start(u32 infoMode);
void jpeg_enc_Stop(void);
void jpeg_enc_Isr(void);
void AddIndex(u32 uType);
void (*jpeg_isrfp)(void);
void jpeg_Isr();

#endif
