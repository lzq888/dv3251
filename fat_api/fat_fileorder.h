/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : fat_api.h
* Author             : pengtao_zhang
* Version            : V1204a
* Date               : 12/04/2014
* Description        : fat ext HEADER FILE.
***************************************************************************/
#ifndef _FAT_EXT_H_
#define _FAT_EXT_H_


extern u16 RecFileNum[MAX_FILE_NAME_NUM+1];


void sys_update_FileOrder(void);
char *f_get_RecFileName(u16 RecFileValue);
void f_FileOrder_AddFile(char *fname);
u32 f_get_firstfile_num(u8 RecType,u8 LockFlag);
u32 f_get_lastfile_num(u8 RecType,u8 LockFlag);
u32 f_get_totalfile_num(u8 RecType);
char * f_get_file_name(u32 sortindex, u32 sorttotal);
void f_del_file_name(char *fname);
void f_lock_unlock_FileName(char *fname,u8 LockFlag);
void f_update_FileOrder(void);
void f_Write_FlieOrder(void);
#endif