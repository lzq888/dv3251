#include "../header/include.h"
#include "gp_fifo.h"

AVI_INFO g_AVIFileInfo;

aIndexInfo g_IndexInfo;
aIndexInfo g_VideoIndexInfo;
aIndexInfo g_AudioIndexInfo;

aIndexInfo g_VideoIndexBuf[10];
aIndexInfo g_AudioIndexBuf[1];
GP_FIFO g_VideoIndexFIFO;
GP_FIFO g_AudioIndexFIFO;

aFrameInfo g_VideoFrameBuf;
aFrameInfo g_AudioFrameBuf;
aFrameInfo g_DispFrameBuf;
aFrameInfo g_DecodeVideoFrameBuf[1];
aFrameInfo g_DecodeDispFrameBuf[1];
GP_FIFO g_DecodeVideoFrameFIFO;
GP_FIFO g_DecodeDispFrameFIFO;

BOOL bPlayVideo_DacFlag = 0;
BOOL bOpenBackLightFlag = 0;

void avi_Parser(FIL *fp)
{
	u32 temp;
	u32 readed;
	FRESULT ret;
	
	ret = f_lseek(fp, 0);
	ret = f_read(fp, &temp,4,(uint *)(&readed));
 	//deg_Printf("ret = %d,readed = %d,temp = 0x%x\n",ret ,readed,temp);

	if(temp != 0x46464952)	// "RIFF"
		return;

	ret = f_read(fp,&g_AVIFileInfo.RIFFChunkSize, 4,(uint *)(&readed));
	//deg_Printf("g_AVIFileInfo.RIFFChunkSize = %d\n",g_AVIFileInfo.RIFFChunkSize );

	ret = f_read(fp, &temp,4,(uint *)(&readed));
	//deg_Printf("ret = %d,readed = %d,temp = 0x%x\n",ret ,readed,temp);
	if(temp != 0x20495641)	// "AVI "
		return;

	ret = f_read(fp, &temp,4,(uint *)(&readed));
	//deg_Printf("ret = %d,readed = %d,temp = 0x%x\n",ret ,readed,temp);
	if(temp != 0x5453494c)	// "LIST"
		return;

	ret = f_read(fp, &g_AVIFileInfo.hdrlChunkSize,4,(uint *)(&readed));
	//deg_Printf("g_AVIFileInfo.hdrlChunkSize = 0x%x\n",g_AVIFileInfo.hdrlChunkSize );

	ret = f_read(fp, &temp,4,(uint *)(&readed));
	//deg_Printf("ret = %d,readed = %d,temp = 0x%x\n",ret ,readed,temp);
	if(temp != 0x6c726468)	// "hdrl"
		return;

	ret = f_read(fp, &g_AVIFileInfo.aviMainHeader,64,(uint *)(&readed));
	//deg_Printf("ret = %d,readed = %d\n",ret ,readed);
	if(g_AVIFileInfo.aviMainHeader.fcc != 0x68697661)	// "avih"
		return;

	ret = f_lseek(fp, g_AVIFileInfo.hdrlChunkSize + 8 + 12);
	//deg_Printf("ret = %d,g_AVIFileInfo.hdrlChunkSize + 8 + 12 = %d\n",ret ,g_AVIFileInfo.hdrlChunkSize + 8 + 12);

	ret = f_read(fp, &temp,4,(uint *)(&readed));
	//deg_Printf("ret = %d,readed = %d,temp = 0x%x\n",ret ,readed,temp);
	if(temp != 0x5453494c)	// "LIST"
		return;

	ret = f_read(fp, &g_AVIFileInfo.moviChunkSize,4,(uint *)(&readed));
	//deg_Printf("ret = %d,readed = %d,g_AVIFileInfo.moviChunkSize = 0x%x\n",ret ,readed,g_AVIFileInfo.moviChunkSize);

	ret = f_read(fp, &temp,4,(uint *)(&readed));
	//deg_Printf("ret = %d,readed = %d,temp = 0x%x\n",ret ,readed,temp);
	if(temp != 0x69766f6d)	// "movi"
		return;

	ret = f_lseek(fp, g_AVIFileInfo.hdrlChunkSize + g_AVIFileInfo.moviChunkSize + 8*2 + 12);
	//deg_Printf("g_AVIFileInfo.hdrlChunkSize + g_AVIFileInfo.moviChunkSize + 8*2 + 12 = 0x%x \n",g_AVIFileInfo.hdrlChunkSize + g_AVIFileInfo.moviChunkSize + 8*2 + 12);

	ret = f_read(fp, &temp,4,(uint *)(&readed));
	//deg_Printf("ret = %d,readed = %d,temp = 0x%x\n",ret ,readed,temp);
	if(temp != 0x31786469)	// "idx1"
		return;

	ret = f_read(fp, &g_AVIFileInfo.idx1ChunkSize,4,(uint *)(&readed));
	if(ret != FR_OK) {
		deg_Printf("AVI read failed:%d\n",ret);
	}
	//deg_Printf("ret = %d,readed = %d,g_AVIFileInfo.idx1ChunkSize = 0x%x\n",ret ,readed,g_AVIFileInfo.idx1ChunkSize);
	g_AVIFileInfo.idx1Offset = 0;

	deg_Printf("avi parser ok\n");
}

