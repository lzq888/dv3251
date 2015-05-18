/******************** (C) COPYRIGHT 2014 BUILDWIN ************************
* File Name          : lcd_s2700l0_g.h
* Author             :  
* Version            :  
* Date               : 02/27/2014
* Description        : lcd s2700l0_g SPI_RGB_2.7 HEADER FILE.
***************************************************************************/
#ifndef _LCD_ILI6480_
#define _LCD_ILI6480_

#define  LCD_MCU					0

#if	(USER_CONFIG==CONFIG_AX3250_K6000)
	#define PIN_CONF()    REG32(PF_DIR) &= ~0xfff; 

	//#define LCD_SPI_PMAP0()    REG32(PMAP_CFG0) |=(1<<24); REG32(PMAP_CFG0) &=~(1<<25);
	#define LCD_SPI_PMAP1()    REG32(PMAP_CFG0) |=(1<<25); REG32(PMAP_CFG0) &=~(1<<24)
	#ifdef LCD_SPI_PMAP0 
		#define LCD_SPI_CLK_PIN              5
		#define LCD_SPI_DI_PIN               7
		#define LCD_SPI_CS_PIN               4
		#define LCD_SPI_DAT_PIN              6
	#endif
	#ifdef LCD_SPI_PMAP1  
		#define LCD_SPI_CLK_PIN              13
		#define LCD_SPI_DI_PIN               12
		#define LCD_SPI_CS_PIN               15
		#define LCD_SPI_DAT_PIN              14
	#endif
	#define SPI_PIN_CONF()     LCD_SPI_PMAP1();REG32(PF_DIR) &= ~((1<<LCD_SPI_CS_PIN)|(1<<LCD_SPI_DAT_PIN)|(1<<LCD_SPI_CLK_PIN));

#elif (USER_CONFIG==CONFIG_AX3251_K6000)
	//#define PIN_CONF()    REG32(PF_DIR) &= ~0xf8d;
	#define PIN_CONF()    REG32(PF_DIR) &= ~0xfff; 
	
	#define LCD_SPI_PMAP0()    REG32(PMAP_CFG0) |=(1<<24); REG32(PMAP_CFG0) &=~(1<<25)
	//#define LCD_SPI_PMAP1()    REG32(PMAP_CFG0) |=(1<<25); REG32(PMAP_CFG0) &=~(1<<24);
	#ifdef LCD_SPI_PMAP0 
		#define LCD_SPI_CLK_PIN              5
		#define LCD_SPI_DI_PIN               7
		#define LCD_SPI_CS_PIN               4
		#define LCD_SPI_DAT_PIN              6
	#endif
	#ifdef LCD_SPI_PMAP1  
		#define LCD_SPI_CLK_PIN              13
		#define LCD_SPI_DI_PIN               12
		#define LCD_SPI_CS_PIN               15
		#define LCD_SPI_DAT_PIN              14
	#endif
	#define SPI_PIN_CONF()     LCD_SPI_PMAP0();REG32(PF_DIR) &= ~((1<<LCD_SPI_CS_PIN)|(1<<LCD_SPI_DAT_PIN)|(1<<LCD_SPI_CLK_PIN));
#else
	......
#endif

void lcd_spi_sendcmd(u16 cmd);

void delay(u32 delay_ms_cnt); 

void lcd_spi_init(u16 *p);

//======for outside call======
void lcd_init(void); 
void lcd_set_backlight(int flag);		//flag : 0 is close, 1 is open
u32 lcd_get_w();
u32 lcd_get_h();



#endif