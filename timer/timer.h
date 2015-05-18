/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : timer.h
* Author             : pengtao_zhang
* Version            : V0816a
* Date               : 08/16/2013
* Description        : timer HEADER FILE.
***************************************************************************/
#ifndef _TIMER_H_
#define _TIMER_H_

extern volatile u32 u32Timer0_1msCnt;
extern volatile u32 u32Delay_1msCnt;
extern volatile u32 u32Test_1msCnt;
void timer_Init(void);

void timer_Timer0_Start(void);
void timer_Timer0_Stop(void);
void timer_Timer1_Start(void);
void timer_Timer1_Stop(void);
void timer_Timer2_Start(void);
void timer_Timer2_Stop(void);
void timer_Timer3_Start(void);
void timer_Timer3_Stop(void);

void timer0_isr(void);
void timer1_isr(void);
void timer2_isr(void);
void timer3_isr(void);

#endif
