
#include "ec11.h"

unsigned int ec11_add = 50;

void interrupt_init()
{
	EA = 1;
	EX0 = 1;
	IT0 = 1;
}

void interrupt_n() interrupt INTERRUPT_N
{
	EX0 = 0;
	sleep_us(100);
	if (dt) {
		while (!clk);
		while (dt);
		ec11_add++;
		if (ec11_add > 100)
			ec11_add = 100;
	} else if (!dt) {
		while (!clk);
		while (!dt);
		ec11_add--;
		if (ec11_add < 0)
			ec11_add = 0;		
	}
	EX0 = 1;
}
