
#ifndef __MPU6050_H__
#define __MPU6050_H__

#include <reg52.h>

#include "time.h"

#define SMPLRT_DIV      0x19
#define CONFIG          0x1a

#define GYRO_CONFIG     0x1b
#define ACCEL_CONFIG    0x1c

#define ACCEL_XOUT_H    0x3b
#define ACCEL_XOUT_L    0x3c
#define ACCEL_YOUT_H    0x3d
#define ACCEL_YOUT_L    0x3e
#define ACCEL_ZOUT_H    0x3f
#define ACCEL_ZOUT_L    0x40

#define TEMP_OUT_H      0x41
#define TEMP_OUT_L      0x42

#define GYRO_XOUT_H     0x43
#define GYRO_XOUT_L     0x44
#define GYRO_YOUT_H     0x45
#define GYRO_YOUT_L     0x46
#define GYRO_ZOUT_H     0x47
#define GYRO_ZOUT_L     0x48

#define PWR_MGMT_1      0x6b
#define WHO_AM_I        0x75

#define MPU6050_ADDRESS 0xd0
#define MPU6050_WRITE      0
#define MPU6050_READ       1

#define MPU6050_START      1
#define MPU6050_FINISH     0

#define MPU6050_ACK        0
#define MPU6050_NOACK      1

sbit mpu6050_scl = P2^1;
sbit mpu6050_sda = P2^0;

extern void mpu6050_stafinish(bit state);
extern void master_sendack_mpu6050(bit ack);
extern void check_mpu6050_ack();
extern void mpu6050_send_bit(bit a_bit);
extern void mpu6050_send_byte(unsigned char a_byte);
extern unsigned char master_receive_mpu6050();
extern void mpu6050_write(unsigned char reg_address, unsigned char reg_data);
extern void mpu6050_init();
extern unsigned char mpu6050_read(unsigned char reg_address);
extern int mpu6050_data(unsigned char reg_address);

#endif
