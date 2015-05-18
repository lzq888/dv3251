#include "../header/Hunter.h"
#include "../config/config.h"
#include "../header/spi_boot_cfg.h"

	.global encrypt_byte
  	.equ    encrypt_byte,    ENCRYPT_BYTE
 
    .global boot_clksrc
    .equ    boot_clksrc,     CLKSRC_EN

    .global boot_clktun
    .equ    boot_clktun,     CLKTUN_ADDR

	.global boot_clktun_val
    .equ    boot_clktun_val, CLKTUN_VAL

	.global boot_reft
    .equ    boot_reft,       SDR_REFT_VAL

	.global boot_cfg0
    .equ    boot_cfg0,       SDR_CFG0_VAL

	.global boot_cfg1
    .equ    boot_cfg1,       SDR_CFG1_VAL

    .global boot_sys_con
    .equ    boot_sys_con,    SYS_CON_ADDR

    .global boot_sys_cfg
    .equ    boot_sys_cfg,    SYS_CFG_ADDR

    .global boot_sys_cfg_val
    .equ    boot_sys_cfg_val,SYS_CFG_VAL

    .global boot_pll_int_n
    .equ    boot_pll_int_n,  PLL_INT

    .global boot_pll_frac_n
    .equ    boot_pll_frac_n, PLL_FRAC

    .global boot_sys_div
    .equ    boot_sys_div,    SYS_DIV

	.global boot_spi_dma
    .equ    boot_spi_dma,    SPI_DMA

	.global boot_spi_baud
    .equ    boot_spi_baud,   SPIBAUD

	.global boot_iokey_port
    .equ    boot_iokey_port, IOKEY_PORT
	
	.global boot_iokey_dir
    .equ    boot_iokey_dir,  IOKEY_DIR

	.global boot_iokey_pu0
    .equ    boot_iokey_pu0,  IOKEY_PU0

	.global boot_iokey_pd0
    .equ    boot_iokey_pd0,  IOKEY_PD0
	
	.global boot_iokey_pin
    .equ    boot_iokey_pin,   IOKEY_PIN

	.global boot_adc_baud
    .equ    boot_adc_baud,   ADCBAUD
	
	.global boot_adkey_port
    .equ    boot_adkey_port, ADKEY_PORT
	
	.global boot_adkey_dir
    .equ    boot_adkey_dir,  ADKEY_DIR

	.global boot_adkey_pu0
    .equ    boot_adkey_pu0,  ADKEY_PU0

	.global boot_adkey_pd0
    .equ    boot_adkey_pd0,  ADKEY_PD0
	
	.global boot_adkey_pin
    .equ    boot_adkey_pin,   ADKEY_PIN
	
	.global boot_adkey_ie
    .equ    boot_adkey_ie,   ADKEY_IE
	
	
	.global boot_adkey_upvalue
    .equ    boot_adkey_upvalue,   ADKEY_UPVALUE

	.global boot_adkey_downvalue
    .equ    boot_adkey_downvalue,   ADKEY_DOWNVALUE
	
    .equ    btsct, .bootsect

