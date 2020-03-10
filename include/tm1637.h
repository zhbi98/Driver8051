
#ifndef __TM1637_H__
#define __TM1637_H__

#include <reg52.h>

#include "time.h"

#define TM1637_START  1
#define TM1637_FINISH 0

sbit tm1637_scl = P2^2;
sbit tm1637_sda = P2^3;

bit twinkle = 1;
                                                                                
struct hou {
	unsigned char ten;
	unsigned char bits;
} hour;

struct min {
	unsigned char ten;
	unsigned char bits;
} minute;

extern unsigned char code num_code[];
extern unsigned char code twinkle_code[];

extern void tm1637_stafinish(bit state);
extern void check_tm1637_ack();
extern void tm1637_send_bit(bit a_bit);
extern void tm1637_send_byte(unsigned char a_byte);
extern void write_command(unsigned char command);
extern void write_data(unsigned char address, unsigned char dat_a);
extern void display_value(unsigned int value);
extern void display_time(unsigned char h, unsigned m);
extern void display_off();

#endif
