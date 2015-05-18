/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : gpdma.c
* Author             : pengtao_zhang
* Version            : V0807a
* Date               : 08/07/2013
* Description        : This file provides all the gpdma firmware functions.
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
#if 0

u8 channel_check(u8 ch){
    if((DMA_ChEnRegL & (1<<ch)) == (1<<ch))
        return 1;
    else
        return 0;
}
//channel 0
void channel0_disable(){
    DMA_CFG0L |= (1<<8);                             // Set CH_SUSP Bit
    while((DMA_CFG0L & (1<<9)) == 0);                // Wait for FIFO Empty
    DMA_ChEnRegL = DMA_ChEnRegL & ~(1<<0) | (1<<8);  // Clear CH_EN
    DMA_CFG0L &= ~(1<<8);
}

void channel0_ctl(u8 tt_fc,        u8 intr_en,
                  u8 src_itf,      u8 dst_itf,
                  u8 src_msize,    u8 dst_msize,
                  u8 src_adr_mode, u8 dst_adr_mode,
                  u8 src_tr_width, u8 dst_tr_width
                 ){
	DMA_CTL0L  = ((tt_fc&0x7)<<20)       | ((intr_en&0x01)<<0) |
                 //((src_llp_en&0x01)<<28) | ((dst_llp_en&0x01)<<27) |
				 ((0 & 0x01)<<28) | ((0 & 0x01)<<27) |
                 ((src_itf&0x3)<<25)     | ((dst_itf&0x3)<<23) |
                 //((src_gat_en&0x01)<<17) | ((dst_sat_en&0x01)<<18) |
				 ((0 & 0x01)<<17) | ((0 & 0x01)<<18) |
                 ((src_msize&0x7)<<14)   | ((dst_msize&0x7)<<11) |
                 ((src_adr_mode&0x3)<<9) | ((dst_adr_mode&0x03)<<7) |
                 ((src_tr_width&0x7)<<4) | ((dst_tr_width&0x7)<<1);
    DMA_LLP0L  = 0;
}

void channel0_cfg(u8 src_hs_ch,   u8 dst_hs_ch,
                  u8 src_hs_sel,  u8 dst_hs_sel
                 ){
	DMA_CFG0H  = ((src_hs_ch&0xf)<<7)  | ((dst_hs_ch&0xf)<<11) |
                 ((0&0x1)<<6) | ((0&0x1)<<5) |
                 ((0&0x7)<<2) | ((1&0x01)<<1) |  //FIFO MODE
                 (0&0x01);
	DMA_CFG0L  = ((0&0x1)<<30)   | ((0&0x1)<<31) |
                 ((0&0x3ff)<<20) |
                 ((0&0x1)<<19)   | ((0&0x1)<<18) |
                 ((0&0x1)<<17)   | ((0&0x1)<<16) |
                 ((0&0x3)<<14)   | ((0&0x3)<<12) |
                 ((src_hs_sel&0x1)<<11)  | ((dst_hs_sel&0x1)<<10) |
                 ((0&0x1)<<8)    | ((0&0x7)<<5);
}

void channel0_trans_start(u32 srcadr, u32 dstadr, u16 trans_blk){
    DMA_SAR0L = srcadr;
    DMA_DAR0L = dstadr;
    DMA_CTL0H = trans_blk;
    dmac_channel_enable(0);
}

void gpdma_channel0_mem2peri(u8 srcchnum,u8 dstchnum, u8 intr_en)
{
	channel0_ctl(1, intr_en, 0, 0, 0, 0, 0, 2, 2, 2);
    channel0_cfg(srcchnum, dstchnum, 0, 0);
}

//channel 1
void channel1_disable(){
    DMA_CFG1L |= (1<<8);                             // Set CH_SUSP Bit
    while((DMA_CFG1L & (1<<9)) == 0);                // Wait for FIFO Empty
    DMA_ChEnRegL = DMA_ChEnRegL & ~(1<<1) | (1<<9);  // Clear CH_EN
    DMA_CFG1L &= ~(1<<8);
}

