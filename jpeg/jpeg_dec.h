/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : jpeg_dec.h
* Author             : pengtao_zhang
* Version            : V0829a
* Date               : 08/29/2013
* Description        : jpeg decode HEADER FILE.
***************************************************************************/
#ifndef _JPEG_DEC_H_
#define _JPEG_DEC_H_

/******* MARKER CODE ASSIGNMENTS *********/
#define    SOI       0xFFD8
#define    SOF0      0xFFC0
#define    SOF1      0xFFC1
#define    SOF2      0xFFC2
#define    SOF3      0xFFC3
#define    SOF5      0xFFC5
#define    SOF6      0xFFC6
#define    SOF7      0xFFC7
#define    SOF9      0xFFC9
#define    SOFA      0xFFCA
#define    SOFB      0xFFCB
#define    SOFD      0xFFCD
#define    SOFE      0xFFCE
#define    SOFF      0xFFCF
#define    SOS       0xFFDA
#define    DQT       0xFFDB
#define    DHT       0xFFC4
#define    DRI       0xFFDD
#define    EOI       0xFFD9


extern volatile u8 jpdec_flag;
extern u32 u32jpegSize_H,u32jpegSize_V;

BOOL mjpdec_Start(u8 * idma_ptr, u8 *odma_ptr);
u8 jpeg_header_decode(void);
void jpdec_Stop(void);
void jpdec_Isr(void);

#endif
