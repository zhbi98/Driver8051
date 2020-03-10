
#ifndef __EC11_H__
#define __EC11_H__

#include <reg52.h>

#include "time.h"

#define INTERRUPT_N 0

sbit sw = P3^4;
sbit dt = P3^3;
sbit clk = P3^2;

unsigned int ec11_add;

extern void interrupt_init();

#endif
