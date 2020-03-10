
#include "pwm.h"

void out_time(unsigned int us)
{
	while (us--);	
}

void pwm_out(unsigned int period, unsigned int time_l)
{
	pwm_pin = 0;
	out_time(time_l);
	pwm_pin = 1;
	out_time(period - time_l);
}
