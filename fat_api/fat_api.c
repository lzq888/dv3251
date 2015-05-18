/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : fat_api.c
* Author             : pengtao_zhang
* Version            : V0810a
* Date               : 08/10/2013
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

FATFS work_fatfs;		/* FatFs work area needed for each volume */
BOOL bPhotoScalFlag=0;
static u32 AccFiles;
static FILINFO Finfo;
FILATTR fnlist[MAX_FILE_NAME_NUM];
char filename[28];
char index_filename[28];
FIL Fil;
FIL indexFil;
BOOL bRecording_Display_Flag; 
BOOL bStopVideo_Flag;

FATFS delFS;
DWORD delCLST;
u32 delResult = FR_OK;

#if (WORK_DIR_CNT==2)
	const char work_dir_dc[] = WORK_DIR_DC_NAME; 
	const char work_dir_dv[] = WORK_DIR_DV_NAME;
#elif (WORK_DIR_CNT==1)
	const char work_dir_dc[] = WORK_DIR_NAME; 
	const char work_dir_dv[] = WORK_DIR_NAME;
#else
	......
#endif

/*******************************************************************************
* Function Name  : InitRecordFolder
* Description    : initialize the record folder
* Input          : None
* Output         : BOOL
* Return         : TURE--initialize folder is right;FALSE--initialize folder is error
*******************************************************************************/
BOOL InitRecordFolder(void)
{ 
	char path[32]={0};
	u8 i;
	/*if(!bsd_Init())
	{
		sys_ctl.SD_err_off_flag = 1;
		g_SystemState = SYSTEM_CARD_ERROR;
		deg_Printf("sd init err!!!!!!!!!!\n");
		return FALSE; 
	}
	else*/
	{ 
		removeChainInit(&delFS);
		f_bound_init();
		my_memset(&delFS,0,sizeof(delFS));
		delCLST = 0;
		delResult = FR_OK;
		my_memset(&work_fatfs, 0, sizeof(work_fatfs));
		my_memset(&Fil,0,sizeof(Fil));
		//deg_Printf("Fatfs size=%x,Fil=%x\n",sizeof(work_fatfs),sizeof(Fil));
		//deg_Printf("work_fatfs.win = 0x%x\n",work_fatfs.win);
		//deg_Printf("Fil.buf = 0x%x\n",Fil.buf);
		FRESULT ret = f_mount(&work_fatfs, ROOT_DIR_NAME, 1);		/* Give a work area to the default drive */
		//deg_Printf("pass f_mount ret = 0x%x \n",ret);
		sys_update_FileOrder();
		i=0;
		my_memset(path,0,sizeof(path));
		while(i<sizeof(work_dir_dc)) {
			if('/'==work_dir_dc[i] || '\0'==work_dir_dc[i]) {
				ret = f_mkdir(path);
				//deg_Printf("pass f_mkdir:%s,ret = 0x%x \n",path,ret);
				if('\0'==work_dir_dc[i])
					break;
			} 
			path[i]=work_dir_dc[i];
			i++;
		};

		i=0;
		my_memset(path,0,sizeof(path));
		while(i<sizeof(work_dir_dv)) {
			if('/'==work_dir_dv[i] || '\0'==work_dir_dv[i]) {
				ret = f_mkdir(path);
				//deg_Printf("pass f_mkdir:%s,ret = 0x%x \n",path,ret);
				if('\0'==work_dir_dv[i])
					break;
			} 
			path[i]=work_dir_dv[i];
			i++;
		};
	
		return TRUE;
	}
}

u32 fat_GetReserveSpace(void)
{
	u32 SDResSpace = CRC_RECORD_RESERVE_SIZE + 0x32000;
	if(sys_ctl.jpeg_video_size == VIDEO_SIZE_640_480) 
	{
		if(sys_ctl.crc_record==1)
			SDResSpace = (CRC_RECORD_RESERVE_SIZE*3/30) + 0x32000;
		else if(sys_ctl.crc_record==2)
			SDResSpace = (CRC_RECORD_RESERVE_SIZE*5/30) + 0x32000;
		else
			SDResSpace = (CRC_RECORD_RESERVE_SIZE*1/3) + 0x32000;
	}
	else if((sys_ctl.jpeg_video_size == VIDEO_SIZE_1280_720)||(sys_ctl.jpeg_video_size == VIDEO_SIZE_1920_1080))
	{
		if(sys_ctl.crc_record==1)
			SDResSpace = (CRC_RECORD_RESERVE_SIZE*3/10) + 0x32000;
		else if(sys_ctl.crc_record==2)
			SDResSpace = (CRC_RECORD_RESERVE_SIZE*5/10) + 0x32000 ;
		else
			SDResSpace = CRC_RECORD_RESERVE_SIZE + 0x32000 ;
	}
	return SDResSpace;
}


