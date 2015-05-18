#ifndef _HUNTER_H_
#define _HUNTER_H_

#define SFR_AT *(volatile unsigned long*)
#define SFR_8_AT *(volatile unsigned char*)

// AHB_DMA
#define DMA_BASE                0x14030000

#define DMA_SAR0L                (DMA_BASE + (0x00 << 3))
#define DMA_DAR0L                (DMA_BASE + (0x01 << 3))
#define DMA_LLP0L                (DMA_BASE + (0x02 << 3))
#define DMA_CTL0L                (DMA_BASE + (0x03 << 3))
#define DMA_SSTAT0L              (DMA_BASE + (0x04 << 3))
#define DMA_DSTAT0L              (DMA_BASE + (0x05 << 3))
#define DMA_SSTATAR0L            (DMA_BASE + (0x06 << 3))
#define DMA_DSTATAR0L            (DMA_BASE + (0x07 << 3))
#define DMA_CFG0L                (DMA_BASE + (0x08 << 3))
#define DMA_SGR0L                (DMA_BASE + (0x09 << 3))
#define DMA_DSR0L                (DMA_BASE + (0x0a << 3))
#define DMA_SAR1L                (DMA_BASE + (0x0b << 3))
#define DMA_DAR1L                (DMA_BASE + (0x0c << 3))
#define DMA_LLP1L                (DMA_BASE + (0x0d << 3))
#define DMA_CTL1L                (DMA_BASE + (0x0e << 3))
#define DMA_SSTAT1L              (DMA_BASE + (0x0f << 3))
#define DMA_DSTAT1L              (DMA_BASE + (0x10 << 3))
#define DMA_SSTATAR1L            (DMA_BASE + (0x11 << 3))
#define DMA_DSTATAR1L            (DMA_BASE + (0x12 << 3))
#define DMA_CFG1L                (DMA_BASE + (0x13 << 3))
#define DMA_SGR1L                (DMA_BASE + (0x14 << 3))
#define DMA_DSR1L                (DMA_BASE + (0x15 << 3))
#define DMA_SAR2L                (DMA_BASE + (0x16 << 3))
#define DMA_DAR2L                (DMA_BASE + (0x17 << 3))
#define DMA_LLP2L                (DMA_BASE + (0x18 << 3))
#define DMA_CTL2L                (DMA_BASE + (0x19 << 3))
#define DMA_SSTAT2L              (DMA_BASE + (0x1a << 3))
#define DMA_DSTAT2L              (DMA_BASE + (0x1b << 3))
#define DMA_SSTATAR2L            (DMA_BASE + (0x1c << 3))
#define DMA_DSTATAR2L            (DMA_BASE + (0x1d << 3))
#define DMA_CFG2L                (DMA_BASE + (0x1e << 3))
#define DMA_SGR2L                (DMA_BASE + (0x1f << 3))
#define DMA_DSR2L                (DMA_BASE + (0x20 << 3))
#define DMA_SAR3L                (DMA_BASE + (0x21 << 3))
#define DMA_DAR3L                (DMA_BASE + (0x22 << 3))
#define DMA_LLP3L                (DMA_BASE + (0x23 << 3))
#define DMA_CTL3L                (DMA_BASE + (0x24 << 3))
#define DMA_SSTAT3L              (DMA_BASE + (0x25 << 3))
#define DMA_DSTAT3L              (DMA_BASE + (0x26 << 3))
#define DMA_SSTATAR3L            (DMA_BASE + (0x27 << 3))
#define DMA_DSTATAR3L            (DMA_BASE + (0x28 << 3))
#define DMA_CFG3L                (DMA_BASE + (0x29 << 3))
#define DMA_SGR3L                (DMA_BASE + (0x2a << 3))
#define DMA_DSR3L                (DMA_BASE + (0x2b << 3))
#define DMA_SAR4L                (DMA_BASE + (0x2c << 3))
#define DMA_DAR4L                (DMA_BASE + (0x2d << 3))
#define DMA_LLP4L                (DMA_BASE + (0x2e << 3))
#define DMA_CTL4L                (DMA_BASE + (0x2f << 3))
#define DMA_SSTAT4L              (DMA_BASE + (0x30 << 3))
#define DMA_DSTAT4L              (DMA_BASE + (0x31 << 3))
#define DMA_SSTATAR4L            (DMA_BASE + (0x32 << 3))
#define DMA_DSTATAR4L            (DMA_BASE + (0x33 << 3))
#define DMA_CFG4L                (DMA_BASE + (0x34 << 3))
#define DMA_SGR4L                (DMA_BASE + (0x35 << 3))
#define DMA_DSR4L                (DMA_BASE + (0x36 << 3))
#define DMA_SAR5L                (DMA_BASE + (0x37 << 3))
#define DMA_DAR5L                (DMA_BASE + (0x38 << 3))
#define DMA_LLP5L                (DMA_BASE + (0x39 << 3))
#define DMA_CTL5L                (DMA_BASE + (0x3a << 3))
#define DMA_SSTAT5L              (DMA_BASE + (0x3b << 3))
#define DMA_DSTAT5L              (DMA_BASE + (0x3c << 3))
#define DMA_SSTATAR5L            (DMA_BASE + (0x3d << 3))
#define DMA_DSTATAR5L            (DMA_BASE + (0x3e << 3))
#define DMA_CFG5L                (DMA_BASE + (0x3f << 3))
#define DMA_SGR5L                (DMA_BASE + (0x40 << 3))
#define DMA_DSR5L                (DMA_BASE + (0x41 << 3))
#define DMA_SAR6L                (DMA_BASE + (0x42 << 3))
#define DMA_DAR6L                (DMA_BASE + (0x43 << 3))
#define DMA_LLP6L                (DMA_BASE + (0x44 << 3))
#define DMA_CTL6L                (DMA_BASE + (0x45 << 3))
#define DMA_SSTAT6L              (DMA_BASE + (0x46 << 3))
#define DMA_DSTAT6L              (DMA_BASE + (0x47 << 3))
#define DMA_SSTATAR6L            (DMA_BASE + (0x48 << 3))
#define DMA_DSTATAR6L            (DMA_BASE + (0x49 << 3))
#define DMA_CFG6L                (DMA_BASE + (0x4a << 3))
#define DMA_SGR6L                (DMA_BASE + (0x4b << 3))   
#define DMA_DSR6L                (DMA_BASE + (0x4c << 3))
#define DMA_SAR7L                (DMA_BASE + (0x4d << 3))
#define DMA_DAR7L                (DMA_BASE + (0x4e << 3))
#define DMA_CTL7L                (DMA_BASE + (0x50 << 3))
#define DMA_LLP7L                (DMA_BASE + (0x4f << 3))
#define DMA_SSTAT7L              (DMA_BASE + (0x51 << 3))
#define DMA_DSTAT7L              (DMA_BASE + (0x52 << 3))
#define DMA_SSTATAR7L            (DMA_BASE + (0x53 << 3))
#define DMA_DSTATAR7L            (DMA_BASE + (0x54 << 3))
#define DMA_CFG7L                (DMA_BASE + (0x55 << 3))
#define DMA_SGR7L                (DMA_BASE + (0x56 << 3))
#define DMA_DSR7L                (DMA_BASE + (0x57 << 3))
#define DMA_RawTfrL              (DMA_BASE + (0x58 << 3))
#define DMA_RawBlockL            (DMA_BASE + (0x59 << 3))
#define DMA_RawSrcTranL          (DMA_BASE + (0x5a << 3))
#define DMA_RawDstTranL          (DMA_BASE + (0x5b << 3))
#define DMA_RawErrL              (DMA_BASE + (0x5c << 3))
#define DMA_StatusTfrL           (DMA_BASE + (0x5d << 3))
#define DMA_StatusBlockL         (DMA_BASE + (0x5e << 3))
#define DMA_StatusSrcTranL       (DMA_BASE + (0x5f << 3))
#define DMA_StatusDstTranL       (DMA_BASE + (0x60 << 3))
#define DMA_StatusErrL           (DMA_BASE + (0x61 << 3))
#define DMA_MaskTfrL             (DMA_BASE + (0x62 << 3))
#define DMA_MaskBlockL           (DMA_BASE + (0x63 << 3))
#define DMA_MaskSrcTranL         (DMA_BASE + (0x64 << 3))
#define DMA_MaskDstTranL         (DMA_BASE + (0x65 << 3))
#define DMA_MaskErrL             (DMA_BASE + (0x66 << 3))
#define DMA_ClearTfrL            (DMA_BASE + (0x67 << 3))
#define DMA_ClearBlockL          (DMA_BASE + (0x68 << 3))
#define DMA_ClearSrcTranL        (DMA_BASE + (0x69 << 3))
#define DMA_ClearDstTranL        (DMA_BASE + (0x6a << 3))
#define DMA_ClearErrL            (DMA_BASE + (0x6b << 3))
#define DMA_StatusIntL           (DMA_BASE + (0x6c << 3))
#define DMA_ReqSrcRegL           (DMA_BASE + (0x6d << 3))
#define DMA_ReqDstRegL           (DMA_BASE + (0x6e << 3))
#define DMA_SglReqSrcRegL        (DMA_BASE + (0x6f << 3))
#define DMA_SglReqDstRegL        (DMA_BASE + (0x70 << 3))
#define DMA_LstSrcRegL           (DMA_BASE + (0x71 << 3))
#define DMA_LstDstRegL           (DMA_BASE + (0x72 << 3))
#define DMA_CfgRegL              (DMA_BASE + (0x73 << 3))
#define DMA_ChEnRegL             (DMA_BASE + (0x74 << 3))
#define DMA_DmaIdRegL            (DMA_BASE + (0x75 << 3))
#define DMA_DmaTestRegL          (DMA_BASE + (0x76 << 3))
#define DMA_COMP_PARAMS_6L       (DMA_BASE + (0x79 << 3))
#define DMA_COMP_PARAMS_5L       (DMA_BASE + (0x7a << 3))
#define DMA_COMP_PARAMS_4L       (DMA_BASE + (0x7b << 3))
#define DMA_COMP_PARAMS_3L       (DMA_BASE + (0x7c << 3))
#define DMA_COMP_PARAMS_2L       (DMA_BASE + (0x7d << 3))
#define DMA_COMP_PARAMS_1L       (DMA_BASE + (0x7e << 3))
#define DMA_ComponentIDL         (DMA_BASE + (0x7f << 3))

