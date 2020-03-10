
#include "i2cbus.h"

void master_stafinish(bit state)
{
    sda = state;
    scl = 1;
    sleep_us(5);
    sda = !state;
    sleep_us(5);
    scl = 0;
}

void master_send_ack(bit ack)
{
    sda = ack;
    scl = 1;
    sleep_us(2);
    sda = !ack;
    scl = 0;
}

void check_slave_ack()
{
    unsigned char ack = 0;

    scl = 1;
    sleep_us(2);
    while ((sda == 1) && (ack < 255))
        ack++;
    scl = 0;
    sleep_us(2);
}

void master_send_bit(bit a_bit)
{
    scl = 0;
    sleep_us(2);
    if (a_bit)
        sda = 1;
    else
        sda = 0;
    sleep_us(2);
    scl = 1;
    sleep_us(2);
}

void master_send_byte(unsigned char a_byte)
{
    unsigned char send;

    for (send = 0; send < 8; send++) {
        master_send_bit((a_byte << send) & 0x80);
    }
    scl = 0;
    sleep_us(2);
    sda = 1;
    sleep_us(2);
    scl = 1;
    sleep_us(2);
}

unsigned char master_receive_byte()
{
    unsigned char dat_a;
    unsigned char receive;
    
    scl = 0; 
    sleep_us(2);
    sda  = 1;
    sleep_us(2);
    
    for (receive = 0; receive < 8; receive++) {
        scl = 1;
        sleep_us(2);
        dat_a = (dat_a << 1) | sda;
        scl = 0;
        sleep_us(2);
    }
    return dat_a;
}