/*******************************************************************************
* Function Name  : RecordJPGFile
* Description    : record a photograph  file name  PIC00X.JPG
* Input          : None
*
* Output         : None
* Return         : FR_OK: record photograph  success
*******************************************************************************/
u8 RecordJPGFile(void)
{
	FRESULT ret;
	u32 filenum;
	u32 u32TimeOut;
	u32 strLen;
	u8 lock_flag=0;
	u32 writed;
	ret = FR_OK;

	ret = f_scan_files((char *)work_dir_dc,".JPG",&filenum);
	//deg_Printf("pass f_scan_files, ret =%d,filenum = %d\n ",ret,filenum);
	t_photo.file_num = 0;
	strLen = my_strlen((const char*)work_dir_dc);
	my_memcpy(filename,(void *)work_dir_dc,strLen);
	my_memcpy(filename+strLen,"/PIC000.JPG",12);

	if(filenum > 0)
	{
		if(f_get_totalfile_num(3) == PIC_MAX_FILE_NUM)
		{
			lock_flag=1;
			if(f_get_lastfile_num(1,lock_flag) == ALL_FILE_LOCKED)
			{
				deg_Printf("pic file num full and all file lock\n",t_photo.file_num);
				return 21;	
			}
		}
	 	//deg_Printf("f_get_scan_min_num() = %d,f_get_scan_max_num() = %d \n",f_get_scan_min_num(filenum),f_get_scan_max_num(filenum));
		lock_flag=0;
		//t_photo.file_num = f_get_scan_last_num(filenum,lock_flag)+1;
		t_photo.file_num = f_get_lastfile_num(1,lock_flag) + 1;
		if(t_photo.file_num >= PIC_MAX_FILE_NUM)
			t_photo.file_num = 0;
		//deg_Printf("t_photo.file_num = %d \n",t_photo.file_num);

		filename[strLen+4]='0'+ ((t_photo.file_num/100)%10);
		filename[strLen+5]='0'+ ((t_photo.file_num/10)%10);
		filename[strLen+6]='0'+ (t_photo.file_num%10);
		//deg_Printf("jpeg filename = %s\n",filename);
	}

	u32TimeOut = 0;
	while(f_check_file_num(t_photo.file_num,filenum,&lock_flag))		//exist file num
	{
		u32TimeOut++;
		if(u32TimeOut >= PIC_MAX_FILE_NUM)
		{
			if(0 == lock_flag)		//del unlock file
			{
				lock_flag = 1;				//get unlock file
				t_photo.file_num = f_get_firstfile_num(1,lock_flag);
				deg_Printf("first t_photo.file_num=%x\n",t_photo.file_num);
				if(t_photo.file_num == ALL_FILE_LOCKED)
				{
					return 21;	
				}
				
				filename[strLen+4]='0'+ ((t_photo.file_num/100)%10);
				filename[strLen+5]='0'+ ((t_photo.file_num/10)%10);
				filename[strLen+6]='0'+ (t_photo.file_num%10);
				ret = f_unlink((char *)filename);	
				deg_Printf("del jpeg filename = %s,ret = 0x%x\n",filename,ret);
				if(FR_OK == ret)
				{
					f_del_file_name(filename);
					break;
				}
				else
				{
					deg_Printf("unlink err ret = 0x%x\n",ret);
				}
			}
		}
		//====next filenum===
		t_photo.file_num++;
		if(t_photo.file_num >= PIC_MAX_FILE_NUM)
			t_photo.file_num = 0;
	}

	filename[strLen+4]='0'+ ((t_photo.file_num/100)%10);
	filename[strLen+5]='0'+ ((t_photo.file_num/10)%10);
	filename[strLen+6]='0'+ (t_photo.file_num%10);

	ret =  f_open(&Fil,(char const *)filename, FA_CREATE_NEW| FA_WRITE | FA_READ);

	if(FR_OK == ret)
	{
		if((sys_ctl.jpeg_picture_size == JPEG_SIZE_2560_1440) || (sys_ctl.jpeg_picture_size == JPEG_SIZE_1920_1080))
		{
				deg_Printf("big crt jpeg %s ok\n",filename);

				DIS_OSD1();
				DIS_OSD2();
				DIS_OSD3();
				lcd_set_panel_colour(0,0,0);
				REG32(LCDCON0) &= ~(BIT(6));
				
				csi_Start(0,0);
				bPhotoScalFlag = 1;
				//while(!bcsi_FrameEndFlag);
				//bcsi_FrameEndFlag = 0;
				while(csi_buf_point != 1);
				csi_Stop();
				lcd_PostScale_Start(); 

				if(sys_ctl.picture_time_info_en)
					csi_InserTimeInfo();
				jpeg_enc_Start(2);
				jpeg_LineBuffer_Start();
				bStopVideo_Flag = 0;
				ret = WriteVideoInfo(&Fil,&indexFil);
				//ret = f_truncate(&Fil);	//modify the file size
				//deg_Printf("big jpeg truncate ret =%d\n",ret);
				if(FR_OK == ret) {
					f_close(&Fil);
					sd_WaitSdStopTran();
					if(!sys_ctl.fast_view)
					{
						lcd_PostScale_Stop();
						bPhotoScalFlag = 0;
					}
				}
				else
				{
					audio_adc_Stop(); 
					jpeg_enc_Stop();
					timer_Timer2_Stop();
					lcd_PostScale_Stop();
					bPhotoScalFlag = 0;
					deg_Printf("WriteVideoInfo Fail=%d\n",ret);
					return ret;
				}				
		}
		else
		{
				deg_Printf("small crt jpeg %s ok\n",filename);
				csi_Start(0,1);
				jpeg_enc_Start(0);
				bStopVideo_Flag = 0;
				if(FR_OK != WriteVideoInfo(&Fil,&indexFil))
				{
					audio_adc_Stop(); 
					jpeg_enc_Stop();
					timer_Timer2_Stop();
					return 21;
				}
				if(t_photo.fast_view_time>0)
					csi_Stop();
				//ret = f_truncate(&Fil);	//modify the file size
				//deg_Printf("small jpeg truncate ret =%d\n",ret);
				f_close(&Fil);
				sd_WaitSdStopTran();
		}
		//----------------------------------------------------
		u16 i=0;
		for(i=0;i<MAX_FILE_NAME_NUM;i++)
		{
			if(RecFileNum[i] == 0)
				break;
		}
		RecFileNum[i] = t_photo.file_num;
		RecFileNum[i] |= 3<<14;
		//deg_Printf("i=%d,RecFileNum[i]=%x\n",i,RecFileNum[i]);
		ret=f_open(&Fil,(char const *)FILEORDER_NAME, FA_WRITE | FA_READ);
		f_write(&Fil,RecFileNum, MAX_FILE_NAME_NUM*2,&writed);
		f_close(&Fil);
		sd_WaitSdStopTran();
		//----------------------------------------------------
	}
	else
	{
		deg_Printf("crt jpeg %s fail:%d\n",filename,ret);
	}
	return FR_OK;
}

