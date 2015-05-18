/*
 * audio_adc.
 *
 *  Created on: 2013年10月11日
 *      Author: jingcunxu
 */


#include "../header/include.h"
#include "audio_adc.h"
#include "../audio_dac/audio_dac.h"

static U32 u32Framecount = 0;
volatile u32 audio_buffer_ptr = ((u32)JPEG_BUFFER_END_ADDRESS - (AUDIO_BUFFER_NUM*0x2000));
u8 volatile agcflg;

u8 ep3buf[64];
u8 volatile audio_offset=0;

void audio_adc_isr(void)
{
	u32 agc_sta = rd_reg(AGC_STA);

	if(agc_sta & BIT(4))
	{
		agcflg=0x0a;
//		deg_Printf("audio_adc_isr a\n");
	}
	else
	{
		agcflg=0x0b;
//		deg_Printf("audio_adc_isr b\n");
	}
	wr_reg(AGC_CFG_CLR, rd_reg(AGC_CFG_CLR)|BIT(0));
}


void audio_adc_analog_init()
{
	
	REG32(DAC_ACON0) |= BIT(0)|BIT(17)|BIT(13)|BIT(15);
	REG32(AUDIO_ACON) |= BIT(0)|BIT(1);
	REG32(AUDIO_ACON) &= ~BIT(4);	
	
}

void audio_adc_init()
{
	u8 adr;
	
	REG32(PCON0)   &= ~(1<<21);    // enable dac clock
	REG32(CLKCON1) &= ~(0xf<<8);
	REG32(CLKCON1) |= (9<<8);//10 div  240M/(9+1)=24M
	REG32(CLKCON0) &= ~((1<<6)|(1<<7));
	
	g_stcJpegInfo.u32AudioDataReady = 0;
	g_stcJpegInfo.iAudioFillBufCnt=0;
	g_stcJpegInfo.iAudioFSWriteBufCnt=0;
	g_stcJpegInfo.dwAudiobufSize = 0x2000;
	g_stcJpegInfo.pAudioDataBuf = (u8 *)((u32)JPEG_BUFFER_END_ADDRESS - 0x2000);

	audio_adc_analog_init();//

    //llp_peri2mem(AUDIO_ADC_DMA_CH, (6<<7)|(0<<11), 0, (DMA_LLP *)(&adc_llp0));
	dmac_channel_disable(AUDIO_ADC_DMA_CH);
   	dma_peri2mem_Ext(AUDIO_ADC_DMA_CH, (0<<11)|(6<<7)|(0<<1), (0<<11)|(0<<10), AUADC_DMA_TX_ADR, (audio_buffer_ptr+8), (2048-2));
	REG32(DMA_ClearTfrL) = BIT(3);
	REG32(DMA_MaskTfrL)  |=  (BIT(3) | BIT(3+8));
	SetIntSrc(DMA_INT);
	
    wr_reg(DACCFG,rd_reg(DACCFG)|G_AUADC_EN|G_AGC_EN);//AGC EN ADC EN
	for(adr=0; adr<140; adr++)
	{
		wr_reg(AUADC_DAT,0);
	}

	wr_reg(AUADC_BAUD,4);//24000000/192000/25-1
	wr_reg(AUADC_CFG,AUADC_FILT1_DOWN(2)|AUADC_FILT2_DOWN(2)|AUADC_FILT3_DOWN(3)|AUADC_COEF_EN|AUADC_FILT1_EN|AUADC_FILT2_EN|AUADC_EN);

	// DMA enable and AGC enable
	//wr_reg(AGC_CFG0,rd_reg(AGC_CFG0)|DMA_EN|AGC_IE);
	wr_reg(AGC_CFG0,rd_reg(AGC_CFG0)|DMA_EN);
	// block number, block size
	wr_reg(AGC_CFG3,(1<<12)|((2048-2)<<0));
	// clear DMA_DONE pending flag before kit-start AGC
	wr_reg(AGC_CFG_CLR,1<<0);
	// kit-start AGC
	wr_reg(AGC_CFG_CLR,1<<4);

	wr_reg(AGC_CFG1,0x17e6);			//mic sound is max
	wr_reg(AGC_CFG2,0x780);				//mic sound set 
	REG32(AUDIO_ACON) |= BIT(5);
	
	SetIntSrc(AUADC_INT);

	deg_Printf("audio adc init ok\n");
}

