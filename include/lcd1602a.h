
#ifndef __LCD1602A_H__
#define __LCD1602A_H__

#include <reg52.h>
#include <stdio.h>
#include <stdarg.h>

#include "time.h"

#define lcd1602_data P2

sbit rs = P0^7;
sbit rw = P0^6;
sbit en = P0^5;

extern void write_command(unsigned char command);   
extern void write_data(unsigned char dat_a);
extern void lcd1602_init();
extern void clean();
extern void display_character(unsigned char y, unsigned char x, unsigned char character);
extern void display_string(unsigned char y, unsigned char x, const unsigned char * string);
extern void display_value(unsigned char y, unsigned char x, unsigned char * format, ...);

#endif
