/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : fat_api.c
* Author             : pengtao_zhang
* Version            : V0625a
* Date               : 06/25/2014
* Description        : This file provides all the fat_api firmware functions.
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
u32 u32DataOffset; // after fill data,need to update index segment.

FRESULT WriteIndexData(FIL* indexFile,u32 len)
{
	u32 writed;
	FRESULT ret;
	if((g_stcJpegInfo.dwIndexWrLen & (AVI_INDEX_DEST_BUFF_LEN-1)) + len <= AVI_INDEX_DEST_BUFF_LEN) {
		deg_Printf("i");
		ret = f_write(indexFile,(void *)AVI_INDEX_DEST_BUFF_ADDR+(g_stcJpegInfo.dwIndexWrLen & (AVI_INDEX_DEST_BUFF_LEN-1)), len, (uint*)(&writed));
		if(len != writed) {
			ret = FR_NOT_READY;
		}
		if(FR_OK !=ret)
		{
			deg_Printf("write index data err:%d\n",ret);
			return ret;
		}
		g_stcJpegInfo.dwIndexWrLen += len;
		return FR_OK;
	}
	else {
		deg_Printf("data range err\n");
		return FR_INT_ERR;
	}
}
/*******************************************************************************
* Function Name  : Write4KJpegData
* Description    : write 4k data
* Input          : uDataType: 0:indexdata
                              1:jpeg data
                              2:audio data
* Output         : None
* Return         : FRESULT
*******************************************************************************/
FRESULT Write4KJpegData(FIL* file,u32 uDataType) //0:indexdata ; 1:frame data;2:audio data
{

	FRESULT ret;
	int i;
	DWORD *pWriteData;
	UINT writed;
	u32 *indexbuf=(u32 *)AVI_INDEX_DEST_BUFF_ADDR;
	if ( 1 == uDataType)
	{
//		deg_Printf("f");
		REG32(SDR_CFG1) &= ~BIT(6);
		REG32(SDR_CFG1) |= BIT(6);
		pWriteData = (DWORD *)g_stcJpegInfo.pFSWriteBuf;
		if(task_ctl.work_sta == TASK_RECORD_VIDEO)
		{
			if(pWriteData[0] == 0x63643030)
			{
				//pWriteData[1] = g_stcJpegInfo.iJpegFrameSize-8;
			}
		}
		ret = f_write(file, (void *)pWriteData, 0x2000,&writed);
		if(0x2000 != writed) {
			ret = FR_NOT_READY;
		}
		if(FR_OK !=ret)
		{
			deg_Printf("write frame data err:%d\n",ret);
			return ret;
		}

	}
	else
	{
//		deg_Printf("a");
		pWriteData = (DWORD *)g_stcJpegInfo.pAudioDataBuf;
		pWriteData[0] = 0x62773130;
		pWriteData[1] = 0x00001ff8;

		ret = f_write(file, (void*)pWriteData, 0x2000,&writed);
		if(0x2000 != writed) {
			ret = FR_NOT_READY;
		}
		if(FR_OK !=ret)
		{
			deg_Printf("write audio data err:%d\n",ret);
			return ret;
		}
	}
	return FR_OK;

}

