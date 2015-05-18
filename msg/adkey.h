/******************** (C) COPYRIGHT 2013 BUILDWIN ************************/
#ifndef _ADKEY_H_
#define _ADKEY_H_

#define ADC_BAUDRATE   4000000

#define ADCEN	4
#define ADCSEL	0
#define BGOE	7

#define ADC_CH0_PA0				0
#define ADC_CH1_PA2				1
#define ADC_CH2_PA3				2
#define ADC_CH3_PA5				3
#define ADC_CH4_PG9				4
#define ADC_CH5_PG10			5
#define ADC_CH6_PG12			6
#define ADC_CH7_MIXIO			7
#define ADC_CH8_TVOUT			8
#define ADC_CH9_BANGAP			9
#define ADC_CH10_HALFLDO		10
#define ADC_KEY_CHANNEL    		ADC_CH3_PA5

//definite 32 keys
#define NO_KEY                  0
#define T_KEY_1                 0x1
#define T_KEY_2                 0x2
#define T_KEY_3                 0x3
#define T_KEY_4                 0x4
#define T_KEY_5                 0x5
#define T_KEY_6                 0x6
#define T_KEY_7                 0x7
#define T_KEY_8                 0x8
#define T_KEY_9                 0x9
#define T_KEY_9                 0x9
#define T_KEY_10                0xa
#define T_KEY_11                0xb
#define T_KEY_12                0xc
#define T_KEY_13                0xd
#define T_KEY_14                0xe
#define T_KEY_15                0xf
#define T_KEY_16                0x10
#define T_KEY_17                0x11
#define T_KEY_18                0x12
#define T_KEY_19                0x13
#define T_KEY_20                0x14
#define T_KEY_21                0x15
#define T_KEY_22                0x16
#define T_KEY_23                0x17
#define T_KEY_24                0x18
#define T_KEY_25                0x19
#define T_KEY_26                0x1a
#define T_KEY_27                0x1b
#define T_KEY_28                0x1c
#define T_KEY_29                0x1d
#define T_KEY_30                0x1e
#define T_KEY_31                0x1f

#define T_KEY_SHORT             0x00
#define T_KEY_SHORT_UP          0x20
#define T_KEY_LONG              0x40
#define T_KEY_LONG_UP           0x60
#define T_KEY_HOLD              0x80

#define SDMMC_CHANGE_IN	        0xf0
#define SDMMC_CHANGE_OUT        0xf1
#define USB_DEVICE_IN           0xf4
#define USB_DEVICE_CHANG_OUT	0xf5

#define SYSTEM_500MS 			0xfd 
#define SYSTEM_1S    			0xfe

#define T_KEY_DOWN				T_KEY_1
#define T_KEY_UP				T_KEY_2
#define T_KEY_PLAY				T_KEY_3
#define T_KEY_MENU				T_KEY_4
#define T_KEY_MODE				T_KEY_5
#define T_KEY_POWER				T_KEY_6
#define T_KEY_LOCK				T_KEY_7

#define	T_KEY_AIRBORNE_CTRL		T_KEY_20
#define T_KEY_AIRBORNE_PHOTO	T_KEY_21
#define T_KEY_AIRBORNE_VIDEO	T_KEY_22


#if (USER_CONFIG==CONFIG_AX3251_AIRBORNE)
	#if(1 == KEY_NUM)
	#define KEY_SCAN_TIMES          4          	//scan time per 8ms		// 32ms ~800ms is take photo ,  > 800ms is video
	#define KEY_LONG_TIMES          100       
	#define KEY_HOLD_TIMES          25         
	#else
	#define KEY_SCAN_TIMES          4        	//scan time equal KEY_SCAN_TIMES*8ms
	#define KEY_LONG_TIMES          100      
	#define KEY_HOLD_TIMES          25        
	#endif
#else
	#define KEY_SCAN_TIMES          4			//scan time equal KEY_SCAN_TIMES*8ms
	#define KEY_LONG_TIMES          100
	#define KEY_HOLD_TIMES          25
#endif

#if LED_REUSE_ADKEY
	extern u8 adc_chk_flag;
	extern u32 adkey_IOStatus;
#endif
#if (LCD_USE != LCD_NO_DISPLAY)
extern u8 skip_key_msg;
#endif
void ADKeyInit(void);
void ADKeyEnd(void);
void KeyInit(void);
bool get_adValue(u16 * adValue);
u8 GetADKeyTpye(DWORD dwADKeyVal);
void ScanKey(u32 flag);

u32 key_powerkey_check();

u8 GetIOKeyTpye(void);

void SarAdcinit(u32 ubaudrate, u8 uchannel);
void SarAdcChangeCh(u8 uchannel, u8 ubgoe);
void battery_check_vol();


#endif
