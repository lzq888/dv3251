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
	sys_Init();

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
