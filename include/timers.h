

#ifndef __TIMERS_H__
#define __TIMERS_H__

#include <reg52.h>
#include <intrins.h>

#define TIME_US       50000

#define CURRENT_TIMER 0

#if (CURRENT_TIMER == 0)
	#define THX TH0
	#define TLX TH0
	#define TRX TR0
	#define ETX ET0
	#define INTERRUPT_N 1
#elif (CURRENT_TIMER == 1)
	#define THX TH1
	#define TLX TH1
	#define TRX TR1
	#define ETX ET1
	#define INTERRUPT_N 3
#endif

extern void t_set_mode(bit gate);
extern void t_set_time(unsigned int t);
extern void t_init(bit gate, unsigned int t);

#endif
