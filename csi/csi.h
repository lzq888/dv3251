/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : csi.h
* Author             : pengtao_zhang
* Version            : V0904a
* Date               : 09/04/2013
* Description        : csi HEADER FILE.
***************************************************************************/
#ifndef _CSI_H_
#define _CSI_H_



#define CSI_EOF_INTR			0x01		// bit 0
#define CSI_MD0_INTR			0x02		// bit 1
#define CSI_MD1_INTR			0x04		// bit 2
#define CSI_BUF1_FUll_INTR		0x08		// bit 3
#define CSI_BUF0_FUll_INTR		0x10		// bit 4
#define CSI_FIFO_FUll_INTR		0x20        // bit 5
#define CSI_MD_ERR_INTR	    	0x40        // bit 6
#define CSI_MD_FIFO_FULL_INTR	0x80        // bit 7
#define TIME_INFO_BUF_EMPTY	    0x100        // bit 8

#define   CSI_BUF0           0x0000
#define   CSI_BUF1           0x0f00

#define  MD_STOP_VIDEO_S	 60

#define  CC_PARA_00           256
#define  CC_PARA_01           0
#define  CC_PARA_02           0
#define  CC_PARA_10           0
#define  CC_PARA_11           256
#define  CC_PARA_12           0
#define  CC_PARA_20           0
#define  CC_PARA_21           0
#define  CC_PARA_22           256

extern u8 volatile bcsi_FrameEndFlag;
extern u32 u32sdr_Buff_Len;
extern BOOL bMD_Flag;
extern u32 u32MDCnt;
extern BOOL bMD_StopVideo_Flag;
extern u32 u32csi_Dma_Size_H,u32csi_Dma_Size_V;

volatile u8 csi_buf_point; 



void csi_Init(void);
void csi_Start(u8 recordtype,u8 lcd_set);
void csi_DmaSet(void);
void csi_SetDataWidth(u8 u8DataBusWidth);
void csi_SetInputSize(u16 u16Hsize,u16 u16Vsize);
void csi_SetOutputSize(u8 recordtype);
void csi_SetOutMode(u8 recordtype);
void csi_SetScaler(u8 recordtype,u8 u8resType);
void csi_DmaEnable(void);
void csi_ParameterSet(u8 recordtype,u8 u8resType);
void csi_Stop(void);
void csi_Enable(void);
void csi_Isr(void);
void csi_MD_Start(void);
void csi_MD_Enable(void);
void csi_MD_Disable(void);
void csi_CheckMD(void);
void csi_SetColorCorrection(void);
void csi_InserTimeInfo(void);
void csi_camera_init(void);
void csi_camera_on(void);
void csi_camera_off(void);
#endif
