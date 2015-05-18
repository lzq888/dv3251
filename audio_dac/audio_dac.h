/*
 * dac.h
 *
 *  Created on: 2013Äê8ÔÂ13ÈÕ
 *      Author: jingcunxu
 */

#ifndef AUDIO_DAC_H_
#define AUDIO_DAC_H_


//DACCFG
#define DAC_EN			(1<<0)
#define DAC_EQ_EN		(1<<1)
#define DAC_DISEL		(1<<3)//white noise dither
#define G_AUADC_EN		(1<<8)
#define G_AGC_EN		(1<<9)
#define OBUF_EN			(1<<10)
#define DAC_MULT_EN		(1<<11)

//OBUF_STA
#define OBUF_PND		0x01
#define OBUF_EMPTY		0x02
#define DAC_BLK_CNT		0x3C//DAC is in which block to read samples


//OBUF_CFG
#define SAMP_CNT		(0x1F<<5)
#define	OBUF_EMPTY_INT	(1<<4)//when obuf samples is less than software setting,generate a interrupt if this bit enable(set 1)
#define OBUF_EMPTY_EN	(1<<3)//when obuf samples is less than software setting,generate a pending if this bit enable(set 1)
#define OBUF_PND_INT	(1<<2)//when obuf has mulfiple block,the same size,if one block is read,then generate a pending and interrupt if needed.
#define SOFT_SPD_EN		(1<<1)


//DAC_ACON0


//DAC_SAMPLE
#define DAC_SAMPLE_48000   	0x0
#define DAC_SAMPLE_44100   	0x1
#define DAC_SAMPLE_32000   	0x2
#define DAC_SAMPLE_24000   	0x4
#define DAC_SAMPLE_22050    0x5
#define DAC_SAMPLE_16000   	0x6
#define DAC_SAMPLE_12000   	0x8
#define DAC_SAMPLE_11025   	0x9
#define DAC_SAMPLE_8000   	0xa

void key_voice_init();
void wr_reg(u8 addr, u32 reg_dat);
u32 rd_reg(u8 addr);
void audio_dac_init();
void audio_dac_Stop(void);
void audio_amplifier_open();
void audio_amplifier_close();
void key_voice();
void key_voice_after_recording();
void dac_irq(void);
void music_init(u32 *tempbuf,u16 volume,u8 sample,u8 delay_flag);
void music_play(u8 *srcbuf ,u32 buf_len);

#endif /* DAC_H_ */
