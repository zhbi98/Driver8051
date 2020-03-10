
#ifndef __WATCHDT_H__
#define __WATCHDT_H__

#include <reg52.h>

sfr WDT_CONTR = 0xe1;

/*
	
	WDT_CONTR (STC89C52RC(0xe1) ,STC12C5A60S2(0xc1))
	D7  D6  D5      D4       D3        D2   D1    D0
	__  __  EN_WDT  CLR_WDT  IDLE_WDT  PS2  PS1  PS0

 */

enum errort
{
	MS_65   = 0x30,
	MS_131  = 0x31,
	MS_262  = 0x32,
	MS_520  = 0x33,
	MS_1000 = 0x34,
	MS_2000 = 0x35,
	MS_4000 = 0x36,
	MS_8000 = 0x37
};

extern void watchdt(unsigned char errort);

#endif
