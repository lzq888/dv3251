/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : gsensor.c
* Author             : zhipen_lin
* Version            : V0726a
* Date               : 09/05/2014
* Description        : This file provides all the sensor  firmware functions.
***************************************************************************/
//===================================================================
//                                                     	            |
//                       INCLUDE FILES                              |
//                                                                  |
//===================================================================
#include "../header/include.h"

#if(G_SEN_USE == G_SEN_NULL)
//===================================================================
//                                                     	            |
//                      GLOBAL VARIABLE                             |
//                                                                  |
//===================================================================

static s16 sen_hold_last_xdata = 0;
static s16 sen_hold_last_ydata = 0;
static s16 sen_hold_last_zdata = 0;


void Gsen_set_Threshold(u8 threshold)
{
	
}

void G_sensor_init(void)
{

}

void Gsen_Int_Set(void)
{

}

//======return 0: do nothing , 1: will lock file====
u8 Gsen_check_lock_flag(void)
{

	return 0;
}

#endif