/* Filename:     idle_mode.c
 * Version:      1.0
 * Author:       zhiyong_zeng <zhiyong_zeng@buildwin.com.cn>
 * Started:      10th March 2014
 * Target Soc:   arm(32bit)
 * 
 * Description: Foring Hunter Soc to enter idle mode, this time, the system clock is gated, 
 * and clock to system logic modules is halted. No clock switching while entering the system logic
 * moudules so that power consumption is minimized.
 * 
 * Note: During idle mode, the device can be wake up by all interrupt source, which include all
 * peripheral interrupt.
 * 
 * when wake up from idle mode, if interrupt is enabled, hunter will enters corresponding interrupt
 * service subroutine(ISR), otherwise, device will directly execute the instruction following idle.
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
#define	HOLD_CODE_ADDRESS		0x10000400

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


/* idle模式 
 * 注意: 此模式下，sdram将进入'自刷新'状态以保存已有数据，sdram不可用
 * 此段程序将在sram区域跑
 * */
void cpu_idle_func(void) {
//    PCON2 |= BIT(5);   //close otp clk
#ifdef RTCMODE_EN
	while(1)
	{
		PCON0 |= BIT(1);
	}
#else

#ifdef PORT_WAKE_INTERRUPT

	/* 转移页表地址到sram区域，并且重新映射0x0000000到0x10000000 -- for irq, 
	 * 0x20000000到0x10000000 -- for fixed link address '0x2xxxxxxx'
	 * */
	__asm__ __volatile__(	"ldr 	r0, =0x10004000\n"
							"mcr 	p15, 0, r0, c2, c0, 0\n"
							"mrc 	p15, 0, r0, c1, c0, 0\n"	/* important: read-write c1寄存器以使mmu刷新dcache */
							"mcr 	p15, 0, r0, c1, c0, 0\n" : : : "r0");		
	__asm__("nop"); __asm__("nop");
	__asm__("nop");	__asm__("nop");
	
	unsigned long stored_stack;
	
	/* 
	 * 重新设置irq模式的stack地址到sram指定区域 
	 * */
	__asm__ __volatile__(	"mrs	r1, cpsr\n"
							"msr	cpsr, #0xd2\n"	/* 切换到irq模式以设置相应的stack */
							"mov	%[res], sp\n"	/* 保存sdram时候irq的stack，以便退出Hold模式时还原 */
							"ldr	sp, =0x10004000\n"	/* 设置sram时候irq的stack */
							"msr	cpsr, r1\n"
							 : [res] "=r" (stored_stack)
							 :
							 : "memory", "sp", "r1", "cc");
	__asm__("nop"); __asm__("nop");
	
#endif	/* PORT_WAKE_INTERRUPT */

	/* 使能sdram进入'自刷新'状态 
	 * 注意:'自刷新'状态下的sdram不能再被访问
	 * */
	REG32(SYS_CON) = 0x932B;
	REG32(SYS_CFG) |= (1 << 4);
	while (!(REG32(SYS_CFG) & (1 << 16)));
	REG32(SYS_CON) = 0;
	
//	__asm__("ldr	r2, =0x14004000");
//	__asm__("ldr	r3, =0x932b");
//	__asm__("str	r3, [r2, #176]");	// 0xb0
//	
//	__asm__("ldr	r3, [r2, #52]");	// 0x34
//	__asm__("orr	r3, r3, #16");
//	__asm__("str	r3, [r2, #52]");
//	
//	__asm__("tst_syscfg1:	ldr		r3, [r2, #52]");
//	__asm__("tst	r3, #65536");	// (1<<16)
//	__asm__("beq	tst_syscfg1");
//	
//	__asm__("ldr	r3, =0x14004000");
//	__asm__("mov	r2, #0");
//	__asm__("str	r2, [r3, #176]");	// 0xb0

	
	/* 进入Hold模式，程序在此处halt住
	 * 注意:若使能中断, 则由port wakeup唤醒后,先进入相应的中断处理函数,
	 * 处理完中断后才继续跑下一条指令.
	 * */
	REG32(PCON0) |= (1 << CPU_IDLE);
//	__asm__("ldr	r2, [r3]");
//	__asm__("orr	r2, r2, #4");	// (1 << CPU_IDLE)
//	__asm__("str	r2, [r3]");
	
	/* 由hold模式唤醒，此时已经处理完中断(if needed), 程序将继续往下跑 */
	__asm__("nop"); __asm__("nop");
	__asm__("nop");	__asm__("nop");
	
	/* sdram退出'自刷新'状态 
	 * */
	REG32(SYS_CON) = 0x932B;
	REG32(SYS_CFG) &= ~(1 << 4);
	while ((REG32(SYS_CFG) & (1 << 16)));
	REG32(SYS_CON) = 0;
//	__asm__("ldr	r2, =0x14004000");
//	__asm__("ldr	r3, =0x932b");
//	__asm__("str	r3, [r2, #176]");	// 0xb0
//	
//	__asm__("ldr	r3, [r2, #52]");	// 0x34
//	__asm__("bic	r3, r3, #16");		// ~(1 << 4)
//	__asm__("str	r3, [r2, #52]");
//	
//	__asm__("tst_syscfg2:	ldr		r3, [r2, #52]");
//	__asm__("ands	r3, r3, #65536");	// (1<<16)
//	__asm__("bne	tst_syscfg2");
//
//	__asm__("ldr	r3, =0x14004000");	
//	__asm__("mov	r2, #0");
//	__asm__("str	r2, [r3, #176]");	// 0xb0
	
//	__asm__("");
//	__asm__("");
//	__asm__("");
//	__asm__("");
//	__asm__("");
//	__asm__("");
//	__asm__("");
//	__asm__("");
//	__asm__("");
//	__asm__("");
	
#ifdef PORT_WAKE_INTERRUPT

	/* 重新将页表地址切换回到sdram区域，由此返回sdram
	 * */
	__asm__ __volatile__(	"ldr 	r0, =0x201a0000\n"
							"mcr 	p15, 0, r0, c2, c0, 0\n"
							"mrc 	p15, 0, r0, c1, c0, 0\n"	/* important: read-write c1寄存器以使mmu刷新dcache */
							"mcr 	p15, 0, r0, c1, c0, 0\n" : : : "r0");
	__asm__("nop"); __asm__("nop");
	__asm__("nop");	__asm__("nop");

	/* 
	 * 重新恢复irq的stack地址到sdram区域 
	 * */
	__asm__ __volatile__(	"mrs	r1, cpsr\n"
							"msr	cpsr, #0xd2\n"
							"mov	sp, %[val]\n"
							"msr	cpsr, r1\n"
							 :
							 : [val] "r" (stored_stack)
							 : "memory", "sp", "r1", "cc");
	__asm__("nop"); __asm__("nop");	

#endif /* PORT_WAKE_INTERRUPT */
	
#endif
//    PCON2 &= ~BIT(5); //open otp clk
}


