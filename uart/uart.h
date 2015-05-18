/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : uart.h
* Author             : pengtao_zhang
* Version            : V0719a
* Date               : 07/19/2013  ;mm/dd/yyyy
* Description        : uart HEADER FILE.
***************************************************************************/
#ifndef _UART_H_
#define _UART_H_

#include "../config/config.h"

//========== UART select ========
#define UART0_MAP0	0
#define UART1_MAP1	1

#define UART_USE	UART1_MAP1
//================================= 

#define UART_BAUDRATE   115200

#if (0 == DEBUG_EN)
#define  deg(...)              
#define  deg_Printf(...)       
#define  deg_PrintfBuf(p,i)     
#define  my_printf(...)		
#else
#define  deg(...)               //uart_Printf(__VA_ARGS__)
#define  deg_Printf(...)        uart_Printf(__VA_ARGS__)  
#define  deg_PrintfBuf(p,i)     uart_PrintfBuf(p,i)
#define  my_printf(...)			//uart_Printf(__VA_ARGS__)
#endif

void uart_Init(void);
void uart_PutChar(u8 c);
void uart_PutChar_n(u8 c);
void uart_PutStr(u8 *p_str) ;
void uart_Put_hex(DWORD dwHex, BOOL bMode);
void uart_Put_udec(DWORD dwDec);
void uart_Put_dec(long lDec);
void uart_Printf(const char *pszStr, ...);
void uart_PrintfBuf(void *pBuf, int iDataLen);

#endif
