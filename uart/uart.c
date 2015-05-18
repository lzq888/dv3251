/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : uart.c
* Author             : pengtao_zhang
* Version            : V0719a
* Date               : 07/19/2013 ;mm/dd/yyyy
* Description        : This file provides all the uart firmware functions.
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
* Function Name  : uart_Init
* Description    : initialize the uart
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void uart_Init(void) 
{
	REG32(PMAP_CFG0)  &= ~((1<<7) | (1<<6) | (1<<5) | (1<<4));
	#if(UART_USE == UART1_MAP1)
	REG32(PG_DIR) &= ~(1<<12);
	REG32(PMAP_CFG0)  |= 1<<7;
	REG32(UART1_BAUD) = APB_CLK/UART_BAUDRATE - 1;
	REG32(UART1_CFG)  = 0x10;
	#elif(UART_USE == UART0_MAP0)
	REG32(PA_DIR) &= ~(1<<9);
    REG32(PMAP_CFG0)  |= 1<<4;
	REG32(UART0_BAUD) = APB_CLK/UART_BAUDRATE - 1;
	REG32(UART0_CFG)  = 0x10;	
	#endif
}

/*******************************************************************************
* Function Name  : uart_PutChar
* Description	 : uart put a char
* Input 		 : c : put the char
* Output         : None
* Return		 : None
*******************************************************************************/
void uart_PutChar(u8 c) 
{
	if(bIRQStateFlag)
	{
		#if(UART_USE == UART1_MAP1)
		REG32(UART1_DATA) = c;
		while((REG32(UART1_CFG) & BIT(9))==0);
		REG32(UART1_CPND) |= BIT(9);	
		#elif(UART_USE == UART0_MAP0)
		REG32(UART0_DATA) = c;
		while((REG32(UART0_PND) & 0x2)==0);
		REG32(UART0_PND) |= BIT(1);
		#endif
	}
	else
	{
		asm("msr cpsr_c,#0xdf");      //close global IRQ and FIQ
		#if(UART_USE == UART1_MAP1)
		REG32(UART1_DATA) = c;
		while((REG32(UART1_CFG) & BIT(9))==0);
		REG32(UART1_CPND) |= BIT(9);	
		#elif(UART_USE == UART0_MAP0)
		REG32(UART0_DATA) = c;
		while((REG32(UART0_PND) & 0x2)==0);
		REG32(UART0_PND) |= BIT(1);
		#endif
		asm("msr cpsr_c,#0x5f");      //open global IRQ
	}
}

/*******************************************************************************
* Function Name  : uart_PutChar_n
* Description    : '\n' denote newline
* Input          : c:character
* Output         : None
* Return         : None
*******************************************************************************/
void uart_PutChar_n(u8 c)
{
   	if('\n' == c)
	{
		uart_PutChar(0x0D);
		uart_PutChar(0x0A);
	}
	else
	{
       	 	uart_PutChar(c);
	}
}

/*******************************************************************************
* Function Name  : uart_PutStr
* Description    : uart output strings
* Input          : p_str:strings pointer
* Output         : None
* Return         : None
*******************************************************************************/
void uart_PutStr(u8 *p_str)     
{
    while(*p_str)
        uart_PutChar_n(*p_str++);
}

/*******************************************************************************
* Function Name  : uart_Put_hex
* Description    : uart output  use hex number
* Input          : dwHex: unsigned  long number
*                  bMode: 0: small letter, 1:capital letter
* Output         : None
* Return         : None
*******************************************************************************/
void uart_Put_hex(DWORD dwHex, BOOL bMode)
{
    BYTE HexTable[16] = {'0','1','2','3','4','5','6','7','8','9',bMode?'A':'a'};
    BYTE aHex[8] = {0};
    int i;

    for (i=11; i<16; i++)
    {
        HexTable[i] = HexTable[i-1] + 1;
    }

    i = 8;
    do
    {
        aHex[--i] = dwHex & 0xf;
        dwHex >>= 4;
    } while (dwHex);

    while (i < 8)
    {
        uart_PutChar(HexTable[aHex[i++]]);
    }
}

