
#include "pcf8591.h"

void pcf8591_stafinish(bit state)
{
    pcf8591_sda = state;
    pcf8591_scl = 1;
    sleep_us(5);
    pcf8591_sda = !state;
    sleep_us(5);
    pcf8591_scl = 0;
}

void master_sendack_pcf8591(bit ack)
{
    pcf8591_sda = ack;
    pcf8591_scl = 1;
    sleep_us(2);
    pcf8591_sda = !ack;
    pcf8591_scl = 0;
}

void check_pcf8591_ack()
{
    unsigned char ack = 0;

    pcf8591_scl = 1;
    sleep_us(2);
    while ((pcf8591_sda == 1) && (ack < 255))
        ack++;
    pcf8591_scl = 0;
    sleep_us(2);
}

void pcf8591_send_bit(bit a_bit)
{
    pcf8591_scl = 0;
    sleep_us(2);
    if (a_bit)
        pcf8591_sda = 1;
    else
        pcf8591_sda = 0;
    sleep_us(2);
    pcf8591_scl = 1;
    sleep_us(2);
}

void pcf8591_send_byte(unsigned char a_byte)
{
    unsigned char send;

    for (send = 0; send < 8; send++) {
        pcf8591_send_bit((a_byte << send) & 0x80);
    }
    pcf8591_scl = 0;
    sleep_us(2);
    pcf8591_sda = 1;
    sleep_us(2);
    pcf8591_scl = 1;
    sleep_us(2);
}

unsigned char master_receive_pcf8591()
{
    unsigned char dat_a;
    unsigned char receive;
    
    pcf8591_scl = 0; 
    sleep_us(2);
    pcf8591_sda  = 1;
    sleep_us(2);
    
    for (receive = 0; receive < 8; receive++) {
        pcf8591_scl = 1;
        sleep_us(2);
        dat_a = (dat_a << 1) | pcf8591_sda;
        pcf8591_scl = 0;
        sleep_us(2);
    }
    return dat_a;
}

unsigned char pcf8591_read(unsigned char ain)
{
    unsigned char ad_value;

    pcf8591_stafinish(PCF8591_START);
    pcf8591_send_byte(PCF8591_ADDRESS + PCF8591_WRITE);
    pcf8591_send_byte(0x40 + ain - 1);
    check_pcf8591_ack();
    pcf8591_stafinish(PCF8591_FINISH);

    pcf8591_stafinish(PCF8591_START);
    pcf8591_send_byte(PCF8591_ADDRESS + PCF8591_READ);
    ad_value = master_receive_pcf8591();
    master_sendack_pcf8591(PCF8591_NOACK);
    pcf8591_stafinish(PCF8591_FINISH);

    return ad_value;
}

void pcf8591_aout(unsigned char da_value)
{
    pcf8591_stafinish(PCF8591_START);
    pcf8591_send_byte(PCF8591_ADDRESS + PCF8591_WRITE);
    check_pcf8591_ack();
    pcf8591_send_byte(0x40);
    check_pcf8591_ack();
    pcf8591_send_byte(da_value);
    check_pcf8591_ack();
    pcf8591_stafinish(PCF8591_FINISH);
}
