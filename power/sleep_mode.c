/* Filename:     sleep_mode.c
 * Version:      1.0
 * Author:       zhiyong_zeng <zhiyong_zeng@buildwin.com.cn>
 * Started:      10th March 2014
 * Target Soc:   arm(32bit)
 * 
 * Description: Foring Hunter Soc to enter sleep mode, this time, all clock sources,
 * and all memory chip select signals are disabled to further reduce power consumption.
 * However, before entering sleep mode, all peripherals should be disable separately,
 * especially, analog peripherals and memory, should be closed manually.
 * 
 * Note: Before entering sleep mode, the system clock is recommended to change back
 * to RC oscillator clock as the system clock.
 * During sleep mode, the device can be wake up by watchdog interrupt, rtcc interrupt, 
 * external port wakeup interrupt, MCLR reset.
 * Importantly, when wake up from sleep mode, the device will be reset directly.
 * 
 * Copyright (C) 2014 BuildWin Co.Ltd, Zhuhai, China
 * 		http://www.buildwin.com.cn
 *
 * Hunter Low Power Managerment Unit
 * */

#include "../header/include.h"
#include <stdbool.h>

#include "./cpu_mode.h"

//#define RTCMODE_EN		/* 是否使用RTC'秒唤醒'模式 */

/* hold模式下，是否使能中断 */
#define PORT_WAKE_INTERRUPT

/* arm异常矢量表起始地址，根据链接地址具体情况具体裁定 */
#define VECTOR_TABLE_ADDRESS	0x20000000

/* SRAM起始地址 */
#define	SRAM_ADDRESS			0x10000000

/* Hold模式下的代码起始地址 */
#define	SLEEP_CODE_ADDRESS		0x10000400

/* hold模式下页表的基地址 */
#define	HOLD_TBL_ADDRESS		0x10004000

/* hold模式下irq stack的起始地址 */
#define	HOLD_IRQ_STACK			0x10004000

/* Hunter Supports Ports Interrupt And Wake Up Function.
 * There Are Four Modules.
 * */
#define PORTWK_MODULE0		/* PA2 */
#define PORTWK_MODULE1		/* PA3 */
#define PORTWK_MODULE2		/* PG11/LSA1, Select One Via PMAP_CFG0[22:21], Default PG11 */
#define PORTWK_MODULE3		/* PG12/IR/LSA0/RTC/PA5/PA9/PE2/PD12, Select One Via PMAP_CFG0[28:26], Default PG12 */

/* Port Wakeup Event Select
 * Note:
 * */
#define RISING		0
#define FALLING		1

#define PORTWK0_EDG 	FALLING		/*  */
#define PORTWK1_EDG 	RISING
#define PORTWK2_EDG 	FALLING
#define PORTWK3_EDG 	RISING


/*
 * 由此入口进入sleep模式
 * 注意:进入sleep之前, 推荐“切换内部的RC晶振作为系统clock”;
 * 		数字模块被自动关闭, 但需手动关闭模拟模块(如adc/dac);
 * 		唤醒后，系统自动复位...
 * */
