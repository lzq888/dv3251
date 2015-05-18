/******************** (C) COPYRIGHT 2013 BUILDWIN ********************************
* File Name          : adkey.c
* Author             :
* Version            :
* Date               : 24/10/2013
* Description        : key or adkey function.
**********************************************************************************/
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
#if (SOFT_POWER_ON_OFF)
static U8 key_power_flag;			//è«èèéºèè¨é²è§powerkey èé©´è·¯å¸½ç¢çèåæ¢å¢0: is ç¢çèåæ¢å¢1 æ³éºè§è, just used at first
#endif
#if LED_REUSE_ADKEY
u8 adc_chk_flag;
u32 adkey_IOStatus;
#endif
u8 adc_step;
#if (LCD_USE != LCD_NO_DISPLAY)
u8 skip_key_msg=0;
#endif
/****************************************************************
*
*function:		 		SarAdcinit	
*describle :			     for all saradc channel comman init interface 
*
*****************************************************************/
#define BAT_CHECK_CNT 		4   
const static u32 bat_table_lev[4] = {3500,3750,3900,4100};			//one level power , two level power,  three level power . full power
static u32 bat_check_cnt = 0;

#if	(KEY_TYPE==AD_KEY_TYPE)
const static DWORD tbl_key_adc[KEY_NUM+1] = {KEY_ADC};
const static u8 tbl_key_val[KEY_NUM+1] = {KEY_VAL};
#endif

void SarAdcinit(u32 ubaudrate, u8 uchannel)
{
	//deg_Printf("********* SarAdcinit! *********\r\n");
	REG32(PCON0) &= ~(BIT(18));//enable SARADC clock 
	REG32(ADC_BAUD) = ubaudrate;
	REG32(ADC_CFG) = (1<<ADCEN)|(uchannel<<ADCSEL);
	REG32(ADC_PND) = 0x01; 	
}

void SarAdcChangeCh(u8 uchannel, u8 ubgoe)
{
//	deg_Printf("********* SarAdcChangeCh! *********\r\n");
//	REG32(ADC_CFG) &= ~((1<<ADCEN)|(0xff<<ADCSEL)|(1<<BGOE));
	REG32(ADC_CFG) &= ~(0xff<<ADCSEL);
	REG32(ADC_CFG) |= (1<<ADCEN)|(uchannel<<ADCSEL)|(ubgoe<<BGOE);
	REG32(ADC_PND) = 0x01; 	
}