void channel1_ctl(u8 tt_fc,        u8 intr_en,
                  u8 src_itf,      u8 dst_itf,
                  u8 src_msize,    u8 dst_msize,
                  u8 src_adr_mode, u8 dst_adr_mode,
                  u8 src_tr_width, u8 dst_tr_width
                  ){
  	DMA_CTL1L  = ((tt_fc&0x7)<<20)       | ((intr_en&0x01)<<0) |
                 //((src_llp_en&0x01)<<28) | ((dst_llp_en&0x01)<<27) |
				 ((0 & 0x01)<<28) | ((0 & 0x01)<<27) |
                 ((src_itf&0x3)<<25)     | ((dst_itf&0x3)<<23) |
                 //((src_gat_en&0x01)<<17) | ((dst_sat_en&0x01)<<18) |
				 ((0 & 0x01)<<17) | ((0 & 0x01)<<18) |
                 ((src_msize&0x7)<<14)   | ((dst_msize&0x7)<<11) |
                 ((src_adr_mode&0x3)<<9) | ((dst_adr_mode&0x03)<<7) |
                 ((src_tr_width&0x7)<<4) | ((dst_tr_width&0x7)<<1);
    DMA_LLP1L  = 0;
}

void channel1_cfg(u8 src_hs_ch,    u8 dst_hs_ch,
                  u8 src_hs_sel,   u8 dst_hs_sel
                 ){
	DMA_CFG1H  = ((src_hs_ch&0xf)<<7)  | ((dst_hs_ch&0xf)<<11) |
                 ((0&0x1)<<6) | ((0&0x1)<<5) |
                 ((0&0x7)<<2) | ((1&0x01)<<1) |    //FIFO MODE
                 (0&0x01);
	DMA_CFG1L  = ((0&0x1)<<30)   | ((0&0x1)<<31) |
                 ((0&0x3ff)<<20) |
                 ((0&0x1)<<19)   | ((0&0x1)<<18) |
                 ((0&0x1)<<17)   | ((0&0x1)<<16) |
                 ((0&0x3)<<14)   | ((0&0x3)<<12) |
                 ((src_hs_sel&0x1)<<11)  | ((dst_hs_sel&0x1)<<10) |
                 ((0&0x1)<<8)    | ((0&0x7)<<5);
}

void channel1_trans_start(u32 srcadr, u32 dstadr, u16 trans_blk){
     DMA_SAR1L = srcadr;
     DMA_DAR1L = dstadr;
     DMA_CTL1H = trans_blk;
     dmac_channel_enable(1);
}

void gpdma_channel1_mem2peri(u8 srcchnum,u8 dstchnum, u8 intr_en){
    //FC = PERI
    channel1_ctl(6, intr_en, 0, 1, 1, 0, 0, 2, 2, 2);
    channel1_cfg(srcchnum, dstchnum, 0, 0);
}

//channel 2
void channel2_disable(){
    DMA_CFG2L |= (1<<8);                              // Set CH_SUSP Bit
    while((DMA_CFG2L & (1<<9)) == 0);                 // Wait for FIFO Empty
    DMA_ChEnRegL = DMA_ChEnRegL & ~(1<<2) | (1<<10);  // Clear CH_EN
    DMA_CFG1L &= ~(1<<8);
}

void channel2_ctl(u8 tt_fc,        u8 intr_en,
                  u8 src_itf,      u8 dst_itf,
                  u8 src_msize,    u8 dst_msize,
                  u8 src_adr_mode, u8 dst_adr_mode,
                  u8 src_tr_width, u8 dst_tr_width
                  ){
  	DMA_CTL2L  = ((tt_fc&0x7)<<20)       | ((intr_en&0x01)<<0) |
                 //((src_llp_en&0x01)<<28) | ((dst_llp_en&0x01)<<27) |
				 ((0 & 0x01)<<28) | ((0 & 0x01)<<27) |
                 ((src_itf&0x3)<<25)     | ((dst_itf&0x3)<<23) |
                 //((src_gat_en&0x01)<<17) | ((dst_sat_en&0x01)<<18) |
				 ((0 & 0x01)<<17) | ((0 & 0x01)<<18) |
                 ((src_msize&0x7)<<14)   | ((dst_msize&0x7)<<11) |
                 ((src_adr_mode&0x3)<<9) | ((dst_adr_mode&0x03)<<7) |
                 ((src_tr_width&0x7)<<4) | ((dst_tr_width&0x7)<<1);
    DMA_LLP2L  = 0;
}

