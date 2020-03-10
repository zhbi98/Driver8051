
#ifndef __PCF8591_H__
#define __PCF8591_H__

#include <reg52.h>

#include "time.h"

#define PCF8591_START      1
#define PCF8591_FINISH     0

#define PCF8591_ACK        0
#define PCF8591_NOACK      1

#define PCF8591_ADDRESS 0x90

#define PCF8591_WRITE      0
#define PCF8591_READ       1

sbit pcf8591_scl = P2^0;
sbit pcf8591_sda = P2^1;

extern void pcf8591_stafinish(bit state);
extern void master_sendack_pcf8591(bit ack);
extern void check_pcf8591_ack();
extern void pcf8591_send_bit(bit a_bit);
extern void pcf8591_send_byte(unsigned char a_byte);
extern unsigned char master_receive_pcf8591();
extern unsigned char pcf8591_read(unsigned char ain);
extern void pcf8591_aout(unsigned char da_value);

#endif