#define DMA_SAR0H                (DMA_BASE + (0x00 << 3)+4)
#define DMA_DAR0H                (DMA_BASE + (0x01 << 3)+4)
#define DMA_LLP0H                (DMA_BASE + (0x02 << 3)+4)
#define DMA_CTL0H                (DMA_BASE + (0x03 << 3)+4)
#define DMA_SSTAT0H              (DMA_BASE + (0x04 << 3)+4)
#define DMA_DSTAT0H              (DMA_BASE + (0x05 << 3)+4)
#define DMA_SSTATAR0H            (DMA_BASE + (0x06 << 3)+4)
#define DMA_DSTATAR0H            (DMA_BASE + (0x07 << 3)+4)
#define DMA_CFG0H                (DMA_BASE + (0x08 << 3)+4)
#define DMA_SGR0H                (DMA_BASE + (0x09 << 3)+4)
#define DMA_DSR0H                (DMA_BASE + (0x0a << 3)+4)
#define DMA_SAR1H                (DMA_BASE + (0x0b << 3)+4)
#define DMA_DAR1H                (DMA_BASE + (0x0c << 3)+4)
#define DMA_LLP1H                (DMA_BASE + (0x0d << 3)+4)
#define DMA_CTL1H                (DMA_BASE + (0x0e << 3)+4)
#define DMA_SSTAT1H              (DMA_BASE + (0x0f << 3)+4)
#define DMA_DSTAT1H              (DMA_BASE + (0x10 << 3)+4)
#define DMA_SSTATAR1H            (DMA_BASE + (0x11 << 3)+4)
#define DMA_DSTATAR1H            (DMA_BASE + (0x12 << 3)+4)
#define DMA_CFG1H                (DMA_BASE + (0x13 << 3)+4)
#define DMA_SGR1H                (DMA_BASE + (0x14 << 3)+4)
#define DMA_DSR1H                (DMA_BASE + (0x15 << 3)+4)
#define DMA_SAR2H                (DMA_BASE + (0x16 << 3)+4)
#define DMA_DAR2H                (DMA_BASE + (0x17 << 3)+4)
#define DMA_LLP2H                (DMA_BASE + (0x18 << 3)+4)
#define DMA_CTL2H                (DMA_BASE + (0x19 << 3)+4)
#define DMA_SSTAT2H              (DMA_BASE + (0x1a << 3)+4)
#define DMA_DSTAT2H              (DMA_BASE + (0x1b << 3)+4)
#define DMA_SSTATAR2H            (DMA_BASE + (0x1c << 3)+4)
#define DMA_DSTATAR2H            (DMA_BASE + (0x1d << 3)+4)
#define DMA_CFG2H                (DMA_BASE + (0x1e << 3)+4)
#define DMA_SGR2H                (DMA_BASE + (0x1f << 3)+4)
#define DMA_DSR2H                (DMA_BASE + (0x20 << 3)+4)
#define DMA_SAR3H                (DMA_BASE + (0x21 << 3)+4)
#define DMA_DAR3H                (DMA_BASE + (0x22 << 3)+4)
#define DMA_LLP3H                (DMA_BASE + (0x23 << 3)+4)
#define DMA_CTL3H                (DMA_BASE + (0x24 << 3)+4)
#define DMA_SSTAT3H              (DMA_BASE + (0x25 << 3)+4)
#define DMA_DSTAT3H              (DMA_BASE + (0x26 << 3)+4)
#define DMA_SSTATAR3H            (DMA_BASE + (0x27 << 3)+4)
#define DMA_DSTATAR3H            (DMA_BASE + (0x28 << 3)+4)
#define DMA_CFG3H                (DMA_BASE + (0x29 << 3)+4)
#define DMA_SGR3H                (DMA_BASE + (0x2a << 3)+4)
#define DMA_DSR3H                (DMA_BASE + (0x2b << 3)+4)
#define DMA_SAR4H                (DMA_BASE + (0x2c << 3)+4)
#define DMA_DAR4H                (DMA_BASE + (0x2d << 3)+4)
#define DMA_LLP4H                (DMA_BASE + (0x2e << 3)+4)
#define DMA_CTL4H                (DMA_BASE + (0x2f << 3)+4)
#define DMA_SSTAT4H              (DMA_BASE + (0x30 << 3)+4)
#define DMA_DSTAT4H              (DMA_BASE + (0x31 << 3)+4)
#define DMA_SSTATAR4H            (DMA_BASE + (0x32 << 3)+4)
#define DMA_DSTATAR4H            (DMA_BASE + (0x33 << 3)+4)
#define DMA_CFG4H                (DMA_BASE + (0x34 << 3)+4)
#define DMA_SGR4H                (DMA_BASE + (0x35 << 3)+4)
#define DMA_DSR4H                (DMA_BASE + (0x36 << 3)+4)
#define DMA_SAR5H                (DMA_BASE + (0x37 << 3)+4)
#define DMA_DAR5H                (DMA_BASE + (0x38 << 3)+4)
#define DMA_LLP5H                (DMA_BASE + (0x39 << 3)+4)
#define DMA_CTL5H                (DMA_BASE + (0x3a << 3)+4)
#define DMA_SSTAT5H              (DMA_BASE + (0x3b << 3)+4)
#define DMA_DSTAT5H              (DMA_BASE + (0x3c << 3)+4)
#define DMA_SSTATAR5H            (DMA_BASE + (0x3d << 3)+4)
#define DMA_DSTATAR5H            (DMA_BASE + (0x3e << 3)+4)
#define DMA_CFG5H                (DMA_BASE + (0x3f << 3)+4)
#define DMA_SGR5H                (DMA_BASE + (0x40 << 3)+4)
#define DMA_DSR5H                (DMA_BASE + (0x41 << 3)+4)
#define DMA_SAR6H                (DMA_BASE + (0x42 << 3)+4)
#define DMA_DAR6H                (DMA_BASE + (0x43 << 3)+4)
#define DMA_LLP6H                (DMA_BASE + (0x44 << 3)+4)
#define DMA_CTL6H                (DMA_BASE + (0x45 << 3)+4)
#define DMA_SSTAT6H              (DMA_BASE + (0x46 << 3)+4)
#define DMA_DSTAT6H              (DMA_BASE + (0x47 << 3)+4)
#define DMA_SSTATAR6H            (DMA_BASE + (0x48 << 3)+4)
#define DMA_DSTATAR6H            (DMA_BASE + (0x49 << 3)+4)
#define DMA_CFG6H                (DMA_BASE + (0x4a << 3)+4)
#define DMA_SGR6H                (DMA_BASE + (0x4b << 3)+4)   
#define DMA_DSR6H                (DMA_BASE + (0x4c << 3)+4)
#define DMA_SAR7H                (DMA_BASE + (0x4d << 3)+4)
#define DMA_DAR7H                (DMA_BASE + (0x4e << 3)+4)
#define DMA_CTL7H                (DMA_BASE + (0x50 << 3)+4)
#define DMA_LLP7H                (DMA_BASE + (0x4f << 3)+4)
#define DMA_SSTAT7H              (DMA_BASE + (0x51 << 3)+4)
#define DMA_DSTAT7H              (DMA_BASE + (0x52 << 3)+4)
#define DMA_SSTATAR7H            (DMA_BASE + (0x53 << 3)+4)
#define DMA_DSTATAR7H            (DMA_BASE + (0x54 << 3)+4)
#define DMA_CFG7H                (DMA_BASE + (0x55 << 3)+4)
#define DMA_SGR7H                (DMA_BASE + (0x56 << 3)+4)
#define DMA_DSR7H                (DMA_BASE + (0x57 << 3)+4)
#define DMA_RawTfrH              (DMA_BASE + (0x58 << 3)+4)
#define DMA_RawBlockH            (DMA_BASE + (0x59 << 3)+4)
#define DMA_RawSrcTranH          (DMA_BASE + (0x5a << 3)+4)
#define DMA_RawDstTranH          (DMA_BASE + (0x5b << 3)+4)
#define DMA_RawErrH              (DMA_BASE + (0x5c << 3)+4)
#define DMA_StatusTfrH           (DMA_BASE + (0x5d << 3)+4)
#define DMA_StatusBlockH         (DMA_BASE + (0x5e << 3)+4)
#define DMA_StatusSrcTranH       (DMA_BASE + (0x5f << 3)+4)
#define DMA_StatusDstTranH       (DMA_BASE + (0x60 << 3)+4)
#define DMA_StatusErrH           (DMA_BASE + (0x61 << 3)+4)
#define DMA_MaskTfrH             (DMA_BASE + (0x62 << 3)+4)
#define DMA_MaskBlockH           (DMA_BASE + (0x63 << 3)+4)
#define DMA_MaskSrcTranH         (DMA_BASE + (0x64 << 3)+4)
#define DMA_MaskDstTranH         (DMA_BASE + (0x65 << 3)+4)
#define DMA_MaskErrH             (DMA_BASE + (0x66 << 3)+4)
#define DMA_ClearTfrH            (DMA_BASE + (0x67 << 3)+4)
#define DMA_ClearBlockH          (DMA_BASE + (0x68 << 3)+4)
#define DMA_ClearSrcTranH        (DMA_BASE + (0x69 << 3)+4)
#define DMA_ClearDstTranH        (DMA_BASE + (0x6a << 3)+4)
#define DMA_ClearErrH            (DMA_BASE + (0x6b << 3)+4)
#define DMA_StatusIntH           (DMA_BASE + (0x6c << 3)+4)
#define DMA_ReqSrcRegH           (DMA_BASE + (0x6d << 3)+4)
#define DMA_ReqDstRegH           (DMA_BASE + (0x6e << 3)+4)
#define DMA_SglReqSrcRegH        (DMA_BASE + (0x6f << 3)+4)
#define DMA_SglReqDstRegH        (DMA_BASE + (0x70 << 3)+4)
#define DMA_LstSrcRegH           (DMA_BASE + (0x71 << 3)+4)
#define DMA_LstDstRegH           (DMA_BASE + (0x72 << 3)+4)
#define DMA_CfgRegH              (DMA_BASE + (0x73 << 3)+4)
#define DMA_ChEnRegH             (DMA_BASE + (0x74 << 3)+4)
#define DMA_DmaIdRegH            (DMA_BASE + (0x75 << 3)+4)
#define DMA_DmaTestRegH          (DMA_BASE + (0x76 << 3)+4)
#define DMA_COMP_PARAMS_6H       (DMA_BASE + (0x79 << 3)+4)
#define DMA_COMP_PARAMS_5H       (DMA_BASE + (0x7a << 3)+4)
#define DMA_COMP_PARAMS_4H       (DMA_BASE + (0x7b << 3)+4)
#define DMA_COMP_PARAMS_3H       (DMA_BASE + (0x7c << 3)+4)
#define DMA_COMP_PARAMS_2H       (DMA_BASE + (0x7d << 3)+4)
#define DMA_COMP_PARAMS_1H       (DMA_BASE + (0x7e << 3)+4)
#define DMA_ComponentIDH         (DMA_BASE + (0x7f << 3)+4)


