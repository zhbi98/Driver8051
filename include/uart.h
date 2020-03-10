
#ifndef __UART_H__
#define __UART_H__

#include <reg52.h>
#include <stdio.h>
#include <stdarg.h>

#define INTERRUPT_N 4

extern unsigned char uart_recv[];

/*

				SCON(0x98)
	D7   D6   D5   D4   D3   D2   D1   D0
	SM0  SM1  SM2  REN  TB8  RB8  TI   RI
			
				PCON(0x87)
	SMOD __   __   __   Gf1  GF0  PD   IDL

 */

extern void uart_init(unsigned char bd);
extern void uart_send_byte(unsigned char byte);
extern void uart_send_data(unsigned char * dat_a);
extern void uart_send_value(unsigned char * format, ...);
extern unsigned char uart_receive_byte();
extern void uart_receive_data();

#endif