void channel2_cfg(u8 src_hs_ch,    u8 dst_hs_ch,
                  u8 src_hs_sel,   u8 dst_hs_sel
                 ){
	DMA_CFG2H  = ((src_hs_ch&0xf)<<7)  | ((dst_hs_ch&0xf)<<11) |
                 ((0&0x1)<<6) | ((0&0x1)<<5) |
                 ((0&0x7)<<2) | ((1&0x01)<<1) | //FIFO MODE
                 (0&0x01);
	DMA_CFG2L  = ((0&0x1)<<30)   | ((0&0x1)<<31) |
                 ((0&0x3ff)<<20) |
                 ((0&0x1)<<19)   | ((0&0x1)<<18) |
                 ((0&0x1)<<17)   | ((0&0x1)<<16) |
                 ((0&0x3)<<14)   | ((0&0x3)<<12) |
                 ((src_hs_sel&0x1)<<11)  | ((dst_hs_sel&0x1)<<10) |
                 ((0&0x1)<<8)    | ((0&0x7)<<5);
}

void channel2_trans_start(u32 srcadr, u32 dstadr, u16 trans_blk){
     DMA_SAR2L = srcadr;
     DMA_DAR2L = dstadr;
     DMA_CTL2H = trans_blk;
     dmac_channel_enable(2);
}

void gpdma_channel2_peri2mem(u8 srcchnum,u8 dstchnum, u8 intr_en){
    //FC = PERI
    channel2_ctl(4, intr_en, 1, 0, 0, 1, 2, 0, 2, 2);
    channel2_cfg(srcchnum, dstchnum, 0, 0);
}

void gpdma_channel2_mem2peri(u8 srcchnum,u8 dstchnum, u8 intr_en){
    //FC = PERI
    channel2_ctl(6, intr_en, 0, 1, 1, 0, 0, 2, 2, 2);
    channel2_cfg(srcchnum, dstchnum, 0, 0);
}

//channel 3
void channel3_disable(){
    DMA_CFG3L |= (1<<8);                              // Set CH_SUSP Bit
    while((DMA_CFG3L & (1<<9)) == 0);                 // Wait for FIFO Empty
    DMA_ChEnRegL = DMA_ChEnRegL & ~(1<<3) | (1<<11);  // Clear CH_EN
    DMA_CFG3L &= ~(1<<8);
}

void channel3_ctl(u8 tt_fc,        u8 intr_en,
                  u8 src_itf,      u8 dst_itf,
                  u8 src_msize,    u8 dst_msize,
                  u8 src_adr_mode, u8 dst_adr_mode,
                  u8 src_tr_width, u8 dst_tr_width
                  ){
  	DMA_CTL3L  = ((tt_fc&0x7)<<20)       | ((intr_en&0x01)<<0) |
                 //((src_llp_en&0x01)<<28) | ((dst_llp_en&0x01)<<27) |
				 ((0 & 0x01)<<28) | ((0 & 0x01)<<27) |
                 ((src_itf&0x3)<<25)     | ((dst_itf&0x3)<<23) |
                 //((src_gat_en&0x01)<<17) | ((dst_sat_en&0x01)<<18) |
				 ((0 & 0x01)<<17) | ((0 & 0x01)<<18) |
                 ((src_msize&0x7)<<14)   | ((dst_msize&0x7)<<11) |
                 ((src_adr_mode&0x3)<<9) | ((dst_adr_mode&0x03)<<7) |
                 ((src_tr_width&0x7)<<4) | ((dst_tr_width&0x7)<<1);
    DMA_LLP3L  = 0;
}

void channel3_cfg(u8 src_hs_ch,    u8 dst_hs_ch,
                  u8 src_hs_sel,   u8 dst_hs_sel
                 ){
	DMA_CFG3H  = ((src_hs_ch&0xf)<<7)  | ((dst_hs_ch&0xf)<<11) |
                 ((0&0x1)<<6) | ((0&0x1)<<5) |
                 ((0&0x7)<<2) | ((1&0x01)<<1) | //FIFO Mode
                 (0&0x01);
	DMA_CFG3L  = ((0&0x1)<<30)   | ((0&0x1)<<31) |
                 ((0&0x3ff)<<20) |
                 ((0&0x1)<<19)   | ((0&0x1)<<18) |
                 ((0&0x1)<<17)   | ((0&0x1)<<16) |
                 ((0&0x3)<<14)   | ((0&0x3)<<12) |
                 ((src_hs_sel&0x1)<<11)  | ((dst_hs_sel&0x1)<<10) |
                 ((0&0x1)<<8)    | ((0&0x7)<<5);
}

