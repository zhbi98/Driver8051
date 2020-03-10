
#include "mpu6050data.h"

float accel_x()
{
    float ax;

    ax = mpu6050_data(ACCEL_XOUT_H);
    ax = 19.6 * (ax / 32768);

    return ax;
} 

float accel_y()
{
    float ay;

    ay = mpu6050_data(ACCEL_YOUT_H);
    ay = 19.6 * (ay / 32768);
    
    return ay;
}

float accel_z()
{
    float az;

    az = mpu6050_data(ACCEL_ZOUT_H);
    az = 19.6 * (az / 32768);

    return az;
}

float gyro_x()
{
    float gx;

    gx = mpu6050_data(GYRO_XOUT_H);
    gx = 250 * (gx / 32768);

    return gx;
} 

float gyro_y()
{
    float gy;

    gy = mpu6050_data(GYRO_YOUT_H);
    gy = 250 * (gy / 32768);
   
    return gy;
}

float gyro_z()
{
    float gz;

    gz = mpu6050_data(GYRO_ZOUT_H);
    gz = 250 * (gz / 32768);
    
    return gz;
}

float temper()
{
    float t;

    t = mpu6050_data(TEMP_OUT_H);
    t = 36.53 + (t / 340);

    return t;
}