//------------------------------------------------------------------------------
// DMA ADDRESS REGISTER BASE
//------------------------------------------------------------------------------
#define DMA_ADR_BASE            0x14020000

//------------------------------------------------------------------------------
// DMA ADDRESS Configuration Register
//------------------------------------------------------------------------------
#define SPI0_DMA_TX_ADR        (DMA_ADR_BASE + 0x00)
#define SPI0_DMA_RX_ADR        (DMA_ADR_BASE + 0x04)
#define SPI1_DMA_TX_ADR        (DMA_ADR_BASE + 0x08)
#define SPI1_DMA_RX_ADR        (DMA_ADR_BASE + 0x0c)

#define SDC0_DMA_TX_ADR        (DMA_ADR_BASE + 0x10)
#define SDC0_DMA_RX_ADR        (DMA_ADR_BASE + 0x14)

#define SDC1_DMA_TX_ADR        (DMA_ADR_BASE + 0x18)
#define SDC1_DMA_RX_ADR        (DMA_ADR_BASE + 0x1c)

#define UART1_DMA_TX_ADR       (DMA_ADR_BASE + 0x20)
#define UART1_DMA_RX_ADR       (DMA_ADR_BASE + 0x24)
#define AUADC_DMA_TX_ADR       (DMA_ADR_BASE + 0x28)
#define DAC_DMA_RX_ADR         (DMA_ADR_BASE + 0x2c)
#define RGB_DMA_TX_ADR         (DMA_ADR_BASE + 0x30)
#define USB11_DMA_RX_ADR       (DMA_ADR_BASE + 0x34)
#define USB11_DMA_TX_ADR       (DMA_ADR_BASE + 0x38)
#define IIS_DMA_RX_ADR         (DMA_ADR_BASE + 0x3c)
#define IIS_DMA_TX_ADR         (DMA_ADR_BASE + 0x40)

