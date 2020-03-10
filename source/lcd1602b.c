
#include "lcd1602b.h"

unsigned char pcf_data = 0x08;

void pcf8574_stafinish(bit state)
{
	pcf8574_sda = state;
	pcf8574_scl = 1;
	sleep_us(5);
	pcf8574_sda = !state;
	sleep_us(5);
	pcf8574_scl = 0;
}

void check_pcf8574_ack()
{
	unsigned char ack = 0;

	pcf8574_scl = 1;
	sleep_us(1);
	while ((pcf8574_sda == 1) && (ack < 255))
		ack++;
	pcf8574_scl = 0;
	sleep_us(1);
}

void pcf8574_send_bit(bit a_bit)
{
	pcf8574_scl = 0;
	sleep_us(1);
	if (a_bit)
		pcf8574_sda = 1;
	else
		pcf8574_sda = 0;
	sleep_us(1);
	pcf8574_scl = 1;
	sleep_us(1);
}

void pcf8574_send_byte(unsigned char a_byte)
{
	unsigned char send;

	for (send = 0; send < 8; send++) {
		pcf8574_send_bit((a_byte << send) & 0x80);
	}
	pcf8574_scl = 0;
	sleep_us(1);
	pcf8574_sda = 1;
	sleep_us(1);
	pcf8574_scl = 1;
	sleep_us(1);
}

void pcf8574_write(unsigned char address, unsigned char dat_a)
{
	pcf8574_stafinish(PCF8574_START);
	pcf8574_send_byte(address);
	check_pcf8574_ack();
	pcf8574_send_byte(dat_a);
	check_pcf8574_ack();
	pcf8574_stafinish(PCF8574_FINISH);
}

void lcd1602_en()
{
	pcf_data |= (1 << (3 - 1));	
	pcf8574_write(PCF8597AT_ADDRESS, pcf_data);
	sleep_us(2);
	pcf_data &= ~(1 << (3 - 1));
	pcf8574_write(PCF8597AT_ADDRESS, pcf_data);
}

void write_command(unsigned char command)
{
	pcf_data &= ~(1 << (1 - 1));
	pcf_data &= ~(1 << (2 - 1));
	pcf8574_write(PCF8597AT_ADDRESS, pcf_data);

	pcf_data &= 0x0f;
	pcf_data |= command & 0xf0;
	pcf8574_write(PCF8597AT_ADDRESS, pcf_data);
	lcd1602_en();

	command <<= 4;

	pcf_data &= 0x0f;
	pcf_data |= command & 0xf0;
	pcf8574_write(PCF8597AT_ADDRESS, pcf_data);
	lcd1602_en();
}

void write_data(unsigned char dat_a)
{
	pcf_data |= 1 << (1 - 1);
	pcf_data &= ~(1 << (2 - 1));
	pcf8574_write(PCF8597AT_ADDRESS, pcf_data);

	pcf_data &= 0x0f;
	pcf_data |= dat_a & 0xf0;
	pcf8574_write(PCF8597AT_ADDRESS, pcf_data);
	lcd1602_en();

	dat_a <<= 4;

	pcf_data &= 0x0f;
	pcf_data |= dat_a & 0xf0;
	pcf8574_write(PCF8597AT_ADDRESS, pcf_data);
	lcd1602_en();
}

void lcd1602_init()
{	
	write_command(0x02);
    write_command(0x28);
    write_command(0x0c);
    write_command(0x01);
    
    sleep_ms(10);
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