void channel3_trans_start(u32 srcadr, u32 dstadr, u16 trans_blk){
     DMA_SAR3L = srcadr;
     DMA_DAR3L = dstadr;
     DMA_CTL3H = trans_blk;
     dmac_channel_enable(3);
}

void gpdma_channel3_peri2mem(u8 srcchnum,u8 dstchnum, u8 intr_en){
    channel3_ctl(2, intr_en, 1, 0, 0, 1, 2, 0, 2, 2);
    channel3_cfg(srcchnum, dstchnum, 0, 0);
}

//channel 4
void channel4_disable(){
    DMA_CFG4L |= (1<<8);                              // Set CH_SUSP Bit
    while((DMA_CFG4L & (1<<9)) == 0);                 // Wait for FIFO Empty
    DMA_ChEnRegL = DMA_ChEnRegL & ~(1<<4) | (1<<12);  // Clear CH_EN
    DMA_CFG4L &= ~(1<<8);
}

void channel4_ctl(u8 tt_fc,        u8 intr_en,
                  u8 src_itf,      u8 dst_itf,
                  u8 src_msize,    u8 dst_msize,
                  u8 src_adr_mode, u8 dst_adr_mode,
                  u8 src_tr_width, u8 dst_tr_width
                 ){
	DMA_CTL4L  = ((tt_fc&0x7)<<20)       | ((intr_en&0x01)<<0) |
                 //((src_llp_en&0x01)<<28) | ((dst_llp_en&0x01)<<27) |
				 ((0 & 0x01)<<28) | ((0 & 0x01)<<27) |
                 ((src_itf&0x3)<<25)     | ((dst_itf&0x3)<<23) |
                 //((src_gat_en&0x01)<<17) | ((dst_sat_en&0x01)<<18) |
				 ((0 & 0x01)<<17) | ((0 & 0x01)<<18) |
                 ((src_msize&0x7)<<14)   | ((dst_msize&0x7)<<11) |
                 ((src_adr_mode&0x3)<<9) | ((dst_adr_mode&0x03)<<7) |
                 ((src_tr_width&0x7)<<4) | ((dst_tr_width&0x7)<<1);
    DMA_LLP4L  = 0;
}

void channel4_cfg(u8 src_hs_ch,    u8 dst_hs_ch,
                  u8 src_hs_sel,   u8 dst_hs_sel
                 ){
	DMA_CFG4H  = ((src_hs_ch&0xf)<<7)  | ((dst_hs_ch&0xf)<<11) |
                 ((0&0x1)<<6) | ((0&0x1)<<5) |
                 ((0&0x7)<<2)    | ((1&0x01)<<1) |  //FIFO MODE
                 (0&0x01);
	DMA_CFG4L  = ((0&0x1)<<30)   | ((0&0x1)<<31) |
                 ((0&0x3ff)<<20) |
                 ((0&0x1)<<19)   | ((0&0x1)<<18) |
                 ((0&0x01)<<17)  | ((0&0x1)<<16) |
                 ((0&0x3)<<14)   | ((0&0x3)<<12) |
                 ((src_hs_sel&0x1)<<11)  | ((dst_hs_sel&0x1)<<10) |
                 ((0&0x1)<<8)    | ((0&0x7)<<5);
}

void channel4_trans_start(u32 srcadr, u32 dstadr, u16 trans_blk)
{
     DMA_SAR4L = srcadr;
     DMA_DAR4L = dstadr;
     DMA_CTL4H = trans_blk;
     dmac_channel_enable(4);
}

