
#include "led.h"

void led_display(unsigned int time_l, unsigned int time_h, unsigned int second)
{
	if (second) {
		for (; second > 0; second--) {
			led_pin = 0;
			sleep_ms(time_l);
			led_pin = 1;
			sleep_ms(time_h);
		}
	} else
		led_pin = 0;
}

void led(unsigned int period, unsigned int time_l)
{
	unsigned int time_h;

	time_h = period - time_l;

	led_pin = 0;
	while (time_l--);
	led_pin = 1;
	while (time_h--);
}

void led_breath()
{
	unsigned int i;

	while (1) {
		for (i = 0; i < 600; i = i + 2) {
			led(600, i);
		}
		for (i = 600; i > 0; i = i - 2) {
			led(600, i);
		}
	}
}