extern volatile unsigned char UacSampFreqChange;
void close_adc(void)
{	
	audio_adc_Stop();
	UacSampFreqChange = 0;
}
void audio_adc_Stop(void)
{
	REG32(AUDIO_ACON) |= BIT(4);//mute adc	
	REG32(AUDIO_ACON) &= ~(BIT(0)|BIT(1));//mic disable/adc analog
	wr_reg(AUADC_CFG,rd_reg(AUADC_CFG)&(~AUADC_EN));
	wr_reg(DACCFG,rd_reg(DACCFG)&(~G_AUADC_EN)&(~G_AGC_EN));
	ClrIntSrc(AUADC_INT);
	dmac_channel_disable(AUDIO_ADC_DMA_CH);
	
}

void audio_AGC_DMA_Isr(void)
{
	u32 agc_sta = rd_reg(AGC_STA);
	//deg_Printf(" %x\n",agc_sta);
	if((agc_sta & 0x1) == 0x1)
		wr_reg(AGC_CFG_CLR, rd_reg(AGC_CFG_CLR)|BIT(0));

	wr_reg(AGC_CFG0,rd_reg(AGC_CFG0)&(~BIT(5)));
	if((g_stcJpegInfo.iAudioFillBufCnt+1) < (g_stcJpegInfo.iAudioFSWriteBufCnt + AUDIO_BUFFER_NUM))
	{
		if(audio_buffer_ptr == ((u32)JPEG_BUFFER_END_ADDRESS - 0x2000))
			audio_buffer_ptr = (u32)JPEG_BUFFER_END_ADDRESS-(AUDIO_BUFFER_NUM*0x2000);
		else
			audio_buffer_ptr += g_stcJpegInfo.dwAudiobufSize;

		g_stcJpegInfo.iAudioFillBufCnt++;
	}
	else
	{
		deg_Printf("d");
		g_stcJpegInfo.i30FrameCnt -=((192*(u32Framecount+1))/25 -(192*u32Framecount)/25);
		u32Framecount++;
		if(u32Framecount >= 25)
		{
			u32Framecount = 0;
		}
		g_stcJpegInfo.iJpeg10MSCnt -= 25;
	}
	dmac_channel_disable(AUDIO_ADC_DMA_CH);
	//dma_peri2mem_Ext(AUDIO_ADC_DMA_CH, (0<<11)|(6<<7)|(0<<1), (0<<11)|(0<<10), AUADC_DMA_TX_ADR, (audio_buffer_ptr+8), (2048-2));
	REG32(DMA_DAR0L + AUDIO_ADC_DMA_CH*0x58) = (u32)(audio_buffer_ptr+8);
	dmac_channel_enable(AUDIO_ADC_DMA_CH);
	
	wr_reg(AGC_CFG0,rd_reg(AGC_CFG0)|(BIT(5)));
	wr_reg(AGC_CFG_CLR, rd_reg(AGC_CFG_CLR)|BIT(5));
}


typedef enum {
	ADC_44_1K,
	ADC_16K,
	ADC_48K,
	ADC_32K,
} ADC_SAMPLE_RATE;

volatile u32 dac_buf_0 = ((u32)JPEG_BUFFER_END_ADDRESS - (AUDIO_BUFFER_NUM*0x2000));
volatile u32 dac_buf_1 = ((u32)JPEG_BUFFER_END_ADDRESS - (11*0x2000));