/*******************************************************************************
* Function Name  : RecordVideoFile
* Description    : start  to record video file withe file name REC00X.AVI
* Input          : None
*
* Output         : None
* Return         : FR_OK: record video file success -other failed
*******************************************************************************/
u8 RecordVideoFile(void)
{
	FRESULT ret;
	u32 filenum;
	u8 lock_flag;
	u32 u32TimeOut;
	u32 SDRestSpace;
	u32 SDCurRestSpace;
	u32 strLen;
	u32 writed;
	//----crc record video---------------
	SDRestSpace = fat_GetReserveSpace();

	ret = f_scan_files((char *)work_dir_dv,".AVI",&filenum);
	deg_Printf("filenum = %x\n ",filenum);
	t_record_video.file_num = 0;
	strLen = my_strlen(work_dir_dv);
	my_memcpy(filename,(void *)work_dir_dv,strLen);
	my_memcpy(filename+strLen,"/REC000.AVI",12);
	if(filenum > 0)
	{
		if(f_get_totalfile_num(2) == VDO_MAX_FILE_NUM)
		{
			lock_flag=1;
			if(f_get_lastfile_num(0,lock_flag) == ALL_FILE_LOCKED)
			{
				deg_Printf("video file num full and all file lock\n",t_photo.file_num);
				return 21;	
			}
		}
		//deg_Printf("f_get_scan_last_num = %d \n", f_get_scan_last_num(filenum));
		lock_flag = 0;				//get all
		//t_record_video.file_num = f_get_scan_last_num(filenum,lock_flag)+1;
		t_record_video.file_num = f_get_lastfile_num(0,lock_flag)+1;
		if(t_record_video.file_num >= VDO_MAX_FILE_NUM)
			t_record_video.file_num = 0;
		//deg_Printf("t_record_video.file_num = %d \n",t_record_video.file_num);

		filename[strLen+4]='0'+ ((t_record_video.file_num/100)%10);
		filename[strLen+5]='0'+ ((t_record_video.file_num/10)%10);
		filename[strLen+6]='0'+ (t_record_video.file_num%10);
	}

	if(sys_ctl.crc_record)		//loop record
	{
		//deg_Printf("f_get_free_space()=0x%x,MIN_FREESECTOR = 0x%x\n ",f_get_free_space(),MIN_FREESECTOR);
		SDCurRestSpace = f_get_free_space();
		while(SDCurRestSpace < SDRestSpace)
		{
			if(filenum < 1)
			{

				if(SDCurRestSpace < MIN_FREESECTOR)		//real no space
				{
					deg_Printf("no file,no space\n ");
					return 20;							//no file ,no space
				}
				else
				{
					break;								//still record file
				}

			}
			lock_flag = 1;				//get unlock file
			//int temp = f_get_scan_first_num(filenum,lock_flag);
			u32 temp = f_get_firstfile_num(0,lock_flag);
			if(temp == ALL_FILE_LOCKED) {
				deg_Printf("all file locked\n ");
				return 21;
			}
			filename[strLen+4]='0'+ ((temp/100)%10);
			filename[strLen+5]='0'+ ((temp/10)%10);
			filename[strLen+6]='0'+ (temp%10);
			deg_Printf("filename = %s\n",filename);
			SDCurRestSpace += f_getFileClustSize(filename);
		#if 1
			ret=f_unlink_removeDir(filename,&delFS);
			f_del_file_name(filename);
			delResult = f_unlink_removeChain(&delFS, &work_fatfs,&delCLST,1);
			deg_Printf("A");
			
			if(ret == FR_OK)
				deg_Printf("delete DIR OK %s \n ",filename);
			else {
				deg_Printf("delete DIR Fail %s \n ",filename);
				return ret;
			}
		#else
			ret = f_unlink((char *)filename);						//del file, for test
			deg_Printf("delete video %s,ret = 0x%x\n ",filename,ret);
			f_del_file_name(filename);
		#endif
			f_scan_files((char* )work_dir_dv,".AVI",&filenum);
		}
	}
	else
	{
		if(f_get_free_space() < MIN_FREESECTOR)
		{
			g_SystemState = SYSTEM_CARD_OVERSPACE;
			deg_Printf("no space \n");
			return 22;
		}
	}
	u32TimeOut = 0;
	lock_flag = 0;				//get all file
	while(f_check_file_num(t_record_video.file_num,filenum,&lock_flag))		//exist file num
	{
		//====next filenum===
		t_record_video.file_num++;
		if(t_record_video.file_num >= VDO_MAX_FILE_NUM)
			t_record_video.file_num = 0;
		u32TimeOut++;
		if(u32TimeOut >= VDO_MAX_FILE_NUM)
		{
			deg_Printf(" file num full \n ");
			lock_flag = 1;				//get unlock file
			//t_record_video.file_num = f_get_scan_first_num(filenum,lock_flag);
			t_record_video.file_num = f_get_firstfile_num(0,lock_flag);
			if(t_record_video.file_num == ALL_FILE_LOCKED)
			{
				return 21;
			}
			filename[strLen+4]='0'+ ((t_record_video.file_num/100)%10);
			filename[strLen+5]='0'+ ((t_record_video.file_num/10)%10);
			filename[strLen+6]='0'+ (t_record_video.file_num%10);
		#if 1
			ret=f_unlink_removeDir(filename,&delFS);
			f_del_file_name(filename);
			delResult = f_unlink_removeChain(&delFS, &work_fatfs,&delCLST,1);
			deg_Printf("B");
			
			if(ret == FR_OK)
				deg_Printf("delete DIR OK %s \n ",filename);
			else
				return ret;
		#else
			ret = f_unlink(filename);	
			deg_Printf("delete video %s\n ",filename);
			f_del_file_name(filename);
		#endif
			f_scan_files((char* )work_dir_dv,".AVI",&filenum);
		}
	}
 
	filename[strLen+4]='0'+ ((t_record_video.file_num/100)%10);
	filename[strLen+5]='0'+ ((t_record_video.file_num/10)%10);
	filename[strLen+6]='0'+ (t_record_video.file_num%10);
		
	ret =  f_open(&Fil,(char const *)filename, FA_CREATE_NEW| FA_WRITE | FA_READ);

	if(FR_OK == ret)
	{
		deg_Printf("open file ok:%s\n",filename);
		my_memcpy(index_filename,(void *)work_dir_dv,strLen);
		my_memcpy(index_filename+strLen,"/IDX000.DAT",12);
		index_filename[strLen+4]='0'+ ((t_record_video.file_num/100)%10);
		index_filename[strLen+5]='0'+ ((t_record_video.file_num/10)%10);
		index_filename[strLen+6]='0'+ (t_record_video.file_num%10);
		ret = f_open(&indexFil,(char const *)index_filename, FA_CREATE_NEW| FA_WRITE | FA_READ);
		f_chmod((char const *)index_filename,6,0x06); 
		if(ret != FR_OK)
			return FR_INVALID_NAME;
		else
			deg_Printf("open index file ok:%s\n",index_filename);
		deg_Printf("fp2->dir_sect=%d\n",indexFil.dir_sect);
		deg_Printf("crt video %s ok\n", filename);
		g_stcJpegInfo.iJpeg10MSCnt = 0;
		g_stcJpegInfo.bTimeOverFlag = FALSE;
		Fat_WriteAviHead(&Fil);
		csi_Start(1,1);
		//deg_Printf(" pass csi_Start \n ");
		jpeg_enc_Start(0x01);
		//AGCStart(0);
		if(sys_ctl.record_voice) 
			audio_adc_init();
		Gsen_Int_Set();
		bStopVideo_Flag = 0;
		if(FR_OK != WriteVideoInfo(&Fil,&indexFil))
		{
			audio_adc_Stop(); 
			jpeg_enc_Stop();
			timer_Timer1_Stop();
			timer_Timer2_Stop();
			g_stcJpegInfo.bAudioAutoRecordFlag = 0;
			g_stcJpegInfo.bVideoAutoRecordFlag = 0;
			deg_Printf(" WriteVideoInfo err \n ");
			return 21;
		}		
		//deg_Printf("WriteVideoOK\n");
		ret = UpdateAVIInfo(&Fil,&indexFil);
		//deg_Printf("pass UpdateAVIInfo, ret =%d\n ",ret);
		f_close(&Fil);
		sd_WaitSdStopTran();

		if(task_get_lock_mode_flag())						//lock file will set file name such as "LOK000.avi"
		{
			char newname[20];
			memcpy__(newname,filename,20);
			newname[strLen+1] = 'L';
			newname[strLen+2] = 'O';
			newname[strLen+3] = 'K';
			ret = f_rename(filename, newname);
			deg_Printf("lock file  ret = 0x%x,filename =%s \n",ret,newname);
		}
		//---------------------------------------------------------------
		u16 temp;
		u16 i=0;
		temp = (filename[10]-'0')*100 + (filename[11]-'0')*10 + (filename[12]-'0');
		for(i=0;i<MAX_FILE_NAME_NUM;i++)
		{
			if(RecFileNum[i] == 0)
				break;
		}
		RecFileNum[i] = temp;
		RecFileNum[i] |= 2<<14;
		if(task_get_lock_mode_flag())
		{

			RecFileNum[i] |= 1<<12;
		}
		//deg_Printf("i=%d,RecFileNum[i]=%x\n",i,RecFileNum[i]);
		ret =f_open(&Fil,(char const *)FILEORDER_NAME, FA_WRITE | FA_READ);
		ret = f_write(&Fil,RecFileNum, MAX_FILE_NAME_NUM*2,&writed);
		ret = f_close(&Fil);
		sd_WaitSdStopTran();
		//---------------------------------------------------------------
	}
	else
	{
		deg_Printf("fopen fail ret = 0x%x,file num =0x%x\n",ret,t_record_video.file_num);
		return FR_INVALID_NAME;
	}

	return FR_OK;
}


