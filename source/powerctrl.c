
#include "powerctrl.h"

void interrupt_init()
{
	EA = 1;
	EX0 = 1;
	IT0 = 0;
}

/*

			   PCON(0x87)
	D7    D6  D5  D4  D3  D2  D1   D0
	SMOD  __  __  __  GF1 GF0 PD  IDL

 */

void sleep(bit on_off)
{
	if (on_off) {
		delete_content();
		PCON = 0x01;
	} else
		PCON = 0;	
}

void power_off(bit on_off)
{
	if (on_off) {
		delete_content();
		PCON = 0x02;
	} else
		PCON = 0;
}

void interrupt_n() interrupt INTERRUPT_N
{
	sleep(OFF);
	power_off(OFF);
}