void battery_check_vol(u32 vol)
{
#if (USER_CONFIG==CONFIG_AX3251_AIRBORNE)
	static u32 count = 0;
       static u32 five_val[5];
	static u16 low_cnt = 0;
	
	if(count < 5)
	{
		five_val[count] = vol;
		count++;
	}
	else
	{
		int i = 0;
		u32 temp = 0;
		for(i = 0;i < 5;i++)
		{
			temp += five_val[i];
		}
		temp = temp/5;			//5 times average val
		if(temp < AD_CHECK_BAT_LOW_VOL)			//low power 
		{
			low_cnt++;
		}
		else						//clear 
		{
			low_cnt = 0;
		}
		if(low_cnt > 19)			// real low power
		{
			low_cnt = 0;
			//======low power handle=====
			g_stcJpegInfo.bLowPowerFlag = TRUE;
			g_stcJpegInfo.bPowerOffFlag = TRUE;
			g_SystemState = SYSTEM_LVD_DETECT;	
			deg_Printf("low power\n");
		}
		count = 0;
	}
#else
	static u32 changetime = 0;
	static u32 bat_vol = 0;
	static u32 bat_full_flag = 0;
	static u32 dcin_check_cnt = 0;
	static u8 dcin_flag=0xff;
	static u8 dcin_pre_flag = 0;		//for flag change compare,0 : dc not in ,   1 : dc in
	static u32 low_power_cnt;
	bat_vol += vol;	//read bat vol
	bat_check_cnt ++;

	if(sys_dcin_check() == 1)							//dc in 
	{
		if(dcin_flag != 1) {
			deg_Printf("DC IN\n");
			dcin_flag=1;
		}
		if(bat_check_cnt >= BAT_CHECK_CNT)
		{
			//======average======
			bat_vol = bat_vol/BAT_CHECK_CNT;
			//deg_Printf("dc bat_vol = %d\n",bat_vol);

			if( bat_vol  > bat_table_lev[3] )			//full
			{
//				bat_full_flag = 1;
				task_ctl.bat_lev = 3;
				bat_full_flag = 0;						// never stop
			}
			else if( bat_vol - 70 >= bat_table_lev[2] )		//
			{
				task_ctl.bat_lev = 3;
				bat_full_flag = 0;
			}
			else if(bat_vol - 100 >= bat_table_lev[1] )		//
			{
				task_ctl.bat_lev = 2;
				bat_full_flag = 0;
			}
			else if(bat_vol - 180 >= bat_table_lev[0] )		//
			{
				task_ctl.bat_lev = 1;
				bat_full_flag = 0;
			}
			//deg_Printf("BatL=%d\n",bat_level);
			bat_vol = 0;
			bat_check_cnt = 0;
		}


//================change icon============
		changetime ++;
		if(changetime > 100)
		{
			changetime = 0;
		}
		else if(changetime > 50)
		{
			task_ctl.flag_update_bat  = 2;
		}
		else
		{
			task_ctl.flag_update_bat = 1;
		}
//================change icon end==========
		dcin_check_cnt++;
		if(dcin_check_cnt > 50)
		{
			if(0 == dcin_pre_flag)
			{
				dcin_pre_flag = 1;
			}
			dcin_check_cnt = 0;
		}

	}
	else		//only bat 
	{
		if(dcin_flag != 0) {
			deg_Printf("DC OUT\n");
			dcin_flag=0;
		}
		if(bat_check_cnt >= BAT_CHECK_CNT)
		{
			//======average======
			bat_vol = bat_vol/BAT_CHECK_CNT;
			//deg_Printf("bat_vol = %d\n",bat_vol);
			
			if( bat_vol >= bat_table_lev[2] )		//
			{
				low_power_cnt = 0;
				task_ctl.bat_lev = 3;
				task_ctl.flag_update_bat = 1;		// 1 show bat, 2 show charge
			}
			else if(bat_vol >= bat_table_lev[1] )
			{
				low_power_cnt = 0;
				task_ctl.bat_lev = 2;
				task_ctl.flag_update_bat = 1;		// 1 show bat, 2 show charge
			}
			else if(bat_vol >= bat_table_lev[0] )
			{
				low_power_cnt = 0;
				task_ctl.bat_lev = 1;
				task_ctl.flag_update_bat = 1;		// 1 show bat, 2 show charge
			}
			else		//low power
			{
				low_power_cnt++;
				task_ctl.bat_lev = 0;
				task_ctl.flag_update_bat = 1;		// 1 show bat, 2 show charge

				if(low_power_cnt > 5)
				{
					//set power off
					//======low power handle=====
					deg_Printf("low power\n");
					task_ctl.work_sta = TASK_POWER_OFF;		// break task ,and power off
					g_stcJpegInfo.bPowerOffFlag = 1;		//break record,and play,and power off
					g_stcJpegInfo.bLowPowerFlag = 1;
					g_SystemState = SYSTEM_LVD_DETECT;	
				}
			}
			//deg_Printf("BatLB=%d\n",bat_level);
			bat_vol = 0;
			bat_check_cnt = 0;
		}

//=============dc out handle========
		if(1 == dcin_pre_flag)
		{
			dcin_check_cnt++;
			if(dcin_check_cnt > 100)
			{
				dcin_pre_flag = 0;
				dcin_check_cnt = 0;
				task_exit();				//yes dcout poweroff
			}
		}
//============end dc out handle======
	}
#endif
}
#if (SOFT_POWER_ON_OFF)
void power_key_init()
{
	//powkey init
	SETB(POWERKEY_PORT_DIR,POWERKEY_PORT_BIT);	//set it input
	CLRB(POWERKEY_PORT_PU,POWERKEY_PORT_BIT);	//not pull up
	CLRB(POWERKEY_PORT_PD,POWERKEY_PORT_BIT);	//not pull down

	if(key_powerkey_check())
	{
		key_power_flag = 1;
	}
	else
	{
		key_power_flag = 0;
	}
}