void cpu_sleep_mode(void) {
	
	/************************ Base IO Setting ****************************/
	/* 根据外围的实际情况来调整，才能使功耗降到最低 */
//	PA_DIR = 0xF7;PA_DIR = 0xFF;PA_DIR = 0xFF;PA_DIR = 0xFF;
//	PA_PU0 = 0xFF;PA_PU0 |= BIT(7);PUP3 = 0xFF;PUP1 |= BIT(6) | BIT(7);

	__asm__("nop");
	__asm__("nop");
	__asm__("nop");
	
	/************************ Port Wakeup IO Setting *********************/
	/* 根据外围的实际硬件情况来进行调整 */
#ifdef PORTWK_MODULE0
#if(FALLING == PORTWK0_EDG)
	REG32(PA_PU0) |= BIT(2);	/* PA2 Pull Up */
	REG32(PA_DIR) |= BIT(2);
#else
	REG32(PA_PD0) |= BIT(2);	/* PA2 Pull Down */
	REG32(PA_DIR) |= BIT(2);
#endif
#endif	/* PORTWK_MODULE0 */

#ifdef PORTWK_MODULE1
#if(FALLING == PORTWK1_EDG)
	REG32(PA_PU0) |= BIT(3);	/* PA3 Pull Up */
	REG32(PA_DIR) |= BIT(3);
#else
	REG32(PA_PD0) |= BIT(3);	/* PA3 Pull Down */
	REG32(PA_DIR) |= BIT(3);
#endif
#endif	/* PORTWK_MODULE1 */

#ifdef PORTWK_MODULE2
#if(FALLING == PORTWK2_EDG)
	REG32(PG_PU0) |= BIT(11);	/* PG11/LSA1 Pull Up */
	REG32(PG_DIR) |= BIT(11);
#else
	REG32(PG_PD0) |= BIT(11);	/* PG11/LSA1 Pull Down */
	REG32(PG_DIR) |= BIT(11);
#endif
#endif	/* PORTWK_MODULE2 */

#ifdef PORTWK_MODULE3
#if(FALLING == PORTWK3_EDG)
	REG32(PG_PU0) |= BIT(12);	/* PG12/IR/LSA0/RTC/PA5/PA9/PE2/PD12 Pull Up */
	REG32(PG_DIR) |= BIT(12);
#else
	REG32(PG_PD0) |= BIT(12);	/* PG12/IR/LSA0/RTC/PA5/PA9/PE2/PD12 Pull Down */
	REG32(PG_DIR) |= BIT(12);
#endif
#endif	/* PORTWK_MODULE3 */


	/************************ Close Analog Module *********************/
//    LVDCON |= 0x2C;
//    SPMODE &= ~BIT(4);
//    UARTCON = 0x00;
//    CLKCON |= BIT(2);
//    asm("nop");asm("nop");asm("nop");
//    CLKCON &= ~0x03;
//    asm("nop");asm("nop");
//    CLKCON |= 0x48;
//    asm("nop");asm("nop");asm("nop");asm("nop");
//    CLKCON |= 0x01;
//    asm("nop");asm("nop");asm("nop");asm("nop");
//    CLKCON &= ~BIT(2);
//    asm("nop");asm("nop");asm("nop");
//
//    ATCON1 = 0x44;
//    PLLCON = 0x00;
//
//    PCON0 |= BIT(4);


__SKIP_BACK:

	/************************ Port Wakeup Edge Setting *********************/
	/* 根据外围的实际硬件情况来进行调整 */

#ifdef PORTWK_MODULE0
#if(FALLING == PORTWK0_EDG)
	REG32(PORTWKEDG) |= BIT(0);        // PA2 falling edge wakup
#else
	REG32(PORTWKEDG) &= ~BIT(0);        // PA2 Rising edge wakup
#endif
#endif	/* PORTWK_MODULE0 */

#ifdef PORTWK_MODULE1
#if(FALLING == PORTWK1_EDG)
	REG32(PORTWKEDG) |= BIT(1);        // PA3 falling edge wakup
#else
	REG32(PORTWKEDG) &= ~BIT(1);        // PA3 Rising edge wakup
#endif
#endif	/* PORTWK_MODULE1 */

#ifdef PORTWK_MODULE2
#if(FALLING == PORTWK2_EDG)
	REG32(PORTWKEDG) |= BIT(2);        // PG11/LSA1 falling edge wakup
#else
	PORTWKEDG &= ~BIT(2);        // PG11/LSA1 Rising edge wakup
#endif
#endif	/* PORTWK_MODULE2 */

	/* 注意: PORTWK3若选用了RTC进行唤醒，每秒钟将会唤醒一次，因此不能使用IO的边沿触发唤醒 */
#ifdef PORTWK_MODULE3
#if(FALLING == PORTWK3_EDG)
	REG32(PORTWKEDG) |= BIT(3);        // PG12/IR/LSA0/RTC/PA5/PA9/PE2/PD12 Falling  wakup
#else
	REG32(PORTWKEDG) &= ~BIT(3);        // PG12/IR/LSA0/RTC/PA5/PA9/PE2/PD12 Rising  wakup
#endif
#endif	/* PORTWK_MODULE3 */

	__asm__("nop");
	__asm__("nop");
	__asm__("nop");
	
	/* Clear Wakeup Event Pending */
	REG32(PORTWKEN) &= 0x0f;
	
	__asm__("nop");
	__asm__("nop");
	__asm__("nop");


	/************************ Port Wakeup Module Enable/Disable *********************/
	
#ifdef PORTWK_MODULE0
	REG32(PORTWKEN) &= ~0x01;    // Enable PA2 Wake Up
#endif
#ifdef PORTWK_MODULE1
	REG32(PORTWKEN) &= ~0x02;    // Enable PA3 Wake Up
#endif
#ifdef PORTWK_MODULE2
	REG32(PORTWKEN) &= ~0x04;    // Enable PG11/LSA1 Wake Up
#endif
#ifdef PORTWK_MODULE3
	REG32(PORTWKEN) &= ~0x08;    // Enable PG12/IR/LSA0/RTC/PA5/PA9/PE2/PD12 Wake Up
#endif

#ifdef PORT_WAKE_INTERRUPT
//	REG32(IE) |= (1 << 19);      // PORTWAKEUP    

	REG32(IE) |= (1<<13);	// OPEN Portwakeup Interrupt
	REG32(IRT_CFG) |= (1<<9);	// Second Interrupt for rtc
#endif

	
	/* 进入sleep */
	REG32(PCON0) |= (1 << CPU_SLEEP);

}

