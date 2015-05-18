
/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : iodetect.c
* Author             : mianwei_chen
* Version            : V0719a
* Date               : 03/17/2014  ;mm/dd/yyyy
* Description        : This file provides interface for io detect.
***************************************************************************/
#ifndef _IODETECT_H_
#define _IODETECT_H_

#define PMAP_PA4NO_PG4	1

#define ADCEN	4
#define ADCSEL	0
#define BGOE	7

#define CH_BANGAP	9
#define CH_HALFLOD	10


typedef struct _USB11_DETECT_RESERVE
{
	u32 clkcon0;
	u32 clkcon1;
	u32 pa_ie;
	u32 fsusb_brgcfg;
	u32 fsusb_dpdmctl;
	
}USB11_DETECT_RESERVE;

typedef struct _USB20_INT_DETECT_RESERVE
{
	u32 usbcfg;
	u32 usb_power;
	u32 usb_devctl;
	u32 usb_intrusbe;
	u32 usb_testmode;
	u32 ie;
	
}USB20_INT_DETECT_RESERVE;

typedef struct _IR_DETECT_RESERVE
{
	u32	clkcon0;
	u32	clkcon1; 
	u32	pcon0;
	u32	pmap_cfg0;
	u32	pa_dir;
	u32	pa_ie;
	u32	pa_pu0; 
	u32	pg_dir;
	u32	pg_ie;
	u32	pg_pu0; 
	u32	ir_repeat_con;
	u32	ir_start_con; 
	u32	ir_cycle_con;
	u32	ie;
	u32	ir_con0;
	
}IR_DETECT_RESERVE;

typedef struct _SD_DETECT_RESERVE
{
	u32 pa_dir;
	u32 pa_ie; 
	u32 pa_pu0;
	
}SD_DETECT_RESERVE;

typedef struct _BATTERY_DETECT_RESERVE
{
	u32 pcon0;
	u32 adc_cfg;
	u32 adc_baud;		
	u32 adc_pnd; 	
	
}BATTERY_DETECT_RESERVE;


void USB2_0_Detect_Init(void);
void DetectUSB2_0(void);
void DetectUSB2_0_HighandFull(void);
void USB2_0_Detect_End(void);
void USB1_1_Detect_Init(void);
void DetectUSB1_1(void);
void USB1_1_Detect_End(void);

void IoDetectUsb2_0(void);
void IoDetectUsb1_1(void);
void IoDetectTest(void);

void USBIntDetectStart2_0(void);
void USBIntDetectEnd2_0(void);
void IoDetectUsbInt2_0(void);
void IoDetectUsbIntFlag2_0(void);

void ir_init(void);
void ir_End(void);
void IoDetectIR(void);
void IoDetectIRIntFlag(void);

#endif

