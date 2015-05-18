/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : fat_api.h
* Author             : pengtao_zhang
* Version            : V0810a
* Date               : 08/10/2013
* Description        : fat api HEADER FILE.
***************************************************************************/
#ifndef _FAT_API_H_
#define _FAT_API_H_

#define VDO_MAX_FILE_NUM				1000
#define PIC_MAX_FILE_NUM				1000
#define ALL_FILE_LOCKED					0x10000000

#define CRC_MAX_RECORD_FILE_NUM		(VDO_MAX_FILE_NUM+PIC_MAX_FILE_NUM)
#define CRC_RECORD_RESERVE_SIZE	    0x400000 //unit:sector,4*1024*1024*1024/512  2GB,720P,10min

#define MAX_FILE_NAME_NUM			(VDO_MAX_FILE_NUM+PIC_MAX_FILE_NUM)		//just for short file name for test

extern FATFS work_fatfs;		/* FatFs work area needed for each volume */
extern u32 u32DataOffset; // after fill data,need to update index segment.
extern BOOL bPhotoScalFlag;
extern char filename[];
extern FIL Fil;
extern BOOL bRecording_Display_Flag;

extern FATFS delFS; 
extern DWORD delCLST;
extern u32 delResult;

typedef struct{
 char fname[13];
 u32 ftime;
 u32 fsortnum;
}FILATTR;

extern FILATTR fnlist[MAX_FILE_NAME_NUM];

BOOL InitRecordFolder(void);
u32 f_getFileClustSize(char* path);
u32 fat_GetReserveSpace(void);
u8 RecordJPGFile(void);
u8 RecordVideoFile(void);
u32 fillCurrentCluster(u32 ind);
FRESULT Write4KJpegData(FIL* file,u32 uDataType);
FRESULT WriteVideoInfo(FIL* file, FIL* indexFile);
FRESULT	Fat_WriteAviHead(FIL* file);
void CheckVideoStopCondition(void);
void f_exchangesort_file(u32 filenumbers);

FRESULT PlayVideoFile(FIL * file);
FRESULT PlayPictureFile(FIL * file);

//////////////////////////////////////////////////////////////////////////////
/* for delete file */
#define DELETE_CURRENT	0
#define DELETE_ALL		1

void delete_file(u8 delete);
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
/* for lock/unlock file */
#define CURRENT_FILE			(0<<0)
#define ALL_FILE				(1<<0)
#define CURRENT_ALL_MASK		(1<<0)

#define LOCK					(0<<1)
#define UNLOCK					(1<<1)
#define LOCK_UNLOCK_MASK		(1<<1)

#define LCASE_BASE      0x08            // filename base in lower case  
#define LCASE_EXT       0x10            // filename extension in lower case 
#define FILE_LOCK		0x80			// file lock, can't be deleted

void lock_unlock_file(u8 type);
//////////////////////////////////////////////////////////////////////////////



//=================fs=============

FRESULT f_scan_files (
	char* path,		/* Pointer to the working buffer with start path */
	char* postfix,	/*such as .avi .jpg .mp3 .mp4 .......*/
	u32 *filenum		/* postfix file num  */
);

char * f_get_scan_file_name(u32 sortindex, u32 sorttotal);
u32 f_get_filenum(u32 filenum);
u32 f_get_scan_min_num(u32 filenum);
u32 f_get_scan_max_num(u32 filenum);
u32 f_get_scan_first_num(u32 filenum,u8 lockflag);
u32 f_get_scan_last_num(u32 filenum,u8 lockflag);
u8 f_check_file_num(u32 filenum,u32 maxnum,u8 *lock_flag);

u32 f_get_free_space();
FRESULT SyncAVIInfo(FIL* file, FIL* indexFile);
FRESULT UpdateAVIInfo(FIL* file, FIL* indexFile);
FRESULT f_fastseek_init(FIL *fp);
void f_check_rec_video_file_size();

#endif
