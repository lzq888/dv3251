/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : int.c
* Author             : pengtao_zhang
* Version            : V0731a
* Date               : 07/31/2013
* Description        : This file provides all the interrupt firmware functions.
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
void IRQ_EINT_Handle(void)   __attribute__ ((interrupt("IRQ"))) __attribute__((section(".text.irq_entry")));
void FIQ_EINT_Handle(void)   __attribute__ ((interrupt("FIQ")));
volatile BOOL bIRQStateFlag=0;
/*******************************************************************************
* Function Name  : IRQ_EINT_Handle
* Description    : normal interrupt
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
extern u32 Ep1Deal;
void IRQ_EINT_Handle(void)
{
	u32 u32IrqFlag;
	bIRQStateFlag = 1;
	u32IrqFlag = REG32(IRQPND);
	//deg_Printf("\n IrqFlag =%x\n",u32IrqFlag);
	if(u32IrqFlag & BIT(JPEG_INT))
		jpeg_Isr();

	if(u32IrqFlag & BIT(TIMER0_INT))
		timer0_isr();

	if(u32IrqFlag & BIT(TIMER1_INT))
		timer1_isr();

	if(u32IrqFlag & BIT(TIMER2_INT))
		timer2_isr();
	if(u32IrqFlag & BIT(USB_MC_INT))
	{
		usb_irq_isr();
		//IoDetectUsbIntFlag2_0();	//for temp test, need be delete
	}	
	
	if(u32IrqFlag & BIT(TIMER3_INT))
		timer3_isr();

	if(u32IrqFlag & BIT(CSI_INT))
	{
		csi_Isr();
	}
//	Ep1Deal = 0;

	if(u32IrqFlag & BIT(DMA_INT))
		gpdma_Isr();

	if(u32IrqFlag & BIT(AUADC_INT))
	{
		audio_adc_isr();
	}

	if(u32IrqFlag & BIT(OBUF_INT))
	{
		dac_irq();
	}

	if(u32IrqFlag & BIT(LCD_INT))
		lcd_Isr();

	if(u32IrqFlag & BIT(USB_MC_INT))
	{
		usb_irq_isr();
		//IoDetectUsbIntFlag2_0();	//for temp test, need be delete
	}	

	/*if (u32IrqFlag & (1 << IR_INT)) // ir mac pnding read only reg
	{
		IoDetectIRIntFlag();	//for temp test, need be delete
	}*/

	if(u32IrqFlag & BIT(PORT_WAKEUP_INT)) {	// port wakeup
	
//		REG32(UART0_DATA) = 0x55;
//		while((REG32(UART0_PND) & 0x2)==0);
//		REG32(UART0_PND) |= BIT(1);

//		PA_PU0 |= (1<<2);	/* PA2 Pull Up */
		REG32(PORTWKEN) &= 0x0F;       // Clear the pending
//		deg_Printf("\n* IRQ port");

		REG32(IRQPND) &= ~(1 << 19);
	}
	
	if(u32IrqFlag & BIT(RTC_INT)) {
		
//		REG32(UART0_DATA) = 0x33;
//		while((REG32(UART0_PND) & 0x2)==0);
//		REG32(UART0_PND) |= BIT(1);
		
		deg_Printf("\n* rtc");

		REG32(IRT_CPND) |= (1<<0);
		REG32(IRQPND) &= ~(1 << 13);
	}


	bIRQStateFlag = 0;
}

/*******************************************************************************
* Function Name  : FIQ_EINT_Handle
* Description    : fast interrupt
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void FIQ_EINT_Handle(void)
{
           
}

/*******************************************************************************
* Function Name  : SetIntSrc
* Description    : turn on interrupt
* Input          : interrupt ID
* Output         : None
* Return         : None
*******************************************************************************/
void SetIntSrc(INT_SRC eIntSrc)
{
	SETB(REG32(IE), eIntSrc);
}

/*******************************************************************************
* Function Name  : ClrIntSrc
* Description    : turn off interrupt
* Input          : interrupt ID
* Output         : None
* Return         : None
*******************************************************************************/
void ClrIntSrc(INT_SRC eIntSrc)
{
	CLRB(REG32(IE), eIntSrc);
}
