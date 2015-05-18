/******************** (C) COPYRIGHT 2014 BUILDWIN ************************
* File Name          : lcd_tdo24theb2.h
* Author             :  
* Version            :  
* Date               : 02/27/2014
* Description        : lcd tdo24theb2 SPI_RGB_2.4 HEADER FILE.
***************************************************************************/
#ifndef _LCD_TDO24THEB2_H_
#define _LCD_TDO24THEB2_H_


#define PIN_CONF()    REG32(PF_DIR) &= ~0xfff; REG32(PG_DIR) &= ~0x1fff;

//#define LCD_SPI_PMAP0()    PMAP_CFG0 |=(1<<24); PMAP_CFG0 &=~(1<<25);
#define LCD_SPI_PMAP1()    REG32(PMAP_CFG0) |=(1<<25); REG32(PMAP_CFG0) &=~(1<<24);

#define SPI_PIN_CONF()     REG32(PF_DIR) &= ~((1<<LCD_SPI_CS_PIN)|(1<<LCD_SPI_DAT_PIN)|(1<<LCD_SPI_CLK_PIN));

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

void lcd_spi_sendcmd(u16 cmd);

void delay(u32 delay_ms_cnt); 

void lcd_spi_init(u16 *p);


//======for outside call======
void lcd_init(void); 
void lcd_set_backlight(int flag);		//flag : 0 is close, 1 is open
u32 lcd_get_w();
u32 lcd_get_h();


#endif