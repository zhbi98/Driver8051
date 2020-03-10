
#ifndef __ADCSTC12_H__
#define __ADCSTC12_H__

#include <reg52.h>

#include "time.h"

sfr P1ASF     = 0x9d;
sfr ADC_CONTR = 0xbc;
sfr ADC_RES   = 0xbd;
sfr ADC_RESL  = 0xbe;

/* 
						ADC_CONTR(0xbc)
	D7         D6      D5      D4        D3         D2    D1       D0
	ADC_POWER  SPEED1  SPEED0  ADC_FLAG  ADC_START  CHS2  CHS1   CHS0

						ADC_RES(0xbd)
	ADCV9      ADCV8   ADCV7   ADCV6     ADCV5      ADCV4 ADCV3 ADCV2
						ADC_RESL(0xbe)
	_____      _____   _____   _____     _____      _____ ADCV1 ADCV0

*/

extern void adcstc_init();
extern unsigned int adcstc_read(unsigned char ain);
 
 #endif