//SDRAM
#define  SDR_CFG0               (DMA_ADR_BASE + 0xa0)
#define  SDR_CFG1               (DMA_ADR_BASE + 0xa4)
#define  SDR_REFT               (DMA_ADR_BASE + 0xa8)
#define  SDR_WBTO               (DMA_ADR_BASE + 0xac)

//------------------------------------------------------------------------------
// DAC, ADC, AGC Command Defines
//------------------------------------------------------------------------------
// For DAC
#define DACCFG                 0
#define DACSTA                 1
#define DACCLR                 2
#define DACVOL                 3
#define DACVCON                4
#define TRIMCON1               5
#define TRREGL                 6
#define TRREGR                 7
#define DACLRMIX0              8
#define DACLRMIX1              9
#define DACEQGAIN0             10
#define DACEQGAIN1             11
#define DACEQGAIN2             12
#define DACEQGAIN3             13
#define DACEQGAIN4             14
#define EQCOEFFADR             15
#define EQCOEFF                16

// For ADC
#define AUADC_CFG              20
#define AUADC_BAUD             21
#define AUADC_DAT              22

// For AGC
#define AGC_CFG0               25
#define AGC_CFG1               26
#define AGC_CFG2               27
#define AGC_CFG3               28
#define AGC_CFG_CLR            29
#define AGC_STA                30
#define AGC_DATA               31

// For OBUF
#define OBUF_CFG               35
#define OBUF_SIZE              36
#define OBUF_BLK               37
#define OBUF_STA               38
#define OBUF_CLR               39
#define FIFO_SPEED             40
#define FIFO_CNT               41


