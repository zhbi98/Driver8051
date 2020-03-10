
#include "mx1508.h"

void motor_a(unsigned char direction)
{
	if (direction == 1) {
		in1 = 1;
		in2 = 0;
	} else if (direction == 2) {
		in1 = 0;
		in2 = 1;
	} else {
		in1 = in2 = 0;
	}
}

void motor_b(unsigned char direction)
{
	if (direction == 1) {
		in3 = 1;
		in4 = 0;
	} else if (direction == 2) {
		in3 = 0;
		in4 = 1;
	} else {
		in3 = in4 = 0;
	}
}

void motor_run(bit motor, unsigned char direction)
{
	if (motor)
		motor_b(direction);
	else
		motor_a(direction);
}
