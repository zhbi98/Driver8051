
#ifndef __T0_16_H__
#define __T0_16_H__

#include <reg52.h>

#define CURRENT_TIMER 0

extern unsigned int t0;

extern void t0_set_mode(bit gate);
extern void t0_set_time(unsigned int t);
extern void t0_init(bit gate, unsigned int t);

#endif