ADC_SAMPLE_RATE adc_sample_rate = ADC_44_1K;
u32 adc_single_double_ch = 0;
#define DAC_BLOCK_CNT	2048

//unsigned char dac_buf_0[DAC_BLOCK_CNT*2] __attribute__ ((aligned(4)));
//unsigned char dac_buf_1[DAC_BLOCK_CNT*2] __attribute__ ((aligned(4)));

static DMA_LLP adc_llp1;
static DMA_LLP adc_llp0 =
{
	.SAR   = AUADC_DMA_TX_ADR,
	.DAR   = ((u32)JPEG_BUFFER_END_ADDRESS - (AUDIO_BUFFER_NUM*0x2000)),
	.next  = &adc_llp1,
	.CTL_L = (1<<28) | (1<<27) |  (1<<25) | (0<<23) | (2<<20) | (2<<9) | (0<<7) | (2<<4) | (2<<1),
//	.CTL_L = (1<<28) | (1<<27) |  (1<<25) | (0<<23) | (2<<20) | (2<<9) | (0<<7) | (1<<4) | (1<<1),
	.CTL_H = DAC_BLOCK_CNT
};

static DMA_LLP adc_llp1 =
{
	.SAR   = AUADC_DMA_TX_ADR,
	.DAR   = ((u32)JPEG_BUFFER_END_ADDRESS - ((AUDIO_BUFFER_NUM-1)*0x2000)),
	.next  = &adc_llp0,
	.CTL_L = (1<<28) | (1<<27) |  (1<<25) | (0<<23) | (2<<20) | (2<<9) | (0<<7) | (2<<4) | (2<<1),
//	.CTL_L = (1<<28) | (1<<27) |  (1<<25) | (0<<23) | (2<<20) | (2<<9) | (0<<7) | (1<<4) | (1<<1),
	.CTL_H = DAC_BLOCK_CNT
};

extern volatile unsigned char UacSampFreq[3];
extern volatile unsigned char UacSampFreqChange;
extern volatile unsigned char uac_on;
extern u8 *usbep3buf;

void set_usb_audio_usr_para(void)
{	
	adc_single_double_ch = 1;
	
	if((UacSampFreq[0] == 0x80)&&(UacSampFreq[1] == 0x3E)
		&&(UacSampFreq[2] == 0))
	{
		adc_sample_rate = ADC_16K;
	}
	else if((UacSampFreq[0] == 0x00)&&(UacSampFreq[1] == 0x7D)
		&&(UacSampFreq[2] == 0))
	{
		adc_sample_rate = ADC_32K;
	}
	else if((UacSampFreq[0] == 0x44)&&(UacSampFreq[1] == 0xAC)
		&&(UacSampFreq[2] == 0))
	{
		adc_sample_rate = ADC_44_1K;
	}
	else if((UacSampFreq[0] == 0x80)&&(UacSampFreq[1] == 0xBB)
		&&(UacSampFreq[2] == 0))
	{
		adc_sample_rate = ADC_48K;
	}
	else
	{
		deg_Printf("set_usb_audio_usr_para5\r\n");
	}
}