/*******************************************************************************
* Function Name  : Fat_WriteAviHead
* Description    : write AVI header
* Input          : None
* Output         : None
* Return         : FRESULT
*******************************************************************************/
FRESULT	Fat_WriteAviHead(FIL* file)
{

	FRESULT ret;
	UINT writed;
	
	AVIFILEHEADER *aviheader = (AVIFILEHEADER *)__TEMP_BUFF_BEG;
	memset__((void *)__TEMP_BUFF_BEG,0,AVI_HEAD_SIZE);

	//fill fcc and fcc type
	aviheader->riff.fcc = 0x46464952;		//"RIFF"
	aviheader->riff.fcctype = 0x20495641;	//"AVI "
	aviheader->hdrl.fcc = 0x5453494c;		//"LIST"
	aviheader->hdrl.cb = AVI_HEAD_SIZE - 12 - 8-12;
	aviheader->hdrl.fcctype = 0x6c726468;	//"hdrl"

	//fill avimainheader
	aviheader->avih.fcc = 0x68697661;	//"avih"
	aviheader->avih.cb = sizeof(AVIMAINHEADER)-8;						//avi header size
	aviheader->avih.dwMicroSecPerFrame = 0x8235;			// 30fps ,so (1s/30)*1000*1000 = 33333us
	aviheader->avih.dwFlags = AVIF_HASINDEX;							//has index
	aviheader->avih.dwStreams = 0x2;					// jpeg and pcm 
	if((sys_ctl.jpeg_video_size == VIDEO_SIZE_1280_720) || (sys_ctl.jpeg_video_size == VIDEO_SIZE_1920_1080))
	{
		aviheader->avih.dwWidth = 1280;
		aviheader->avih.dwHeight = 720;
	}
	else
 	{
		aviheader->avih.dwWidth = 640;
		aviheader->avih.dwHeight = 480;
	}

	//file move fcc and fcc type
	aviheader->strl_v.fcc = 0x5453494c;			//"LIST"
	aviheader->strl_v.cb = sizeof(aviheader->strl_v.fcctype) + sizeof(AVISTREAMHEADER)+sizeof(CHUNK)+sizeof(BITMAPINFOHEADER);
	aviheader->strl_v.fcctype = 0x6c727473;		//"strl"
	aviheader->strh_v.fcc = 0x68727473;						//"strh"
	aviheader->strh_v.cb = sizeof(AVISTREAMHEADER)-8;		
	aviheader->strh_v.fccType = 0x73646976;					//"vids"
	aviheader->strh_v.fccHandler = 0x47504a4d;				//"MJPG"
	aviheader->strh_v.dwScale = 1;
	aviheader->strh_v.dwRate = 30;							
	aviheader->strh_v.dwStart = 0;
	if((sys_ctl.jpeg_video_size == VIDEO_SIZE_1280_720) || (sys_ctl.jpeg_video_size == VIDEO_SIZE_1920_1080))
	{
		aviheader->strh_v.rcFrame.right = 1280;
		aviheader->strh_v.rcFrame.bottom = 720;
	}
	else
	{
		aviheader->strh_v.rcFrame.right = 640;
		aviheader->strh_v.rcFrame.bottom = 480;
	}

	//fill vids stream info
	aviheader->strf_v.dwFourCC = 0x66727473;							//"strf"
	aviheader->strf_v.dwSize = sizeof(BITMAPINFOHEADER);				
	aviheader->bitmapinfo.biSize = sizeof(BITMAPINFOHEADER);			
	if((sys_ctl.jpeg_video_size == VIDEO_SIZE_1280_720) || (sys_ctl.jpeg_video_size == VIDEO_SIZE_1920_1080))
	{
		aviheader->bitmapinfo.biWidth = 1280;
		aviheader->bitmapinfo.biHeight = 720;
	}
	else
	{
		aviheader->bitmapinfo.biWidth = 640;
		aviheader->bitmapinfo.biHeight = 480;
	}
	aviheader->bitmapinfo.biPlanes = 1;							// always 1
	aviheader->bitmapinfo.biBitCount = 24;							// 1, 4, 8, 16, 24, 32
	aviheader->bitmapinfo.biCompression = 0x47504a4d;				//"MJPG"

	//fill strl auds
	aviheader->strl_a.fcc = 0x5453494c;			//"LIST"
	aviheader->strl_a.cb = sizeof(aviheader->strl_a.fcctype)+sizeof(AVISTREAMHEADER)+sizeof(CHUNK)+sizeof(WAVEFORMATEX);
	aviheader->strl_a.fcctype = 0x6c727473;		//"strl"

	//fill auds stream
	aviheader->strh_a.fcc = 0x68727473;						//"strh"
	aviheader->strh_a.cb = sizeof(AVISTREAMHEADER)-8;		
	aviheader->strh_a.fccType = 0x73647561;					//"auds" 
	aviheader->strh_a.dwScale = 4;
	aviheader->strh_a.dwRate = 64000;
	aviheader->strh_a.dwLength = 2048;
	aviheader->strh_a.dwSampleSize = 4;

	//fill auds stream info
	aviheader->strf_a.dwFourCC = 0x66727473;							//"strf"
	aviheader->strf_a.dwSize = sizeof(WAVEFORMATEX);
//	deg_Printf("sizeof(WAVEFORMATEX) = 0x%x \n",sizeof(WAVEFORMATEX));
	aviheader->wavinfo.wFormatTag = 1;			//1:pcm    2:adpcm
	aviheader->wavinfo.nChannels = 2;
	aviheader->wavinfo.nSamplesPerSec = 16000;	//11025 , 22050, 44100
	aviheader->wavinfo.nAvgBytesPerSec = 64000;
	aviheader->wavinfo.nBlockAlign = 4;			// ch*bitspersample /8
	aviheader->wavinfo.wBitsPerSample = 16;
	
	//fill junk
	aviheader->junk.dwFourCC= 0x4b4e554a;			//"JUNK"
	aviheader->junk.dwSize= AVI_HEAD_SIZE - (sizeof(AVIFILEHEADER) + 12);

	ret = f_write(file,(void*)aviheader, AVI_HEAD_SIZE,&writed);			// 4K AVI head
	if(ret != FR_OK) {
		deg_Printf("AVIHead write failed:%d\n",ret);
	}
//	deg_Printf("WriteAviHead:ret = 0x%x,writed = 0x%x\n",ret,writed);


	return FR_OK;

}

