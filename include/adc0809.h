
#ifndef __ADC0809_H__
#define __ADC0809_H__

#include <reg52.h>

#include "time.h"

#define data_encoded P1

#define INTERRUPT_N  1

sbit start = P0^4;
sbit eoc = P0^3;
sbit oe = P0^2;
sbit clock = P0^1;
/*
sbit adda = P0^5;
sbit addb = P0^6;
sbit addc = P0^7;
*/
sbit ale = P0^0;

extern void timer0_8_init();
extern void adc0809_init();
extern unsigned char adc0809_read();

#endif 
