
#include "tft.h"

void tft_bus(unsigned char h_bits, unsigned char l_bits)
{
    cs = 0;

    tft_data_h = h_bits;
    tft_data_l = l_bits;

    wr = 0;
    wr = 1;

    cs = 1;
}

void write_command(unsigned int command)
{
    rs = 0;

    tft_bus(command >> 8, command);
}

void write_data(unsigned int dat_a)
{
    rs = 1;

    tft_bus(dat_a >> 8, dat_a);
}

void write_register(unsigned int register_address, unsigned int register_value)
{
    write_command(register_address);
    write_data(register_value);
}

void tft_reset()
{
    rst = 1;
    sleep_ms(50);
    rst = 0;
    sleep_ms(50);
    rst = 1;
    sleep_ms(50);
}

void tft_direction(unsigned char direction)
{
    write_command(0x36);

    switch (direction) {
        // +----- x 
        // |
        // |
        // y
        case 0 : write_data(0xa8); break;
        // y -----+
        //        |
        //        |
        //        x
        case 1 : write_data(0x08); break;
        //        y
        //        |
        //        |
        // x -----+
        case 2 : write_data(0x68); break;
        // x
        // |
        // |
        // +----- y
        case 3 : write_data(0xc8); break;
    }
}

void tft_init()
{
    // tft_reset();
    // sleep_ms(200);

    write_command(0xb0);
    write_data(0x00);
  
    write_command(0x3a);
    write_data(0x55);

    write_command(0xe0);
    write_data(0x0f);
    write_data(0x1f);
    write_data(0x1c);
    write_data(0x0c);
    write_data(0x0f);
    write_data(0x08);
    write_data(0x48);
    write_data(0x98);
    write_data(0x37);
    write_data(0x0a);
    write_data(0x13);
    write_data(0x04);
    write_data(0x11);
    write_data(0x0d);
    write_data(0x00);

    write_command(0xe1);
    write_data(0x0f);
    write_data(0x32);
    write_data(0x2e);
    write_data(0x0b);
    write_data(0x0d);
    write_data(0x05);
    write_data(0x47);
    write_data(0x75);
    write_data(0x37);
    write_data(0x06);
    write_data(0x10);
    write_data(0x03);
    write_data(0x24);
    write_data(0x20);
    write_data(0x00);

    write_command(0xe2);
    write_data(0x0f);
    write_data(0x32);
    write_data(0x2e);
    write_data(0x0b);
    write_data(0x0d);
    write_data(0x05);
    write_data(0x47);
    write_data(0x75);
    write_data(0x37);
    write_data(0x06);
    write_data(0x10);
    write_data(0x03);
    write_data(0x24);
    write_data(0x20);
    write_data(0x00);
    // direction seting
    // write_command(0x36);
    // write_data(0xa8);
    if (HORIZONTAL)
        tft_direction(0);
    else
        tft_direction(1);
    
    write_command(0x38);

    write_command(0xb1);
    write_data(0xb0);
    write_data(0x11);

    write_command(0xc2);
    write_data(0x55); 

    write_command(0xb4);
    write_data(0x02);

    write_command(0xb6);
    write_data(0x02);
    write_data(0x22);
    write_data(0x3b);

    write_command(0x11);
    write_command(0x29);

    tft_clear(white);
}

void display_position(unsigned int y, unsigned int x)
{
    unsigned char seting_x = 0x2a;
    unsigned char seting_y = 0x2b;

    y = y - 1;
    x = x - 1;

    write_command(seting_x);
    write_data(x >> 8);
    write_data(0x00ff & x);
    write_data((x + 1) >> 8);
    write_data((x + 1));
    
    write_command(seting_y);
    write_data(y >> 8);
    write_data(0x00ff & y);
    write_data((y + 1) >> 8);
    write_data((y + 1));

    // display pixel
    write_command(0x2c);
}

void display_pixel_8(unsigned int y, unsigned int x, unsigned int color)
{
    display_position(y, x);

    cs = 0;
    
    rd = 1;
    rs = 1;

    tft_data_l = (color >> 8);

    wr = 0;
    wr = 1;

    tft_data_l = color;

    wr = 0;
    wr = 1;

    cs = 1;
}

void display_pixel(unsigned int y, unsigned int x, unsigned int color)
{
    display_position(y, x);
    write_data(color);
}

void tft_clear(unsigned int color)
{
    unsigned int x;
    unsigned int y;

    for (y = 1; y < TFT_HEIGH; y++) {
        for (x = 1; x < TFT_WIDTH; x++) {
            display_pixel(y, x, color);
        }
    }
}

void display_character(unsigned int y, unsigned int x, unsigned int bg, unsigned int fg, unsigned char character)
{
    unsigned char font_h;
    unsigned char font_w;
    unsigned char font_c[16];

    character = character - ' ';

    x = (x * 8) - 8 + 1;
    y = (y * 16) - 16 + 1;

    for (font_h = 0; font_h < 16; font_h++)
        font_c[font_h] = black8x16[16 * character + font_h];

    for (font_h = 0; font_h < 16; font_h++) {
        for (font_w = 0; font_w < 8; font_w++) {
            if (font_c[font_h] & (0x80 >> font_w))
                display_pixel(y + font_h, x + font_w, fg);
            else
                display_pixel(y + font_h, x + font_w, bg);
        }
    }
}

void display_character_16x32(unsigned int y, unsigned int x, unsigned int bg, unsigned int fg, unsigned char character)
{
    unsigned char font_h;
    unsigned char font_w;
    unsigned int byte;
    unsigned char bits = 0;
    unsigned char font_c[64];

    character = character - ' ';

    x = (x * 16) - 16 + 1;
    y = (y * 32) - 32 + 1;

    for (font_h = 0; font_h < 64; font_h++)
        font_c[font_h] = black16x32[64 * character + font_h];

    for (font_h = 0; font_h < 32; font_h++) {

        byte = font_c[bits];
        byte = byte << 8;
        byte = byte | font_c[bits + 1];
        bits = bits + 2;

        for (font_w = 0; font_w < 16; font_w++) {
            if (byte & (0x8000 >> font_w))
                display_pixel(y + font_h, x + font_w, fg);
            else
                display_pixel(y + font_h, x + font_w, bg);
        }
    }
}

void display_string(unsigned int y, unsigned int x, unsigned int bg, unsigned int fg, unsigned char *string)
{
    unsigned char bits = 0;

    while (string[bits] != '\0') {
        display_character(y, x, bg, fg, string[bits]);
        
        bits++;
        x++;
    }
}

void display_string_16x32(unsigned int y, unsigned int x, unsigned int bg, unsigned int fg, unsigned char *string)
{
    unsigned char bits = 0;

    while (string[bits] != '\0') {
        display_character_16x32(y, x, bg, fg, string[bits]);
        
        bits++;
        x++;
    }
}

void display_value(unsigned int y, unsigned int x, unsigned int bg, unsigned int fg, unsigned char *format, ...)
{
    unsigned char value[16];

    va_list parameter_pointer;
    va_start(parameter_pointer, format);

    vsprintf(value, format, parameter_pointer);
    
    va_end(parameter_pointer);

    display_string(y, x, bg, fg, value);
}

void display_value_16x32(unsigned int y, unsigned int x, unsigned int bg, unsigned int fg, unsigned char *format, ...)
{
    unsigned char value[16];

    va_list parameter_pointer;
    va_start(parameter_pointer, format);

    vsprintf(value, format, parameter_pointer);
    
    va_end(parameter_pointer);

    display_string_16x32(y, x, bg, fg, value);
}
