
#ifndef __PWMSTC12_H__
#define __PWMSTC12_H__

#include <reg52.h>

sfr CCON     =   0xd8;
sbit CF      = CCON^7;
sbit CR      = CCON^6;
sbit CCF1    = CCON^1;
sbit CCF0    = CCON^0;

sfr CMOD     =   0xd9;

sfr CL       =   0xe9;
sfr CH       =   0xf9;

sfr CCAPM0   =   0xda;
sfr CCAPM1   =   0xdb;

sfr CCAP0L   =   0xea;
sfr CCAP0H   =   0xfa;

sfr CCAP1L   =   0xeb;
sfr CCAP1H   =   0xfb;

sfr PCA_PWM0 =   0xf2;
sfr PCA_PWM1 =   0xf3;

extern void pwmstc_init();
extern void pwmstc_out(unsigned char lowt);

#endif
