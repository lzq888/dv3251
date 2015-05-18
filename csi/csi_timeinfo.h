/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : csi.h
* Author             : pengtao_zhang
* Version            : V0904a
* Date               : 09/04/2013
* Description        : csi tiem info HEADER FILE.
***************************************************************************/
#ifndef _CSI_TIMEINFO_H_
#define _CSI_TIMEINFO_H_


/**********for timeinfo*****************************/
#define   TIME_POS_X         4             // Time information position X: CSI_TIME_POS[26:16]
#define   TIME_POS_Y         4             // Time information position Y: CSI_TIME_POS[11:0]

#define   TIME_INFO_EN       1          //1: OSD Time information enable; 0:OSD Time information disable
#define   TIME_INFO_Y        0xff //0xe1//0x7f//0xe1      // Time information color Y: CSI_TIME_INFO[23:16]
#define   TIME_INFO_U        0x80 //0x01//0x95//0x01      // Time information color U: CSI_TIME_INFO[15:8]
#define   TIME_INFO_V        0x80 //0x95//0x01//0x95      // Time information color V: CSI_TIME_INFO[7:0]
#define	  TIME_INFO_LEN		  19//20	     // the length of the time info buffer  //ÔÝÊ±Ö»Ö§³ÖÅ¼Êý
#define	  TIME_FONT_W		  32//16
#define	  TIME_FONT_H		  32//24

#define   TIME_W         	  TIME_FONT_W*TIME_INFO_LEN  // Width (pixel) for time info: AE_PARA6[27:16]
#define   TIME_H         	  TIME_FONT_H            // Heigth (pixel) for time info: AE_PARA6[11:0]
#define   FONT_LEN            TIME_FONT_W*TIME_FONT_H/8                //24*16/8

extern u8  TimeInfoCurrent[TIME_INFO_LEN];    //store curent timerinfo
extern u32 *TimerInfoPixelBuf;
extern u32 lastTimeCount;

void csi_TimeInfo_Init(void);
void csi_SetTimePos(void);
void csi_SetTimeInfo(void);
void csi_SetTimeInfoSize(void);
void csi_SetTime(void);
u8 csi_SetTimeInfoRam(u8 *p_TimeInfo);




#endif
