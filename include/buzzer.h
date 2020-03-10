
#ifndef __BUZZER_H__
#define __BUZZER_H__

#include <reg52.h>

#include "time.h"

sbit buzzer = P3^3;

extern void buzzer_ring(unsigned char second);

#endif
