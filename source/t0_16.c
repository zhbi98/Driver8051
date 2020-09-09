
#include "t0_16.h"

void t0_set_mode(bit gate)
{
#if (CURRENT_TIMER == 0)
    // gate * 8 because gate bit is bit 4
    // (+1) set 16 bit mode
    TMOD = (TMOD & 0xf0) + ((gate * 8 + 1) << 0);
#elif (CURRENT_TIMER == 1)
    // gate * 8 because gate bit is bit 7
    // (+1) set 16 bit mode
    TMOD = (TMOD & 0x0f) + ((gate * 8 + 1) << 4);
#endif
}

void t0_set_time(unsigned int t)
{
    TH0 = (65536 - t) / 256;
    TL0 = (65536 - t) % 256;
}

void t0_init(bit gate, unsigned int t)
{
    /*
       T1                 T0
    GATE  C/T  M1  M0,  GATE  C/T  M1  M0

        M1:0, M0:0  13 bit mode
        M1:0, M0:1  16 bit mode
        M1:1, M0:0   8 bit mode
        M1:1, M0:1  16 bit mode

        set GATE 0 or set 1
    */
 
    t0_set_mode(gate);

    // max 65536 us = 65.5ms
    t0_set_time(t);

    TR0 = 1;
    EA  = 1;
    ET0 = 1;
}

unsigned int t0;
void t0_interrupt() interrupt 1
{
    t0++;
}