void adc_init(void)
{
//	u16 tmp;
	deg_Printf("adc_init\r\n");
	u8 adr;

	REG32(PCON0) &= ~(1<<21);    // enable dac clock
	REG32(CLKCON1) &= ~(0xf<<8);
	REG32(CLKCON1) |= (9<<8);//10 div  240M/(9+1)=24M
	REG32(CLKCON0) &= ~((1<<6)|(1<<7));
	
	if(1 == adc_single_double_ch)
	{
		adc_llp0.CTL_L = (1<<28) | (1<<27) |  (1<<25) | (0<<23) | (2<<20) | (2<<9) | (0<<7) | (1<<4) | (1<<1);
		adc_llp1.CTL_L = (1<<28) | (1<<27) |  (1<<25) | (0<<23) | (2<<20) | (2<<9) | (0<<7) | (1<<4) | (1<<1);
	}
	else
	{
		adc_llp0.CTL_L = (1<<28) | (1<<27) |  (1<<25) | (0<<23) | (2<<20) | (2<<9) | (0<<7) | (2<<4) | (2<<1);
		adc_llp1.CTL_L = (1<<28) | (1<<27) |  (1<<25) | (0<<23) | (2<<20) | (2<<9) | (0<<7) | (2<<4) | (2<<1);
	}
	
    llp_peri2mem (AUDIO_ADC_DMA_CH, (6<<7)|(0<<11), 0, &adc_llp0);
//	dmac_channel_disable(AUDIO_ADC_DMA_CH);
//	dma_peri2mem(AUDIO_ADC_DMA_CH, (0<<11)|(6<<7)|(0<<1), (0<<11)|(0<<10), AUADC_DMA_TX_ADR, (u32)(&audio_buffer_ptr[0]), 1024/4);

	REG32(DAC_ACON0) |= BIT(0)|BIT(17)|BIT(13)|BIT(15);
	REG32(AUDIO_ACON) |= BIT(0)|BIT(1);
	REG32(AUDIO_ACON) &= ~BIT(4);
//	audio_adc_analog_init();//

    wr_reg(DACCFG,rd_reg(DACCFG)|G_AUADC_EN|G_AGC_EN);//AGC EN ADC EN

	for(adr=0; adr<140; adr++)
	{
		wr_reg(AUADC_DAT,0);
	}
#if 0
	wr_reg(AGC_CFG0,(1<<5)); 
	wr_reg(AGC_CFG_CLR,(1<<4));
	
	wr_reg(AUADC_CFG,(1<<6) |(1<<4)| (1<<0)); 
	wr_reg(AUADC_BAUD,15);
	

#else
	if (ADC_44_1K == adc_sample_rate)
	{
		wr_reg(AUADC_BAUD,7);//24000000/176400/17-1
		// ADC filter1sample multiple, adc filter1 enable, Audio ADC enable
		wr_reg(AUADC_CFG,AUADC_FILT1_DOWN(4)/*|AUADC_FILT2_DOWN(2)|AUADC_FILT3_DOWN(2)|AUADC_COEF_EN|AUADC_FILT2_EN*/|AUADC_COEF_EN|AUADC_FILT1_EN|AUADC_SAMP_SEL|AUADC_RMDC_EN|AUADC_EN);
		deg_Printf (("adc simple setting ADC_44_1K\r\n"));
	//	wr_reg(AUADC_CFG,AUADC_FILT1_DOWN(2)|AUADC_COEF_EN|(1<<6)|AUADC_SAMP_SEL|AUADC_RMDC_EN|AUADC_EN);
	}
	else if (ADC_16K == adc_sample_rate)
	{
		wr_reg(AUADC_BAUD,4);//24000000/192000/25-1
		wr_reg(AUADC_CFG,AUADC_FILT1_DOWN(2)|AUADC_FILT2_DOWN(2)|AUADC_FILT3_DOWN(3)|AUADC_COEF_EN|AUADC_FILT1_EN|AUADC_FILT2_EN|AUADC_EN);
		deg_Printf (("adc simple setting ADC_16K\r\n"));
	}
	else if (ADC_48K == adc_sample_rate)
	{
		wr_reg(AUADC_BAUD,4);//24000000/192000/25-1
		// ADC filter1sample multiple, adc filter1 enable, Audio ADC enable
		wr_reg(AUADC_CFG,AUADC_FILT1_DOWN(4)/*|AUADC_FILT2_DOWN(2)|AUADC_FILT3_DOWN(2)|AUADC_COEF_EN|AUADC_FILT2_EN*/|AUADC_COEF_EN|AUADC_FILT1_EN|AUADC_RMDC_EN|AUADC_EN);
		deg_Printf (("adc simple setting ADC_48K\r\n"));
	}
	else if (ADC_32K == adc_sample_rate)
	{
		wr_reg(AUADC_BAUD,4);//24000000/192000/25-1
		// ADC filter1sample multiple, adc filter1 enable, Audio ADC enable
		wr_reg(AUADC_CFG,AUADC_FILT1_DOWN(6)/*|AUADC_FILT2_DOWN(2)|AUADC_FILT3_DOWN(2)|AUADC_COEF_EN|AUADC_FILT2_EN*/|AUADC_COEF_EN|AUADC_FILT1_EN|AUADC_RMDC_EN|AUADC_EN);
		deg_Printf (("adc simple setting ADC_32K\r\n"));
	}
	else
	{
		deg_Printf (("adc simple setting unknown\r\n"));
	}
	// DMA enable and AGC enable
	//wr_reg(AGC_CFG0,rd_reg(AGC_CFG0)|DMA_EN);
//	wr_reg(AGC_CFG0,rd_reg(AGC_CFG0)|DMA_EN);
	wr_reg(AGC_CFG0,rd_reg(AGC_CFG0)|DMA_EN|AGC_IE);

	// block number, block size
	wr_reg(AGC_CFG3,(2<<12)|(DAC_BLOCK_CNT<<0));

	// clear DMA_DONE pending flag before kit-start AGC
	wr_reg(AGC_CFG_CLR,1<<0);
	// kit-start AGC
	wr_reg(AGC_CFG_CLR,1<<4);

	wr_reg(AGC_CFG1,0x16e6);
	wr_reg(AGC_CFG2,0x600);

	SetIntSrc(AUADC_INT);

#endif

//	APP_TRACE_INFO(("adc init over\r\n"));
	return ;
}