//------------------------------------------------------------------------------
// APB Peri Register
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// PAGE0
#define TMR0_CFG                0x14000000
#define TMR0_PND                0x14000004
#define TMR0_CPND               0x14000008
#define TMR0_CNT                0x1400000c
#define TMR0_PR                 0x14000010
#define TMR0_PWM                0x14000014

#define TMR1_CFG                0x14000018
#define TMR1_PND                0x1400001c
#define TMR1_CPND               0x14000020
#define TMR1_CNT                0x14000024
#define TMR1_PR                 0x14000028
#define TMR1_PWM                0x1400002c

#define TMR2_CFG                0x14000030
#define TMR2_PND                0x14000034
#define TMR2_CPND               0x14000038
#define TMR2_CNT                0x1400003c
#define TMR2_PR                 0x14000040
#define TMR2_PWM                0x14000044

#define TMR3_CFG                0x14000048
#define TMR3_PND                0x1400004c
#define TMR3_CPND               0x14000050
#define TMR3_CNT                0x14000054
#define TMR3_PR                 0x14000058
#define TMR3_PWM                0x1400005c

#define	 IRT_CFG		0x14000060
#define	 IRT_CPND		0x14000064
#define	 IRT_SECCNT		0x14000068
#define	 IRT_DATA		0x1400006c

#define IR_CON0                  0x14000070
#define IR_START_CON             0x14000074
#define IR_DATAH                 0x14000078
#define IR_DATAL                 0x1400007c

#define WDT_CFG                  0x14000084

#define ADC_CFG                  0x14000088
#define ADC_PND                  0x1400008c
#define ADC_BAUD                 0x14000090
#define ADC_DATA                 0x14000094

#define LVDCON                   0x140000a0

#define LED_CON              0x140000a4
#define LED_CON1             0x140000a8
#define LED_CON2             0x140000ac
#define LED_CYCLE            0x140000b0
#define LED_HIGH             0x140000b4
#define LED_ADC              0x140000b8
#define LED_TRIM             0x140000bc
#define LED_PAUS             0x140000c0

#define IR_CYCLE_CON          0x140000C4
#define IR_REPEAT_CON         0x140000C8

//------------------------------------------------------------------------------
// PAGE1
//UART0
#define  UART0_CFG              0x14001000
#define  UART0_BAUD             0x14001004
#define  UART0_DATA             0x14001008
#define  UART0_PND              0x1400100C

//UART1
#define  UART1_CFG              0x14001010
#define  UART1_CPND             0x14001014
#define  UART1_BAUD             0x14001018
#define  UART1_DATA             0x1400101c
#define  UART1_MINUS            0x14001020
#define  UART1_LOOPCNT          0x14001024
#define  UART1_DMACNT           0x14001028
#define  UART1_DTXCNT           0x1400102C

//SPI0
#define  SPI0_CFG               0x14001040
#define  SPI0_BUF               0x14001044
#define  SPI0_BAUD              0x14001048
#define  SPI0_DMACNT            0x1400104c
//SPI1
#define  SPI1_CFG               0x14001050
#define  SPI1_BUF               0x14001054
#define  SPI1_BAUD              0x14001058
#define  SPI1_DMACNT            0x1400105c

//SDHOST0
#define  SDC0_CFG0               0x14001060
#define  SDC0_CFG1               0x14001064
#define  SDC0_CFG2               0x14001068
#define  SDC0_BAUD               0x1400106c
#define  SDC0_DCNT               0x14001070
#define  SDC0_INDEX              0x14001074
#define  SDC0_ARG                0x14001078
#define  SDC0_RESP0              0x1400107c
#define  SDC0_RESP1              0x14001080
#define  SDC0_RESP2              0x14001084
#define  SDC0_RESP3              0x14001088
#define  SDC0_RESP4              0x1400108c

//SDHOST1
#define  SDC1_CFG0               0x14001090 
#define  SDC1_CFG1               0x14001094
#define  SDC1_CFG2               0x14001098
#define  SDC1_BAUD               0x1400109c 
#define  SDC1_DCNT               0x140010a0
#define  SDC1_INDEX              0x140010a4
#define  SDC1_ARG                0x140010a8
#define  SDC1_RESP0              0x140010ac
#define  SDC1_RESP1              0x140010b0
#define  SDC1_RESP2              0x140010b4
#define  SDC1_RESP3              0x140010b8
#define  SDC1_RESP4              0x140010bc


//IIC
#define  I2C_PRER               0x140010c0
#define  I2C_CFG                0x140010c4
#define  I2C_TX                0x140010c8
#define  I2C_CMD                 0x140010cc
#define  I2C_RCV                0x140010d0
#define  I2C_STA                 0x140010d4

//LFSR
#define  LFSR_FIFO               0x140010d8
#define  LFSR_POLY               0x140010dc
#define  LFSR_CODEENC            0x140010e0

//CRC
#define  CRC_FIFO                0x140010e4
#define  CRC_REG                 0x140010e8

#define  MBIST_CON               0x140010ec
#define  MBIST_CNT               0x140010f0
#define  MBIST_RES0              0x140010f4
#define  MBIST_RES1              0x140010f8

//Full speed USB
#define  M_FADDR                 0x14001100
#define  M_POWER                 0x14001101
#define  M_INTRTX1               0x14001102
#define  M_INTRTX2               0x14001103
#define  M_INTRRX1               0x14001104
#define  M_INTRRX2               0x14001105
#define  M_INTRUSB               0x14001106
#define  M_INTRTX1E              0x14001107
#define  M_INTRTX2E              0x14001108
#define  M_INTRRX1E              0x14001109
#define  M_INTRRX2E              0x1400110A
#define  M_INTRUSBE              0x1400110B
#define  M_FRAMENUM1             0x1400110C
#define  M_FRAMENUM2             0x1400110D
#define  M_INDEX                 0x1400110E
#define  M_DEVCTL                0x1400110F
#define  M_TXMAXP                0x14001110
#define  M_CSR0                  0x14001111
#define  M_TXCSR1                0x14001111
#define  M_TXCSR2                0x14001112
#define  M_RXMAXP                0x14001113
#define  M_RXCSR1                0x14001114
#define  M_RXCSR2                0x14001115
#define  M_COUNT0                0x14001116
#define  M_RXCOUNT1              0x14001116
#define  M_RXCOUNT2              0x14001117
#define  M_TXTYPE                0x14001118
#define  M_TXINTERVAL            0x14001119
#define  M_RXTYPE                0x1400111A
#define  M_RXINTERVAL            0x1400111B
#define  M_FIFO0                 0x14001120
#define  M_FIFO1                 0x14001121

