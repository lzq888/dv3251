

#ifndef _CPU_BASE_H
#define _CPU_BASE_H


/* CPU Mode Description
 * Sleep:
 * Hold: All Digital Modules Will Be Closed Automaticlly. Analog Modules Such As ADC, DAC, etc,Should Be Closed Manually.
 * Idle: CPU Clock Disabled.
 * */
enum CPU_MODE {
	CPU_SLEEP, CPU_HOLD, CPU_IDLE,
};





#endif /* _CPU_BASE_H */