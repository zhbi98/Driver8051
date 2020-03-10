
#include "time.h"

void sleep_us(unsigned int us)
{	
	for (; us > 0; us--)
		_nop_();
}

void sleep_ms(unsigned int ms)
{
	unsigned int loop;

	for (; ms > 0; ms--)
		for (loop = 125; loop > 0; loop--);
}

void sleep_s(unsigned int s)
{
	unsigned char count;
	
	TMOD = 0x01;
	for (; s > 0; s--) {
		for (count = 0; count < 20; count++) {
			TH0 = (65536 - 45872) / 256;
			TL0 = (65536 - 45872) % 256;
			TR0 = 1;
			while (!TF0);
			TF0 = 0;
		}
	}
}
