
#include "jlx12864g.h"

unsigned char jvm[1024];

void jlx12864_send_bit(unsigned char a_bit)
{
    if (a_bit)
        sda = 1;
    else
        sda = 0;
}

void jlx12864_send_byte(unsigned char a_byte)
{
    unsigned char write;

    cs = 0;

    for (write = 0; write < 8; write++) {
        scl = 0;
        jlx12864_send_bit((a_byte << write) & 0x80);
        sleep_us(1);
        scl = 1;
    }
    
    cs = 1;
}

void write_command(unsigned char command)
{
    rs = 0;
    jlx12864_send_byte(command);

}

void write_data(unsigned char dat_a)
{
    rs = 1;
    jlx12864_send_byte(dat_a);
}

void clean(unsigned char dat_a)
{
    unsigned char x, page;

    for (page = 0; page < 8; page++) {
        write_command(0xb0 + page);
        write_command(0x00);
        write_command(0x10);
        for (x = 0; x < 128; x++)
            write_data(dat_a);
    }
}

void jlx12864g_init()
{

    rst = 0;
    sleep_ms(100);
    rst = 1;
    sleep_ms(100);
    
    // soft reset
    write_command(0xe2); 
    sleep_ms(5);
    // step up -> 1
    write_command(0x2c); 
    sleep_ms(50);
    // step up -> 2
    write_command(0x2e); 
    sleep_ms(50);
    // step up -> 3
    write_command(0x2f);
    sleep_ms(5);
    // coarse adjustment
    // of contrast
    // adjustable
    // range 0x20-0x27
    write_command(0x23);
    // fine tune contrast
    write_command(0x81);
    // fine tune the 
    // contrast value, 
    // the range can be 
    // set 0x00-0x3f  
    write_command(0x28);
    // 1/9 bias ratio
    write_command(0xa3);
    // line scan order
    // from top to bottom
    write_command(0xc8);
    // column scan order
    // from left to right
    write_command(0xa0);
    // start line start
    // of the first line
    write_command(0x40);
    // display on
    write_command(0xaf);
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

void display_pixel(unsigned char y, unsigned char x, unsigned char color, unsigned char vm[])
{
    unsigned char page;
    unsigned char bit;

    page = y / 8;
    bit = y % 8;

    vm[page * 128 + x] |= ((color & 0x01) << bit);
}

void send_display_memory(unsigned char vm[])
{
    unsigned int x, page;
    unsigned int v = 0;

    for (page = 0; page < 8; page++) {
        write_command(0xb0 + page);
        write_command(0x00);
        write_command(0x10);
        for (x = 0; x < 128; x++) {
            write_data(vm[v]);
            v++;
        }
    }   
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
    unsigned char value[32];

    va_list parameter_pointer;
    va_start(parameter_pointer, format);

    vsprintf(value, format, parameter_pointer);
    
    va_end(parameter_pointer);

    display_string(y, x, value);
}

void display_bevel_rectangle(unsigned char y, unsigned char x, unsigned char width, unsigned char height, unsigned char radian, unsigned char vm[])
{
    unsigned char i, j;

    for (i = radian; i > 0; i--) {
        for (j = 0; j < (width - i * 2); j++) {
            display_pixel(y, x + i + j, black, vm);
        }
        y++;
    }
    for (i = 0; i < (height - radian * 2); i++) {
        for (j = 0; j < width; j++) {
            display_pixel(y, x + j, black, vm);
        }
        y++;
    }
    for (i = 0; i < radian + 1; i++) {
        for (j = 0; j < (width - i * 2); j++) {
            display_pixel(y, x + i + j, black, vm);
        }
        y++;
    }
}
