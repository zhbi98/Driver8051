
#ifndef __LCD12864A_H__
#define __LCD12864A_H__

#include <reg52.h>
#include <stdio.h>
#include <stdarg.h>

#include "time.h"

#define lcd12864_data P2

sbit rs = P0^7;
sbit rw = P0^6;
sbit en = P0^5;
sbit psb = P0^4;

extern void testing_lcd12864_busy();
extern void write_command(unsigned char command);
extern void write_data(unsigned char dat_a);
extern void lcd12864_init();
extern void clean();
extern void display_position(unsigned char y, unsigned char x);
extern void display_character(unsigned char y, unsigned char x, unsigned char character);
extern void display_string(unsigned char y, unsigned char x, const unsigned char * string);
extern void display_value(unsigned char y, unsigned char x, unsigned char * format, ...);

#endif
