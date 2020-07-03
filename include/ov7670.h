
#ifndef __OV7670_H__
#define __OV7670_H__

#include <reg52.h>

#include "time.h"
#include "uart.h"

#define OV7670_START      1
#define OV7670_STOP       0

#define OV7670_ACK        0
#define OV7670_NOACK      1

#define Ov7670_ADDRESS 0X42

#define OV7670_WRITE      0
#define OV7670_READ       1

#define ov7670_data      P2

#define INTERRUPT_NN      0

sbit sccb_sda     = P3^6;
sbit sccb_scl     = P3^5;

sbit ov7670_rclk  = P0^7;
sbit ov7670_wen   = P0^6;
sbit ov7670_wrst  = P0^5;
sbit ov7670_rrst  = P0^4;
sbit ov7670_oe    = P0^3;
sbit ov7670_vsync = P0^2;

extern unsigned char p;

extern void sccb_on();
extern void sccb_off();
extern void send_no_ack();
extern unsigned char sccb_send_byte(unsigned char dat_a);
extern unsigned char sccb_receive_byte();
extern unsigned char sccb_write_reg(unsigned char reg_address, unsigned char reg_data);
extern unsigned char sccb_read_reg(unsigned char reg_address);

extern unsigned char ov7670_init();
extern unsigned int ov7670_image_data();
extern void read_ov7670();

extern void white_balance_setting(unsigned char setting);
extern void saturation_setting(unsigned char setting);
extern void brightness_setting(unsigned char setting);
extern void contrast_setting(unsigned char setting);
extern void special_effects_setting(unsigned char setting);
extern void display_area_setting(unsigned int y, unsigned int x, unsigned int width,unsigned int height);

extern void interrupt_init();

#endif