#define  FSUSB_DMACNT            0x14001124
#define  FSUSB_DMACTL            0x14001128
#define  FSUSB_BRGCFG            0x1400112c
#define  FSUSB_DPDMCTL           0x14001130
#define  FSUSB_SOFPND            0x14001134

//IIS
#define IIS_CFG0                 0x14001140 
#define IIS_CKCON                0x14001144 
#define IIS_TX_DATA              0x14001148
#define IIS_WS_SMP               0x1400114c  
#define IIS_RX_DATA0             0x14001150  
#define IIS_RX_DATA1             0x14001154

//------------------------------------------------------------------------------
// PAGE2
#define  AT_ADR                  0x14002000
#define  AT_DAT                  0x14002004

//------------------------------------------------------------------------------
// PAGE3
#define  PA                      0x14003000
#define  PB                      0x14003004
#define  PC                      0x14003008
#define  PD                      0x1400300c
#define  PE                      0x14003010
#define  PF                      0x14003014
#define  PG                      0x14003018

#define  PA_DIR                  0x14003020
#define  PB_DIR                  0x14003024
#define  PC_DIR                  0x14003028
#define  PD_DIR                  0x1400302c
#define  PE_DIR                  0x14003030
#define  PF_DIR                  0x14003034
#define  PG_DIR                  0x14003038

#define  PA_PU0                  0x14003040
#define  PB_PU0                  0x14003044
#define  PC_PU0                  0x14003048
#define  PD_PU0                  0x1400304c
#define  PE_PU0                  0x14003050
#define  PF_PU0                  0x14003054
#define  PG_PU0                  0x14003058

#define  PA_PD0                  0x14003060
#define  PB_PD0                  0x14003064
#define  PC_PD0                  0x14003068
#define  PD_PD0                  0x1400306c
#define  PE_PD0                  0x14003070
#define  PF_PD0                  0x14003074
#define  PG_PD0                  0x14003078

#define  PC_DRV                  0x1400307c
#define  PD_DRV                  0x14003080
#define  PE_DRV                  0x14003084

#define  PORTWKEN                0x140030a0
#define  PORTWKEDG               0x140030a4
#define  PA_IE                   0x140030a8
#define  PG_IE                   0x140030ac

#define  PC_BT0                  0x140030c0
#define  PC_BT1                  0x140030c4
#define  PC_BT2                  0x140030c8
#define  PC_BT3                  0x140030cc
#define  PC_BT4                  0x140030b0
#define  PC_BT5                  0x140030b4
#define  PC_BT6                  0x140030b8
#define  PC_BT7                  0x140030bc

//------------------------------------------------------------------------------
// PAGE4
#define  PCON0                  0x14004000
#define  CLKCON0                0x14004004
#define  CLKCON1                0x14004008
#define  CLKCON2                0x1400400c

#define  AUPLL_CFG               0x1400401c

#define  PLL_CFG                 0x14004020
#define  PLL_INT_N               0x14004024
#define  PLL_FRAC_N              0x14004028
#define  SOFT_RST                0x1400402c

#define  PMAP_CFG0              0x14004030
#define  PMAP_CFG1              0x14004084

#define  SYS_CFG                0x14004034
#define  IE                     0x14004038
#define  FIQCON                 0x1400403c

#define  FIQPND                 0x14004040
#define  IRQPND                 0x14004044
#define  IRQPRI0                 0x14004048
#define  IRQPRI1                 0x1400404c

#define  USBCFG                  0x14004050
#define  USBTST0                 0x14004054
#define  USBTST1                 0x14004058
#define  USBTST_OUT              0x1400405c

#define  VDAC_CFG                0x14004060
#define  CPU_RD_OTP              0x14004064
#define  OTP_XPGM_CON             0x14004068
#define  OTP_XREAD_CON             0x1400406c

#define  RGB_DAT                 0x14004070
#define  RGB_STATUS              0x14004074

#define  USBDMAADDR              0x14004078
#define  USBDMACNT               0x1400407c
#define  USBDMACTL               0x14004080

#define  DAC_ACON0               0x14004090
#define  DAC_ACON1               0x14004094
#define  DAC_ACON2               0x14004098

#define  IRQSTA                  0x140040a0
#define  AUDIO_ACON              0x140040a4
#define  LDO_ACON                0x140040a8
#define  EA                      0x140040ac

#define  SYS_CON                 0x140040b0
#define  CLKTUN                  0x140040b4
#define  SPMODE                  0x140040b8
#define  CHIP_ID                 0x140040bc

#define  OTP_XDIN_XA            0x140040c0
#define  CHIP_ENC                0x140040c4

#define  BUS_MON_CFG             0x140040c8

#define  BUS_SB_M1               0x140040cc
#define  BUS_SB_M2               0x140040d0
#define  BUS_SB_M3               0x140040d4
#define  BUS_SB_M4               0x140040d8

#define  BUS_SDRB_M0             0x140040dc
#define  BUS_SDRB_M1             0x140040e0
#define  BUS_SDRB_M2             0x140040e4
#define  BUS_SDRB_M3             0x140040e8

#define  BUS_SYSBUS_ALL          0x140040ec
#define  BUS_SDRBUS_ALL          0x140040f0

//------------------------------------------------------------------------------
// PAGE5
//------------------------------------------------------------------------------
// CSI
#define CSIMODE                   0x14005000
#define CSI_IMAGE_SIZE            0x14005004
#define CSI_WIN_CROPH             0x14005008
#define CSI_WIN_CROPV             0x1400500c
#define CSI_EDGE_ENHANCE1         0x14005010
#define CSI_EDGE_ENHANCE2         0x14005014
#define CSI_PROLONG_MODE          0x14005018
#define NOISE_MODE                0x1400501c

#define TEST_MODE                 0x14005020

