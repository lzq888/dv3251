/*
 * audio_adc.h
 *
 *  Created on: 2013Äê10ÔÂ11ÈÕ
 *      Author: jingcunxu
 */

#ifndef AUDIO_ADC_H_
#define AUDIO_ADC_H_

//AUADC_CFG
#define AUADC_EN				(1<<0)
#define AUADC_COEF_EN			(1<<1)
#define AUADC_FILT1_EN			(1<<2)
#define AUADC_FILT2_EN			(1<<3)
#define AUADC_SAMP_SEL  		(1<<4)//0:192k or divide of 192k,1:176.4k
#define AUADC_RMDC_EN			(1<<5)
//#define AUADC_RMDC_CLR  		(1<<7)

#define AUADC_FILT1_DOWN(n)		((n-1)<<8)  //8>=n>=2,n´ú±ín·ÖÆµ
#define AUADC_FILT2_DOWN(n)		((n-1)<<11)  //4>=n>=2
#define AUADC_FILT3_DOWN(n)		((n-1)<<13)

//AGC_CFG0
#define AGC_IE					(1<<4)
#define DMA_EN					(1<<5)
#define NOISE_ACT				(1<<6)
#define AGC_EN					(1<<7)
#define TS_MODE					(1<<8)
#define	AGC_CH_NUM				(1<<9)//0:one channel,1:two channel


//AGC_CFG1

//AGC_CFG2 ÔöÒæµ÷½Ú£¬10~7bitÎªÄ£Äâµ÷½Ú£¬6~0bitÎªÊý×Öµ÷½Ú

//AGC_CFG3
#define AGC_BLK_NUM(n)			((n&0x0f)<<12)//the max size is 4096
#define AGC_BLK_SIZE(n)			(n&0x0fff)//the max size is 4096

//AGC_STA
#define AGC_DMA_DONE			0x01//ÊÇ·ñ½ÓÊÕÍêÒ»¸öblock
#define AGC_BLK_CNT				0xF0//µ±Ç°Ê¹ÓÃµÄblockºÅ
#define AGC_DATA_RD				0x04
#define	AGC_SIG_FLAG			0x08

//AGC_CFG_CLR
#define	AGC_DMA_CLR				0x01//clear DMA DONE penging
#define AGC_DMA_WR				0x04//software can wrtie data to AGC when in test mode
#define	AGC_DMA_OFF				0x08//init AGC control counter
#define AGC_KICK_START			0x10

extern volatile u32 audio_buffer_ptr;

void audio_adc_init();
void wr_reg(u8 addr, u32 reg_dat);
u32 rd_reg(u8 addr);
void audio_adc_Stop(void);
void audio_adc_isr(void);
void audio_AGC_DMA_Isr(void);
void close_adc(void);
#endif /* AUDIO_ADC_H_ */
