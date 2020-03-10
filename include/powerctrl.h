
#ifndef __POWERCTRL_H__
#define __POWERCTRL_H__

#include <reg52.h>

#define ON  1
#define OFF 0

#define INTERRUPT_N 0

extern void interrupt_init();

/*

			   PCON(0x87)
	D7    D6  D5  D4  D3  D2  D1   D0
	SMOD  __  __  __  GF1 GF0 PD  IDL

 */

extern void sleep(bit on_off);
extern void power_off(bit on_off);

#endif
