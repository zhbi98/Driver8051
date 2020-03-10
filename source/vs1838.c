
#include "vs1838.h"

unsigned int value = 0;

void interrupt_init()
{
	EA = 1;
	EX0 = 1;
	IT0 = 1;
}

void delay(unsigned int us)
{
	TMOD = 0;
	TH0 = (8192 - us) / 32;
	TL0 = (8192 - us) % 32;
	TR0 = 1;

	while (!TF0);
	TF0 = 0;
}

unsigned int vs1838b_decoding()
{
	unsigned char byte, bits;
	unsigned char dat_a[4];

	EX0 = 0;

	TMOD = 1;
	TH0 = 0;
	TL0 = 0;
	TR0 = 1;
	while (!out);
	TR0 = 0;
	if (TH0 < 30 || TH0 > 40) {
		EX0 = 1;
		return 0;
	}
	TH0 = 0;
	TR0 = 1;
	while (out) {
		if (TH0 > 22) {
			EX0 = 1;
			return 0;
		}
	}
	TR0 = 0;
	if (TH0 < 12) {
		EX0 = 1;
		return 0;
	}
	for (byte = 0; byte < 4; byte++) {
		dat_a[byte] = 0;
		for (bits = 0; bits < 8; bits++) {
			while (!out);
			delay(840);
			dat_a[byte] = dat_a[byte] >> 1;
			if (out) {
				dat_a[byte] = dat_a[byte] | 0x80;
				while (out);
			}
		}
	}
	EX0 = 1;
	return dat_a[2];
}

void interrupt_n() interrupt INTERRUPT_N
{
	EX0 = 0;
	value = vs1838b_decoding();
	EX0 = 1;
}
