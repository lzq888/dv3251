/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : iodetect.c
* Author             : mianwei_chen
* Version            : V0719a
* Date               : 03/17/2014  ;mm/dd/yyyy
* Description        : This file provides interface for io detect.
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
u32 ulUsbCfgReserve = 0;
USB11_DETECT_RESERVE tUsb11DetectReserve;
USB20_INT_DETECT_RESERVE tUsb20IntDetectReserve;
IR_DETECT_RESERVE tIrDetectReserve;
SD_DETECT_RESERVE tSdDetectReserve;

//===================================================================
//                                                     	            |
//                      INTERFACE FUNCTION                          |
//                                                                  |
//===================================================================



/********************************* USB2.0 Detect *********************************/
/*******              call (USB2_0_Detect_Init),  call (DetectUSB2_0)  or 
********              call (USB2_0_Detect_Init),  call (DetectUSB2_0_HighandFull)
********              finally call (USB2_0_Detect_End) restore configure 
*/
  
/****************************************************************
*
*function:			  USB2_0_Detect_Init	
*describle:      		usb 2.0 detect initialize  
*                              don't use with USBIntDetectStart2_0 together before USB2_0_Detect_End,
*                               it will generate conflict
*
*****************************************************************/
	void USB2_0_Detect_Init(void)
	{
		deg_Printf("\r\nUSB PHY USBTestInit\r\n\r\n");
		// initial USB host phy
		ulUsbCfgReserve = REG32(USBCFG);
		REG32(USBCFG)|= 0x80; //osc enable
		delay_us(1);
		REG32(USBCFG) |= 0x40; //pll enable
		delay_us(1000);
//		USBCFG |= 0x6400;//vbusvalid adevice downstream_port
//		delay_us(100);
		REG32(USBCFG) |= 0x1;	//release sie reset
		delay_us(1);
		REG32(USBCFG) |= 0x4;	//release phy reset
		delay_us(100);
//		USB_Power = 0x70; //High SPEED

//		USB_Devctl=0x03;
	}

/****************************************************************
*
*function:			  USB2_0_Detect_End	
*describle:      		usb 2.0 detect End  
*
*****************************************************************/
	void USB2_0_Detect_End(void)
	{
		deg_Printf("\r\nUSB PHY USB2.0 detect over\r\n\r\n");
		// initial USB host phy
		REG32(USBCFG) = ulUsbCfgReserve;
	}


/****************************************************************
*
*function: 		  DetectUSB2_0	
*describle : 	 usb 2.0 detect operation (only high speed)	, if need call it repeatedly
*
*****************************************************************/

	void DetectUSB2_0(void)
	{
		static int i = 0;
		unsigned int DPDMstatus = 0;
		unsigned int tmp = 0;
		
		i++;
		if (i % 2 == 0)
		{
			deg_Printf("\r\n now pulldown 10k DP DM\r\n");
			REG32(USBCFG) &= ~((1<<17)|(1<<18)|(1<<19));
			REG32(USBCFG) |= (1<<20)|(1<<21);
			REG32(USBCFG) |= (1<<17)|(1<<18);
			REG32(USBCFG) &= ~(1<<21);
			delay_ms(500);
			tmp = REG32(USBCFG);
			DPDMstatus = (tmp>>30);
			deg_Printf("DP DM tmp is %x\r\n",tmp);				
			deg_Printf("DP DM status is %x\r\n",DPDMstatus); 			
		}
		else
		{
			deg_Printf("\r\n now pullup 120k DP DM\r\n");
			REG32(USBCFG) &= ~((1<<17)|(1<<18)|(1<<19));
			REG32(USBCFG) |= (1<<20)|(1<<21);
			REG32(USBCFG) |= (1<<17)|(1<<18);
			REG32(USBCFG) &= ~(1<<21);
			delay_ms(500);
			tmp = REG32(USBCFG);
			DPDMstatus = (tmp>>30);
			deg_Printf("DP DM tmp is %x\r\n",tmp);				
			deg_Printf("DP DM status is %x\r\n",DPDMstatus);			
		}
		if (3 == DPDMstatus)
		{
			deg_Printf("************ there is a Usb disk detect! 2.0 ***********\r\n");
		}
		
		else if (0 == DPDMstatus)
		{
			deg_Printf("************ there is a PC detect! 2.0 ***********\r\n");
		}
		else
		{
			deg_Printf("************ idle state! 2.0 ***********\r\n");
		}
	}


