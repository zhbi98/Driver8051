
#ifndef __SPIBUS_H__
#define __SPIBUS_H__

#include <reg52.h>

#include "time.h"

sbit miso = P0^0;
sbit mosi = P0^1;
sbit sclk = P0^2;
sbit cs   = P0^3;

extern void spi_init();
extern void master_send_bit(bit a_bit);
extern void master_send_byte(unsigned char a_byte);
extern unsigned char master_receive_byte();

#endif
