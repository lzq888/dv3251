/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : timer.c
* Author             : pengtao_zhang
* Version            : V0816a
* Date               : 08/16/2013
* Description        : This file provides all the timer firmware functions.
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

/*******************************************************************************
* Function Name  : timer_Init
* Description    : timer clock initial
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void timer_Init(void)
{
	REG32(PCON0) &= ~BIT(11);  //timer clock enable
}

/*******************************************************************************
* Function Name  : timer_Timer0_Start
* Description    : timer0 start ; 1ms
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void timer_Timer0_Start(void)
{	
#define T0BAUDRATE	1000
#define T0PSR	1
#define T0PR	(((APB_CLK/T0BAUDRATE)/(1<<T0PSR))-1)
	REG32(TMR0_CFG) = 0x2010 | (T0PSR<<8);		
	REG32(TMR0_PR) = T0PR;  
	REG32(TMR0_CNT) = 0x0000;
	SetIntSrc(TIMER0_INT);
	u32Timer0_1msCnt = 0;
	u32Delay_1msCnt = 0;
}

/*******************************************************************************
* Function Name  : timer_Timer1_Stop
* Description    : timer1 stop
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void timer_Timer0_Stop(void)
{
	REG32(TMR0_CFG) &= ~(BIT(5)|BIT(4));  //timer1 disable
	ClrIntSrc(TIMER0_INT);
}

/*******************************************************************************
* Function Name  : timer_Timer1_Start
* Description    : timer1 start ; 10ms
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void timer_Timer1_Start(void)
{
#define T1BAUDRATE	100
#define T1PSR	5
#define T1PR	(((APB_CLK/T1BAUDRATE)/(1<<T1PSR))-1)
	REG32(TMR1_CFG) = 0x2010 | (T1PSR<<8);		
	REG32(TMR1_PR) = T1PR;  
	REG32(TMR1_CNT) = 0x0000;
	SetIntSrc(TIMER1_INT);
	//deg_Printf("Timer1 Start\n");
}

/*******************************************************************************
* Function Name  : timer_Timer1_Stop
* Description    : timer1 stop
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void timer_Timer1_Stop(void)
{
	g_stcJpegInfo.bTimeOverFlag = TRUE;
	REG32(TMR1_CFG) &= ~(BIT(5)|BIT(4));  //timer1 disable
	ClrIntSrc(TIMER1_INT);
	//deg_Printf("Timer1 stop\n");
}

/*******************************************************************************
* Function Name  : timer_Timer2_Start
* Description    : timer2 start; (1/30)s
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void timer_Timer2_Start(void)
{
#define T2BAUDRATE	30
#define T2PSR	7
#define T2PR	(((APB_CLK/T2BAUDRATE)/(1<<T2PSR))-1)
	REG32(TMR2_CFG) = 0x2010 | (T2PSR<<8);		
	REG32(TMR2_PR) = T2PR;  
	REG32(TMR2_CNT) = 0x0000;
	SetIntSrc(TIMER2_INT);
	//deg_Printf("Timer2 Start\n");
}

/*******************************************************************************
* Function Name  : timer_Timer2_Stop
* Description    : timer2 stop
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void timer_Timer2_Stop(void)
{
	g_stcJpegInfo.bFileOverFlag = TRUE;
	REG32(TMR2_CFG) &= ~(BIT(5)|BIT(4));  //timer2 disable
	ClrIntSrc(TIMER2_INT);
	//deg_Printf("Timer2 stop\n");
}

/*******************************************************************************
* Function Name  : timer_Timer3_Start
* Description    : timer3 start; one ADC conversation can be completed in 13 ADC clocks cycle. In case of margin, so timer3's frequency is ADCBAUD/20
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void timer_Timer3_Start(void)
{
#define T3BAUDRATE		(ADC_BAUDRATE/20)
#define T3PSR			0
#define T3PR			(((APB_CLK/T3BAUDRATE)/(1<<T3PSR))-1)
	REG32(TMR3_CFG) = 0x2000 | (T3PSR<<8);		
	REG32(TMR3_PR) = T3PR;  
	REG32(TMR3_CNT) = 0x0000;
	REG32(TMR3_CPND) |= (BIT(1)|BIT(0)); 
	SetIntSrc(TIMER3_INT);
	REG32(TMR3_CFG) |= BIT(4);	
}

/*******************************************************************************
* Function Name  : timer_Timer3_Stop
* Description    : timer3 stop
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void timer_Timer3_Stop(void)
{
	REG32(TMR3_CFG) &= ~(BIT(5)|BIT(4));  //timer2 disable
	ClrIntSrc(TIMER3_INT);
}

