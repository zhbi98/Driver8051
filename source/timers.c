
#include "timers.h"

void t_set_mode(bit gate)
{
#if (CURRENT_TIMER == 0)
	// gate * 8 because gate bit is bit 7
	TMOD = (TMOD & 0xf0) + gate * 8 + 1;

#elif (CURRENT_TIMER == 1)
	// gate * 8 because gate bit is bit 7
	// TMOD << 4 because timer 1 is heigh 4 bit
	TMOD = (TMOD & 0x0f) + ((gate * 8 + 1) << 4);
#endif
}

void t_set_time(unsigned int t)
{
	THX = (65536 - t) / 256;
	TLX = (65536 - t) % 256;
}

void t_init(bit gate, unsigned int t)
{
	/*
       T1                 T0
	GATE  C/T  M1  M0,  GATE  C/T  M1  M0

		M1:0, M0:0  13 bit mode
		M1:0, M0:1  16 bit mode
		M1:1, M0:0  8  bit mode
		M1:1, M0:1  16 bit mode

		set GATE 0 or 1
	*/

	t_set_mode(gate);

	// max 65536 us = 65.5ms
	t_set_time(t);

	TRX = 1;
	EA  = 1;
	ETX = 1;
}

void t_interrupt() interrupt INTERRUPT_N
{

}
