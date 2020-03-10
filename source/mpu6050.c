
#include "mpu6050.h"

void mpu6050_stafinish(bit state)
{
    mpu6050_sda = state;
    mpu6050_scl = 1;
    sleep_us(5);
    mpu6050_sda = !state;
    sleep_us(5);
    mpu6050_scl = 0;
}

void master_sendack_mpu6050(bit ack)
{
    mpu6050_sda = ack;
    mpu6050_scl = 1;
    sleep_us(2);
    mpu6050_sda = !ack;
    mpu6050_scl = 0;
}

void check_mpu6050_ack()
{
    unsigned char ack = 0;

    mpu6050_scl = 1;
    sleep_us(2);
    while ((mpu6050_sda == 1) && (ack < 255))
        ack++;
    mpu6050_scl = 0;
    sleep_us(2);
}

void mpu6050_send_bit(bit a_bit)
{
    mpu6050_scl = 0;
    sleep_us(2);
    if (a_bit)
        mpu6050_sda = 1;
    else
        mpu6050_sda = 0;
    sleep_us(2);
    mpu6050_scl = 1;
    sleep_us(2);
}

void mpu6050_send_byte(unsigned char a_byte)
{
    unsigned char send;

    for (send = 0; send < 8; send++) {
        mpu6050_send_bit((a_byte << send) & 0x80);
    }
    mpu6050_scl = 0;
    sleep_us(2);
    mpu6050_sda = 1;
    sleep_us(2);
    mpu6050_scl = 1;
    sleep_us(2);
}

unsigned char master_receive_mpu6050()
{
    unsigned char dat_a;
    unsigned char receive;
    
    mpu6050_scl = 0; 
    sleep_us(2);
    mpu6050_sda  = 1;
    sleep_us(2);
    
    for (receive = 0; receive < 8; receive++) {
        mpu6050_scl = 1;
        sleep_us(2);
        dat_a = (dat_a << 1) | mpu6050_sda;
        mpu6050_scl = 0;
        sleep_us(2);
    }
    return dat_a;
}

void mpu6050_write(unsigned char reg_address, unsigned char reg_data)
{
    mpu6050_stafinish(MPU6050_START);

    mpu6050_send_byte(MPU6050_ADDRESS + MPU6050_WRITE);
    check_mpu6050_ack();

    mpu6050_send_byte(reg_address);
    check_mpu6050_ack();

    mpu6050_send_byte(reg_data);
    check_mpu6050_ack();

    mpu6050_stafinish(MPU6050_FINISH);

}

void mpu6050_init()
{
    mpu6050_write(PWR_MGMT_1, 0x00);
    mpu6050_write(SMPLRT_DIV, 0x07);
    mpu6050_write(CONFIG, 0x06);
    mpu6050_write(GYRO_CONFIG, 0x18);
    mpu6050_write(ACCEL_CONFIG, 0x01);
}

unsigned char mpu6050_read(unsigned char reg_address)
{
    unsigned char reg_data;

    mpu6050_stafinish(MPU6050_START);

    mpu6050_send_byte(MPU6050_ADDRESS + MPU6050_WRITE);
    check_mpu6050_ack();

    mpu6050_send_byte(reg_address);
    check_mpu6050_ack();

    mpu6050_stafinish(MPU6050_START);

    mpu6050_send_byte(MPU6050_ADDRESS + MPU6050_READ);
    reg_data = master_receive_mpu6050();
    master_sendack_mpu6050(MPU6050_NOACK);

    mpu6050_stafinish(MPU6050_FINISH);
    return reg_data;
}

int mpu6050_data(unsigned char reg_address)
{
    unsigned char h_bit, l_bit;

    h_bit = mpu6050_read(reg_address);
    l_bit = mpu6050_read(reg_address + 1);

    return ((h_bit << 8) + l_bit);
}