void channel4_llp_cfg(u32 sar, u32 dar, u32 ctl_L, u32 ctl_H,
                      u32 llp_cur_adr, u32 llp_nxt_adr)
{
    u32 *llp_adr;
     llp_adr   = llp_cur_adr;   // LLP.LLP_CUR_ADR
    *llp_adr++ = sar;           // LLP.SAR
    *llp_adr++ = dar;           // LLP.DAR
    *llp_adr++ = llp_nxt_adr;   // LLP.LLP_NXT_ADR
    *llp_adr++ = ctl_L;         // LLP.CTL_L
    *llp_adr++ = ctl_H;         // LLP.CTL_H
}

void channel4_llp_enable(u8 src_hs_ch, u8 dst_hs_ch, u32 llp_cur_adr){
    DMA_CFG4H = (src_hs_ch<<7) | (dst_hs_ch<<11); //SET CHannel 4 handshake channel num
    DMA_CFG4L = 0;
    DMA_CTL4L = (0<<25) | (1<<23);  //SRC SEL M1,DST SEL M2
    DMA_CTL4L = (1<<28) | (1<<27);  //SRC LLP ENABLE,and DST LLP ENABLE
    //DMA_LLP4L = llp_cur_adr & 0xfffffff3;
    DMA_LLP4L = llp_cur_adr & 0xfffffffC;
	dmac_channel_enable(4);
}

void gpdma_channel4_peri2mem(u8 srcchnum,u8 dstchnum, u8 intr_en){
    //FC = PERI
    channel4_ctl(4, intr_en, 1, 0, 0, 1, 2, 0, 2, 2);
    channel4_cfg(srcchnum, dstchnum, 0, 0);
}

void gpdma_ch4_llp(u32 sar0, u32 dst0, u32 ctl0_L, u32 ctl0_H,
                   u32 sar1, u32 dst1, u32 ctl1_L, u32 ctl1_H,
                   u32 sram_adr) {
    // the first link
    channel4_llp_cfg(sar0, dst0, ctl0_L, ctl0_H, sram_adr, sram_adr+28);
    // the second link
    channel4_llp_cfg(sar1, dst1, ctl1_L, ctl1_H, sram_adr+28, sram_adr);
}
#endif
//channel 5
void channel5_disable(void){
    REG32(DMA_CFG5L) |= (1<<8);                              // Set CH_SUSP Bit
    while((REG32(DMA_CFG5L) & (1<<9)) == 0);                 // Wait for FIFO Empty
    REG32(DMA_ChEnRegL) = (REG32(DMA_ChEnRegL) & (~(1<<5))) | (1<<13);  // Clear CH_EN
    REG32(DMA_CFG5L) &= ~(1<<8);
}

void channel5_ctl(u8 tt_fc,        u8 intr_en,
                  u8 src_itf,      u8 dst_itf,
                  u8 src_msize,    u8 dst_msize,
                  u8 src_adr_mode, u8 dst_adr_mode,
                  u8 src_tr_width, u8 dst_tr_width
                 ){
	REG32(DMA_CTL5L)  = ((tt_fc&0x7)<<20)       | ((intr_en&0x01)<<0) |
                 //((src_llp_en&0x01)<<28) | ((dst_llp_en&0x01)<<27) |
				 ((0 & 0x01)<<28) | ((0 & 0x01)<<27) |
                 ((src_itf&0x3)<<25)     | ((dst_itf&0x3)<<23) |
                 //((src_gat_en&0x01)<<17) | ((dst_sat_en&0x01)<<18) |
				 ((0 & 0x01)<<17) | ((0 & 0x01)<<18) |
                 ((src_msize&0x7)<<14)   | ((dst_msize&0x7)<<11) |
                 ((src_adr_mode&0x3)<<9) | ((dst_adr_mode&0x03)<<7) |
                 ((src_tr_width&0x7)<<4) | ((dst_tr_width&0x7)<<1);
	REG32(DMA_LLP5L)  = 0;
}

