/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : int.h
* Author             : pengtao_zhang
* Version            : V0731a
* Date               : 07/31/2013
* Description        : interrupt HEADER FILE.
***************************************************************************/
#ifndef _INT_H_
#define _INT_H_


typedef enum
{
    TIMER0_INT,
    TIMER1_INT,
    TIMER2_INT,
    TIMER3_INT,
    SPI0_INT,
    SPI1_INT,
    IIC_INT,
    SDC0_INT,
    SDC1_INT,
    UART0_INT,
    UART1_INT,
    DMA_INT,
    IR_INT,
    RTC_INT,
    WDT_INT,
    CSI_INT,
    JPEG_INT,
    USB_MC_INT,
    IIS_INT,
    PORT_WAKEUP_INT,
    LVD_INT,
    OBUF_INT,
    AUADC_INT,
    LCD_INT
}INT_SRC;

extern volatile BOOL bIRQStateFlag;

void SetIntSrc(INT_SRC eIntSrc);
void ClrIntSrc(INT_SRC eIntSrc);

#endif
