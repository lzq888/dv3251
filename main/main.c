/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : main.c
* Author             : pengtao_zhang
* Version            : V0719a
* Date               : 07/19/2013  ;mm/dd/yyyy
* Description        : This file provides code entry functions.
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


int main(void)
{	
	//unsigned char buf[2] = "\x55\x55";
	unsigned char buf[32] = "01234567890abcdefhijklmnopqrstuvwxyz";
	//unsigned char buf[2] = "\x00\x00";
	sys_Init();

	lcd_init();
#if 0
	deg_Printf("spi sending 0x55\n");
	REG32(PMAP_CFG0) &=~(1UL<<25);
	REG32(PMAP_CFG0) &=~(1UL<<24);
	REG32(PF_DIR) &= ~0xf0;  //set to output
	REG32(PF) &= ~0x0f0;
#endif
	for(;;) {
		deg_Printf("spi sending 0x55\n");
		//deg_Printf("low\n");
		//REG32(PF) &= ~0x0f0UL;
		//spi_send(buf, 2);
		//Delay_MS(4000);
		//deg_Printf("high\n");
		//REG32(PF) |= 0x0f0UL;
	//REG32(PF) &= ~(1<<LCD_SPI_CS_PIN);
		//spi_send("\x901234567890abcdefghijklmnopqrstuvwxyz",33);
		spi_send("\x90\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55",33);
		//spi_send(buf, 32);
		Delay_MS(500);
		//Delay_MS(4000);
	//REG32(PF) |= (1<<LCD_SPI_CS_PIN);
	}
#if 0
	for(;;) {
		LED_RED_ON();
		LED_GREEN_ON();
		Delay_MS(500);
		LED_RED_OFF();
		LED_GREEN_OFF();
		Delay_MS(500);
	}
#endif
#if 0
	while(1) {
		deg_Printf("last while!!!!!!!\n");
		Delay_MS(1000);
	}
#endif
	while (NO_KEY != get_msg());
	run_task();
#if SOFT_POWER_ON_OFF
	sys_power_off(0);
#endif
//====power_off not success====

	deg_Printf("last while!!!!!!!\n");
	while(1); 

	return 0;
}
