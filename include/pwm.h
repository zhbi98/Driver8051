
#ifndef __PWM_H__
#define __PWM_H__

#include <reg52.h>

sbit pwm_pin = P1^0;

extern void out_time(unsigned int us);
extern void pwm_out(unsigned int period, unsigned int time_l);

#endif