/****************************************************************
*
*function: 		           DetectUSB2_0_HighandFull	
*describle : 	 usb 2.0 detect operation (high speed and low speed), 
*                    if need call it repeatedly
*
*****************************************************************/
	void DetectUSB2_0_HighandFull(void)
	{
		static int i = 0;
		unsigned int DPDMstatus = 0;
		unsigned int tmp = 0;
		
		i++;
		if (i % 2 == 0)
		{
			deg_Printf("\r\n now pulldown 10k DP DM\r\n");
			REG32(USBCFG) &= ~((1<<17)|(1<<18)|(1<<19));
			REG32(USBCFG) |= (1<<20)|(1<<21);
			REG32(USBCFG) |= (1<<17);
			REG32(USBCFG) &= ~((1<<21)|(1<<20)); //pull up dm dp
			delay_ms(500);
			tmp = REG32(USBCFG);
			DPDMstatus = (tmp>>30);
			deg_Printf("DP DM tmp is %x\r\n",tmp);				
			deg_Printf("DP DM status is %x\r\n",DPDMstatus);			
			if (0 == DPDMstatus)
			{
				deg_Printf("******* there is a PC detect! 2.0 *********\r\n");
			}
		}
		else
		{
			deg_Printf("\r\n now pullup 120k DP DM\r\n");
			REG32(USBCFG) &= ~((1<<17)|(1<<18)|(1<<19));
			REG32(USBCFG) |= (1<<20)|(1<<21);
			REG32(USBCFG) |= (1<<17)|(1<<18)|(1<<19); // pull down dm dp
			delay_ms(500);
			tmp = REG32(USBCFG);
			DPDMstatus = (tmp>>30);
			deg_Printf("DP DM tmp is %x\r\n",tmp);				
			deg_Printf("DP DM status is %x\r\n",DPDMstatus);			
			if (1 == DPDMstatus)
			{
				deg_Printf("********* there is a high speed Usb disk detect! 2.0 *********\r\n");
			}
			else if (2 == DPDMstatus)
			{
				deg_Printf("********** there is a low speed Usb disk detect! 2.0 **********\r\n");
			}
		}
	}


/****************************************************************
*
*function: 		           USBIntDetectStart2_0	
*describle : 	 usb 2.0 interrupt detect operation
*                    working in host mode, when a usb disk is inserted into the board,
*                    interrupt would generate
*                    don't use with USB2_0_Detect_Init together before USBIntDetectEnd2_0,
*                    it will generate conflict
*
*****************************************************************/
void USBIntDetectStart2_0(void)
{
	deg_Printf("********* Start Usb disk Interrupt detect! 2.0 *********\r\n");
	memset__((void *)(&tUsb20IntDetectReserve), 0, sizeof(tUsb20IntDetectReserve));
	tUsb20IntDetectReserve.usbcfg = REG32(USBCFG);
	tUsb20IntDetectReserve.usb_power = USB_Power;
	tUsb20IntDetectReserve.usb_devctl = USB_Devctl;
	tUsb20IntDetectReserve.usb_intrusbe = USB_IntrUSBE;
	tUsb20IntDetectReserve.usb_testmode = USB_Testmode;
	tUsb20IntDetectReserve.ie = REG32(IE);
	
	REG32(USBCFG) |= 0x80;	//osc enable
	delay_us(1);
	REG32(USBCFG) |= 0x40;	//pll enable
	delay_us(1000);
	REG32(USBCFG) |= 0x6400;//vbusvalid adevice downstream_port
	delay_us(100);
	REG32(USBCFG) |= 0x1;	//release sie reset
	delay_us(1);
	REG32(USBCFG) |= 0x4;	//release phy reset
	delay_us(100);

	
	USB_Power = 0x70; //High SPEED
	USB_Devctl=0x03;
	USB_IntrUSBE  = 0x30;

	USB_Testmode = 0; // Close Testmode

	REG32(IE) |= (1 << 17);    //bit[17], usb mac interrupt enable
}


