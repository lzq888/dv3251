/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : led.c
* Author             : pengtao_zhang
* Version            : V1017a
* Date               : 10/17/2014   ; mm/dd/yyyy
* Description        : This file provides all the led functions.
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
volatile SYSTEM_STATE g_SystemState = SYSTEM_POWER_ON;

#if(USER_CONFIG==CONFIG_AX3251_AIRBORNE)
const u16 u16LedParam_RED[SYSTEM_STATE_MAX] =
{	
	LED_ON |  0 <<8,	//SYSTEM_POWER_ON,
	LED_ON	|  0 <<8,	//SYSTEM_POWER_OFF
	LED_ON |  0 <<8,	//SYSTEM_IDLE
	LED_OFF	|  0 <<8,	//SYSTEM_LVD_DETECT
	LED_TWK	| 100 <<8,//SYSTEM_RECORD_VIDEO
	LED_ON |  0 <<8,	//SYSTEM_STOP_RECORD_VIDEO
	LED_OFF  |  0 <<8,	//SYSTEM_RECORD_PICTURE
	LED_ON |  0 <<8,	//SYSTEM_STOP_RECORD_PICTURE
	LED_TWK |  50 <<8,	//SYSTEM_CARD_OVERSPACE
	LED_TWK |  50 <<8,	//SYSTEM_RECORD_ERROR
	LED_TWK |  50 <<8,	//SYSTEM_CARD_ERROR
	LED_TWK |  50 <<8,//SYSTEM_SENSOR_ERROR,
	LED_ON |   0 <<8,//SYSTEM_USB_CONNECT,
	LED_TWK |   50 <<8,//SYSTEM_CARD_UPDATA_SUCCESS
	LED_ON |  0 <<8,	//SYSTEM_PLAY_VIDEO
};

const u16 u16LedParam_GREEN[SYSTEM_STATE_MAX] =
{	
	LED_OFF |  0 <<8,	//SYSTEM_POWER_ON,
	LED_ON	|  0 <<8,	//SYSTEM_POWER_OFF
	LED_OFF |  0 <<8,	//SYSTEM_IDLE
	LED_ON	|  0 <<8,	//SYSTEM_LVD_DETECT
	LED_OFF	|  0 <<8,	//SYSTEM_RECORD_VIDEO
	LED_OFF |  0 <<8,	//SYSTEM_STOP_RECORD_VIDEO
	LED_OFF |  0 <<8,	//SYSTEM_RECORD_PICTURE
	LED_OFF |  0 <<8,	//SYSTEM_STOP_RECORD_PICTURE
	LED_OFF | 0 <<8,//SYSTEM_CARD_OVERSPACE
	LED_OFF |  0 <<8,	//SYSTEM_RECORD_ERROR
	LED_OFF |  0 <<8,//SYSTEM_CARD_ERROR
	LED_TWK |  50 <<8,//SYSTEM_SENSOR_ERROR,
	LED_TWK | 50 <<8,//SYSTEM_USB_CONNECT,
	LED_TWK |   50 <<8,//SYSTEM_CARD_UPDATA_SUCCESS
	LED_OFF |  0 <<8,	//SYSTEM_PLAY_VIDEO
};

#else
const u16 u16LedParam_RED[SYSTEM_STATE_MAX] =
{	
	LED_OFF |  0 <<8,	//SYSTEM_POWER_ON,
	LED_ON	|  0 <<8,	//SYSTEM_POWER_OFF
	LED_OFF |  0 <<8,	//SYSTEM_IDLE
	LED_OFF	|  0 <<8,	//SYSTEM_LVD_DETECT
	LED_TWK	| 100 <<8,//SYSTEM_RECORD_VIDEO
	LED_ON |  0 <<8,	//SYSTEM_STOP_RECORD_VIDEO
	LED_OFF  |  0 <<8,	//SYSTEM_RECORD_PICTURE
	LED_ON |  0 <<8,	//SYSTEM_STOP_RECORD_PICTURE
	LED_TWK |  50 <<8,	//SYSTEM_CARD_OVERSPACE
	LED_TWK |  50 <<8,	//SYSTEM_RECORD_ERROR
	LED_OFF |  50 <<8,	//SYSTEM_CARD_ERROR
	LED_TWK |  50 <<8,//SYSTEM_SENSOR_ERROR,
	LED_ON |   0 <<8,//SYSTEM_USB_CONNECT,
	LED_TWK |   50 <<8,//SYSTEM_CARD_UPDATA_SUCCESS
	LED_ON |  0 <<8,	//SYSTEM_PLAY_VIDEO
};

