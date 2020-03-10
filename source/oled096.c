
#include "oled096.h"

void oled096_send_bit(bit a_bit)
{
    if (a_bit)
        d1 = 1;
    else
        d1 = 0;
}

void oled096_send_byte(unsigned char a_byte)
{
    unsigned char write;

    cs = 0;
    for (write = 0; write < 8; write++) {
        d0 = 0;
        oled096_send_bit((a_byte << write) & 0x80);
        sleep_us(1);
        d0 = 1;
    }
    cs = 1;
}

void write_command(unsigned char command)
{
    dc = 0;
    oled096_send_byte(command);

}

void write_data(unsigned char dat_a)
{
    dc = 1;
    oled096_send_byte(dat_a);
}

void clean(unsigned char dat_a)
{
    unsigned char x, page;

    for (page = 0; page < 8; page++) {
        write_command(0xb0 + page);
        write_command(0x02);
        write_command(0x10);
        for (x = 0; x < 128; x++)
            write_data(dat_a);
    }
}

void oled096_init()
{
    rs = 0;
    sleep_ms(1);
    rs = 1;

    write_command(0xae);
    write_command(0xd5);
    write_command(0x80);
    write_command(0xa8);
    write_command(0x3f);
    write_command(0xd3);
    write_command(0x00);
    write_command(0x40);
    write_command(0xa1);
    write_command(0xc8);
    write_command(0xda);
    write_command(0x12);
    write_command(0x81);
    write_command(0xcf);
    write_command(0xd9);
    write_command(0xdb);
    write_command(0x30);
    write_command(0xa4);
    write_command(0xa6);
    write_command(0x8d);
    write_command(0x14);
    write_command(0xaf);
    clean(0x00);
    sleep_ms(1);
}

void display_on()
{
    write_command(0x8d);
    write_command(0x14);
    write_command(0xaf);
}

void display_off()
{
    write_command(0x8d);
    write_command(0x10);
    write_command(0xae);
}

void display_position(unsigned char y, unsigned char x)
{
    unsigned char page;

    page = (y * 2) - 2;
    x = (x * 8) - 8;

    write_command(0xb0 + page);
    write_command(((x & 0xf0) >> 4) | 0x10);
    write_command((x & 0x0f) | 0x01);   
}

void display_character(unsigned char y, unsigned char x, unsigned char character)
{       
    unsigned char column = 0;
    unsigned char page;

    character = character - ' ';

    display_position(y, x);

    for(column = 0; column < 8; column++) {
        write_data(f8x16[(character * 16) + column]);
    }

    page = (y * 2) - 1;
    x = (x * 8) - 8;
    write_command(0xb0 + page);
    write_command(((x & 0xf0) >> 4) | 0x10);
    write_command((x & 0x0f) | 0x01);

    for(column = 0; column < 8; column++) {                                                                                                                                                 
        write_data(f8x16[(character * 16) + column + 8]);
    }
}

void display_string(unsigned char y, unsigned char x, const unsigned char * string)
{
    unsigned char bits = 0;

    while (string[bits] != '\0') {
        display_character(y, x, string[bits]);
        
        bits++;
        x++;
    }
}

void display_value(unsigned char y, unsigned char x, unsigned char *format, ...)
{
    unsigned char value[16];

    va_list parameter_pointer;
    va_start(parameter_pointer, format);

    vsprintf(value, format, parameter_pointer);
    
    va_end(parameter_pointer);

    display_string(y, x, value);
}
