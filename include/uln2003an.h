
#ifndef __ULN2003N_H__
#define __ULN2003N_H__

#include <reg52.h>

#include "time.h"

sbit in1 = P3^7;
sbit in2 = P3^6;
sbit in3 = P3^5;
sbit in4 = P3^4;

extern void run_positive(unsigned char speed);
extern void run_negative(unsigned char speed);
extern void run_stop();
extern void positive_cycle(unsigned int cycle);
extern void negative_cycle(unsigned int cycle);

#endif
