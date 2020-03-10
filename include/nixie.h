
#ifndef __NIXIE_H__
#define __NIXIE_H__

#include <reg52.h>

#include "time.h"

#define DATA P1

sbit a = P2^7;
sbit b = P2^6;
sbit c = P2^5;
sbit d = P2^4;

extern unsigned char code num_code[];

// extern unsigned char code num_code[];

extern void display_value(unsigned int number);

#endif
