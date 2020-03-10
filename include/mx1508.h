
#ifndef __MX1508_H__
#define __MX1508_H__

#include <reg52.h>

#define POSITIVE 1
#define NEGATIVE 2
#define STOP 0

#define A 0
#define B 1

sbit in1 = P3^7;
sbit in2 = P3^6;
sbit in3 = P3^5;
sbit in4 = P3^4;

extern void motor_a(unsigned char direction);
extern void motor_b(unsigned char direction);
extern void motor_run(bit motor, unsigned char direction);

#endif