/*
 * 由此入口进入idle模式
 * 注意: 数字模块被自动关闭, 需手动关闭模拟模块(如adc/dac)
 * */
void cpu_idle_mode(void) {
	
	unsigned char const *sdram_code;
	unsigned char *sram_code;
	unsigned int i;
	
	void (*funpt)();

#ifdef PORT_WAKE_INTERRUPT
	funpt = (void (*)()) SRAM_ADDRESS;
	sdram_code = (unsigned char const *) ((unsigned int) VECTOR_TABLE_ADDRESS);
	sram_code = funpt;

	/* 拷贝arm异常矢量表到sram区域, 0x10000000起始, 为irq准备;
	 * */
	for (i = 0; i < 0x400; i++) {
		*sram_code++ = *sdram_code++;
	}

	/* 重新建立mmu虚物地址映射表 
	 * 注意: 0x0000000被重新映射到0x10000000,为irq准备;
	 * 		 0x2000000被重新映射到0x10000000,因为链接地址是由0x20000000起始, 避免绝对寻址出错;
	 * */
//	creat_page_table_hold();
	
#endif	/* PORT_WAKE_INTERRUPT */

	/* 拷贝hold模式下要跑的代码到sram相应区域 
	 * */
	funpt = (void (*)()) HOLD_CODE_ADDRESS;
	sdram_code = (unsigned char const *) ((unsigned int) cpu_idle_func);
	sram_code = funpt;

	for (i = 0; i < 2*1024; i++) {
		*sram_code++ = *sdram_code++;
	}

	deg_Printf("\n copy code ok\n");

//	PMAP_CFG0 |= (0b000 << 26);	// IR/LSA0/RTC/PA5/PA9/PE2/PD12/PG12, select one
//	PMAP_CFG0 |= (0b00 << 21);	// PG11/LSA1, select one


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
	REG32(IE) |= (1 << 19);      // PORTWAKEUP    
#endif

	/* 强制跳转到sram区域，由此入口准备进入hold模式
	 * */
	(*funpt)();
	/* 由hold模式唤醒 */
	__asm__("nop");
	__asm__("nop");

	/* Wakeup */

	__asm__("nop");
	__asm__("nop");
	__asm__("nop");
	__asm__("nop");
	
	/************************ Open Analog Module *********************/
	
	

	deg_Printf("\n HOLE MODE wake up\n");
}

