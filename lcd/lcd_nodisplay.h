/******************** (C) COPYRIGHT 2014 BUILDWIN ************************
* File Name          : lcd_nodisplay.h
* Author             :  
* Version            :  
* Date               : 11/07/2014   ;mm/dd/yyyy
* Description        : lcd nodisplay HEADER FILE.
***************************************************************************/
#ifndef _LCD_NODISPLAY_
#define _LCD_NODISPLAY_

void lcd_spi_sendcmd(u16 cmd);

void delay(u32 delay_ms_cnt); 

void lcd_spi_init(u16 *p);

//======for outside call======
void lcd_init(void); 
void lcd_set_backlight(int flag);		//flag : 0 is close, 1 is open
u32 lcd_get_w();
u32 lcd_get_h();



#endif