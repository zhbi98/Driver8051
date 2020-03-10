
#include "hcsr04.h"

void timer0_16_init()
{
    TMOD = 0x01;
    TH0 = 0;
    TL0 = 0;  
}

void hcsr04_start()
{
    trig = 0;   
    trig = 1;
    sleep_us(22);
    trig = 0;
}

unsigned int compute_distance()
{
    unsigned int time = 0;
    unsigned int calculated = 0;
    
    time = TH0 * 256 + TL0;
    
    TH0 = 0;
    TL0 = 0;
    
    calculated = (time * 1.8) / 100;

    return calculated; 
}

unsigned int hcsr04_ranging()
{       
    unsigned int distance = 0;
    
    timer0_16_init();
           
    hcsr04_start();
    while (!echo);
    TR0 = 1;
    while (echo);
    TR0 = 0;       
    distance = compute_distance();
    sleep_ms(220);
    
    return distance; 
}
