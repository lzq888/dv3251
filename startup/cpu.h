/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : cpu.h
* Author             : pengtao_zhang
* Version            : V1007a
* Date               : 10/7/2013
* Description        : cpu header file
***************************************************************************/

#ifndef _CPU_H_
#define _CPU_H_

void creat_page_table(void);
void creat_page_table_hold(void);
void cpu_hold_mode(void);
void DrainWriteBuffer(void);
void CleanDCacheLine(u32 mva);
void CleanInvalidDCacheLine(u32 mva);
void CleanDCacheRegion(u32 addr, u32 size);
void CleanInvalidDCacheRegion(u32 addr, u32 size);

#endif