/****************************************************************
*
*function: 		           USBIntDetectEnd2_0	
*describle : 	 usb 2.0 interrupt detect operation
*                    working in host mode, when a usb disk is inserted into the board,
*                    interrupt would generate
*
*****************************************************************/
void USBIntDetectEnd2_0(void)
{
	REG32(USBCFG) = tUsb20IntDetectReserve.usbcfg;
	USB_Power = tUsb20IntDetectReserve.usb_power;
	USB_Devctl = tUsb20IntDetectReserve.usb_devctl;
	USB_IntrUSBE = tUsb20IntDetectReserve.usb_intrusbe;
	USB_Testmode = tUsb20IntDetectReserve.usb_testmode;
	REG32(IE) = tUsb20IntDetectReserve.ie;
	deg_Printf("********* End Usb disk Interrupt detect! 2.0 *********\r\n");
}


/********************************* USB1.1 Detect *********************************/
/*******              call (USB1_1_Detect_Init),  call (DetectUSB1_1)  or 
********              finally call (USB1_1_Detect_End) restore configure 
*****************************************************************************/
/****************************************************************
*
*function:			  USB1_1_Detect_Init	
*describle: 			usb 1.1 detect initialize  
*
*****************************************************************/

void USB1_1_Detect_Init(void)
{
	deg_Printf("\r\nUSB PHY USB1.1 Detect Initial\r\n\r\n");

	memset__((void *)(&tUsb11DetectReserve), 0, sizeof(tUsb11DetectReserve));
	tUsb11DetectReserve.clkcon0 = REG32(CLKCON0);
	tUsb11DetectReserve.clkcon1 = REG32(CLKCON1);
	tUsb11DetectReserve.pa_ie   = REG32(PA_IE);
	tUsb11DetectReserve.fsusb_brgcfg = REG32(FSUSB_BRGCFG);
	tUsb11DetectReserve.fsusb_dpdmctl = REG32(FSUSB_DPDMCTL);

	REG32(CLKCON0) |= (1 << 30); // Select USB2.0 96MHZ As USB1.1 SIE PLL 
//	delay_us(2);	
	REG32(CLKCON1) |= (4 << 5); // USB1.1 SIE CLK DIV, USB1.1 CLK=48MHZ
//	delay_us(2);		
	REG32(PA_IE) &= ~(3<<10);
//	SOFT_RST |= (1<<4);  // release reset sie mode
//	PCON0 &= ~(1<<30);
	
	REG32(FSUSB_BRGCFG) |= (1<<2);  //PHY power on
	delay_us(100);
	REG32(FSUSB_BRGCFG) |= (1<<3);  //DPPSEL
	delay_us(100);
	REG32(FSUSB_BRGCFG) |= (1<<5)|(1<<6)|(1<<7);  //
//	FSUSB_BRGCFG = 0x35d; /* phy enable, sie, slow */ 
	REG32(FSUSB_DPDMCTL) = 0x00; /*  */

}


/****************************************************************
*
*function:			  USB1_1_Detect_End	
*describle: 			usb 1.1 detect End  
*
*****************************************************************/

void USB1_1_Detect_End(void)
{
	deg_Printf("\r\nUSB PHY USB1.1 Detect Over!\r\n\r\n");

	REG32(CLKCON0) = tUsb11DetectReserve.clkcon0;
	REG32(CLKCON1) = tUsb11DetectReserve.clkcon1;
	REG32(PA_IE)   = tUsb11DetectReserve.pa_ie;
	REG32(FSUSB_BRGCFG) = tUsb11DetectReserve.fsusb_brgcfg;
	REG32(FSUSB_DPDMCTL) = tUsb11DetectReserve.fsusb_dpdmctl;
}