/*******************************************************************************
* Function Name  : WriteVideoInfo
* Description    : write  record video data,include index???????¡ê????????????????video???????¡ê????????????????audio 
* Input          : None
* Output         : None
* Return         : FRESULT
*******************************************************************************/
FRESULT WriteVideoInfo(FIL* file, FIL* indexFile)
{

	FRESULT ret;
	u32DataOffset = 0;
	static u8 cnt = 0;
	if(RECORD_VIDEO == g_stcJpegInfo.RecordType)
		timer_Timer1_Start();
	timer_Timer2_Start();

	flush_msg();

	while (TRUE)
	{
	    cnt++;
		if(cnt%16 == 0)
		{
		 	CheckVideoStopCondition();
		}
		if (g_stcJpegInfo.bFileOverFlag && (g_stcJpegInfo.iFSWriteBufCnt==g_stcJpegInfo.iJpegFillBufCnt))
		{
			ret = Write4KJpegData(file,1);
			if(FR_OK !=ret )
				return ret;
		    g_stcJpegInfo.iFSWriteBufCnt++;
			
			if(g_stcJpegInfo.iAudioFSWriteBufCnt < g_stcJpegInfo.iAudioFillBufCnt)
			{
				if(gp_fifo_num_ele_ava(&auido_sd_locat_fifo))
				{
					if ( (gp_fifo_look(&auido_sd_locat_fifo)+1) == g_stcJpegInfo.iFSWriteBufCnt)
					{
						if(g_stcJpegInfo.pAudioDataBuf == (u8 *)((u32)JPEG_BUFFER_END_ADDRESS - 0x2000))
							g_stcJpegInfo.pAudioDataBuf = (u8 *)((u32)JPEG_BUFFER_END_ADDRESS - (AUDIO_BUFFER_NUM*0x2000));
						else
							g_stcJpegInfo.pAudioDataBuf += g_stcJpegInfo.dwAudiobufSize ;
						
						gp_fifo_read(&auido_sd_locat_fifo);
						ret = Write4KJpegData(file,2);		//write audio data
						if(FR_OK !=ret )
							return ret;
						//g_stcJpegInfo.u32AudioDataReady = 0;
						deg(":");
						g_stcJpegInfo.iAudioFSWriteBufCnt++;
					}
				}
			}
			if (g_stcJpegInfo.bSpaceOverFlag)
			{
				timer_Timer1_Stop();
			}
			if(RECORD_VIDEO == g_stcJpegInfo.RecordType) {
				deg_Printf("write index finish\n");
				while(g_stcJpegInfo.dwIndexWrLen < g_stcJpegInfo.dwIndexLen) {
					if(g_stcJpegInfo.dwIndexWrLen + 0x2000 < g_stcJpegInfo.dwIndexLen) {
						ret = WriteIndexData(indexFile,0x2000);
						if(FR_OK !=ret )
							return ret;
					}
					else {
						ret = WriteIndexData(indexFile,g_stcJpegInfo.dwIndexLen-g_stcJpegInfo.dwIndexWrLen);
						if(FR_OK !=ret )
							return ret;
					}
				}
			}
			g_stcJpegInfo.dwIndexWrLen = 0;
			deg_Printf("finish OK\n");
			break;
		}
		if(g_stcJpegInfo.bRewritePicture)
		{
			g_stcJpegInfo.bRewritePicture = 0;
			g_stcJpegInfo.iFSWriteBufCnt = 0;
			f_lseek(file, 0);
			g_stcJpegInfo.pFSWriteBuf = g_stcJpegInfo.pFrameStartAddr;
			deg_Printf("RewritePicture\n");
		}

	 	 if(g_stcJpegInfo.iJpegFrameWriteCnt < g_stcJpegInfo.iJpegFrameFillCnt)
		{
			if (g_stcJpegInfo.iFSWriteBufCnt < g_stcJpegInfo.iJpegFillBufCnt)
			{
				ret = Write4KJpegData(file,1);		//write 4k chunk
				if(FR_OK !=ret )return ret;
				//deg("FC = %i; JC = %i\n", g_stcJpegInfo.iFSWriteBufCnt, g_stcJpegInfo.iJpegFillBufCnt);

				//update data buffer pointer
				g_stcJpegInfo.iFSWriteBufCnt++;
				g_stcJpegInfo.pFSWriteBuf += 0x2000;
				if (0x2000*g_stcJpegInfo.iJpegBuffSize == (g_stcJpegInfo.pFSWriteBuf-(BYTE *)(JPEG_BUFFER_START_ADDRESS)))
				{
					g_stcJpegInfo.pFSWriteBuf = (BYTE *)(JPEG_BUFFER_START_ADDRESS);
				}
			}
			if(gp_fifo_num_ele_ava(&JpegFrame_locat_fifo))
			{
				if (gp_fifo_look(&JpegFrame_locat_fifo) == g_stcJpegInfo.iFSWriteBufCnt)
				{
					g_stcJpegInfo.iJpegFrameWriteCnt++;
					gp_fifo_read(&JpegFrame_locat_fifo);
				}
			}
		}
		else if(g_stcJpegInfo.iJpegLineBufDone)
		{
			g_stcJpegInfo.iJpegLineBufDone = 0;

			if (sys_ctl.jpeg_picture_size == JPEG_SIZE_2560_1440)
			{
				WriteHalfLineBuffer();
			}
			else
			{
				WriteLineBuffer();
			}

			//deg_Printf("write line buffer\n");
		}
		if((g_stcJpegInfo.iJpegFrameWriteCnt == g_stcJpegInfo.iJpegFrameFillCnt)&&(g_stcJpegInfo.bFileOverFlag))
		{
			if (g_stcJpegInfo.iFSWriteBufCnt < g_stcJpegInfo.iJpegFillBufCnt)
			{
				ret = Write4KJpegData(file,1);		//write 4k chunk
				if(FR_OK !=ret )return ret;
				//deg("FC = %i; JC = %i\n", g_stcJpegInfo.iFSWriteBufCnt, g_stcJpegInfo.iJpegFillBufCnt);

				//update data buffer pointer
				g_stcJpegInfo.iFSWriteBufCnt++;
				g_stcJpegInfo.pFSWriteBuf += 0x2000;
				if (0x2000*g_stcJpegInfo.iJpegBuffSize == (g_stcJpegInfo.pFSWriteBuf-(BYTE *)(JPEG_BUFFER_START_ADDRESS)))
				{
					g_stcJpegInfo.pFSWriteBuf = (BYTE *)(JPEG_BUFFER_START_ADDRESS);
				}
			}
		}
		if(g_stcJpegInfo.iAudioFSWriteBufCnt < g_stcJpegInfo.iAudioFillBufCnt)
		{
			if(gp_fifo_num_ele_ava(&auido_sd_locat_fifo))
			{
				if ( (gp_fifo_look(&auido_sd_locat_fifo)+1) == g_stcJpegInfo.iFSWriteBufCnt)
				{
					if(g_stcJpegInfo.pAudioDataBuf == (u8 *)((u32)JPEG_BUFFER_END_ADDRESS - 0x2000))
						g_stcJpegInfo.pAudioDataBuf = (u8 *)((u32)JPEG_BUFFER_END_ADDRESS - (AUDIO_BUFFER_NUM*0x2000));
					else
						g_stcJpegInfo.pAudioDataBuf += g_stcJpegInfo.dwAudiobufSize ;
					
					gp_fifo_read(&auido_sd_locat_fifo);
					ret = Write4KJpegData(file,2);		//write audio data
					if(FR_OK !=ret )return ret;
					//g_stcJpegInfo.u32AudioDataReady = 0;
					//deg_Printf(":");
					g_stcJpegInfo.iAudioFSWriteBufCnt++;
				}
			}
		}
		if(RECORD_VIDEO == g_stcJpegInfo.RecordType) {
			if(g_stcJpegInfo.dwIndexWrLen + 0x3000 < g_stcJpegInfo.dwIndexLen) {
				ret = WriteIndexData(indexFile,0x2000);
				if(FR_OK !=ret )return ret;
				f_bound(file, indexFile);
				SyncAVIInfo(file, indexFile);
				sd_WaitSdStopTran();
			}
		}
	}

	return FR_OK;
}



