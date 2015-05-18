
#define  ENCRYPT           1
#define  CLKTUN_EN         1
#define  BUS1              0
#define  REMAP             0
#define  SPIDMA_EN         1
#define  ENABLE_32K        1
#define  ENABLE_12M        0


#define  RC_CLOCK          11000
#define  MPLL_OUT          192000
#define  SPI_BAUDRATE      12000
#define  SYS_OUT           48000

#define  SDRITUN           (2<<6)|(1<<5)|(0<<4)|(10<<0)/*DATA INPUT */
#define  SCOTUN            (1<<13)|(0<<12)|(0<<8)	   /*CLK OUT    */
#define  SDOTUN            (1<<30)|(1<<29)|(10<<24)    /*DATA OUTPUT*/
#define  SDR_REFT_VAL      300

#if (HUNTER_IC==HUNTER_64PIN)
#define  SDR_CFG0_VAL      0x1FC0008
#else
#define  SDR_CFG0_VAL      0x1FC000A
#endif

#define  SDR_CFG1_VAL      0x7FC
//#define  SDR_CFG1_VAL      0x3BC

#define  DUMMY_ADDR        0x10007C00
#define  CLKSRC_EN         (ENABLE_32K<<15)/*|(ENABLE_12M<<7)*/
#define  ADC_BOOT_BAUDRATE  0x80

#if  ENCRYPT
#define ENCRYPT_BYTE      0x15 //0x11  new version chksum 
#else
#define ENCRYPT_BYTE      0x05 //0x1
#endif

#if  CLKTUN_EN 
# define CLKTUN_ADDR       CLKTUN
#else 
# define CLKTUN_ADDR       DUMMY_ADDR
#endif
#define  CLKTUN_VAL        SDRITUN|SCOTUN|SDOTUN 

#if  SPIDMA_EN 
# define SPI_DMA           0x10
#else 
# define SPI_DMA           0
#endif

#define  SYS_CFG_VAL       (BUS1<<3)|(REMAP<<2)

#if  SYS_CFG_VAL
# define SYS_CON_ADDR      SYS_CON
# define SYS_CFG_ADDR      SYS_CFG
#else
# define SYS_CON_ADDR      DUMMY_ADDR
# define SYS_CFG_ADDR      DUMMY_ADDR
#endif    

#define  PLL_INT           (MPLL_OUT/RC_CLOCK)
#define  PLL_FRAC          ((MPLL_OUT%RC_CLOCK)* 65536 / RC_CLOCK)
#define  SYS_DIV           ((MPLL_OUT/SYS_OUT)-1)
#define  SPIBAUD           (SYS_OUT / (2*SPI_BAUDRATE) - 1)

#define  ADKEY_PORT         PA
#define  ADKEY_DIR          PA_DIR
#define  ADKEY_IE           PA_IE
#define  ADKEY_PIN          1<<5 
#define  ADCBAUD           (SYS_OUT / (2*ADC_BOOT_BAUDRATE) - 1) 
#define  ADKEY_PU0          PA_PU0
#define  ADKEY_PD0          PA_PD0
#define  ADKEY_UPVALUE      918
#define  ADKEY_DOWNVALUE    818

#define INNER_PULL_UP      1
#define INNER_PULL_DOWN    0

#define  IOKEY_PORT         PF
#define  IOKEY_DIR          PF_DIR
#define  IOKEY_PIN          1<<0

#if INNER_PULL_UP
#define  IOKEY_PU0          PF_PU0

#else
#define  IOKEY_PU0          DUMMY_ADDR
#endif

#if INNER_PULL_DOWN
#define  IOKEY_PD0          PF_PD0

#else
#define  IOKEY_PD0          DUMMY_ADDR
#endif