extern bool bDeleteFile;

void avi_Player(FIL *fp)
{
	//u32 temp;
	u32 readed;
	FRESULT ret;

	aFrameInfo VideoFrameBuf, DispFrameBuf;
	//s16 file_num;
	//u32 i;
	u32 VideoFileOffset = 0;
	BOOL bStopFrameCnt_f = 0;
	u32 valid_frame_cnt = 0;
	u8 u8VideoFrameDropCnt = 0;
	u32 cur_num = play_file_num;
		
	avi_Parser(fp);

	if(g_AVIFileInfo.aviMainHeader.dwWidth == 1280 && g_AVIFileInfo.aviMainHeader.dwHeight == 720)
	{
			deg_Printf("resolution 1280 720\n");
	}
	else if(g_AVIFileInfo.aviMainHeader.dwWidth == 640 && g_AVIFileInfo.aviMainHeader.dwHeight == 360)
	{
			deg_Printf("resolution 640 360\n");
	}
	else if(g_AVIFileInfo.aviMainHeader.dwWidth == 640 && g_AVIFileInfo.aviMainHeader.dwHeight == 480)
	{
			deg_Printf("resolution 640 480\n");
	}
	else return;

	gp_fifo_init(&g_VideoIndexFIFO, g_VideoIndexBuf, sizeof(aIndexInfo), sizeof(g_VideoIndexBuf)/sizeof(aIndexInfo));
	gp_fifo_init(&g_AudioIndexFIFO, g_AudioIndexBuf, sizeof(aIndexInfo), sizeof(g_AudioIndexBuf)/sizeof(aIndexInfo));
	gp_fifo_init(&g_DecodeVideoFrameFIFO, g_DecodeVideoFrameBuf, sizeof(aFrameInfo), sizeof(g_DecodeVideoFrameBuf)/sizeof(aFrameInfo));
	gp_fifo_init(&g_DecodeDispFrameFIFO, g_DecodeDispFrameBuf, sizeof(aFrameInfo), sizeof(g_DecodeDispFrameBuf)/sizeof(aFrameInfo));

	g_IndexInfo.valid = 0;

	g_VideoFrameBuf.buf_addr = (u8 *)AVI_VIDEO_FRAME_BUF_ADDR;
	g_VideoFrameBuf.buf_size = AVI_VIDEO_FRAME_BUF_SIZE;
	g_AudioFrameBuf.buf_addr = (u8 *)AVI_AUDIO_FRAME_BUF_ADDR;
	g_AudioFrameBuf.buf_size = AVI_AUDIO_FRAME_BUF_SIZE;
	g_AudioFrameBuf.valid = 0;

	g_DispFrameBuf.buf_addr = (u8 *)(REG32(LCDCON46) + LCD_VIDEO_SDRAM_SIZE);
	if(g_DispFrameBuf.buf_addr >= (u8 *)(LCD_VIDEO_SDRAM_ADDR + LCD_VIDEO_SDRAM_SIZE*3))
	{
		g_DispFrameBuf.buf_addr = (u8 *)LCD_VIDEO_SDRAM_ADDR;
	}
	
	//g_DispFrameBuf.buf_addr = (u8 *)LCD_VIDEO_SDRAM_ADDR;
	g_DispFrameBuf.buf_size = LCD_VIDEO_SDRAM_SIZE;
	
	
	g_DispFrameBuf.valid = 0;
	DispFrameBuf.valid = 0;

	zeromem__((void *)&g_stcJpegInfo, sizeof(g_stcJpegInfo));


//	my_memset(AVI_AUDIO_FRAME_BUF_ADDR, 0, 0x2000);
//	audio_dac_init();
	timer_Timer2_Start();

	while(1)
	{
		if(!t_play.pause_flag)
		{
			if(!g_IndexInfo.valid)
			{
				if(g_AVIFileInfo.idx1Offset < g_AVIFileInfo.idx1ChunkSize)
				{
					ret = f_lseek(fp, g_AVIFileInfo.hdrlChunkSize + g_AVIFileInfo.moviChunkSize + 8*3 + 12 + g_AVIFileInfo.idx1Offset);
					g_AVIFileInfo.idx1Offset += 16;
					if(FR_OK != ret)
					{
						deg_Printf("f_lseek err \n");
						bStopFrameCnt_f = 1;
						timer_Timer2_Stop();
					}
/*
					if(IndexFile.FileObject.fptr == 0)
					{
						bStopFrameCnt_f = 1;
						timer_Timer2_Stop();
					}
*/
					ret = f_read(fp, &g_IndexInfo.aIndex,4*4,(uint *)(&readed));	//read indexentry
					if(FR_OK != ret)
					{
						deg_Printf("f_read err \n");
						bStopFrameCnt_f = 1;
						timer_Timer2_Stop();
					}
					
/*
					deg_Printf("g_IndexInfo.aIndex = %d\n",g_IndexInfo.aIndex.ckid );
					deg_Printf("g_IndexInfo.aIndex.dwFlags = 0x%x\n",g_IndexInfo.aIndex.dwFlags);
					deg_Printf("g_IndexInfo.aIndex.dwChunkOffset = 0x%x\n",g_IndexInfo.aIndex.dwChunkOffset);
					deg_Printf("g_IndexInfo.aIndex.dwChunkLength = 0x%x\n",g_IndexInfo.aIndex.dwChunkLength);
*/
					if(bStopFrameCnt_f)
					{
						bStopFrameCnt_f = 0;
						timer_Timer2_Start();
					}
					g_IndexInfo.valid = 1;
				}
			}

			if(g_IndexInfo.valid)
			{
				if((g_IndexInfo.aIndex.ckid & 0xffff0000) == 0x63640000)	// "dc"
				{
					if(!g_VideoIndexFIFO.fifo_full)
					{
						gp_fifo_push(&g_VideoIndexFIFO, &g_IndexInfo);
						g_IndexInfo.valid = 0;
					}
				}
				else	// "wb"
				{
					if(!g_AudioIndexFIFO.fifo_full)
					{
						gp_fifo_push(&g_AudioIndexFIFO, &g_IndexInfo);
						g_IndexInfo.valid = 0;
					}
				}
			}

			if(!g_VideoIndexFIFO.fifo_empty)
			{
				if(!g_DecodeVideoFrameFIFO.fifo_full)
				{
					gp_fifo_pop(&g_VideoIndexFIFO, &g_VideoIndexInfo);
					g_stcJpegInfo.iValidFrameCnt++;
					if(g_stcJpegInfo.iValidFrameCnt <= g_stcJpegInfo.i30FrameCnt)
					{
						u8VideoFrameDropCnt++;
					}
					if((g_stcJpegInfo.iValidFrameCnt > g_stcJpegInfo.i30FrameCnt) || (u8VideoFrameDropCnt > 4))
					{
						u8VideoFrameDropCnt = 0;
						u32 Offset;
						if(g_VideoIndexInfo.aIndex.dwChunkLength == 0) continue;
						Offset = g_AVIFileInfo.hdrlChunkSize + g_VideoIndexInfo.aIndex.dwChunkOffset + 8*2 + 12;
						if(VideoFileOffset == Offset) continue;
						VideoFileOffset = Offset;
						valid_frame_cnt++;

						ret = f_lseek(fp, VideoFileOffset);
						if(FR_OK != ret)
						{
							deg_Printf("f_lseek err:VideoFileOffset = 0x%x\n",VideoFileOffset);
							goto end;
						}
						
/*
						if(VideoFile.offset != 0)
							goto end;
*/

						if(g_VideoFrameBuf.buf_size < g_VideoIndexInfo.aIndex.dwChunkLength)
							goto end;
/*
						if(VideoFile.FileObject.fptr == 0 || VideoFile.FileObject.seek > 1024)
						{
							bStopFrameCnt_f = 1;
							timer_Timer2_Stop();
						}
*/

						ret = f_read(fp, g_VideoFrameBuf.buf_addr,g_VideoIndexInfo.aIndex.dwChunkLength,(uint *)(&readed));
						if(FR_OK != ret || g_VideoIndexInfo.aIndex.dwChunkLength != readed)
						{
							deg_Printf("videoindex read err:g_VideoIndexInfo.aIndex.dwChunkLength = 0x%x \n",g_VideoIndexInfo.aIndex.dwChunkLength);
							bStopFrameCnt_f = 1;
							timer_Timer2_Stop();
						}

						if(bStopFrameCnt_f)
						{
							bStopFrameCnt_f = 0;
							timer_Timer2_Start();
						}
						g_VideoFrameBuf.iFrameCnt = g_stcJpegInfo.iValidFrameCnt - 1;
						gp_fifo_push(&g_DecodeVideoFrameFIFO, &g_VideoFrameBuf);
						g_VideoFrameBuf.buf_addr += AVI_VIDEO_FRAME_BUF_SIZE;
						if(g_VideoFrameBuf.buf_addr > (u8 *)(AVI_VIDEO_FRAME_BUF_ADDR + AVI_VIDEO_FRAME_BUF_SIZE))
						{
							g_VideoFrameBuf.buf_addr = (u8 *)AVI_VIDEO_FRAME_BUF_ADDR;
						}
					}
					else
					{
						//deg_Printf("Drop FrameCnt is 0x%x\n", g_stcJpegInfo.iValidFrameCnt);
					}
				}
			}

			if(!g_DecodeVideoFrameFIFO.fifo_empty)
			{
				if(!g_DecodeDispFrameFIFO.fifo_full)
				{
					if(!g_DispFrameBuf.valid)
					{
						gp_fifo_pop(&g_DecodeVideoFrameFIFO, &VideoFrameBuf);
						g_DispFrameBuf.iFrameCnt = VideoFrameBuf.iFrameCnt;
						//deg("m");
						mjpdec_Start(VideoFrameBuf.buf_addr + 8, g_DispFrameBuf.buf_addr);
					}
				}
			}

			if(g_DispFrameBuf.valid == 1)
			{
				gp_fifo_push(&g_DecodeDispFrameFIFO, &g_DispFrameBuf);
				g_DispFrameBuf.valid = 0;
				g_DispFrameBuf.buf_addr += LCD_VIDEO_SDRAM_SIZE;
				if(g_DispFrameBuf.buf_addr >= (u8 *)(LCD_VIDEO_SDRAM_ADDR + LCD_VIDEO_SDRAM_SIZE*3))
				{
					g_DispFrameBuf.buf_addr = (u8 *)LCD_VIDEO_SDRAM_ADDR;
				}
			}

			if(!g_DecodeDispFrameFIFO.fifo_empty)
			{
				if(!DispFrameBuf.valid)
				{
					gp_fifo_pop(&g_DecodeDispFrameFIFO, &DispFrameBuf);
				}
			}

			if(DispFrameBuf.valid == 1)
			{
				if(DispFrameBuf.iFrameCnt < g_stcJpegInfo.i30FrameCnt)
				{
					DispFrameBuf.valid = 2;
	//				REG32(IMAGE_BASE_ADR) = ((u32)DispFrameBuf.buf_addr - 0x100000)>>1;
	//				REG32(LCD_CON) &= ~(1UL<<9);
					if(bOpenBackLightFlag == 1)
					{
						waittingLcdFrameEnd();
						REG32(LCDCON46) = (u32)DispFrameBuf.buf_addr;
					}
					//REG32(LCDCON0) = 0;
					blcd_FrameEnd_Flag = 0;
				}
			}

			if(DispFrameBuf.valid == 2)
			{
	//			if(REG32(LCD_CON) & BIT(9))
				{
					if(bOpenBackLightFlag == 0)
					{
						bOpenBackLightFlag = 1;
						u32 lcd_con_reg_save = REG32(LCDCON0);
						DIS_OSD1();
						DIS_OSD2();
						DIS_OSD3();
						lcd_set_panel_colour(0,0,0);
						#if(0 == LCD_MCU)
							waittingLcdFrameEnd();
							REG32(LCDCON0) &= ~(BIT(0)|BIT(6));
							REG32(LCDCON46) = (u32)DispFrameBuf.buf_addr;
							if(u32jpegSize_H == 1280)
								tvout_display_set(0,0,u32jpegSize_H/2,u32jpegSize_H/2,u32jpegSize_V/2,tvout_get_w(),tvout_get_h());
							else if(u32jpegSize_H == 640)
								tvout_display_set(0,0,u32jpegSize_H/2,u32jpegSize_H/2,u32jpegSize_V/2,tvout_get_w(),tvout_get_h());
							else if((u32jpegSize_H == 1920) | (u32jpegSize_H == 4032))
								tvout_display_set(0,0,u32jpegSize_H/4,u32jpegSize_H/4,u32jpegSize_V/4,tvout_get_w(),tvout_get_h());
							else
								tvout_display_set(0,0,u32jpegSize_H,u32jpegSize_H,u32jpegSize_V,tvout_get_w(),tvout_get_h());

							REG32(LCDCON0) = lcd_con_reg_save;
							REG32(LCDCON0) |= (BIT(0)|BIT(6));

						#else
							REG32(LCDCON0) &= ~(BIT(6));
							waittingLcdFrameEnd();
							REG32(LCDCON46) = (u32)DispFrameBuf.buf_addr;
							if(u32jpegSize_H == 1280)
								tvout_display_set(0,0,u32jpegSize_H/2,u32jpegSize_H/2,u32jpegSize_V/2,tvout_get_w(),tvout_get_h());
							else if(u32jpegSize_H == 640)
								tvout_display_set(0,0,u32jpegSize_H/2,u32jpegSize_H/2,u32jpegSize_V/2,tvout_get_w(),tvout_get_h());
							else if((u32jpegSize_H == 1920) | (u32jpegSize_H == 4032))
								tvout_display_set(0,0,u32jpegSize_H/4,u32jpegSize_H/4,u32jpegSize_V/4,tvout_get_w(),tvout_get_h());
							else
								tvout_display_set(0,0,u32jpegSize_H,u32jpegSize_H,u32jpegSize_V,tvout_get_w(),tvout_get_h());
							waittingLcdFrameEnd();
							REG32(LCDCON0) = lcd_con_reg_save;
							REG32(LCDCON0) |= (BIT(6));
						#endif
						//REG32(LCDCON0) |= (0 << 8) |(1 << 6) | (1 << 5) |(1 << 4)|(1 << 3)|(1 << 0);
	//	                lcd_BackLight(1);
					}
					if(blcd_FrameEnd_Flag == 1)
						DispFrameBuf.valid = 0;

					if(!task_ctl.on_playing)
					{
						t_play.pause_flag = 1;
						timer_Timer2_Stop();//xjc 
						//CloseFrameCntTimer();
						
						/* ä¸ºè§£å³âå é¤ä¸ä¸ªæä»¶ï¼å¦ææ¥ççä¸ä¸ä¸ªæä»¶ä¸ºvideoæä»¶æ¶åï¼menuçé¢è¿åä¸äºâå­å¨çbug.
						 * note: å¦æç¨æ·éæ±ä¸º'å é¤ä¸ä¸ªæä»¶åmenuçé¢å³å³é­ï¼èä¸æ¯menuä¾ç¶å­å¨å¹¶ä¸æé¢è§åè½ä»¥å¯ä»¥æ¥çå é¤
						 * ä¸ä¸ä¸ªæä»?ï¼åå³äºbDeleteFileåéçä»£ç é¨åå¯å»æ.
						 */
						if (bDeleteFile) 		// zzy, 2014-4-21
						{
//							deg_Printf("ready to exit\n");
							t_play.pause_flag = 0;
							//file_num = 0;	// avi_Playerå°éåºï¼ä»¥è¿å?å é¤'èå
						}
					}
				}
			}

			if(!g_AudioFrameBuf.valid)
			{
				if(!g_AudioIndexFIFO.fifo_empty)
				{
					gp_fifo_pop(&g_AudioIndexFIFO, &g_AudioIndexInfo);

					ret = f_lseek( fp, g_AVIFileInfo.hdrlChunkSize + g_AudioIndexInfo.aIndex.dwChunkOffset + 8*2 + 12);
					if(FR_OK != ret)
					{
						goto end;
					}
/*
					if(AudioFile.offset != 0)
						goto end;
*/
					if(g_AudioFrameBuf.buf_size < g_AudioIndexInfo.aIndex.dwChunkLength)
						goto end;

/*
					if(AudioFile.FileObject.fptr == 0 || AudioFile.FileObject.seek > 1024)
					{
						bStopFrameCnt_f = 1;
						timer_Timer2_Stop();
					}
*/

					ret = f_read(fp, g_AudioFrameBuf.buf_addr,(g_AudioIndexInfo.aIndex.dwChunkLength+8),(uint *)(&readed));
					if(FR_OK != ret ||(g_AudioIndexInfo.aIndex.dwChunkLength+8) !=  readed)
					{
						deg_Printf("videoindex read err \n");
						bStopFrameCnt_f = 1;
						timer_Timer2_Stop();
						break;
					}
					
					if(bStopFrameCnt_f)
					{
						bStopFrameCnt_f = 0;
						timer_Timer2_Start();
					}
					g_AudioFrameBuf.valid = 1;


					if(!(rd_reg(OBUF_STA)&0x3C))
						g_AudioFrameBuf.buf_addr = (u8 *)AVI_AUDIO_FRAME_BUF_ADDR+AVI_AUDIO_FRAME_BUF_SIZE;
					else
						g_AudioFrameBuf.buf_addr = (u8 *)AVI_AUDIO_FRAME_BUF_ADDR;

				}
			}

			if(g_AudioFrameBuf.valid == 1)
			{
				g_AudioIndexInfo.aIndex.dwChunkOffset = 8;
				g_AudioFrameBuf.valid = 2;
			}

			if(g_AudioFrameBuf.valid == 2)
			{
				if(bPlayVideo_DacFlag == 0)
				{
					bPlayVideo_DacFlag = 1;
					g_AudioFrameBuf.valid = 0;
				}
				else
				{
	//				g_AudioFrameBuf.valid = 0;
				}
			}

			if(g_VideoIndexFIFO.fifo_empty && g_AudioIndexFIFO.fifo_empty && g_DecodeVideoFrameFIFO.fifo_empty && g_DecodeDispFrameFIFO.fifo_empty
				&& (g_AudioFrameBuf.valid == 0) && (g_DispFrameBuf.valid == 0) && (DispFrameBuf.valid == 0))
			{
				break;
			}
		}
		task_play_deal_msg();
		task_play_display();

		if((cur_num != play_file_num) ||(task_ctl.work_sta != TASK_PLAY) ||(t_play.play_sta == PLAY_EXIT) ||(!(device_online&BIT(B_SD_ONLINE))))
		{
			deg_Printf(" out to play \n");
			break;
		}

	}
end:	
	if(REG32(IE)&BIT(OBUF_INT))
	{
		audio_dac_Stop();
		key_voice_init();
	}

	bPlayVideo_DacFlag = 0;
	bOpenBackLightFlag = 0;

	deg_Printf("Valid FrameCnt is 0x%x 0x%x\n", g_stcJpegInfo.iValidFrameCnt, valid_frame_cnt);
}


