/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : led.h
* Author             : pengtao_zhang
* Version            : V1017a
* Date               : 10/17/2014  ;dd/mm/yyyy
* Description        : led HEADER FILE.
***************************************************************************/
#ifndef _LED_H_
#define _LED_H_

typedef enum
{
	SYSTEM_POWER_ON,
	SYSTEM_POWER_OFF,	
	SYSTEM_IDLE,
	SYSTEM_LVD_DETECT,
	SYSTEM_RECORD_VIDEO,
	SYSTEM_STOP_RECORD_VIDEO,
	SYSTEM_RECORD_PICTURE,
	SYSTEM_STOP_RECORD_PICTURE,
	SYSTEM_CARD_OVERSPACE,
	SYSTEM_RECORD_ERROR,
	SYSTEM_CARD_ERROR,
	SYSTEM_SENSOR_ERROR,
	SYSTEM_USB_CONNECT,
	SYSTEM_CARD_UPDATA_SUCCESS,
	SYSTEM_PLAY_VIDEO,
	SYSTEM_STATE_MAX

}SYSTEM_STATE;

typedef enum
{
	LED_OFF,
	LED_ON,
	LED_TWK
	
}LED_STATUS;

extern volatile  SYSTEM_STATE g_SystemState;

void led_Init(void);
void led_SetStatus(void);
void led_SetStatus_RED(void);
void led_SetStatus_GREEN(void);

#endif