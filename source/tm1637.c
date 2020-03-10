
#include "tm1637.h"

unsigned char code num_code[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66,
                                0x6d, 0x7d, 0x07, 0x7f, 0x6f};

unsigned char code twinkle_code[] = {0xbf, 0x86, 0xdb, 0xcf, 0xe6,
                                    0xed, 0xfd, 0x87, 0xff, 0xef};

void tm1637_stafinish(bit state)
{
	tm1637_sda = state;
	tm1637_scl = 1;
	sleep_us(5);
	tm1637_sda = !state;
	sleep_us(5);
	tm1637_scl = 0;
}

void check_tm1637_ack()
{
	unsigned char ack = 0;

	tm1637_scl = 1;
	sleep_us(2);
	while ((tm1637_sda == 1) && (ack < 255))
		ack++;
	tm1637_scl = 0;
	sleep_us(2);
}

void tm1637_send_bit(bit a_bit)
{
	tm1637_scl = 0;
	sleep_us(2);
	if (a_bit)
		tm1637_sda = 1;
	else
		tm1637_sda = 0;
	sleep_us(2);
	tm1637_scl = 1;
	sleep_us(2);
}

void tm1637_send_byte(unsigned char a_byte)
{
	unsigned char send;

	for (send = 0; send < 8; send++) {
		tm1637_send_bit((a_byte >> send) & 0x01);
	}
	tm1637_scl = 0;
	sleep_us(2);
	tm1637_sda = 1;
	sleep_us(2);
	tm1637_scl = 1;
	sleep_us(2);
}

void write_command(unsigned char command)
{
	tm1637_stafinish(TM1637_START);
	tm1637_send_byte(command);
	check_tm1637_ack();
	tm1637_stafinish(TM1637_FINISH);	
}

void write_data(unsigned char address, unsigned char dat_a)
{
	tm1637_stafinish(TM1637_START);
	tm1637_send_byte(address);
	check_tm1637_ack();
	tm1637_send_byte(dat_a);
	check_tm1637_ack();
	tm1637_stafinish(TM1637_FINISH);
} 

void display_value(unsigned int value)
{
	unsigned char l;
	unsigned char bits[4];
	
	for (l = 0; l < 4; l++) {
		bits[l] = value % 10;
		value = value / 10;
	}
	write_command(0x44);
	write_data(0xc0, num_code[bits[3]]);
	write_data(0xc1, num_code[bits[2]]);
	write_data(0xc2, num_code[bits[1]]);
	write_data(0xc3, num_code[bits[0]]);	
	write_command(0x8a);	
}

void display_time(unsigned char h, unsigned m)
{
	hour.ten = h / 10;
	hour.bits = h % 10;

	minute.ten = m / 10;
	minute.bits = m % 10;

	write_command(0x44);
	write_data(0xc0, num_code[hour.ten]);
	if (twinkle) {
		write_data(0xc1, twinkle_code[hour.bits]);
	} else {
		write_data(0xc1, num_code[hour.bits]);
	}
	
	write_data(0xc2, num_code[minute.ten]);
	write_data(0xc3, num_code[minute.bits]);
	write_command(0x8a);
}

void display_off()
{
	write_command(0x44);
	write_data(0xc0, 0);
	write_data(0xc1, 0);
	write_data(0xc2, 0);
	write_data(0xc3, 0);
	write_command(0x8a);
}
