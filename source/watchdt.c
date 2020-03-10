
#include "watchdt.h"

/*
	
	WDT_CONTR (STC89C52RC(0xe1) ,STC12C5A60S2(0xc1))
	D7  D6  D5      D4       D3        D2   D1    D0
	__  __  EN_WDT  CLR_WDT  IDLE_WDT  PS2  PS1  PS0

 */

void watchdt(unsigned char errort)
{
	WDT_CONTR = errort;
}
