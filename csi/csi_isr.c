/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : csi_isr.c
* Author             : pengtao_zhang
* Version            : V0730a
* Date               : 07/30/2013
* Description        : csi interrupt servicing
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
u32 volatile u32csi_IntFlag;
u8 volatile bcsi_FrameEndFlag;
u8 volatile cnt=0;
BOOL  bMD_Flag;
extern volatile u32 lastPacketSize;
extern volatile u8 csibufflag;
/*******************************************************************************
* Function Name  : csi_isr
* Description    : csi interrupt servicing
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
extern unsigned char volatile uvc_on;
void csi_Isr(void)
{
	//u32 u32CsiPrevSdrBase;
	u32csi_IntFlag = REG32(CSI_INTR);
	//deg_Printf("csiFlag=%x\n",u32csi_IntFlag);
	bMD_Flag = 0;
	if ((u32csi_IntFlag & TIME_INFO_BUF_EMPTY) == TIME_INFO_BUF_EMPTY)
	{
		REG32(CSI_INTR) &= ~(TIME_INFO_BUF_EMPTY);
		deg_Printf("TIME ERR\n");
	}
	if ((u32csi_IntFlag & CSI_BUF0_FUll_INTR) == CSI_BUF0_FUll_INTR)
	{
		REG32(CSI_INTR) &= ~(CSI_BUF0_FUll_INTR);
		REG32(SDR_CFG1) &= ~BIT(5);
		REG32(SDR_CFG1) |= BIT(5);
		if((usb_enum_type==1)&&(task_ctl.work_sta==TASK_USB_DEVICE))
			CsiBuffer0FullIntrHandler();
	}
	if ((u32csi_IntFlag & CSI_BUF1_FUll_INTR) == CSI_BUF1_FUll_INTR)
	{
		REG32(CSI_INTR) &= ~(CSI_BUF1_FUll_INTR);
		REG32(SDR_CFG1) &= ~BIT(5);
		REG32(SDR_CFG1) |= BIT(5);
		if((usb_enum_type==1)&&(task_ctl.work_sta==TASK_USB_DEVICE))
			CsiBuffer1FullIntrHandler();
	}
	if ((u32csi_IntFlag & CSI_FIFO_FUll_INTR) == CSI_FIFO_FUll_INTR)
	{
         REG32(CSI_INTR) &= ~(CSI_FIFO_FUll_INTR);
         deg_Printf("FIFO_FUll\n");
	}
	if ((u32csi_IntFlag & CSI_MD_ERR_INTR) == CSI_MD_ERR_INTR)
	{
	     REG32(CSI_INTR) &= ~(CSI_MD_ERR_INTR);
	     deg_Printf("MD_ERR\n");
	}
	if ((u32csi_IntFlag & CSI_MD_FIFO_FULL_INTR) == CSI_MD_FIFO_FULL_INTR)
	{
	    REG32(CSI_INTR) &= ~(CSI_MD_FIFO_FULL_INTR);
	    deg_Printf("MD_FIFO_FULL\n");
	}
	if ((u32csi_IntFlag & CSI_MD0_INTR) == CSI_MD0_INTR)
	{
		REG32(CSI_INTR) &= ~(CSI_MD0_INTR);
		bMD_Flag = 1;
		//deg_Printf("MD0");
	}
	if ((u32csi_IntFlag & CSI_MD1_INTR) == CSI_MD1_INTR)
	{
		REG32(CSI_INTR) &= ~(CSI_MD1_INTR);
		//deg_Printf("MD1\n");
	}

	if ((u32csi_IntFlag & CSI_EOF_INTR) == CSI_EOF_INTR)
	{
		REG32(CSI_INTR) &= ~(CSI_EOF_INTR);
		REG32(SDR_CFG1) &= ~BIT(5);
		REG32(SDR_CFG1) |= BIT(5);
		if((usb_enum_type==1)&&(task_ctl.work_sta==TASK_USB_DEVICE))
		{
			u32 last_size;
			u8 i=200;
			while(i--)
				asm("nop");

			last_size = REG32(CSI_DMA_ADR)*2;
			if(last_size>=(u32)(CSI_BUF1*8))
		   {
			   lastPacketSize = (last_size - (u32)((CSI_BUF1*8)));
			   csibufflag = 1;
		   }
		   else
		   {
			   lastPacketSize = (last_size - (u32)((CSI_BUF0)));
			   csibufflag = 0;
			   
		   }

			CsiEndOfFrameIntrHandler();
			return;
			
		}
		bcsi_FrameEndFlag = 1;
		//deg_Printf("EF");
		
		 if(csi_buf_point==0)
		 {
			 REG32(CSI_SDR_BASE) &= ~(0xffffff);
			REG32(CSI_SDR_BASE) |= ((VIDEO_BASE_SDRAM_ADDR+LCD_VIDEO_SDRAM_SIZE)>>1) & 0xffffff;
			
			REG32(MOTION_DETECT_PARA0) &=0xff000000;
			REG32(MOTION_DETECT_PARA0) |= (VIDEO_BASE_SDRAM_ADDR>>2)&0x00ffffff;
			
			REG32(LCDCON46) = VIDEO_BASE_SDRAM_ADDR + enlager_offset_len;
			//REG32(LCDCON0) |= (0 << 8) | (1 << 6) | (1 << 0);
			csi_buf_point++;
		 }
		 else if(csi_buf_point==1)
		 {
			REG32(CSI_SDR_BASE) &= ~(0xffffff);
			REG32(CSI_SDR_BASE) |= ((VIDEO_BASE_SDRAM_ADDR+LCD_VIDEO_SDRAM_SIZE*2)>>1) & 0xffffff;

			REG32(MOTION_DETECT_PARA0) &=0xff000000;
			REG32(MOTION_DETECT_PARA0) |= ((VIDEO_BASE_SDRAM_ADDR+LCD_VIDEO_SDRAM_SIZE)>>2) & 0x00ffffff;
			
			REG32(LCDCON46) = VIDEO_BASE_SDRAM_ADDR+LCD_VIDEO_SDRAM_SIZE + enlager_offset_len;
			//REG32(LCDCON0) |= (0 << 8) | (1 << 6) | (1 << 0);
			csi_buf_point++;
		 }
		else if(csi_buf_point==2)
		 {
			REG32(CSI_SDR_BASE) &= ~(0xffffff);
			REG32(CSI_SDR_BASE) |= ((VIDEO_BASE_SDRAM_ADDR)>>1) & 0xffffff;
			
			REG32(MOTION_DETECT_PARA0) &=0xff000000;
			REG32(MOTION_DETECT_PARA0) |= ((VIDEO_BASE_SDRAM_ADDR+(LCD_VIDEO_SDRAM_SIZE<<1))>>2) & 0x00ffffff;
			
			REG32(LCDCON46) = VIDEO_BASE_SDRAM_ADDR+LCD_VIDEO_SDRAM_SIZE*2 + enlager_offset_len;
			//REG32(LCDCON0) |= (0 << 8) | (1 << 6) | (1 << 0);
			csi_buf_point=0;
		 }

#if (1 == DEFAULT_VIDEO_TIME_EN)
		cnt++;
		if(cnt%10 == 0)
		{
			cnt = 0;
			if(g_stcJpegInfo.RecordType == RECORD_VIDEO)
			{
				csi_SetTime();
			}
		}
#endif

	}
}