/****************************************************************
*
*function: 		  DetectUSB1_1	
*describle : 	 usb 1.1 detect operation, if need call it repeatedly
*
*****************************************************************/
void DetectUSB1_1(void)
{
	static int i = 0;
	unsigned int DPDMstatus = 0;
	unsigned int tmp = 0;

	i++;
	if (i % 2 == 0)
	{
		deg_Printf("\r\n now pullup DM 120k\r\n");
		REG32(FSUSB_DPDMCTL) &= ~((1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4));   //clear DM DP
		REG32(FSUSB_DPDMCTL) &= ~(1<<7);
		REG32(FSUSB_DPDMCTL) |= (1<<4)|(1<<2);
//			FSUSB_DPDMCTL |= (1<<0)|(1<<2);     //no sensitive for sometime detect value is wrong
//			FSUSB_DPDMCTL = 0x05;
		delay_ms(500);
		tmp = REG32(FSUSB_DPDMCTL);
		DPDMstatus = ((tmp & (3<<5))>>5);
		deg_Printf("DP DM tmp is %x\r\n",tmp);				
		deg_Printf("DP DM status is %x\r\n",DPDMstatus);
		if (DPDMstatus == 0)
		{
			deg_Printf("****************pc detect***************\r\n");
		}
		else if (DPDMstatus == 1 || DPDMstatus == 3)
		{
			deg_Printf("idle\r\n");
		}
	}
	else
	{
		deg_Printf("\r\n now pulldown DP and DM\r\n");
		REG32(FSUSB_DPDMCTL) &= ~((1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4));   //clear DM DP
		REG32(FSUSB_DPDMCTL) &= ~(1<<7);
		REG32(FSUSB_DPDMCTL) |= (1<<1)|(1<<3);			
//			FSUSB_DPDMCTL = 0x0a;
		delay_ms(500);
		tmp = REG32(FSUSB_DPDMCTL);
		DPDMstatus = ((tmp & (3<<5))>>5);
		deg_Printf("DP DM tmp is %x\r\n",tmp);				
		deg_Printf("DP DM status is %x\r\n",DPDMstatus);
		if (DPDMstatus & 2)
		{
			deg_Printf("******************high speed u disk****************\r\n");
		}
		else if (DPDMstatus & 1)
		{
			deg_Printf("******************low speed u disk *****************\r\n");
		}
		else if (0 == DPDMstatus)
		{
			deg_Printf("idle2\r\n");
		}
	}
}

/********************************* IR Detect *********************************/
/*******              
********              
*****************************************************************************/
/****************************************************************
*
*function: 		  ir_start_detect	
*describle : 	 ir detect operation
*
*****************************************************************/

void ir_start_detect(void)
{	
	REG32(IE) |= BIT(12);//IRQ 
	REG32(IR_CON0) |= BIT(1); //enable ir interrupt 
//	IR_CON0 |= BIT(4); //
	REG32(IR_CON0) |= BIT(0); //enable ir
}

