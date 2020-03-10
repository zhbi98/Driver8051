
#include "lcd1602a.h"

void write_command(unsigned char command)
{
    rs = 0;
    rw = 0;
    sleep_ms(1);
    lcd1602_data = command;
    sleep_ms(1);
    en = 1;
    sleep_ms(1);
    en = 0;
}
    
void write_data(unsigned char dat_a)
{
    rs = 1;
    rw = 0;
    sleep_ms(1);
    lcd1602_data = dat_a;
    sleep_ms(1);
    en = 1;
    sleep_ms(1);
    en = 0;  
}

void lcd1602_init()
{
    en = 0;
    
    write_command(0x38);
    write_command(0x0c);
    write_command(0x06);
    write_command(0x01);
    
    sleep_ms(1);
}

void clean()
{       
    write_command(0x01);   
}

void display_character(unsigned char y, unsigned char x, unsigned char character)
{
    unsigned char command;
    
    x = x - 1;
    y = y - 1;
    
    if (y) {   
        command = x | 0x40;
        command = command | 0x80;
    } else {
        command = x | 0x80;
    }
    
    write_command(command);
    write_data(character);
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

void display_value(unsigned char y, unsigned char x, unsigned char * format, ...)
{
    unsigned char value[16];
    unsigned char bits = 0;

    va_list parameter_pointer;
    va_start(parameter_pointer, format);

    vsprintf(value, format, parameter_pointer);
    
    va_end(parameter_pointer);

    while (value[bits] != '\0') {
        display_character(y, x, value[bits]);

        bits++;
        x++;
    }   
}