void channel5_cfg(u8 src_hs_ch,    u8 dst_hs_ch,
                  u8 src_hs_sel,   u8 dst_hs_sel,
                  u8 src_reload,   u8 dst_reload
                 ){
	REG32(DMA_CFG5H)  = ((src_hs_ch&0xf)<<7)  | ((dst_hs_ch&0xf)<<11) |
                 ((0&0x1)<<6) | ((0&0x1)<<5) |
                 ((0&0x7)<<2)    | ((1&0x01)<<1) |  //FIFO MODE
                 (0&0x01);
	REG32(DMA_CFG5L)  = ((src_reload&0x1)<<30) | ((dst_reload&0x1)<<31) |
                 ((0&0x3ff)<<20) |
                 ((0&0x1)<<19)   | ((0&0x1)<<18) |
                 ((0&0x01)<<17)  | ((0&0x1)<<16) |
                 ((0&0x3)<<14)   | ((0&0x3)<<12) |
                 ((src_hs_sel&0x1)<<11)  | ((dst_hs_sel&0x1)<<10) |
                 ((0&0x1)<<8)    | ((0&0x7)<<5);
}

void channel5_trans_start(u32 srcadr, u32 dstadr, u16 trans_blk){
	REG32(DMA_SAR5L) = srcadr;
	REG32(DMA_DAR5L) = dstadr;
	REG32(DMA_CTL5H) = trans_blk;
    dmac_channel_enable(5);
}

void channel5_llp_cfg(u32 sar, u32 dar, u32 ctl_L, u32 ctl_H,
                      u32 llp_cur_adr, u32 llp_nxt_adr){
    u32 *llp_adr;
     llp_adr   = (u32 *)llp_cur_adr;   // LLP.LLP_CUR_ADR
    *llp_adr++ = sar;           // LLP.SAR
    *llp_adr++ = dar;           // LLP.DAR
    *llp_adr++ = llp_nxt_adr;   // LLP.LLP_NXT_ADR
    *llp_adr++ = ctl_L;         // LLP.CTL_L
    *llp_adr++ = ctl_H;         // LLP.CTL_H
}

void channel5_llp_enable(u8 src_hs_ch, u8 dst_hs_ch, u32 llp_cur_adr){
	REG32(DMA_CFG5H) = (src_hs_ch<<7) | (dst_hs_ch<<11);
	REG32(DMA_CFG5L) = 0;
    //DMA_CTL4L = (1<<25) | (0<<23);  //SRC SEL M2,DST SEL M1
	REG32(DMA_CTL5L) = (1<<28) | (1<<27);
	REG32(DMA_LLP5L) = llp_cur_adr & 0xfffffffC;
	dmac_channel_enable(5);
}

void gpdma_channel5_mem2mem(u8 srcchnum,u8 dstchnum, u8 intr_en)
{
    channel5_ctl(0, intr_en, 0, 0, 1, 1, 0, 0, 2, 2);
    channel5_cfg(srcchnum, dstchnum, 0, 0, 0, 0);
}

void gpdma_ch5_llp(u32 sar0, u32 dst0, u32 ctl0_L, u32 ctl0_H,
                   u32 sar1, u32 dst1, u32 ctl1_L, u32 ctl1_H,
                   u32 sram_adr) {
    // the first link
    channel5_llp_cfg(sar0, dst0, ctl0_L, ctl0_H, sram_adr, sram_adr+28);
    // the second link
    channel5_llp_cfg(sar1, dst1, ctl1_L, ctl1_H, sram_adr+28, sram_adr);
}



//----------------------------------------------------
/*void dma_peri2mem(ch, cfgh, cfgl, sar, dar, cnt)
{
volatile unsigned long *reg = (volatile unsigned long *)((ch)*0x58 + DMA_BASE);
DMA_CfgRegL     = 1;
reg[OFFS_CTLnL] = (4<<20) | (2<<9) | (2<<4) | (2<<1) | (1<<25);
reg[OFFS_LLPnL] = 0;
reg[OFFS_CFGnH] = cfgh;
reg[OFFS_CFGnL] = cfgl;
reg[OFFS_SARnL] = sar;
reg[OFFS_DARnL] = (u32)dar;
reg[OFFS_CTLnH] = cnt;
DMA_ChEnRegL   |= (1<<(ch+8)) | (1<<ch);
}

void dma_mem2peri(ch, cfgh, cfgl, sar, dar, cnt)
{
 volatile unsigned long *reg = (volatile unsigned long *)((ch)*0x58 + DMA_BASE);
 DMA_CfgRegL     = 1;
 reg[OFFS_CTLnL] = (6<<20) | (2<<7) | (2<<4) | (2<<1) | (1<<23);
 reg[OFFS_LLPnL] = 0;
 reg[OFFS_CFGnH] = cfgh;
 reg[OFFS_CFGnL] = cfgl;
 reg[OFFS_SARnL] = (u32)sar;
 reg[OFFS_DARnL] = dar;
 reg[OFFS_CTLnH] = cnt;
 DMA_ChEnRegL   |= (1<<(ch+8)) | (1<<ch);
}
*/
void dma_peri2mem(u8 ch, u32 cfgh, u32 cfgl, u32 sar, u32 dar, u16 cnt)
{
	u32 offset;
	offset = ch*0x58;
	dmac_channel_disable(ch);
	REG32(DMA_CfgRegL)     = 1;
	REG32(DMA_CTL0L + offset) = (4<<20) | (2<<9) | (2<<4) | (2<<1) | (1<<25);
	REG32(DMA_LLP0L + offset) = 0;
	REG32(DMA_CFG0H + offset) = cfgh;
	REG32(DMA_CFG0L + offset) = cfgl;
	REG32(DMA_SAR0L + offset) = sar;
	REG32(DMA_DAR0L + offset) = (u32)dar;
	REG32(DMA_CTL0H + offset) = cnt;
	REG32(DMA_ChEnRegL)   |= (1<<(ch+8)) | (1<<ch);
}

