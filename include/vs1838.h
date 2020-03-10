
#ifndef __VS1838B_H__
#define __VS1838B_H__

#include <reg52.h>

#define INTERRUPT_N 0

sbit out = P3^2;

unsigned int value;

extern void interrupt_init();
extern void delay(unsigned int us);
extern unsigned int vs1838b_decoding();

#endif
