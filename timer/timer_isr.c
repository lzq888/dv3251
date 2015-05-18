/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : timer_isr.c
* Author             : pengtao_zhang
* Version            : V0816a
* Date               : 08/16/2013
* Description        : This file provides timer interrupt functions.
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
volatile u32 u32Timer0_1msCnt;
volatile u32 u32Delay_1msCnt;		//only for Delay_MS()
volatile u32 u32Test_1msCnt;
//volatile static u8  sd_check_flag;			//0 : is no check success , 1: is check success
/*******************************************************************************
* Function Name  : timer1_isr
* Description    : timer1 interrupt per 1ms
* Input          : None
* Output         :
* Return         : None
*******************************************************************************/
void timer0_isr(void)
{
	REG32(TMR0_CPND) |= BIT(1);
	u32Delay_1msCnt++;
	u32Timer0_1msCnt++;
	//u32Test_1msCnt++;
#if LED_REUSE_ADKEY	
	if(u32Timer0_1msCnt%8 == 7)
	{
		if(adc_chk_flag==1) {
			adc_chk_flag = 2;
			ADKeyInit();	
		}
	}
#endif
	
	if(u32Timer0_1msCnt%8 == 0)			//keep the same timeout as the WDT wakeupt time 
	{
	#if (USER_CONFIG==CONFIG_AX3251_AIRBORNE)
		//here not into power save mode
	#else
		powerSaveCheck();
	#endif
		ScanKey(0);
		led_SetStatus();
		sd_Detect();
		usb20_detect();
		
		{
			static SYSTEM_STATE prev_state=0xff;
			if(prev_state != g_SystemState)
			{
				prev_state = g_SystemState;
				//deg_Printf("SYS_State=%d\n",g_SystemState);
			}
		}
	}
	
	if((u32Timer0_1msCnt%500)==0) 
	{ 
		put_msg(SYSTEM_500MS); 
		OSD_changeFlag = 1;
	} 
	if((u32Timer0_1msCnt%1000)==0) 
	{ 
	#if SOFT_POWER_ON_OFF
		poweroff_1s_check(); //add for tmp test	
	#endif
		task_record_1s_check();		//add for md wait some times
		f_check_rec_video_file_size();	
		put_msg(SYSTEM_1S); 
	} 	
}

/*******************************************************************************
* Function Name  : timer1_isr
* Description    : timer1 interrupt per 10ms
* Input          : None
* Output         :
* Return         : None
*******************************************************************************/
void timer1_isr(void)
{

	REG32(TMR1_CPND) |= BIT(1);	
	csi_CheckMD();

	g_stcJpegInfo.iJpeg10MSCnt++;
	if(g_stcJpegInfo.iJpeg10MSCnt > sys_ctl.record_video_s*100)
	{
		if(RECORD_VIDEO == g_stcJpegInfo.RecordType)
		{
			g_stcJpegInfo.bVideoAutoRecordFlag = TRUE;
		}
		if(RECORD_AUDIO == g_stcJpegInfo.RecordType)
		{
			g_stcJpegInfo.bAudioAutoRecordFlag = TRUE;
		}
		return;
	}
	
}

/*******************************************************************************
* Function Name  : timer2_isr
* Description    : timer2 interrupt per 1/30ms
* Input          : None
* Output         :
* Return         : None
*******************************************************************************/
void timer2_isr(void)
{
	REG32(TMR2_CPND) |= BIT(1);
	g_stcJpegInfo.i30FrameCnt++;
}
/*******************************************************************************
* Function Name  : timer3_isr
* Description    : timer3 interrupt, frequency is ADCBAUD/20
* Input          : None
* Output         :
* Return         : None
*******************************************************************************/
void timer3_isr(void)
{
	REG32(TMR3_CPND) |= BIT(1);
#if LED_REUSE_ADKEY
	if(adc_chk_flag == 2) {
		if(REG32(ADC_PND) == 0x00) {	//adc conversation complete
			timer_Timer3_Stop();
			adc_chk_flag = 0;
			//deg_Printf("%d\n",REG32(ADC_DATA));
			ADKeyEnd();
		}
	}
#endif
}

