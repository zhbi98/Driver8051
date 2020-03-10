
#ifndef __I2CBUS_H__
#define __I2CBUS_H__

#include <reg52.h>

#include "time.h"

sbit scl = P2^2;
sbit sda = P2^3;

#define START  1
#define FINISH 0

#define ACK    0
#define NOACK  1

extern void master_stafinish(bit state);
extern void master_send_ack(bit ack);
extern void check_slave_ack();
extern void master_send_bit(bit a_bit);
extern void master_send_byte(unsigned char a_byte);
extern unsigned char master_receive_byte();

#endif