const u16 u16LedParam_GREEN[SYSTEM_STATE_MAX] =
{	
	LED_ON |  0 <<8,	//SYSTEM_POWER_ON,
	LED_ON	|  0 <<8,	//SYSTEM_POWER_OFF
	LED_ON |  0 <<8,	//SYSTEM_IDLE
	LED_ON	|  0 <<8,	//SYSTEM_LVD_DETECT
	LED_OFF	|  0 <<8,	//SYSTEM_RECORD_VIDEO
	LED_OFF |  0 <<8,	//SYSTEM_STOP_RECORD_VIDEO
	LED_OFF |  0 <<8,	//SYSTEM_RECORD_PICTURE
	LED_OFF |  0 <<8,	//SYSTEM_STOP_RECORD_PICTURE
	LED_OFF | 0 <<8,//SYSTEM_CARD_OVERSPACE
	LED_ON |  0 <<8,	//SYSTEM_RECORD_ERROR
	LED_OFF |  0 <<8,//SYSTEM_CARD_ERROR
	LED_TWK |  50 <<8,//SYSTEM_SENSOR_ERROR,
	LED_TWK | 50 <<8,//SYSTEM_USB_CONNECT,
	LED_TWK |   50 <<8,//SYSTEM_CARD_UPDATA_SUCCESS
	LED_OFF |  0 <<8,	//SYSTEM_PLAY_VIDEO
};
#endif


/*******************************************************************************
* Function Name  : led_Init
* Description    : initial led IO,output low
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void led_Init(void)
{
#if LED_RED_BLINK
	LED_RED_INIT();
	LED_RED_ON();
#if LED_REUSE_ADKEY
	adkey_IOStatus = 1;
#endif
#endif


#if LED_GREEN_BLINK
	LED_GREEN_INIT();
	LED_GREEN_ON();
#endif
}

/*******************************************************************************
* Function Name  : led_SetStatus
* Description    : set all led output status
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void led_SetStatus(void)
{
#ifndef SPI_TRANSFER
#if LED_RED_BLINK
	led_SetStatus_RED();		//LED_RED
#endif

#if LED_GREEN_BLINK
	led_SetStatus_GREEN();		//LED_GREEN
#endif
#endif
}

/*******************************************************************************
* Function Name  : led_SetStatus_RED
* Description    : set red led output status
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
#if LED_RED_BLINK
void led_SetStatus_RED(void)
{
	static u32 u32LedCnt_10ms = 0;
	u32LedCnt_10ms++;

	return;
	
	LED_STATUS LedStatus_RED = (LED_STATUS)(u16LedParam_RED[g_SystemState] & 0xff);
	u8 u8LedFreq_RED = (u8)((u16LedParam_RED[g_SystemState] >>8)& 0xff);
	
	if (LED_OFF == LedStatus_RED)
	{
		LED_RED_OFF();
	#if LED_REUSE_ADKEY
		adkey_IOStatus = 0; 
	#endif
	}
	else if (LED_ON == LedStatus_RED)
	{
		LED_RED_ON();
	#if LED_REUSE_ADKEY
		adkey_IOStatus = 1; 
	#endif
	}
	else if (LED_TWK == LedStatus_RED)
	{
		if (u32LedCnt_10ms >= u8LedFreq_RED)
		{
			LED_RED_TWK();
			u32LedCnt_10ms = 0;
		#if LED_REUSE_ADKEY
			adkey_IOStatus ^= BIT(0);
		#endif
		}
	}	
}
#endif
/*******************************************************************************
* Function Name  : led_SetStatus_GREEN
* Description    : set green led output status
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
#if LED_GREEN_BLINK
void led_SetStatus_GREEN(void)
{
	static u32 u32LedCnt_10ms = 0;
	u32LedCnt_10ms++;
	
	return;

	LED_STATUS LedStatus_GREEN = (LED_STATUS)(u16LedParam_GREEN[g_SystemState] & 0xff);
	u8 u8LedFreq_GREEN = (u8)((u16LedParam_GREEN[g_SystemState] >>8)& 0xff);

	if (LED_OFF == LedStatus_GREEN)
	{
		LED_GREEN_OFF();
	}
	else if (LED_ON == LedStatus_GREEN)
	{
		LED_GREEN_ON();
	}
	else if (LED_TWK == LedStatus_GREEN)
	{
		if (u32LedCnt_10ms >= u8LedFreq_GREEN)
		{
			u32LedCnt_10ms = 0;
			LED_GREEN_TWK();
		}
	}	
}
#endif


