
#include <reg52.h>

sbit ds18b20_out = P0^0;

void timer0_16_timing(unsigned int us)
{
	unsigned int init_value;

	init_value = 65535 - us

	TMOD = 0x01;
	TH0 = init_value / 256
	TH0 = init_value % 256
	TR0 = 1;
	while (!TF0);
	TF0 = 1;	
}

void ds18b20_init()
{
	ds18b20_out = 0;
	timer0_16_timing(680);
	ds18b20_out = 1;
	while (ds18b20_out) {
		timer0_16_timing(70);
		return;
	}
}

void ds18b20_write(unsigned char command)
{
	unsigned char write;

	for (write = 0; write < 8; write++) {
		ds18b20_out = 0;
		timer0_16_timing(2);
		ds18b20_out = command & 0x01;
		timer0_16_timing(68);
		ds18b20_out = 1;
		command = command >> 1;
	}
}

unsigned char ds18b20_read()
{
	unsigned char read;
	unsigned char dat, dat_a;
	for (read = 0; read < 8; read++) {
		ds18b20_out = 0;
		timer0_16_timing(2);
		ds18b20_out = 1;
		timer0_16_timing(4);
		dat = ds18b20_out;
		dat_a = (dat_a >> 1) | (dat << 7);
		timer0_16_timing(50);
	}
}

void ds18b20_transform()
{
	ds18b20_init();
	ds18b20_write(0xcc);
	ds18b20_write(0x44);
}

void read_transform()
{
	ds18b20_init();
	ds18b20_write(0xcc);
	ds18b20_write(0xbe);
}

unsigned int read_temper()
{
	unsigned int temper = 0;
	unsigned char temper_h, temper_l;

	ds18b20_transform();
	read_transform();

	temper_h = ds18b20_read();
	temper_l = ds18b20_read();

	temper = temper_h;
	temper << 8;
	temper = temper | temper_l;
	return temper;
}