//start the adc from usb
void USB_start_adc(void)
{
	if (1 == UacSampFreqChange && 1 == uac_on)
	{
		set_usb_audio_usr_para();
//		adc_sample_rate = ADC_32K;
		adc_init();
	}
}

#if 0 // use for adc data play through dac

#define DAC_SAMPLE_48000   	0x0
#define DAC_SAMPLE_44100   	0x1
#define DAC_SAMPLE_32000   	0x2
#define DAC_SAMPLE_24000   	0x4
#define DAC_SAMPLE_22050    0x5
#define DAC_SAMPLE_16000   	0x6
#define DAC_SAMPLE_12000   	0x8
#define DAC_SAMPLE_11025   	0x9
#define DAC_SAMPLE_8000   	0xa

extern const DMA_LLP adc_dac1;
const DMA_LLP adc_dac0 =
{
	.SAR   = ((u32)JPEG_BUFFER_END_ADDRESS - (AUDIO_BUFFER_NUM*0x2000)),
	.DAR   = DAC_DMA_RX_ADR,
	.next  = &adc_dac1,
	.CTL_L = (1<<28) | (1<<27) | (0 << 25) | (1 << 23) | (1<<20) | (1 << 14) | (0 << 11)| (0<<9) | (2<<7) | (2<<4) | (2<<1),
	.CTL_H = DAC_BLOCK_CNT//1152//512
};

const DMA_LLP adc_dac1 =
{
	.SAR   = ((u32)JPEG_BUFFER_END_ADDRESS - ((AUDIO_BUFFER_NUM-1)*0x2000)),
	.DAR   = DAC_DMA_RX_ADR,
	.next  = &adc_dac0,
	.CTL_L = (1<<28) | (1<<27) | (0 << 25) | (1 << 23) | (1<<20) | (1 << 14) | (0 << 11)| (0<<9) | (2<<7) | (2<<4) | (2<<1),
	.CTL_H = DAC_BLOCK_CNT//1152//512
};

