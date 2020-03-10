
#include "buzzer.h"

void buzzer_ring(unsigned char second)
{
	for (; second > 0; second--) {
		buzzer = 0;
		sleep_ms(200);
		buzzer = 1;
		sleep_ms(500);
	}
}