/*******************************************************************************
* Function Name  : key_powerkey_check
* Description    : check powerkey station
* Input          : None
* Output         : None
* Return         : 1: powerkey is push on, 0: powerkey is no push
*******************************************************************************/
u32 key_powerkey_check()
{
	return POWERKEY_STATUS();		//get powerkey flag
}
#endif
/*******************************************************************************
* Function Name  : IOKeyInit
* Description    : adkey k6000 initiate
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void IOKeyInit(void)
{
#if (KEY_TYPE==IO_KEY_TYPE)
	#if (USER_CONFIG==CONFIG_AX3250_K6000)
		REG32(PG_DIR) |= BIT(8)|BIT(6)|BIT(1)|BIT(0);
		REG32(PG_IE) |= BIT(8)|BIT(6)|BIT(1)|BIT(0);
		REG32(PG_PU0) |= BIT(8)|BIT(6)|BIT(1)|BIT(0);
		REG32(PG_PD0) &= ~(BIT(8)|BIT(6)|BIT(1)|BIT(0));
	#elif(USER_CONFIG==CONFIG_AX3251_AIRBORNE)
		REG32(PF_DIR) |= BIT(2)|BIT(3);
		REG32(PF_PU0) |= BIT(2)|BIT(3);
		REG32(PF_PD0) &= ~(BIT(2)|BIT(3));
	#endif
#endif
}

/*******************************************************************************
* Function Name  : ADKeyInit
* Description    : adkey k6000 initiate
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ADKeyInit(void)
{
#if	(KEY_TYPE==AD_KEY_TYPE)
#if (ADC_KEY_CHANNEL==ADC_CH2_PA3)
	REG32(PA_IE) |= BIT(3)|BIT(4);
	REG32(PA_PU0) &= ~(BIT(3)|BIT(4));
#elif (ADC_KEY_CHANNEL==ADC_CH3_PA5)
	REG32(PA_IE) |= BIT(5);
	REG32(PA_PU0) &= ~(BIT(5));
	REG32(PA_PD0) &= ~(BIT(5));
	REG32(PA_DIR) |= BIT(5);
#else
	......
#endif
#endif
}

/*******************************************************************************
* Function Name  : ADKeyEnd
* Description    : adkey check complete, then the port change into output port
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
#if LED_REUSE_ADKEY
void ADKeyEnd(void)
{
#if	(KEY_TYPE==AD_KEY_TYPE)
#if (ADC_KEY_CHANNEL==ADC_CH3_PA5)
	REG32(PA_DIR) &= ~BIT(5);
	if(adkey_IOStatus)
		REG32(PA)|=BIT(5);
	else
		REG32(PA)&=~ BIT(5);
#else
	......
#endif	
#endif
}
#endif

/*******************************************************************************
* Function Name  : KeyInit
* Description    : adkey initiate
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void KeyInit(void)
{
#if	(KEY_TYPE==IO_KEY_TYPE)
	IOKeyInit();
#elif (KEY_TYPE==AD_KEY_TYPE)
#if LED_REUSE_ADKEY
	adc_chk_flag = 0;
#endif
	adc_step = 0;
	ADKeyInit();
#else 
	......
#endif

#if SOFT_POWER_ON_OFF
	power_key_init();
#endif
}

/*******************************************************************************
* Function Name  : get_adValue
* Description    : get adc value
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
bool get_adValue(u16 * adValue)
{
#if LED_REUSE_ADKEY
	if(adc_step==2) {
		if(adc_chk_flag == 0) {
	        *adValue = REG32(ADC_DATA);
	        return TRUE;
	    } else {
	        return FALSE;
	    }
	}
#endif
	if(!(REG32(ADC_PND) == 0x00))	//等待ADC转换完成
		return FALSE;
	*adValue = REG32(ADC_DATA);
	REG32(ADC_PND) = 0x1;
//	deg_Printf("adc_value = %d\n", tmp);
	return TRUE;

}

/*******************************************************************************
* Function Name  : GetADKeyTpye
* Description    : Judge key type base on ADC KEY value
* Input          : None
* Output         : None
* Return         : ADC KEY Tpye
*******************************************************************************/
#if	(KEY_TYPE==AD_KEY_TYPE)
u8 GetADKeyTpye(DWORD dwADKeyVal)
{
	u8 eKeyTpye;
	u32 knum =0;
	//deg_Printf("AD=%d\n",dwADKeyVal);
	while (dwADKeyVal > tbl_key_adc[knum]) {
        knum++;			
    }
	eKeyTpye=tbl_key_val[knum];

#if SOFT_POWER_ON_OFF	
	if(key_powerkey_check()){
		if(key_power_flag==0)
			eKeyTpye = T_KEY_POWER;
	}
	else{
		key_power_flag = 0;			//ç¢çèåé¹¿åªèªç¦å¤èæ½è´¸æ¢å¢ç¦è°©èªç¦è°å¤è¦é0
	}
#endif	
	//deg_Printf("AD=%d,Key=%x\n",dwADKeyVal,eKeyTpye);
	return eKeyTpye;
}
#endif
/*******************************************************************************
* Function Name  : GetIOKeyTpye
* Description    : get key on board k6000
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
u8 GetIOKeyTpye(void)
{
	u8 eKeyTpye = NO_KEY;
#if (USER_CONFIG==CONFIG_AX3250_K6000)
	u32 tmpPortDir;
	u32 tmpPortData;
	char i;
	tmpPortDir = REG32(PG_DIR);
	tmpPortData = REG32(PG);
	REG32(PG_DIR) |= BIT(8)|BIT(6)|BIT(1)|BIT(0);
	for (i=0; i<50; i++)
	{
		asm("nop");
	}
	if (!(REG32(PG)& BIT(8) ))
	{
		eKeyTpye = T_KEY_DOWN;		//Down
	}
	else if(!(REG32(PG)& BIT(6) ))
	{
		eKeyTpye = T_KEY_UP;		//UP
	}
	else if(!(REG32(PG)& BIT(1) ))
	{
		eKeyTpye = T_KEY_PLAY;		// PLAY/OK
	}
	else if(!(REG32(PG)& BIT(0) ))
	{
		eKeyTpye = T_KEY_LOCK;		// HOLD
	}
	else
	{
		REG32(PG) &= ~(BIT(6)|BIT(1));
		REG32(PG_DIR) &= ~(BIT(6)|BIT(1));
		for (i=0; i<50; i++)
		{
			asm("nop");
		}
		if (!(REG32(PG)& BIT(8) ))
		{
			eKeyTpye = T_KEY_MENU;		//Menu
		}
		else if(!(REG32(PG)& BIT(0) ))
		{
			eKeyTpye = T_KEY_MODE;		// MODE
		}
		else
		{
			eKeyTpye = NO_KEY;		// NO_KEY
		}
	}
	REG32(PG_DIR) = tmpPortDir;
	REG32(PG) = tmpPortData;
#elif (USER_CONFIG==CONFIG_AX3251_AIRBORNE)
	u32 tmpPortDir;
	u32 tmpPortData;
	char i;
	tmpPortDir = REG32(PF_DIR);
	tmpPortData = REG32(PF);
	REG32(PF_DIR) |= BIT(3)|BIT(2);
	for (i=0; i<50; i++)
	{
		asm("nop");
	}
	if (!(REG32(PF)& BIT(3) ))
	{
	#if (KEY_NUM==1)
		eKeyTpye = T_KEY_AIRBORNE_CTRL;
	#else
		eKeyTpye = T_KEY_AIRBORNE_PHOTO;	
	#endif
	}
	else if(!(REG32(PF)& BIT(2) ))
	{
	#if (KEY_NUM==1)
		eKeyTpye = T_KEY_AIRBORNE_CTRL;
	#else
		eKeyTpye = T_KEY_AIRBORNE_VIDEO;
	#endif
	}
	
	else
	{
		eKeyTpye = NO_KEY;		// NO_KEY
	}
	REG32(PF_DIR) = tmpPortDir;
	REG32(PF) = tmpPortData;
#endif

#if SOFT_POWER_ON_OFF
	if(key_powerkey_check()){
		if(key_power_flag==0)
			eKeyTpye = T_KEY_POWER;
	}
	else{
		key_power_flag = 0;			//ç¢çèåé¹¿åªèªç¦å¤èæ½è´¸æ¢å¢ç¦è°©èªç¦è°å¤è¦é0
	}
#endif

//	deg_Printf("eKeyTpye %d\r\n",eKeyTpye);
	return eKeyTpye;
}
/*******************************************************************************
* Function Name  : ScanKey
* Description    : scan key
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
u8 KeyDeal(u8 key_val)
{
	static u8 keyPrevious =NO_KEY;
	static u32 keyCounter=0;
	u8 key_return = NO_KEY;
    if (key_val == NO_KEY || key_val != keyPrevious) 
	{

		if (keyCounter >= KEY_LONG_TIMES) {                //长按抬键
			key_return = keyPrevious | T_KEY_LONG_UP;
		} 
		else if (keyCounter >= KEY_SCAN_TIMES) {         //短按抬键
                key_return = keyPrevious | T_KEY_SHORT_UP;
		}
		keyPrevious = key_val;
		keyCounter = 0;
    } else {
        keyCounter++;
        if (keyCounter == KEY_SCAN_TIMES) {                    //去抖
            key_return = key_val;
        } 
		else if (keyCounter == KEY_LONG_TIMES) {             //长按
            key_return = key_val | T_KEY_LONG;
        } 
		else if (keyCounter == KEY_LONG_TIMES + KEY_HOLD_TIMES) {        //连按
            key_return = key_val | T_KEY_HOLD;
            keyCounter = KEY_LONG_TIMES;
        }
    }
	return key_return;
}
void KeyProcess(u8 key_val)
{	
	u8 key_msg;
	key_msg = KeyDeal(key_val);
	if(key_msg != NO_KEY)
	{
		#if (USER_CONFIG!=CONFIG_AX3251_AIRBORNE)
		if(0 == key_power_flag)				
		{
			if((T_KEY_POWER|T_KEY_LONG) == key_msg)				//is power off 
			{
				task_exit();
				//deg_Printf("long pressed %x key\n", key_msg);
				return;
			}
		}
		#endif
		if(sys_ctl.poweroffcnt != 0 && sys_ctl.poweroffcnt != 0xffff) 
		{
			set_poweroff();								
		}

		if(sys_ctl.beep_status)
		{
			if(!((task_ctl.on_recording == 1)&&(key_msg!=(T_KEY_PLAY | T_KEY_SHORT_UP)))  && 
				(task_ctl.work_sta != TASK_POWER_OFF) && 
				(task_ctl.work_sta != TASK_USB_DEVICE)&&
				(!task_ctl.on_playing) &&
				(key_msg <= (T_KEY_31 | T_KEY_SHORT_UP) && key_msg >= (T_KEY_1 | T_KEY_SHORT_UP)))//in recording video mode,no key voice but play key , power_off ,USB mode is no key voice
				key_voice();
		}
		if(key_msg == (T_KEY_LOCK|T_KEY_SHORT_UP))
		{
			if((!bPhotoScalFlag) && (!bFastViewFlag) && (device_online&BIT(B_SD_ONLINE)))
				task_into_lock_record_video();
		}
	#if (LCD_USE == LCD_NO_DISPLAY)
		put_msg(key_msg);
		reset_powerSaveChk();
		lcd_set_backlight(1);
		OSD_changeFlag = 1;
//		deg_Printf("key=%x\n",key_msg);
	#else
/*
		if(skip_key_msg == 0) {
			put_msg(key_msg);
			OSD_changeFlag = 1;
//			deg_Printf("key=%x\n",key_msg);
			if(powerSaveFlag == 0) {
				reset_powerSaveChk();
				lcd_set_backlight(1);
			}
		}

		if((key_msg & T_KEY_SHORT_UP)== T_KEY_SHORT_UP || (key_msg & T_KEY_LONG_UP)== T_KEY_LONG_UP) {
			skip_key_msg=0;
		}
*/
		if(task_ctl.work_sta != TASK_POWER_OFF)				// è·¯èé¹¿è´ç¦ç¤è³éºè¤å¢æ¢å¢èèè°éºè¨è¨éºè²é©´éå¤é²é¹¿è
		{	
			if(powerSaveFlag == 1) 
			{
				if((key_msg & T_KEY_SHORT_UP)== T_KEY_SHORT_UP || (key_msg & T_KEY_LONG_UP)== T_KEY_LONG_UP) 
				{
					reset_powerSaveChk();
					lcd_set_backlight(1);
					powerSaveFlag = 0;
				}
				return;
			}
		}
       
		put_msg(key_msg);
		reset_powerSaveChk();
		OSD_changeFlag = 1;

	#endif
	}
	else
	{
		if(bGsensor_Lock == TRUE)
		{
			bGsensor_Lock = FALSE;
			if((!bPhotoScalFlag) && (!bFastViewFlag) && (device_online&BIT(B_SD_ONLINE)))
				task_into_lock_record_video();
		}
		key_voice_after_recording();
	}
}
/*******************************************************************************
* Function Name  : ScanKey
* Description    : scan key
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ScanKey(u32 flag)
{	
	u8 eKeyTpye;
	u16 adcValue;
	static u32 bangapVol=0,batterVol=0;
	static u32 batterChkCnt=0;
	u32 batteryVolAnalog;
#if	(KEY_TYPE==IO_KEY_TYPE)
	eKeyTpye = GetIOKeyTpye();
	KeyProcess(eKeyTpye);
#endif
	if(get_adValue(&adcValue) == FALSE)
		return;

#if (USER_CONFIG==CONFIG_AX3251_AIRBORNE)
	#if(1 == AD_CHECK_BAT_EN)		//pa5 check bat for low power
		SarAdcChangeCh(ADC_CH3_PA5, 0);
//		deg_Printf("ad=%d\n",adcValue);
		if(sys_dcin_check() == 1)						//dc in not check
		{

		}
		else
		{
			battery_check_vol(adcValue);
		}
	#endif
	return;
#endif

	
	if(adc_step==0) {		//half LDO
		adc_step = 1;
		SarAdcChangeCh(ADC_CH9_BANGAP, 1);
		batterVol=adcValue<<1;
	#if LED_REUSE_ADKEY
		adc_chk_flag = 1;
	#endif
	}
	else if(adc_step==1) {	//bangap
		adc_step = 2;
	#if LED_REUSE_ADKEY
		if(flag == 1) {		//in hold mode
			adc_chk_flag = 2;
			ADKeyInit();	
			delay_ms(1);
		}
	#endif
		SarAdcChangeCh(ADC_CH3_PA5, 0);
	#if LED_REUSE_ADKEY
		if(flag == 0) {
			timer_Timer3_Start();
		}
		else {	//in hold mode
			Delay_10US(10);
			adc_chk_flag = 0;
			ADKeyEnd();
		}
	#endif
		bangapVol=adcValue;
		batterChkCnt++;
		if(batterChkCnt>=4) {
			batteryVolAnalog =(batterVol*850)/bangapVol - 260;
			battery_check_vol(batteryVolAnalog);
			batterChkCnt=0;
		}
	}
#if	(KEY_TYPE==AD_KEY_TYPE)
	else if(adc_step==2) {	//ADKEY
		adc_step = 0;
		SarAdcChangeCh(ADC_CH10_HALFLDO, 0);
		
		eKeyTpye = GetADKeyTpye(adcValue);
		KeyProcess(eKeyTpye);
	}
#endif

}