void dac_init()                                                          
{
//	Uart_SendByte ('\n');Uart_SendByte ('e');Uart_SendByte ('\n');	
	
	REG32(PCON0)   &= ~(1<<21);    // enable dac clock
	REG32(CLKCON0) &= ~(BIT(6)|BIT(7)); 
	REG32(CLKCON1) &= ~(0xf<<8);
	REG32(CLKCON1) |= (9<<8);//10 div  240M/(9+1)=24M
	
	obuf_cfg();
	
	REG32(DAC_ACON0) |= BIT(2);
	wr_reg(FIFO_CNT, DAC_BLOCK_CNT);//
//	wr_reg(OBUF_CLR, 0x02);//clear pending
	
//	dac_analog_init();
	
#if 0
	if(adc_single_double_ch)
	{
		music_llp0.CTL_L = (1<<28) | (1<<27) | (0 << 25) | (1 << 23) | (1<<20) | (1 << 14) | (0 << 11)| (0<<9) | (2<<7) | (1<<4) | (1<<1);
		music_llp1.CTL_L = (1<<28) | (1<<27) | (0 << 25) | (1 << 23) | (1<<20) | (1 << 14) | (0 << 11)| (0<<9) | (2<<7) | (1<<4) | (1<<1);
	}
	else
	{
		music_llp0.CTL_L = (1<<28) | (1<<27) | (0 << 25) | (1 << 23) | (1<<20) | (1 << 14) | (0 << 11)| (0<<9) | (2<<7) | (2<<4) | (2<<1);
		music_llp1.CTL_L = (1<<28) | (1<<27) | (0 << 25) | (1 << 23) | (1<<20) | (1 << 14) | (0 << 11)| (0<<9) | (2<<7) | (2<<4) | (2<<1);
	}
#endif
	
	llp_peri2mem (AUDIO_DAC_DMA_CH, (0<<7)|(7<<11), 0, &adc_dac0); 
	
	wr_reg(DACCFG, (rd_reg(DACCFG)& 0xffffff0f) | ((DAC_SAMPLE_32000)<<4) | DAC_EN);

	digital_volume_set(0x3fff,1,0);//

	REG32(DAC_ACON0) &= ~BIT(2);
	deg_Printf("dac_init\r\n");
	return;
}


void adc_init_dac(void)
{
	dac_init();
}
#endif

void Ep3_audio_adc_init(void)
{
	
	deg_Printf("Ep3_audio_adc start\r\n");
	usbep3buf = (u8 *)&ep3buf;
	memset__(usbep3buf,0,64);
	audio_offset = 0;
	audio_adc_Stop();
//	dac_buf_0 = audio_buffer_ptr;
//	dac_buf_1 = audio_buffer_ptr + 2048*4;
	
	memset__((void *)dac_buf_0, 0, 2048*4);
	memset__((void *)dac_buf_1, 0, 2048*4);
	USB_start_adc();
//	adc_init_dac();

}


//get audio data from ep 3
void Get_ep3_auido_adc(void)
{
	u8 *dst,*src;
	u32 i;
	static u8 adc_buf_num = 1;
	
//	deg_Printf("Get_ep3_auido_adc start\r\n");
	dst = usbep3buf;
	memset__(usbep3buf,0,64);
//	audio_offset = 0;

	if (adc_buf_num == 1)
	{
		src = (u8 *)(dac_buf_0 + 64*audio_offset);
	}
	else if(adc_buf_num == 2)
	{
		src = (u8 *)(dac_buf_1 + 64*audio_offset);
	}
	else 
	{
		src=(u8 *)(dac_buf_0 + 64*audio_offset);
	}
	for(i=0; i<64; i++)
	{
		dst[i] = src[i];
	}
	
	audio_offset++;

	if(audio_offset==64)
	{
		audio_offset =0;
		
		if((adc_buf_num == 1))
		{
			adc_buf_num = 2;
//			deg_Printf("adc_buf_num to 2\r\n");
		}
		else if (adc_buf_num == 2)
		{
			adc_buf_num = 1;
//			deg_Printf("adc_buf_num to 1\r\n");
		}
	}
}

