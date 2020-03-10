
#ifndef __HCSR04_H__
#define __HCSR04_H__

#include <reg52.h>

#include "time.h"

sbit trig = P0^4;
sbit echo = P0^3;

extern void timer0_16_init();
extern void hcsr04_start();
extern unsigned int compute_distance();
extern unsigned int hcsr04_ranging();

#endif
