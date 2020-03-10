
#ifndef __MG90S_H__
#define __MG90S_H__

#include <reg52.h>

sbit mg90s_pwm = P2^0;

enum run_angle {
	RUN_000 =  320,
	RUN_015 =  410,
	RUN_030 =  500,
	RUN_045 =  600,
	RUN_060 =  710,
	RUN_075 =  820,
	RUN_090 =  950,
	RUN_105 = 1050,
	RUN_120 = 1200,
	RUN_135 = 1300,
	RUN_150 = 1400,
	RUN_165 = 1500,
	RUN_180 = 1800	
};

extern void out_time(unsigned int us);
extern void mg90s_run(unsigned int time_h);

#endif
