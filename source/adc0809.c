
#include "adc0809.h"

void timer0_8_init()
{
    TMOD = 0x02;
    TH0 = 100;
    TL0 = 100;
    
    EA = 1;
    ET0 = 1;
    TR0 = 1;
}

void adc0809_init()
{
    ale = 0;
    start = 0;
    oe = 0;
}

unsigned char adc0809_read()
{     
    unsigned char data_value;

    adc0809_init();
    /*
    adda = 1;
    addb = 1;
    addc = 1;
    */
    ale = 1;
    sleep_ms(2);    
    
    start = 0;
    sleep_ms(2);
    start = 1;
    sleep_ms(2);
    start = 0;
    
    while (!eoc);
    oe = 1;
    sleep_ms(2);
    data_encoded = 0xff;
    data_value = data_encoded;
    
    oe = 0;

    return data_value;   
}

void interrupt_n() interrupt INTERRUPT_N
{
    clock = ~ clock;
}