#define GAMMA_PARA0002            0x14005024
#define GAMMA_PARA0305            0x14005028
#define GAMMA_PARA0608            0x1400502c
#define GAMMA_PARA0911            0x14005030
#define GAMMA_PARA1214            0x14005034
#define GAMMA_PARA1517            0x14005038
#define GAMMA_PARA1820            0x1400503c
#define GAMMA_PARA2123            0x14005040
#define GAMMA_PARA2426            0x14005044
#define GAMMA_PARA2729            0x14005048
#define GAMMA_PARA3032            0x1400504c
#define GAMMA_PARA3335            0x14005050
#define GAMMA_PARA3638            0x14005054
#define GAMMA_PARA3941            0x14005058
#define GAMMA_PARA4244            0x1400505c
#define GAMMA_PARA4547            0x14005060
#define GAMMA_PARA4850            0x14005064
#define GAMMA_PARA5153            0x14005068
#define GAMMA_PARA5456            0x1400506c
#define GAMMA_PARA5759            0x14005070
#define GAMMA_PARA6062            0x14005074
#define GAMMA_PARA6364            0x14005078

#define BACKL_PARA0104            0x1400507c
#define BACKL_PARA0508            0x14005080
#define BACKL_PARA0912            0x14005084
#define BACKL_PARA1316            0x14005088
#define BACKL_PARA1720            0x1400508c
#define BACKL_PARA2124            0x14005090
#define BACKL_PARA2528            0x14005094
#define BACKL_PARA2931            0x14005098
#define VIDEO_ENH_MODE            0x1400509c
#define VIDEO_ENH_PARA            0x140050a0
#define COLOR_C_PARA1             0x140050a4
#define COLOR_C_PARA2             0x140050a8
#define COLOR_C_PARA3             0x140050ac
#define COLOR_C_PARA4             0x140050b0
#define COLOR_C_PARA5             0x140050b4

#define CSI_TIME_SIZE             0x140050b8

#define CSI_SCALER_PARA0          0x140050bc
#define CSI_SCALER_PARA1          0x140050c0
#define CSI_SCALER_PARA2          0x140050c4

#define MOTION_DETECT_PARA0       0x140050c8
#define MOTION_DETECT_PARA1       0x140050cc
#define MOTION_DETECT_PARA2       0x140050d0
#define MOTION_DETECT_PARA3       0x140050d4
#define MOTION_DETECT_PARA4       0x140050d8

#define CSI_DMA_MODE              0x140050dc
#define CSI_INTR                  0x140050e0
#define CSI_DMA_ADR               0x140050e4
#define CSI_ISP_BUF               0x140050e8
#define CSI_SDR_BASE              0x140050ec
#define CSI_TIME_POS              0x140050f0
#define CSI_TIME_INFO             0x140050f4
#define CSI_OUT_MODE              0x140050f8
#define CSI_P_SIZE_FRA            0x140050fc

//------------------------------------------------------------------------------
// JPEG
#define JPDMA0                    0x14006000
#define JPDMA1                    0x14006004
#define JPDMA2                    0x14006008

#define JPCON1                    0x1400600c
#define JPCON2                    0x14006010
#define JPCOM1                    0x14006014
#define JPCOM2                    0x14006018
#define JPCOM3                    0x1400601c
#define JPDRI                     0x14006020
#define JPUBIT                    0x14006024
#define JPTEST                    0x14006028
#define JPDPRE0                   0x1400602c
#define JPDPRE1                   0x14006030
#define JPDPRE2                   0x14006034
#define JPMAN                     0x14006038
#define JPMAND                    0x1400603c
#define JPLDH                     0x14006040
#define JPLDL                     0x14006044

#define CCCON                     0x14006048
#define CCY                       0x1400604c
#define CCCR                      0x14006050
#define CCCB                      0x14006054
#define CCR                       0x14006058
#define CCG                       0x1400605c
#define CCB                       0x14006060

#define JPIDMA0                   0x14006064
#define JPIBAS                    0x14006064
#define JPIDMA1                   0x14006068
#define JPIEND                    0x14006068
#define JPODMA0                   0x1400606c
#define JPOBAS                    0x1400606c
#define JPODMA1                   0x14006070
#define JPOEND                    0x14006070
#define JPOLTA                    0x14006074
#define DHTSIZE                   0x14006078
#define JPDHT                     0x14006078
#define JPSIZE                    0x1400607c
#define INTFLAG                   0x14006080
#define JPFLG                     0x14006080

//------------------------------------------------------------------------------
// PAGE7
#define  LCDCON0                 0x14007000
#define  LCDCON1                 0x14007004
#define  LCDCON2                 0x14007008
#define  LCDCON3                 0x1400700c
#define  LCDCON4                 0x14007010
#define  LCDCON5                 0x14007014
#define  LCDCON6                 0x14007018
#define  LCDCON7                 0x1400701c
#define  LCDCON8                 0x14007020
#define  LCDCON9                 0x14007024
#define  LCDCON10                0x14007028
#define  LCDCON11                0x1400702c
#define  LCDCON12                0x14007030
#define  LCDCON13                0x14007034
#define  LCDCON14                0x14007038
#define  LCDCON15                0x1400703c
#define  LCDCON16                0x14007040
#define  LCDCON17                0x14007044
#define  LCDCON18                0x14007048
#define  LCDCON19                0x1400704c
#define  LCDCON20                0x14007050
#define  LCDCON21                0x14007054
#define  LCDCON22                0x14007058
#define  LCDCON23                0x1400705c
#define  LCDCON24                0x14007060
#define  LCDCON25                0x14007064
#define  LCDCON26                0x14007068
#define  LCDCON27                0x1400706c
#define  LCDCON28                0x14007070
#define  LCDCON29                0x14007074
#define  LCDCON30                0x14007078
#define  LCDCON31                0x1400707c
#define  LCDCON32                0x14007080
#define  LCDCON33                0x14007084
#define  LCDCON34                0x14007088
#define  LCDCON35                0x1400708c
#define  LCDCON36                0x14007090
#define  LCDCON37                0x14007094
#define  LCDCON38                0x14007098
#define  LCDCON39                0x1400709c
#define  LCDCON40                0x140070a0
#define  LCDCON41                0x140070a4
#define  LCDCON42                0x140070a8
#define  LCDCON43                0x140070ac
#define  LCDCON44                0x140070b0
#define  LCDCON45                0x140070b4
#define  LCDCON46                0x140070b8
#define  LCDCON47                0x140070bc
#define  LCDCON48                0x140070c0
#define  LCDCON49                0x140070c4
#define  LCDCON50                0x140070c8
#define  LCDCON51                0x140070cc
#define  LCDCON52                0x140070d0
#define  LCDCON53                0x140070d4
#define  LCDCON54                0x140070d8
#define  LCDCON55                0x140070dc
#define  LCDCON56                0x140070e0
#define  LCDCON57                0x140070e4
#define  LCDCON58                0x140070e8
#define  LCDCON59                0x140070ec
#define  LCDCON60                0x140070f0
#define  LCDCON61                0x140070f4
#define  LCDCON62                0x140070f8
#define  LCDCON63                0x140070fc
#define  LCDCON64                0x14007100