/*******************************************************************************
* Function Name  : uart_Put_udec
* Description    : uart output  use unsigned decimal number
* Input          : dwDec:  unsigned  long number
* Output         : None
* Return         : None
*******************************************************************************/
void uart_Put_udec(DWORD dwDec)
{
    BYTE aDec[10] = {0};
    int i = 10;

    do
    {
       aDec[--i] = '0' + dwDec % 10;
       dwDec /= 10;
    } while (dwDec);

    while (i < 10)
    {
       uart_PutChar(aDec[i++]);
    }
}

/*******************************************************************************
* Function Name  : uart_Put_dec
* Description    : uart output  use signed decimal number
* Input          : dwDec:  signed  long number
* Output         : None
* Return         : None
*******************************************************************************/
void uart_Put_dec(long lDec)
{
    BYTE aDec[10] = {0};
    int i = 10;

    if (lDec < 0)
    {
        uart_PutChar('-');
        lDec = ~(lDec - 1);
    }

    do
    {
       aDec[--i] = '0' + lDec % 10;
       lDec /= 10;
    } while (lDec);

    while (i < 10)
    {
       uart_PutChar(aDec[i++]);
    }
}

/*******************************************************************************
* Function Name  : uart_Printf
* Description    : uart output character,type:
*                  %d,%i:signed long decimal number
*                   %u  :unsigned long decimal number
*                   %x  :unsigned  long hex number(small letter)
*                   %X  :unsigned  long hex number(capital letter)
*                   %c  :character
*                   %s  :character string
* Input          :  *pszStr: char type pointer
* Output         : None
* Return         : None
*******************************************************************************/
void uart_Printf(const char *pszStr, ...)
{
    va_list arglist;
	va_start(arglist, pszStr);
	if((bI2CBusy_Flag == 0)&&(bSFBusy_Flag == 0))
	{
		 #if(USER_CONFIG == CONFIG_AX3251_K6000)
		 i2c_SendStop(); 
		 #endif
		 while ('\0' != *pszStr)
		 {
			 if ('%' != *pszStr)
			 {
				  uart_PutChar_n(*pszStr);
			 }
			 else
			 {
				  switch (*(++pszStr))
				  {
				  case '\0':
					   uart_PutChar_n('%');
					   pszStr--;
					   break;

				  case 'd':
				  case 'i':
					   uart_Put_dec(va_arg(arglist, long));
					   break;

				  case 'u':
					   uart_Put_udec(va_arg(arglist, DWORD));
					   break;

				  case 'x':
					   uart_Put_hex(va_arg(arglist, DWORD), FALSE);
					   break;

				  case 'X':
					   uart_Put_hex(va_arg(arglist, DWORD), TRUE);
					   break;

				  case 'c':
					   uart_PutChar_n(va_arg(arglist, int));
					   break;

				  case 's':
					   uart_PutStr(va_arg(arglist, BYTE *));
					   break;

				  default:                                                        
					   uart_PutChar_n('@');
					   break;
				  }
			 }
			 pszStr++;
		 }
	}
}

/*******************************************************************************
* Function Name  : uart_PrintfBuf
* Description    : uart output character use hex number(capital letter)
* Input          : *pBuf   :output character pointer
*                  iDataLen:character length
* Output         : None
* Return         : None
*******************************************************************************/
void uart_PrintfBuf(void *pBuf, int iDataLen)
{
	int i;
	u8 *pTempBuf = (BYTE *)pBuf;
	//uart_Printf("pBuffAddr = 0x%X", (int)pBuf);
	for (i=0; i<iDataLen; i++)
	{
		if (0 == i%32)
		{
			uart_Printf("\n");
		}
		uart_Printf("%X ", pTempBuf[i]);
	}
	uart_Printf("\n");
}