/*******************************************************************************
* Function Name  : CheckVideoStopCondition
* Description    : process stop video event when in record video
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CheckVideoStopCondition(void)
{

	if(delResult != FR_OK) {
		delResult = f_unlink_removeChain(&delFS, &work_fatfs,&delCLST,0);
		//deg_Printf("u");
		if(delResult == FR_OK) {
			deg_Printf("delete OK!!\n");
		}
		else if(delResult != FR_TIMEOUT) {
			deg_Printf("delete fail:%d\n",delResult);
		}
	}
	
	 u8 msg = get_msg();
	if(task_ctl.work_sta == TASK_RECORD_VIDEO)
	{
		if( (T_KEY_PLAY | T_KEY_SHORT_UP) == msg ||
			(T_KEY_AIRBORNE_VIDEO | T_KEY_SHORT_UP) == msg ||
			(T_KEY_AIRBORNE_VIDEO | T_KEY_LONG_UP) == msg)
		{
			deg_Printf("StopVideo\n");
		   task_record_set_push_key_stop_flag(1);
		}
		else if(/*(T_KEY_AIRBORNE_CTRL | T_KEY_SHORT_UP) == msg ||*/	
			(T_KEY_AIRBORNE_CTRL | T_KEY_LONG_UP) == msg||(T_KEY_AIRBORNE_CTRL | T_KEY_SHORT_UP) == msg)
		{
			//here sirborne short up is lvd single stop dv , hold_up is stop DV single
		   	task_record_set_push_key_stop_flag(1);
		}
		else if((T_KEY_UP | T_KEY_SHORT_UP) == msg)
		{
			video_enlager++;
			if(video_enlager>MAX_ENLAGER_FACTOR)
			{
				video_enlager = MAX_ENLAGER_FACTOR;
			}
			tvout_Change_dis_size(video_enlager,0);
		}
		else if((T_KEY_DOWN | T_KEY_SHORT_UP) == msg)
		{
			if(video_enlager>0)
			{
				video_enlager--;
			}
			tvout_Change_dis_size(video_enlager,0);
		}

#if (G_SEN_NULL != G_SEN_USE)
		//Gsen_Scan(50);
		Gsen_Check_Int(100);
#endif

	}
#if (OSDICON_DISPLAY_USE == OSDICON_DISPLAY_ENABLE)
	if(OSD_changeFlag) 
	{
		ZoomNumDisplay();
	}
	if(task_ctl.work_sta == TASK_RECORD_VIDEO)
	{
		if(msg == SYSTEM_1S)
		{
			if(bRecording_Display_Flag == 0)
			{
				lcd_UpdateOsdIconData_FromSdram(&OSD1Inf, OSD_RECORDING, TASK_OSD_XS+TASK_ICON_WIDTH+ICON_INTERVAL_SPACE, TASK_OSD_YS);
				bRecording_Display_Flag = 1;
			}
			else
			{
				lcd_FillPartOsdData(&OSD1Inf, ALPHA_0X00_COLOR, TASK_OSD_XS+TASK_ICON_WIDTH+ICON_INTERVAL_SPACE, TASK_OSD_YS, TASK_ICON_WIDTH, TASK_ICON_HEIGHT);
				bRecording_Display_Flag = 0;
			}
		}
	}
#endif
    if( task_record_get_push_key_stop_flag()|| (g_stcJpegInfo.bVideoAutoRecordFlag) || bMD_StopVideo_Flag|| (TASK_POWER_OFF == task_ctl.work_sta)||(f_get_free_space() < MIN_FREESECTOR)||(TRUE == g_stcJpegInfo.bLowPowerFlag))
    {
    	if((f_get_free_space() < MIN_FREESECTOR) && (sys_ctl.crc_record) && (RECORD_VIDEO == g_stcJpegInfo.RecordType)) {	//in the loop record, if no space, stop current video, then start a new video
			g_stcJpegInfo.bVideoAutoRecordFlag = TRUE;
			deg_Printf("no sp\n");
		}	
		if(!bStopVideo_Flag)
		{
			bMD_StopVideo_Flag = 0;
			timer_Timer1_Stop();
			bStopVideo_Flag = 1;
		}
    }
#if (OSDICON_DISPLAY_USE == OSDICON_DISPLAY_ENABLE)
	if(task_ctl.on_recording == 1)
	{
		if(sys_ctl.video_time_info_en)
		{
			task_record_dis_system_time();
		}
		cal_record_time();
		task_record_dis_record_time();
		if(OSD_changeFlag) 
		{
			OSD_changeFlag = 0;
			BatVolDisplay();
			LockModeDisplay();
			MotionDetectDisplay();
		}
	}
#endif


}

FRESULT PlayVideoFile(FIL * file)
{

	csi_Stop();
	f_fastseek_init(file);
	avi_Player(file);
	return FR_OK;
}
	
FRESULT PlayPictureFile(FIL * file)
{
	csi_Stop();
	play_Picture(file);
	return FR_OK;
}



//============fs=============

FRESULT f_scan_files (
	char* path,		/* Pointer to the working buffer with start path */
	char* postfix,	/*such as .avi .jpg .mp3 .mp4 .......*/
	u32 *filenum		/* postfix file num  */
)
{
	DIR dirs;
	FRESULT res;
	int i;
	char *fn;
	AccFiles = 0;

	res = f_opendir(&dirs, path);
	if (res == FR_OK) 
	{
		i = strlen(path);
		while (((res = f_readdir(&dirs, &Finfo)) == FR_OK) && Finfo.fname[0]) 
		{
			if (_FS_RPATH && Finfo.fname[0] == '.') continue;
#if _USE_LFN
			fn = *Finfo.lfname ? Finfo.lfname : Finfo.fname;
#else
			fn = Finfo.fname;
#endif
			if (Finfo.fattrib & AM_DIR) 
			{
	
				path[i] = '/'; strcpy(path+i+1, fn);
				res = f_scan_files(path,postfix,filenum);
				path[i] = '\0';
				if (res != FR_OK) break;
			} 
			else 
			{
				//deg_Printf("%s/%s\n",path, fn);
				//deg_Printf("%x\n",Finfo.ftime);
				if(AccFiles < MAX_FILE_NAME_NUM)
				_strcpy(fnlist[AccFiles].fname, fn);
				fnlist[AccFiles].ftime = Finfo.fdate<<16 | Finfo.ftime;
				//deg_Printf("%x\n",fnlist[AccFiles].ftime);
				char *fnptr = fn+strlen(fn)-4;		//point to the postfix
				char *posptr = postfix;	
				if(bmemcmp(fnptr,postfix,4))
				{
					AccFiles++;
				}
				else
				{
					posptr +=4;
					while(bmemcmp("|",posptr,1) )
					{
						posptr +=1;
						if(bmemcmp(fnptr,posptr,4))
							AccFiles++;
						else
							posptr+=4;	
					}
				}
			}
		}
		 f_closedir(&dirs);
	}
	*filenum = AccFiles;
	return res;
}


//======must call f_scan_files before call this fun =====
char * f_get_scan_file_name(u32 sortindex, u32 sorttotal)
{
	u32 i;
	for(i=0;i<sorttotal;i++)
	{
		if(sortindex == fnlist[i].fsortnum)
			break;
	}
	return fnlist[i].fname;
}

u32 f_get_filetime(int index)
{
 	return fnlist[index].ftime;
}

u32 f_get_filenum(u32 filenum)
{
 	return ((fnlist[filenum].fname[3]-'0')*100 + (fnlist[filenum].fname[4]-'0')*10 + (fnlist[filenum].fname[5]-'0'));
}

