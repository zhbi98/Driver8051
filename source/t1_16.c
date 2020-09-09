
#include "t1_16.h"

void t1_set_mode(bit gate)
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

void t1_set_time(unsigned int t)
{
    TH1 = (65536 - t) / 256;
    TL1 = (65536 - t) % 256;
}

void t1_init(bit gate, unsigned int t)
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
 
    t1_set_mode(gate);

    // max 65536 us = 65.5ms
    t1_set_time(t);

    TR1 = 1;
    EA  = 1;
    ET1 = 1;
}

unsigned int t1;
void t1_interrupt() interrupt 3
{
    t1++;
}
