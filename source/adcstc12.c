
#include "adcstc12.h"

/* 
						ADC_CONTR(0xbc)
	D7         D6      D5      D4        D3         D2    D1       D0
	ADC_POWER  SPEED1  SPEED0  ADC_FLAG  ADC_START  CHS2  CHS1   CHS0

						ADC_RES(0xbd)
	ADCV9      ADCV8   ADCV7   ADCV6     ADCV5      ADCV4 ADCV3 ADCV2
						ADC_RESL(0xbe)
	_____      _____   _____   _____     _____      _____ ADCV1 ADCV0

*/

void adcstc_init()
{
	ADC_RES = 0;
	ADC_RESL = 0;
	ADC_CONTR = 0x80;
	sleep_ms(20);
}

unsigned int adcstc_read(unsigned char ain)
{	
	ain = ain - 1;
	P1ASF |= 1 << ain;

	ADC_CONTR = ADC_CONTR | 0x88;
	ADC_CONTR = ADC_CONTR | ain;
	sleep_ms(50);

	while (!(ADC_CONTR & 0x10));
	ADC_CONTR &= 0xef;

	return (ADC_RES * 4 + ADC_RESL);
}
