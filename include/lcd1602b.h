
#ifndef __LCD1602B_H__
#define __LCD1602B_H__

#include <reg52.h>
#include <stdio.h>
#include <stdarg.h>

#include "time.h"

#define PCF8574_START        1
#define PCF8574_FINISH       0

#define PCF8597AT_ADDRESS 0x7e

sbit pcf8574_scl = P3^7;
sbit pcf8574_sda = P3^6;

extern unsigned char pcf_data;

extern void pcf8574_stafinish(bit state);
extern void check_pcf8574_ack();
extern void pcf8574_send_bit(bit a_bit);
extern void pcf8574_send_byte(unsigned char a_byte);
extern void pcf8574_write(unsigned char address, unsigned char dat_a);
extern void lcd1602_en();
extern void wrsite_command(unsigned char command);
extern void write_data(unsigned char dat_a);
extern void lcd1602_init();
extern void clean();
extern void display_character(unsigned char y, unsigned char x, unsigned char character);
extern void display_string(unsigned char y, unsigned char x, const unsigned char * string);
extern void display_value(unsigned char y, unsigned char x, unsigned char * format, ...);

#endif
