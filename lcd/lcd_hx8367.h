/******************** (C) COPYRIGHT 2014 BUILDWIN ************************
* File Name          : lcd_st3029.h
* Author             :  
* Version            :  
* Date               : 02/27/2014
* Description        : lcd st3029 EMI HEADER FILE.
***************************************************************************/
#ifndef _LCD_HX8367_H_
#define _LCD_HX8367_H_

#define  LCD_MCU					1

//======for outside call======
void lcd_init(void); 
void lcd_set_backlight(int flag);		//flag : 0 is close, 1 is open
u32 lcd_get_w();
u32 lcd_get_h();


#endif