/****************************************************************
*
*function: 		  ir_init	
*describle : 	 ir detect initialize
*
*****************************************************************/
void ir_init(void) 
{ 
	deg_Printf("********* Start IR Interrupt detect! *********\r\n");
	memset__((void *)(&tIrDetectReserve), 0, sizeof(tIrDetectReserve));
	tIrDetectReserve.clkcon0= REG32(CLKCON0);
	tIrDetectReserve.clkcon1 = REG32(CLKCON1);
	tIrDetectReserve.pcon0 = REG32(PCON0);
	tIrDetectReserve.pmap_cfg0 = REG32(PMAP_CFG0);
#if (PMAP_PA4NO_PG4 == 1)	
	tIrDetectReserve.pa_dir = REG32(PA_DIR);
	tIrDetectReserve.pa_ie = REG32(PA_IE);
	tIrDetectReserve.pa_pu0 = REG32(PA_PU0);
#else
	tIrDetectReserve.pg_dir = REG32(PG_DIR);
	tIrDetectReserve.pg_ie  = REG32(PG_IE);
	tIrDetectReserve.pg_pu0 = REG32(PG_PU0);
#endif
	tIrDetectReserve.ir_repeat_con = REG32(IR_REPEAT_CON);
	tIrDetectReserve.ir_start_con  = REG32(IR_START_CON);
	tIrDetectReserve.ir_cycle_con  = REG32(IR_CYCLE_CON);
	tIrDetectReserve.ie            = REG32(IE);
	tIrDetectReserve.ir_con0       = REG32(IR_CON0);

#if 1//1M 
	REG32(CLKCON0) &= ~(BIT(25));//UPLL 
	REG32(CLKCON0) |= BIT(26);//UPLL/8 
	REG32(CLKCON1) &= ~(0x1F<< 16);//UPLL/8/30 
	REG32(CLKCON1) |= (0x1E<< 16); 

	REG32(CLKCON0) &= ~(BIT(10)|BIT(27)); 
	REG32(PCON0) &= ~(BIT(16));//enable IR clock 

	REG32(PMAP_CFG0) &= ~(0x3<<8);
	
#if (PMAP_PA4NO_PG4 == 1)
	REG32(PMAP_CFG0) |= (1<<8);//PA4 
	REG32(PA_DIR) |= (1<<4)|(1<<3);//128pin封装的是PA3和PA4绑在一起 
	REG32(PA_IE) |= BIT(4); 
//	PA_IE &= ~BIT(4);//turn off digital input 
	REG32(PA_PU0) &= ~(BIT(3)|BIT(4)); 

#else
//    PG4 need trip line from IR pin to PG4
	REG32(PMAP_CFG0) |= (0x2<<8);//PG4 
	REG32(PG_DIR) |= (1<<4);//PG4 input
	REG32(PG_IE)  |= (BIT(4));//turn on digital input 
	REG32(PG_PU0) &= ~(BIT(4)); 
#endif

	//IE |= BIT(12);//IRQ 
	//IR_CON0 |= BIT(1); 

	REG32(IR_REPEAT_CON) = 0x08;               //repeat_cnt:0x02 
	 //4.5ms   9ms 
	REG32(IR_START_CON) = (0x11<<8) | 0x22; 

	REG32(IR_CYCLE_CON) = (0x90<<8) | 0x50;    //one_full:0x5e,zero_cycle:0x28 
	//IR_CON0 |= IREN;//IR enable 
#else//32k 
	CLKCON0 &= ~BIT(27); 
	CLKCON0 |= BIT(10); 
	PCON0 &= ~BIT(16);//enable IR clock 

	PMAP_CFG0 &= ~(0x3<<8); 
	PMAP_CFG0 |= (1<<8);//PA4 

	PA_DIR |= (1<<4)|(1<<3); 
	PA_IE &= ~BIT(4); 

	IR_REPEAT_CON = 0x04;               //repeat_cnt:0x02 
	IR_START_CON = (0x09<<8) | 0x12; 
	IR_CYCLE_CON = (0x5e<<8) | 0x28;    //one_full:0x5e,zero_cycle:0x28 

#endif 

	ir_start_detect();
	deg_Printf("ir init over\r\n"); 
}

