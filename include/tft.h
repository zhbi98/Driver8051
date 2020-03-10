
#ifndef __TFT_H__
#define __TFT_H__

#include <reg52.h>

#include <stdio.h>
#include <stdarg.h>

#include "fonts.h"
#include "time.h"

#define tft_data_l P1
#define tft_data_h P3

#define HORIZONTAL    1

#if (HORIZONTAL)
    #define TFT_WIDTH (480 + 1)
    #define TFT_HEIGH (320 + 1)
#else
    #define TFT_WIDTH (320 + 1)
    #define TFT_HEIGH (480 + 1)
#endif

sbit rs  = P0^3;
sbit rd  = P0^1;
sbit wr  = P0^2;
sbit cs  = P0^4;
sbit rst = P0^0;

enum color {
    white      = 0xffff,
    balck      = 0x0000,

    red        = 0xf800,
    green      = 0x07e0,
    blue       = 0x001f,

    purple     = 0x780f,
    yellow     = 0xffe0,
    orange     = 0xfd20,
    orange_red = 0xfa20,
    strong_red = 0xe000,
    hot_pink   = 0xf8b2,
    misty_rose = 0xff3c,
    sea_green  = 0x2c4a,
    tomato     = 0xfb08,
    olive      = 0x8400,
    cyan       = 0x07ff,
    dimcyan    = 0x03ff,
    dimgray    = 0x7bef,
    light_gray = 0xc618,
    magenta    = 0xf81f
};

extern void tft_bus(unsigned char h_bits, unsigned char l_bits);
extern void write_command(unsigned int command);
extern void write_data(unsigned int dat_a);
extern void write_register(unsigned int register_address, unsigned int register_value);

extern void tft_reset();
extern void tft_direction(unsigned char direction);
extern void tft_init();
extern void display_position(unsigned int y, unsigned int x);
extern void display_pixel_8(unsigned int y, unsigned int x, unsigned int color);
extern void display_pixel(unsigned int y, unsigned int x, unsigned int color);
extern void tft_clear(unsigned int color);
extern void display_character(unsigned int y, unsigned int x, unsigned int bg, unsigned int fg, unsigned char character);
extern void display_character_16x32(unsigned int y, unsigned int x, unsigned int bg, unsigned int fg, unsigned char character);
extern void display_string(unsigned int y, unsigned int x, unsigned int bg, unsigned int fg, unsigned char *string);
extern void display_string_16x32(unsigned int y, unsigned int x, unsigned int bg, unsigned int fg, unsigned char *string);
extern void display_value(unsigned int y, unsigned int x, unsigned int bg, unsigned int fg, unsigned char *format, ...);
extern void display_value_16x32(unsigned int y, unsigned int x, unsigned int bg, unsigned int fg, unsigned char *format, ...);

#endif
