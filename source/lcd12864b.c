
#include "lcd12864b.h"

void write_lcd12864(unsigned char dat_a)
{
    unsigned char send;

    for (send = 0; send < 8; send++) {
        sclk = 0;
        dat_a = dat_a << 1;
        sid = CY;
        sleep_us(1);
        sclk = 1;
        sleep_us(1);
        sclk = 0;
    }
}

void write_command(unsigned char command)
{
    cs = 1;
    sleep_ms(1);
    write_lcd12864(0xf8);
    write_lcd12864(command & 0xf0);
    write_lcd12864((command << 4) & 0xf0);
    cs = 0;
    sleep_ms(1);
}

void write_data(unsigned char dat_a)
{
    cs = 1;
    sleep_ms(1);
    write_lcd12864(0xfa);
    write_lcd12864(dat_a & 0xf0);
    write_lcd12864((dat_a << 4) & 0xf0);
    cs = 0;
    sleep_ms(1);
}

void lcd12864_init()
{
    write_command(0x30);
    write_command(0x02);
    write_command(0x0c);
    write_command(0x06);
    write_command(0x80);
    write_command(0x01);

    sleep_ms(1);
}

void clean()
{
    write_command(0x01);
}

void display_position(unsigned char y, unsigned char x)
{
    unsigned char command;

    x = x - 1;

    if (y == 1) {
        command = x + 0x80;
    } else if (y == 2) {
        command = x + 0x90;
    } else if (y == 3) {
        command = x + 0x88;
    } else if (y == 4) {
        command = x + 0x98;
    }
    write_command(command);
}

void display_character(unsigned char y, unsigned char x, unsigned char character)
{
    display_position(y, x);
    write_data(character);
}

void display_string(unsigned char y, unsigned char x, const unsigned char * string)
{
    unsigned char bits = 0;

    display_position(y, x);

    while (string[bits] != '\0') {
        write_data(string[bits]);

        sleep_ms(1);
        bits++;
    }
}

void display_value(unsigned char y, unsigned char x, unsigned char * format, ...)
{
    unsigned char value[16];

    va_list parameter_pointer;
    va_start(parameter_pointer, format);

    vsprintf(value, format, parameter_pointer);
    
    va_end(parameter_pointer);

    display_string(y, x, value);
}