/****************************************************************
*
*function: 		  ir_End	
*describle : 	 ir detect end
*
*****************************************************************/
void ir_End(void) 
{
	REG32(CLKCON0) = tIrDetectReserve.clkcon0;
	REG32(CLKCON1) = tIrDetectReserve.clkcon1;
	REG32(PCON0) = tIrDetectReserve.pcon0;
	REG32(PMAP_CFG0) = tIrDetectReserve.pmap_cfg0;
#if (PMAP_PA4NO_PG4 == 1)	
	REG32(PA_DIR) = tIrDetectReserve.pa_dir;
	REG32(PA_IE) = tIrDetectReserve.pa_ie;
	REG32(PA_PU0) = tIrDetectReserve.pa_pu0;
#else
	REG32(PG_DIR) = tIrDetectReserve.pg_dir;
	REG32(PG_IE)  = tIrDetectReserve.pg_ie;
	REG32(PG_PU0) = tIrDetectReserve.pg_pu0;
#endif
	REG32(IR_REPEAT_CON) = tIrDetectReserve.ir_repeat_con;
	REG32(IR_START_CON)  = tIrDetectReserve.ir_start_con;
	REG32(IR_CYCLE_CON)  = tIrDetectReserve.ir_cycle_con;
	REG32(IE) 		     = tIrDetectReserve.ie;
	REG32(IR_CON0)	     = tIrDetectReserve.ir_con0;
	deg_Printf("********* End IR Interrupt detect! *********\r\n");
}


/***************************** test function ********************************/

/****************************************************************
*
*function: 		  IoDetectUsb2_0	
*describle : 	 usb2.0 operation test
*
*****************************************************************/

void IoDetectUsb2_0(void)
{
	int i = 0;
	USB2_0_Detect_Init();
	while(i++ < 20)
	{
		DetectUSB2_0();
		delay_ms(1000);
	}
	USB2_0_Detect_End();
}

/****************************************************************
*
*function: 		  IoDetectUsbInt2_0	
*describle : 	 usb2.0 interrupt operation test
*
*****************************************************************/

void IoDetectUsbInt2_0(void)
{
	int i = 0;
	USBIntDetectStart2_0();
	while(i++ < 30)
	{
		delay_ms(1000);
	}
	USBIntDetectEnd2_0();
}


/****************************************************************
*
*function: 		  IoDetectUsb1_1	
*describle : 	 usb1.1 operation test
*
*****************************************************************/

void IoDetectUsb1_1(void)
{
	int i = 0;
	USB1_1_Detect_Init();
	while(i++ < 50)
	{
		DetectUSB1_1();
		delay_ms(200);
	}
	USB1_1_Detect_End();
}

void IoDetectUsbIntFlag2_0(void)
{
	u8 tmp;
	tmp = USB_IntrUSB;
	if ((tmp & 0x10) == 0x10)	//host conect to device INTRRUPT,valid in host mdoe
	{
		deg_Printf("USB Conn_interrupt INTRRUPT\n");
//		device_online |= BIT(0);
	}

	if ((tmp & 0x20) == 0x20)	
	{
		deg_Printf("USB Dis Conn_interrupt INTRRUPT\n");
		REG32(USBCFG) |= ((1<<0)|(1<<2));
//		device_online &=~BIT(0);
	}
}

/****************************************************************
*
*function: 		  IoDetectIR	
*describle : 	 IR interrupt operation test
*
*****************************************************************/
void IoDetectIR(void)
{
	int i = 0;
	ir_init();
	while(i++ < 50)
	{
		delay_ms(1000);
	}
	ir_End();
}


void IoDetectIRIntFlag(void)
{
	u32 tmpIRCON0 = 0;
	u32 cIR_DATAH = 0;
	u32 cIR_DATAL = 0;
	
	tmpIRCON0 = REG32(IR_CON0);
	cIR_DATAH = REG32(IR_DATAH);
	cIR_DATAL = REG32(IR_DATAL);
	deg_Printf("\r\nir irq\r\n");
	if (tmpIRCON0 & (1<<2))
	{
		REG32(IR_CON0) |= BIT(4); 
		deg_Printf("ircon0 = %x\r\n",tmpIRCON0);
		deg_Printf("ir_dataH = %x\r\n",cIR_DATAH);
		deg_Printf("ir_dataL = %x\r\n",cIR_DATAL);
	//			SINGE_DEBUG("IR receiver done\r\n");
	}
}
