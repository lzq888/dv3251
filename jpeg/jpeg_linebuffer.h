/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : jpeg_linebuffer.h
* Author             : pengtao_zhang
* Version            : V0831a
* Date               : 08/31/2013
* Description        : jpeg line buffer HEADER FILE.
***************************************************************************/
#ifndef _JPEG_LINEBUFFER_H_
#define _JPEG_LINEBUFFER_H_

#define LB_ADDRESS      0x10000000


#define JPEG_SCALE_SIZE_H      2560
#define JPEG_SCALE_SIZE_V      1440


extern u8 *YUYVDestBuff;
extern u8 *YUYVSrcBuff;


void jpeg_LineBuffer_Start(void);
void WriteLineBuffer(void);
void WriteHalfLineBuffer(void);
void WriteOneLineBuffer(void);
void InsertOneLineYUYV(u8 *out_buff, u8 *in_buff);
void WriteEightLineBuffer(u8 mode);
void WriteEightHalfLineBuffer(u8 mode);

void lcd_WriteBack(void);
#endif
