
#include "pwmstc12.h"

void pwmstc_init()
{
	CMOD = 0x02;

	CL = 0;
	CH = 0;

	CCAPM0 = 0x42;
	CCAP0L = 0;
	CCAP0H = 0;
	/*
	CCAPM1 = 0x42;
	CCAP1L = 0;
	CCAP1H = 0;
	*/
	CR = 1;
}

void pwmstc_out(unsigned char lowt)
{
	CCAP0H = lowt;
	CCAP0L = lowt;
	/*
	CCAP1H = j;
	CCAP1L = j;
	*/
}
