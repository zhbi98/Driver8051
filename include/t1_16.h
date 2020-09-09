
#ifndef __T1_16_H__
#define __T1_16_H__

#include <reg52.h>

#define CURRENT_TIMER 1

extern unsigned int t1;

extern void t1_set_mode(bit gate);
extern void t1_set_time(unsigned int t);
extern void t1_init(bit gate, unsigned int t);

#endif
