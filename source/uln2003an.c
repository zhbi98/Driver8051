
#include "uln2003an.h"

void run_positive(unsigned char speed)
{
    unsigned char positive = 0;

    for (positive = 0; positive < 8; positive++) {
        in1 = 1, in2 = 0, in3 = 0, in4 = 0;
        sleep_us(speed);
        in1 = 1, in2 = 1, in3 = 0, in4 = 0;
        sleep_us(speed);
        in1 = 0, in2 = 1, in3 = 0, in4 = 1;
        sleep_us(speed);
        in1 = 0, in2 = 1, in3 = 1, in4 = 0;
        sleep_us(speed);
        in1 = 0, in2 = 0, in3 = 1, in4 = 0;
        sleep_us(speed);
        in1 = 0, in2 = 0, in3 = 1, in4 = 1;
        sleep_us(speed);
        in1 = 0, in2 = 0, in3 = 0, in4 = 1;
        sleep_us(speed);
        in1 = 1, in2 = 0, in3 = 0, in4 = 1;
        sleep_us(speed);
    }
}

void run_negative(unsigned char speed)
{
    unsigned char negative = 0;

    for (negative = 0; negative < 8; negative++) {
        in1 = 0, in2 = 0, in3 = 0, in4 = 1;
        sleep_us(speed);
        in1 = 0, in2 = 0, in3 = 1, in4 = 1;
        sleep_us(speed);
        in1 = 0, in2 = 0, in3 = 1, in4 = 0;
        sleep_us(speed);
        in1 = 0, in2 = 1, in3 = 1, in4 = 0;
        sleep_us(speed);
        in1 = 0, in2 = 1, in3 = 0, in4 = 0;
        sleep_us(speed);
        in1 = 1, in2 = 1, in3 = 0, in4 = 0;
        sleep_us(speed);
        in1 = 1, in2 = 0, in3 = 0, in4 = 0;
        sleep_us(speed);
        in1 = 1, in2 = 0, in3 = 0, in4 = 1;
        sleep_us(speed);
    }    
}

void run_stop()
{
    in1 = in2 = in3 = in4 = 0;
}

void positive_cycle(unsigned int cycle)
{
    cycle = cycle * 62;

    while (cycle > 0) {
        run_positive(100);
        cycle--;
    }
}

void negative_cycle(unsigned int cycle)
{
    cycle = cycle * 62;

    while (cycle > 0) {
        run_negative(100);
        cycle--;
    }
}
