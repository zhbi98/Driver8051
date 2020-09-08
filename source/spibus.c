
#include "spibus.h"

void spi_init()
{
	sclk = 0;
	sleep_ms(1);
}

void master_send_bit(bit a_bit)
{
	if (a_bit)
		mosi = 1;
	else
		mosi = 0;
}

void master_send_byte(unsigned char a_byte)
{
	unsigned char send;

	cs = 0;
	for (send = 0; send < 8; send++) {
		sclk = 0;
		master_send_bit((a_byte << send) & 0x80);
		sleep_us(1);
		sclk = 1;
	}
	cs = 1;
}

unsigned char master_receive_byte()
{
	unsigned char receive;
	unsigned char dat_a;

	sclk = 1;
	for (receive = 0; receive < 8; receive++) {
		sclk = 1;
		sleep_us(1);
		sclk = 0;
		dat_a = dat_a << 1;
		dat_a = dat_a | (miso & 0x80);
		sleep_us(1);
	}
	return dat_a;
}
