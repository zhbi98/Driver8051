
#ifndef __WEIGHT_H__
#define __WEIGHT_H__

#include <reg52.h>

#include "lcd1602a.h"
#include "hx711.h"

#define RATIO 430
#define CORRECT 0.52

unsigned long packing;
unsigned long weight;

extern void read_pack();
extern void read_weight();

#endif
