/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : gpdma.h
* Author             : pengtao_zhang
* Version            : V0507a
* Date               : 05/07/2013
* Description        : gpdma HEADER FILE.
***************************************************************************/
#ifndef _GPDMA_H_
#define _GPDMA_H_


typedef struct DMA_LLP_t {
	u32                     SAR;
	u32                     DAR;
	const struct DMA_LLP_t *next;
	u32                     CTL_L;
	u32                     CTL_H;
	u32                     dummy0, dummy1;
} DMA_LLP, *pDMA_LLP;



#define  dmac_global_enable()    (REG32(DMA_CfgRegL)=0x01)
#define  dmac_global_disable()   (REG32(DMA_CfgRegL)=0x00)

#define dmac_channel_enable(CH)  (REG32(DMA_ChEnRegL) |= (1<<(CH+8)) | (1<<CH))
#define dmac_channel_disable(CH) (REG32(DMA_ChEnRegL) = (REG32(DMA_ChEnRegL) & ~(1<<CH)) | (1<<(CH+8)))

#define DMAC_CH_0	0
#define DMAC_CH_1	1
#define DMAC_CH_2	2
#define DMAC_CH_3	3
#define DMAC_CH_4	4
#define DMAC_CH_5	5

#define AUDIO_ADC_DMA_CH	DMAC_CH_3
#define AUDIO_DAC_DMA_CH	DMAC_CH_4

#if 0
u8 channel_check(u8 ch);
void channel0_disable(void);
void channel0_ctl(u8 tt_fc, u8 intr_en, u8 src_itf, u8 dst_itf, u8 src_msize, u8 dst_msize,
		          u8 src_adr_mode, u8 dst_adr_mode, u8 src_tr_width, u8 dst_tr_width);
void channel0_cfg(u8 src_hs_ch, u8 dst_hs_ch, u8 src_hs_sel, u8 dst_hs_sel);
void channel0_trans_start(u32 srcadr, u32 dstadr, u16 trans_blk);
void gpdma_channel0_mem2peri(u8 srcchnum,u8 dstchnum, u8 intr_en);

void channel1_disable(void);
void channel1_ctl(u8 tt_fc,        u8 intr_en,
                  u8 src_itf,      u8 dst_itf,
                  u8 src_msize,    u8 dst_msize,
                  u8 src_adr_mode, u8 dst_adr_mode,
                  u8 src_tr_width, u8 dst_tr_width
                  );
void channel1_cfg(u8 src_hs_ch,    u8 dst_hs_ch,
                  u8 src_hs_sel,   u8 dst_hs_sel
                 );
void channel1_trans_start(u32 srcadr, u32 dstadr, u16 trans_blk);
void gpdma_channel1_peri2mem(u8 srcchnum,u8 dstchnum, u8 intr_en);
#endif

void channel5_disable(void);
void channel5_ctl(u8 tt_fc,        u8 intr_en,
                  u8 src_itf,      u8 dst_itf,
                  u8 src_msize,    u8 dst_msize,
                  u8 src_adr_mode, u8 dst_adr_mode,
                  u8 src_tr_width, u8 dst_tr_width
                 );
void channel5_cfg(u8 src_hs_ch,    u8 dst_hs_ch,
                  u8 src_hs_sel,   u8 dst_hs_sel,
                  u8 src_reload,   u8 dst_reload
                 );
void channel5_trans_start(u32 srcadr, u32 dstadr, u16 trans_blk);
void channel5_llp_cfg(u32 sar, u32 dar, u32 ctl_L, u32 ctl_H,
                      u32 llp_cur_adr, u32 llp_nxt_adr);
void channel5_llp_enable(u8 src_hs_ch, u8 dst_hs_ch, u32 llp_cur_adr);
void gpdma_channel5_mem2mem(u8 srcchnum,u8 dstchnum, u8 intr_en);
void gpdma_ch5_llp(u32 sar0, u32 dst0, u32 ctl0_L, u32 ctl0_H,
                   u32 sar1, u32 dst1, u32 ctl1_L, u32 ctl1_H,
                   u32 sram_adr);



void dma_peri2mem(u8 ch, u32 cfgh, u32 cfgl, u32 sar, u32 dar, u16 cnt);
void dma_mem2peri(u8 ch, u32 cfgh, u32 cfgl, u32 sar, u32 dar, u16 cnt);
void llp_peri2mem(u8 ch, u32 cfgh, u32 cfgl, DMA_LLP *llp);
void dma_peri2mem_Ext(u8 ch, u32 cfgh, u32 cfgl, u32 sar, u32 dar, u16 cnt);
void gpdma_Isr(void);
#endif