#define  CVE2_REGDOUT            0x14007104
#define  CVE2_REGCTL             0x14007108
#define  CVE2_CTL                0x1400710c
#define  CVE2_REGDIN             0x14007110
#define  CVE2_REGADDR            0x14007114
#define  CVE2_PIXEL              0x14007118
#define  CVE2_LINE               0x1400711c

#if 0
//------------------------------------------------------------------------------
//SIE
#define USB_FAddr		 0x14040000
#define USB_Power		 0x14040001
#define USB_IntrInl		 0x14040002
#define USB_IntrInh		 0x14040003
#define USB_IntrOutl		 0x14040004
#define USB_IntrOuth		 0x14040005
#define USB_IntrInel		 0x14040006
#define USB_IntrIneh		 0x14040007
#define USB_IntrOutel		 0x14040008
#define USB_IntrOuteh		 0x14040009
#define USB_IntrUSB		 0x1404000A
#define USB_IntrUSBE		 0x1404000B
#define USB_Frame1		 0x1404000C
#define USB_Frame2		 0x1404000D
#define USB_Index		 0x1404000E
#define USB_Testmode		 0x1404000F
#define USB_InMaxPl		 0x14040010
#define USB_InMaxPh		 0x14040011
#define USB_CSR0		 0x14040012
#define USB_CSR01		 0x14040013
#define USB_InCSR1		 0x14040012
#define USB_InCSR2		 0x14040013
#define USB_OutMaxPl		 0x14040014
#define USB_OutMaxPh		 0x14040015
#define USB_OutCSR1		 0x14040016
#define USB_OutCSR2		 0x14040017
#define USB_OutCount1		 0x14040018
#define USB_OutCount2		 0x14040019
#define USB_TxType		     0x1404001A
#define USB_NAKLimit0		 0x1404001B	
#define USB_TxInterVal		 0x1404001B	
#define USB_RxType		     0x1404001C
#define USB_RxInterVal		 0x1404001D
#define	USB_FIFO0		 0x14040020	/*  FIFOs for Endpoints 0 */
#define	USB_FIFO1		 0x14040024	/*  FIFOs for Endpoints 1 */
#define	USB_FIFO2		 0x14040028	/*  FIFOs for Endpoints 2 */
#define	USB_FIFO3		 0x1404002c	/*  FIFOs for Endpoints 3 */
#define USB_Devctl		     0x14040060

#define USB_DMA_INTR		 0x14040200
#define USB_DMA_CNTL		 0x14040204
#define USB_DMA_ADDR		 0x14040208
#define USB_DMA_COUNT		 0x1404020C
#define USB_DMA_PAUSE		 0x14040210
#else
#define USB_FAddr		SFR_8_AT 0x14040000
#define USB_Power		SFR_8_AT 0x14040001
#define USB_IntrInl		SFR_8_AT 0x14040002
#define USB_IntrInh		SFR_8_AT 0x14040003
#define USB_IntrOutl		SFR_8_AT 0x14040004
#define USB_IntrOuth		SFR_8_AT 0x14040005
#define USB_IntrInel		SFR_8_AT 0x14040006
#define USB_IntrIneh		SFR_8_AT 0x14040007
#define USB_IntrOutel		SFR_8_AT 0x14040008
#define USB_IntrOuteh		SFR_8_AT 0x14040009
#define USB_IntrUSB		SFR_8_AT 0x1404000A
#define USB_IntrUSBE		SFR_8_AT 0x1404000B
#define USB_Frame1		SFR_8_AT 0x1404000C
#define USB_Frame2		SFR_8_AT 0x1404000D
#define USB_Index		SFR_8_AT 0x1404000E
#define USB_Testmode		SFR_8_AT 0x1404000F
#define USB_InMaxPl		SFR_8_AT 0x14040010
#define USB_InMaxPh		SFR_8_AT 0x14040011
#define USB_CSR0		SFR_8_AT 0x14040012
#define USB_CSR01		SFR_8_AT 0x14040013
#define USB_InCSR1		SFR_8_AT 0x14040012
#define USB_InCSR2		SFR_8_AT 0x14040013
#define USB_OutMaxPl		SFR_8_AT 0x14040014
#define USB_OutMaxPh		SFR_8_AT 0x14040015
#define USB_OutCSR1		SFR_8_AT 0x14040016
#define USB_OutCSR2		SFR_8_AT 0x14040017
#define USB_OutCount1		SFR_8_AT 0x14040018
#define USB_OutCount2		SFR_8_AT 0x14040019
#define USB_TXTYPE		SFR_8_AT 0x1404001A
#define USB_RXTYPE		SFR_8_AT 0x1404001C

#define USB_Devctl		SFR_8_AT 0x14040060
#define	USB_FIFO0		SFR_8_AT 0x14040020	/*  FIFOs for Endpoints 0 */
#define	USB_FIFO1		SFR_8_AT 0x14040024	/*  FIFOs for Endpoints 1 */
#define	USB_FIFO2		SFR_8_AT 0x14040028	/*  FIFOs for Endpoints 2 */
#define	USB_FIFO3		SFR_8_AT 0x1404002c	/*  FIFOs for Endpoints 3 */

#define USB_DMA_ADDR		SFR_AT 0x14040208
#define USB_DMA_CNTL		SFR_AT 0x14040204
#define USB_DMA_COUNT		SFR_AT 0x1404020C
#define USB_DMA_INTR		SFR_AT 0x14040200
#define USB_DMA_PAUSE		SFR_AT 0x14040210
	
	
	
#endif

//------------------------------------------------------------------------------
// vcs simulation end flag
//------------------------------------------------------------------------------
#define SIMEND                 0xfffffffc
#define SIMENDFLAG            SIMEND =  0xffffffff;

#endif