//======must call f_scan_files before call this fun =====
u32 f_get_scan_min_num(u32 filenum)
{
	u32 i,j;
	
	for(i = 0,j = 0;i < filenum;i++)
	{
		//if(stricmp(fnlist[j],fnlist[i]) < 0)
		if(datacmp(f_get_filenum(j),f_get_filenum(i)) < 0)
		{
			
		}
		else
		{
			j = i;
		}
	}
//	deg_Printf("j = %d,fnlist[j] = %s \n",j,fnlist[j]);
	return (fnlist[j].fname[3]-'0')*100+(fnlist[j].fname[4]-'0')*10+(fnlist[j].fname[5]-'0');
}

//======must call f_scan_files before call this fun =====
u32 f_get_scan_max_num(u32 filenum)
{
	u32 i,j;
	for(i = 0,j = 0;i < filenum;i++)
	{
		//if(stricmp(fnlist[j],fnlist[i]) > 0)
		if(datacmp(f_get_filenum(j),f_get_filenum(i)) > 0)
		{
			
		}
		else
		{
			j = i;
		}
	}
//	deg_Printf("j = %d,fnlist[j] = %s \n",j,fnlist[j]);
	return (fnlist[j].fname[3]-'0')*100+(fnlist[j].fname[4]-'0')*10+(fnlist[j].fname[5]-'0');
}


	
//======must call f_scan_files before call this fun =====
//lockflag is 0 will scan all file, lockflag is 1 wiil not scan lockfile
u32 f_get_scan_first_num(u32 filenum,u8 lockflag)
{
	u32 i,j;

	if(0 == lockflag)			//scan all
	{
		for(i = 0,j = 0;i < filenum;i++)
		{
			//if(stricmp(fnlist[j],fnlist[i]) < 0)
			if(datacmp(f_get_filetime(j),f_get_filetime(i)) < 0)
			{
				
			}
			else
			{
				j = i;
			}
		}
	}
	else						// no scan lockfile
	{
		//get one unlock file index
		for(j = 0;j < filenum ;j++)
		{
			if('L' != fnlist[j].fname[0])
			{
				break;
			}
		}
		if(j == filenum)		//all file lock
		{
			return ALL_FILE_LOCKED;
		}
		//find first filetime from unlock file 
		for(i = 0;i < filenum;i++)
		{
			//if(stricmp(fnlist[j],fnlist[i]) < 0)
			if(datacmp(f_get_filetime(j),f_get_filetime(i)) < 0)
			{
				
			}
			else
			{
				if('L' != fnlist[i].fname[0])
				{
					j = i;
				}
			}
		}
	}


//	deg_Printf("j = %d,fnlist[j] = %s \n",j,fnlist[j]);
	return (fnlist[j].fname[3]-'0')*100+(fnlist[j].fname[4]-'0')*10+(fnlist[j].fname[5]-'0');
}

//======must call f_scan_files before call this fun =====
//lockflag is 0 will scan all file, lockflag is 1 wiil not scan lockfile
u32 f_get_scan_last_num(u32 filenum,u8 lockflag)
{
	u32 i,j;

	if(0 == lockflag)			//scan all
	{
		for(i = 0,j = 0;i < filenum;i++)
		{
			//if(stricmp(fnlist[j],fnlist[i]) < 0)
			if(datacmp(f_get_filetime(j),f_get_filetime(i)) > 0)
			{
				
			}
			else
			{
				j = i;
			}
		}
	}
	else						//not scan lockfile
	{
		//get one unlock file index
		for(j = 0;j < filenum ;j++)
		{
			if('L' != fnlist[j].fname[0])
			{
				break;
			}
		}
		if(j == filenum)		//all file lock
		{
			return ALL_FILE_LOCKED;
		}
		//find first filetime from unlock file 
		for(i = 0;i < filenum;i++)
		{
			//if(stricmp(fnlist[j],fnlist[i]) < 0)
			if(datacmp(f_get_filetime(j),f_get_filetime(i)) > 0)
			{
				
			}
			else
			{
				if('L' != fnlist[i].fname[0])
				{
					j = i;
				}
			}
		}
	}

	
//	deg_Printf("j = %d,fnlist[j] = %s \n",j,fnlist[j]);
	return (fnlist[j].fname[3]-'0')*100+(fnlist[j].fname[4]-'0')*10+(fnlist[j].fname[5]-'0');
}

void f_exchangesort_file(u32 filenumbers)
{
	u32 sortbuf[CRC_MAX_RECORD_FILE_NUM];
	u32 i,j;
	u32 temp;

	for(i=0;i<filenumbers;i++)
	{
		sortbuf[i]= fnlist[i].ftime;
	}
	for(i=0;i<(filenumbers-1);i++)	
	{
		for(j=i+1;j<filenumbers;j++)
		{
			if(sortbuf[j] > sortbuf[i])
			{
				temp = sortbuf[i];
				sortbuf[i] = sortbuf[j];
				sortbuf[j] = temp;
			}
		}
	}
	for(i=0;i<filenumbers;i++)
	{
		for(j=0;j<filenumbers;j++)
		{
			if(fnlist[i].ftime == sortbuf[j])
				fnlist[i].fsortnum = j;
		}
	}
	for(i=0;i<filenumbers;i++)
	{
		for(j=i+1;j<filenumbers;j++)
		{
			if(fnlist[i].fsortnum == fnlist[j].fsortnum)
				fnlist[j].fsortnum -= 1;
		}
	}
}

//return  : 0 filenum not exist , 1 filenum exist
//if exist , get the file lock flag to lock_flag, lock_flag : 0 is not lock, 1 is lock
u8 f_check_file_num(u32 filenum,u32 maxnum,u8 *lock_flag)
{
	u32 i;
	for(i = 0;i < maxnum;i++)
	{
		if(filenum == ((fnlist[i].fname[3]-'0')*100+(fnlist[i].fname[4]-'0')*10+(fnlist[i].fname[5]-'0')))
		{
			if('L' != fnlist[i].fname[0])
			{
				*lock_flag = 0;
			}
			else
			{
				*lock_flag = 1;
			}
			return 1;
		}
	}

	*lock_flag = 0;
	return 0;
}

//======must call f_mount to FatFs before call this fun =====
u32 f_get_free_space()
{
	FATFS *pfatfs = &work_fatfs;
	u32 free_clst;
	f_getfree(ROOT_DIR_NAME, &free_clst, &pfatfs);
	return free_clst*work_fatfs.csize;
}
u32 f_getFileClustSize(char* path)
{
	u32 size = 0;
	if(f_stat(path, &Finfo) == FR_OK) {
		size = Finfo.fsize/512;
	}
	return size;
}

