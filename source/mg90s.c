
#include "mg90s.h"

void out_time(unsigned int us)
{
	while (us--);
}

void mg90s_run(unsigned int time_h)
{
	unsigned char run;

	for (run = 0; run < 40; run++) {
		mg90s_pwm = 1;
		out_time(time_h);
		mg90s_pwm = 0;
		out_time(20000 - time_h);
	}
}
