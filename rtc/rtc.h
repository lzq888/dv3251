/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : rtc.h
* Author             : pengtao_zhang
* Version            : V0726a
* Date               : 07/26/2013  ;mm/dd/yyyy
* Description        : rtc HEADER FILE.
***************************************************************************/
#ifndef _RTC_H_
#define _RTC_H_

#if 1
#define RTC_WRITE_CFG       0x55
#define RTC_READ_CFG        0x54

#define RTC_WRITE_OSC_CFG   0x59
#define RTC_READ_OSC_CFG    0x58

#define RTC_WRITE_WKPCON    0x5B
#define RTC_READ_WKPCON     0x5A

#define RTC_WRITE_TIM       0xF0
#define RTC_READ_TIM        0xE0

#define RTC_WRITE_ALM       0x53
#define RTC_READ_ALM        0x52

#define RTC_WRITE_RAM       0x57
#define RTC_READ_RAM        0x56

#define RTC_WRITE_TST       0x51

#define YEAR 2000
typedef struct
{
	u16 year;
	u8 month;
	u8 day;
	u8 hour;
	u8 min;
	u8 sec;
} date;


void rtc_Init(void);
u8 rtc_Byte(u8 x);
void rtc_WriteCfg (u8 cfg);
u8 rtc_ReadCfg(void);
void rtc_WriteRam(u8 *buf,u8 adr, u8 len);
void rtc_ReadRam(u8 *buf,u8 adr, u8 len);
void rtc_WriteCnt(u8 cmd, u32 counter);
u32 rtc_ReadCnt(u8 cmd);
u32 isLeapYear(int year);
void byte2Dec(u8 src , u8* dest);
void now(date *datePtr);
void CalcTimeInfo(u8* buf);
void rtc_WriteTime(u16 year,u8 month,u8 day,u8 hour,u8 minute,u8 second);
void rtc_set_wko_down();
void rtc_set_wko_up();

void rtc_check_updata_time_from_txt();

#endif

#endif