FRESULT SyncAVIInfo(FIL* file, FIL* indexFile)
{
	u32 writed;
	u32 sector;
	u32 *ptemp;
 	FRESULT ret;
	AVIFILEHEADER *aviheader = (AVIFILEHEADER *) __TEMP_BUFF_BEG;
	memset__(aviheader,0,AVI_HEAD_SIZE);

//	deg_Printf("g_stcJpegInfo.dwChunkLen =0x%x,g_stcJpegInfo.dwIndexLen = 0x%x \n",g_stcJpegInfo.dwChunkLen,g_stcJpegInfo.dwIndexLen);
//	deg_Printf("g_stcJpegInfo.iValidFrameCnt =0x%x,sizeof(AVIFILEHEADER) =0x%x\n",g_stcJpegInfo.iValidFrameCnt,sizeof(AVIFILEHEADER));
	ptemp = (u32*)( __TEMP_BUFF_BEG);
	sector = clust2sect(indexFile->fs,indexFile->sclust);
	if(0 == bsd_read(ptemp,sector,1)) {
		ptemp[3] = indexFile->fsize-16;//g_stcJpegInfo.dwIndexLen-16;			//not include first 16 bytes
		if(0!=bsd_write(ptemp,sector,1)) {
			deg_Printf("modify index header error\n");
		}
	}
 
//=========fill avifileheader info=========
	sector = clust2sect(file->fs,file->sclust);
	if(0 == bsd_read(aviheader,sector,AVI_HEAD_SIZE/512)) {
		aviheader->riff.cb = file->fsize_prev+indexFile->fsize - 8; 	
		aviheader->avih.dwTotalFrames = g_stcJpegInfo.iValidFrameCnt;
		aviheader->strh_v.dwLength = g_stcJpegInfo.iValidFrameCnt;
		ptemp = (u32*)(__TEMP_BUFF_BEG+AVI_HEAD_SIZE-12);			//data block head
		ptemp[0] = 0x5453494c;										//"LIST"
		ptemp[1] = file->fsize_prev-AVI_HEAD_SIZE+4+8;		// datalen+ "move" + index first 8bytes nouse
		ptemp[2] = 0x69766f6d;										//"movi"
		if(0!=bsd_write(aviheader,sector,AVI_HEAD_SIZE/512)) {
			deg_Printf("modify avi header error\n");
		}
	}
	//deg_Printf("size=%x,%x\n",file->fsize_prev,indexFile->fsize);
	return	FR_OK;
}

FRESULT UpdateAVIInfo(FIL* file, FIL* indexFile)
{
	u32 writed;
	u32 sector;
	u32 *ptemp;
 	FRESULT ret;
	AVIFILEHEADER *aviheader = (AVIFILEHEADER *) __TEMP_BUFF_BEG;
	memset__(aviheader,0,AVI_HEAD_SIZE);

//	deg_Printf("g_stcJpegInfo.dwChunkLen =0x%x,g_stcJpegInfo.dwIndexLen = 0x%x \n",g_stcJpegInfo.dwChunkLen,g_stcJpegInfo.dwIndexLen);
//	deg_Printf("g_stcJpegInfo.iValidFrameCnt =0x%x,sizeof(AVIFILEHEADER) =0x%x\n",g_stcJpegInfo.iValidFrameCnt,sizeof(AVIFILEHEADER));
	ptemp = (u32*)( __TEMP_BUFF_BEG);
	sector = clust2sect(indexFile->fs,indexFile->sclust);
	if(0 == bsd_read(ptemp,sector,1)) {
		ptemp[3] = g_stcJpegInfo.dwIndexLen-16;			//not include first 16 bytes
		if(0!=bsd_write(ptemp,sector,1)) {
			deg_Printf("modify index header error\n");
		}
	}
#if 1
	//merge file and indexFile into file
	f_merge(file,indexFile);
#endif
 
//=========fill avifileheader info=========
	ret = f_lseek(file, 0);
	ret = f_read(file,(void *)aviheader,AVI_HEAD_SIZE,(uint*)(&writed));
//	deg_Printf("f_read:ret =%d,read = 0x%x\n",ret,writed);

	deg_Printf("IndexLen=%x,ChunkLne=%x\n",g_stcJpegInfo.dwIndexLen,g_stcJpegInfo.dwChunkLen);
	//aviheader->riff.cb = g_stcJpegInfo.dwIndexLen + g_stcJpegInfo.dwChunkLen - 8; 	
	aviheader->riff.cb = file->fsize-8;//g_stcJpegInfo.dwIndexLen + g_stcJpegInfo.dwChunkLen - 8; 	
	aviheader->avih.dwTotalFrames = g_stcJpegInfo.iValidFrameCnt;
	aviheader->strh_v.dwLength = g_stcJpegInfo.iValidFrameCnt;
	ptemp = (u32*)(__TEMP_BUFF_BEG+AVI_HEAD_SIZE-12);			//data block head
	ptemp[0] = 0x5453494c;										//"LIST"
	//ptemp[1] = g_stcJpegInfo.dwChunkLen-AVI_HEAD_SIZE+4+8;		// datalen+ "move" + index first 8bytes nouse
	ptemp[1] = file->fsize - g_stcJpegInfo.dwIndexLen -AVI_HEAD_SIZE+4+8; //g_stcJpegInfo.dwChunkLen-AVI_HEAD_SIZE+4+8;		// datalen+ "move" + index first 8bytes nouse
	ptemp[2] = 0x69766f6d;										//"movi"

//=========write avifileheader info=======
	ret = f_lseek(file, 0);
	ret = f_write(file,(void *)aviheader,AVI_HEAD_SIZE,(uint*)(&writed));
	if(ret != FR_OK) {
		deg_Printf("AVIInfo write failed:%d\n",ret);
	}
//	deg_Printf("f_write:ret =%d,writed = 0x%x\n",ret,writed);

	return	FR_OK;
}

#if _USE_FASTSEEK
#define  SZ_TBL 0x400
DWORD clmt[SZ_TBL];
#endif
FRESULT f_fastseek_init(FIL *fp)
{
	FRESULT ret=FR_OK;
#if _USE_FASTSEEK
	fp->cltbl = clmt;
	clmt[0] = SZ_TBL;
	ret = f_lseek(fp, CREATE_LINKMAP); 
#endif
	return ret;
} 

void f_check_rec_video_file_size()
{
#if	(USER_CONFIG==CONFIG_AX3251_AIRBORNE)
	if(task_ctl.on_recording == 1)					//recoding video 
	{
		if(Fil.fsize > 0xf8000000)
		{
//			deg_Printf("Fil.fsize=0x%x", Fil.fsize);
			task_record_set_push_key_stop_flag(1);		//stop video rec
			deg_Printf("file size max\n");
		}
	}
#endif
}

/* Îª½â¾ö¡°É¾³ýÒ»¸öÎÄ¼þ£¬Èç¹û½Ó×ÅµÄÏÂÒ»¸öÎÄ¼þÎªvideoÎÄ¼þÊ±ºò£¬menu½çÃæ·µ»Ø²»ÁË¡±´æÔÚµÄbug.
 * note: Èç¹ûÓÃ»§ÐèÇóÎª'É¾³ýÒ»¸öÎÄ¼þºómenu½çÃæ¼´¹Ø±Õ£¬¶ø²»ÊÇmenuÒÀÈ»´æÔÚÒÔ¿ÉÒÔ½Ó×ÅÉ¾³ýÏÂÒ»¸öÎÄ¼þ'£¬
 * Ôò´Ë±äÁ¿¿ÉÒÔÈ¥µô£¬²¢ÇÒavi_Player()º¯ÊýÀïÃæ¹ØÓÚbDeleteFile±äÁ¿µÄ´úÂë²¿·Ö¿ÉÈ¥µô.
 */
bool bDeleteFile = false;



