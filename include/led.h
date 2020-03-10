
#ifndef __LED_H__
#define __LED_H__

#include <reg52.h>

#include "time.h"

sbit led_pin = P1^7;

extern void led_display(unsigned int time_l, unsigned int time_h, unsigned int second);
extern void led(unsigned int period, unsigned int time_l);
extern void led_breath();

#endif
