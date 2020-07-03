
#ifndef __JLX12864G_H__
#define __JLX12864G_H__

#include <reg52.h>

#include <stdio.h>
#include <stdarg.h>

#include "time.h"
#include "fontlib.h"

#define white 0
#define black 1

extern unsigned char jvm[];

sbit rs = P0^0;
sbit cs = P0^1;
sbit rst = P0^2;
sbit sda = P0^3;
sbit scl = P0^4;

extern void jlx12864_send_bit(unsigned char a_bit);
extern void jlx12864_send_byte(unsigned char a_byte);
extern void write_command(unsigned char command);
extern void write_data(unsigned char dat_a);
extern void clean(unsigned char dat_a);
extern void jlx12864g_init();
extern void display_on();
extern void display_off();
extern void display_pixel(unsigned char y, unsigned char x, unsigned char color, unsigned char vm[]);
extern void send_display_memory(unsigned char vm[]);
extern void display_position(unsigned char y, unsigned char x);
extern void display_character(unsigned char y, unsigned char x, unsigned char character);
extern void display_string(unsigned char y, unsigned char x, const unsigned char * string);
extern void display_value(unsigned char y, unsigned char x, unsigned char *format, ...);
extern void display_bevel_rectangle(unsigned char y, unsigned char x, unsigned char width, unsigned char height, unsigned char radian, unsigned char vm[]);

#endif