void delete_file(u8 del_type)
{
#if (WORK_DIR_CNT==1)
	FRESULT ret;
	u32 filenum;
	if(DELETE_CURRENT == del_type)	
	{
		if(t_play.file_lock_flag)
		{
			//show file is lock tips
//			lcd_FillFullOsdData(menu_mgroup.p_menu_inf,ALPHA_0X00_COLOR);
			DisplayUnicodeStr(&OSD1Inf,(u8 *)(group_file_lock[sys_ctl.language]),0+20,MENU_HEIGHT/2,MENU_ITEM1_W,FONT_HEIGHT,OSD_TIME_COLOR, ALPHA_0X00_COLOR,2);
			Delay_MS(2000);
//			SetOSDDisplayFlag(MENU_HEARD_DISPLAY_FLAG);
//			MenuPageOSDHeaderUpdate();
		}
		else
		{
			//show del file tips
//			lcd_FillFullOsdData(menu_mgroup.p_menu_inf,ALPHA_0X00_COLOR);
			DisplayUnicodeStr(&OSD1Inf,(u8 *)(group_file_delete[sys_ctl.language]),0+20,MENU_HEIGHT/2,MENU_ITEM1_W,FONT_HEIGHT,OSD_TIME_COLOR, ALPHA_0X00_COLOR,2);
			ret = f_unlink(filename);
			deg_Printf("del cur file %s,ret = 0x%x\n",filename,ret);
			f_del_file_name(filename);
			task_paly_get_file_num(PLAY_NEXT_FILE);
		}
	}
	else					//del all file
	{
		u32 i;
		//show del file tips
//		lcd_FillFullOsdData(menu_mgroup.p_menu_inf,ALPHA_0X00_COLOR);
		DisplayUnicodeStr(&OSD1Inf,(u8 *)(group_file_delete[sys_ctl.language]),0+20,MENU_HEIGHT/2,MENU_ITEM1_W,FONT_HEIGHT,OSD_TIME_COLOR, ALPHA_0X00_COLOR,2);
		ret = f_scan_files(WORK_DIR_NAME,".JPG|.AVI",&filenum);
		f_exchangesort_file(filenum);
		for(i = 0;i < filenum;i++)
		{
			char *ptr = f_get_scan_file_name(i,filenum);
			if('L' != ptr[0])								//lock file will not del
			{
				memcpy__(filename+7, ptr, 13);
				ret = f_unlink(filename);
				deg_Printf("del cur file %s,ret = 0x%x\n",filename,ret);
				f_del_file_name(filename);
				task_paly_get_file_num(PLAY_NEXT_FILE);
			}
		}
	}

	//clear tips
	lcd_FillPartOsdData(&OSD1Inf, ALPHA_0X00_COLOR, 0+20, MENU_HEIGHT/2, MENU_ITEM1_W, FONT_HEIGHT*2);	
//	deg_Printf("pass clear tips\n");
	ret = f_scan_files(WORK_DIR_NAME,".JPG|.AVI",&filenum);


	if(filenum < 1) 
	{
		cur_menu.menu_type = MENU_IDLE;
		mode_change();
	} 
	else 
	{		
		t_play.pause_flag = 0;
		task_ctl.on_playing = 0;

		//====pre file====
		if(play_file_num > filenum-1)
		{
			play_file_num = filenum-1;
		}

		f_exchangesort_file(filenum);
		char *ptr = f_get_scan_file_name(play_file_num,filenum);
		memcpy__(filename+7, ptr, 13);
		if('L' == filename[7])
		{
			t_play.file_lock_flag = 1;
		}
		else
		{
			t_play.file_lock_flag = 0;
		}
	}

	deg_Printf("delete file finish\n");
#endif
}


void lock_unlock_file(u8 type)
{	
#if (WORK_DIR_CNT==1)
	FRESULT ret;
	u32 filenum;
	char oldname[20];
	if((type & CURRENT_ALL_MASK) == CURRENT_FILE)		//handle cur file 
	{
		if((type & LOCK_UNLOCK_MASK) == LOCK)			//lock file 
		{
			if('L' != filename[7])
			{
				memcpy__(oldname,filename,20);
				filename[7] = 'L';
				filename[8] = 'O';
				filename[9] = 'K';
				ret = f_rename(oldname,filename);
				deg_Printf("rename file %s,newname = %s,ret = 0x%x\n",oldname,filename,ret);
				f_lock_unlock_FileName(filename,1);
			}
		}
		else if((type & LOCK_UNLOCK_MASK) == UNLOCK)		//unlock file 
		{
			if('L' == filename[7])
			{
				memcpy__(oldname,filename,20);
				if((filename[14] =='J')&&(filename[15] =='P')&&(filename[16] =='G'))
				{
					filename[7] = 'P';
					filename[8] = 'I';
					filename[9] = 'C';
				}
				else
				{
					filename[7] = 'R';
					filename[8] = 'E';
					filename[9] = 'C';
				}
				ret = f_rename(oldname,filename);
				deg_Printf("rename file %s,newname = %s,ret = 0x%x\n",oldname,filename,ret);
				f_lock_unlock_FileName(filename,0);
			}
		}
	}
	else if((type & CURRENT_ALL_MASK) ==  ALL_FILE)		//handle all file
	{
		if((type & LOCK_UNLOCK_MASK) == LOCK)			//lock file 
		{
			u32 i;
			ret = f_scan_files(WORK_DIR_NAME,".JPG|.AVI",&filenum);
			f_exchangesort_file(filenum);
			for(i = 0;i < filenum;i++)
			{
				char *ptr = f_get_scan_file_name(i,filenum);
				if('L' != ptr[0])								//handle unlock
				{
					memcpy__(filename+7, ptr, 13);
					memcpy__(oldname,filename,20);
					filename[7] = 'L';
					filename[8] = 'O';
					filename[9] = 'K';
					ret = f_rename(oldname,filename);
					deg_Printf("rename file %s,newname = %s,ret = 0x%x\n",oldname,filename,ret);
					f_lock_unlock_FileName(filename,1);
				}
			}
		}
		else if((type & LOCK_UNLOCK_MASK) == UNLOCK)		//unlock file 
		{
			u32 i;
			ret = f_scan_files(WORK_DIR_NAME,".JPG|.AVI",&filenum);
			f_exchangesort_file(filenum);
			for(i = 0;i < filenum;i++)
			{
				char *ptr = f_get_scan_file_name(i,filenum);
				if('L' == ptr[0])								//handle lock
				{
					memcpy__(filename+7, ptr, 13);
					memcpy__(oldname,filename,20);
					if((filename[14] =='J')&&(filename[15] =='P')&&(filename[16] =='G'))
					{
						filename[7] = 'P';
						filename[8] = 'I';
						filename[9] = 'C';
					}
					else
					{
						filename[7] = 'R';
						filename[8] = 'E';
						filename[9] = 'C';
					}
					ret = f_rename(oldname,filename);
					deg_Printf("rename file %s,newname = %s,ret = 0x%x\n",oldname,filename,ret);
					f_lock_unlock_FileName(filename,0);
				}
			}
		}
	}

	if('L' == filename[7])
	{
		t_play.file_lock_flag = 1;
	}
	else
	{
		t_play.file_lock_flag = 0;
	}
	t_play.pause_flag = 0;
	task_ctl.on_playing = 0;
	deg_Printf("lock_unlock_file finish\n");
#endif
}

