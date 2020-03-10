
#ifndef __HX711_H__
#define __HX711_H__

#include <reg52.h>

#include "time.h"

sbit sck = P0^3;
sbit dout = P0^4;

extern unsigned long hx711_read();

#endif
