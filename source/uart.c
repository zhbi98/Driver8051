
#include "uart.h"

unsigned char uart_recv[16] = {0};

/*

				SCON(0x98)
	D7   D6   D5   D4   D3   D2   D1   D0
	SM0  SM1  SM2  REN  TB8  RB8  TI   RI
			
				PCON(0x87)
	SMOD __   __   __   Gf1  GF0  PD   IDL

 */

void uart_init(unsigned char bd)
{
	TMOD = 0x20;
	TH1 = 255 - bd;
	TL1 = 255 - bd;
	TR1 = 1;

	SCON = 0x40;
	PCON = 0x00;

	EA = 1;
	ES = 1;
	REN = 1;
 }

void uart_send_byte(unsigned char byte)
{
	SBUF = byte;

	while (!TI);
	TI = 0;
}

void uart_send_data(unsigned char * dat_a)
{
	unsigned char bits = 0;

	while (dat_a[bits] != '\0') {
		uart_send_byte(dat_a[bits]);
		bits++;
	}
}

void uart_send_value(unsigned char * format, ...)
{
	unsigned char value[16];

    va_list parameter_pointer;
    va_start(parameter_pointer, format);

    vsprintf(value, format, parameter_pointer);
    
    va_end(parameter_pointer);

    uart_send_data(value);
}

unsigned char uart_receive_byte()
{
 	unsigned char byte;

 	ES = 0;
 	RI = 0;
 	
 	byte = SBUF;

 	ES = 1;

 	return byte;
} 

void uart_receive_data()
{
	static unsigned char uart_bits = 0;

	uart_receive[uart_bits] = uart_receive_byte();
	uart_bits++;
}

void interrupt_n() interrupt INTERRUPT_N
{
	uart_receive_data();
}
