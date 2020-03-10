
#include "hx711.h"

unsigned long hx711_read()
{
	unsigned long weight;
	unsigned char read;

	dout = 1;
	sleep_ms(1);
	sck = 0;
	weight = 0;
	while (dout);
	for (read = 0; read < 24; read++) {
		sck = 1;
		weight <<= 1;
		sck = 0;
		if (dout)
			weight++;
	}
	sck = 1;
	weight ^= 0x800000;
	sleep_ms(1);
	sck = 0;

	return weight;
}