void dma_mem2peri(u8 ch, u32 cfgh, u32 cfgl, u32 sar, u32 dar, u16 cnt)
{
	u32 offset;
	offset = ch*0x58;
	dmac_channel_disable(ch);
	REG32(DMA_CfgRegL)     = 1;
	REG32(DMA_CTL0L + offset) = (1<<20) | (2<<7) | (2<<4) | (2<<1) | (1<<23);
	REG32(DMA_LLP0L + offset) = 0;
	REG32(DMA_CFG0H + offset) = cfgh;
	REG32(DMA_CFG0L + offset) = cfgl;
	REG32(DMA_SAR0L + offset) = sar;
	REG32(DMA_DAR0L + offset) = dar;
	REG32(DMA_CTL0H + offset) = cnt;
	REG32(DMA_ChEnRegL)   |= (1<<(ch+8)) | (1<<ch);
}

void llp_peri2mem(u8 ch, u32 cfgh, u32 cfgl, DMA_LLP *llp)
{
	u32 offset;
	offset = ch*0x58;
	dmac_channel_disable(ch);
	REG32(DMA_CfgRegL)     = 1;

	REG32(DMA_CTL0L + offset) = (1<<28) | (1<<27);
	REG32(DMA_LLP0L + offset) = (u32)(llp) & 0xFFFFFFFC;
	REG32(DMA_CFG0H + offset) = cfgh;
	REG32(DMA_CFG0L + offset) = cfgl;
	REG32(DMA_ChEnRegL)   |= (1<<(ch+8)) | (1<<ch);
}

void dma_peri2mem_Ext(u8 ch, u32 cfgh, u32 cfgl, u32 sar, u32 dar, u16 cnt)
{
	u32 offset;
	offset = ch*0x58;
	dmac_channel_disable(ch);
	REG32(DMA_CfgRegL)     = 1;
	REG32(DMA_CTL0L + offset) = (2<<20) | (2<<9) | (2<<4) | (2<<1) | (1<<25)|(1<<0);
	REG32(DMA_LLP0L + offset) = 0;
	REG32(DMA_CFG0H + offset) = cfgh;
	REG32(DMA_CFG0L + offset) = cfgl;
	REG32(DMA_SAR0L + offset) = sar;
	REG32(DMA_DAR0L + offset) = (u32)dar;
	REG32(DMA_CTL0H + offset) = cnt;
	REG32(DMA_ChEnRegL)   |= (1<<(ch+8)) | (1<<ch);
}

void gpdma_Isr(void)
{
	u32 u32StatusIntL,u32StatusTrfL;

	u32StatusIntL = REG32(DMA_StatusIntL);
	if((u32StatusIntL & 0x1) == 0x1)
	{
		u32StatusTrfL = REG32(DMA_StatusTfrL);
		if((u32StatusTrfL & 0x8) == 0x8)
		{
			REG32(DMA_ClearTfrL) = BIT(3);
			audio_AGC_DMA_Isr();
		}
		else
		{
			
		}
	}
	else
	{
		
	}
}
