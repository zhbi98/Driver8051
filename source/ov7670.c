
#include "ov7670.h"

unsigned char p = 0;

void sccb_on()
{
    sccb_sda = 1;
    sccb_scl = 1;
    sleep_us(50);  
    sccb_sda = 0;
    sleep_us(50);    
    sccb_scl = 0;
}

void sccb_off()
{
    sccb_sda = 0;
    sleep_us(50);    
    sccb_scl = 1; 
    sleep_us(50); 
    sccb_sda = 1;
    sleep_us(50);
}  

void send_no_ack()
{
    sleep_us(50);
    sccb_sda = 1; 
    sccb_scl = 1; 
    sleep_us(50);
    sccb_scl = 0; 
    sleep_us(50);
    sccb_sda = 0; 
    sleep_us(50);
}

unsigned char sccb_send_byte(unsigned char dat_a)
{
    unsigned char send, t;

    for (send = 0; send < 8; send++) {
        if (dat_a & 0x80)
            sccb_sda = 1; 
        else
            sccb_sda = 0;

        dat_a <<= 1;
        sleep_us(50);
        sccb_scl = 1;
        sleep_us(50);
        sccb_scl = 0;        
    }

    sccb_sda = 1;
    sleep_us(50);
    sccb_scl = 1;
    sleep_us(50);
    if (sccb_sda)
        // send error
        t = 1;
    else
        // send success
        t = 0;
    
    sccb_scl = 0;

    return t;  
}    

unsigned char sccb_receive_byte()
{
    unsigned char t = 0, receive;
    
    for (receive = 8; receive > 0; receive--) {
        sleep_us(50);
        sccb_scl = 1;
        t = t << 1;
        if (sccb_sda)
            t++;   
        sleep_us(50);
        sccb_scl = 0;
    }

    return t;
}

unsigned char sccb_write_reg(unsigned char reg_address, unsigned char reg_data)
{
    unsigned char t = 0;

    sccb_on();

    if (sccb_send_byte(Ov7670_ADDRESS))
        t = 1;
    sleep_us(100);

    if (sccb_send_byte(reg_address))
        t = 1;
    sleep_us(100);

    if (sccb_send_byte(reg_data))
        t = 1;
    
    sccb_off();

    return  t;
}                               

unsigned char sccb_read_reg(unsigned char reg_address)
{
    unsigned char dat_a = 0;

    sccb_on();

    sccb_send_byte(Ov7670_ADDRESS);
    sleep_us(100);
    sccb_send_byte(reg_address);
    sleep_us(100);
    
    sccb_off();
    sleep_us(100);

    sccb_on();
    sccb_send_byte(Ov7670_ADDRESS + OV7670_READ);
    sleep_us(100);
    dat_a = sccb_receive_byte();
    send_no_ack();

    sccb_off();

    return dat_a;
}

unsigned char code ov7670_setting[][2] = {
    // The following is OV7670 QVGA RGB565 parameter
    // dummy
    {0x3a, 0x04},
    // 565
    {0x40, 0xd0},
    // QVGA,RGB output
    {0x12, 0x14},
    // Output window settings
    // HREF control bit[2:0] HREF start 3 LSB bit[5:3] HSTOP HREF end 3LSB
    {0x32, 0x80},
    // HSTART start high 8-bit MSB  
    {0x17, 0x16},
    // 5 HSTOP end high 8-bit
    {0x18, 0x04},
    {0x19, 0x02},
    // 0x7a,
    {0x1a, 0x7b},
    // 0x0a, Frame vertical direction control
    {0x03, 0x06},

    {0x0c, 0x00},
    // 0x00
    {0x15, 0x00},
    // 10
    {0x3e, 0x00},
    {0x70, 0x3a},
    {0x71, 0x35},
    {0x72, 0x11},
    {0x73, 0x00},
    // 15
    {0xa2, 0x02},
    // Clock divider setting, 0, No frequency division
    {0x11, 0x81},
    {0x7a, 0x20},
    {0x7b, 0x1c},
    {0x7c, 0x28},
    // 20
    {0x7d, 0x3c},
    {0x7e, 0x55},
    {0x7f, 0x68},
    {0x80, 0x76},
    {0x81, 0x80},

    {0x82, 0x88},
    {0x83, 0x8f},
    {0x84, 0x96},
    {0x85, 0xa3},
    {0x86, 0xaf},
    // 30
    {0x87, 0xc4},
    {0x88, 0xd7},
    {0x89, 0xe8},
    {0x13, 0xe0},
    // AGC
    {0x00, 0x00},

    {0x10, 0x00},
    // full window, [5:4]: 01 half window，10 1/4 window，11 1/4window 
    {0x0d, 0x00},
    // 0x38, limit the max gain
    {0x14, 0x28},
    {0xa5, 0x05},
    {0xab, 0x07},
    // 40
    {0x24, 0x75},
    {0x25, 0x63},
    {0x26, 0xA5},
    {0x9f, 0x78},
    {0xa0, 0x68},
    // 0x0b
    {0xa1, 0x03},
    // 0xd8
    {0xa6, 0xdf},
    // 0xd8
    {0xa7, 0xdf},
    {0xa8, 0xf0},
    {0xa9, 0x90},
    // 50
    {0xaa, 0x94},
    {0x13, 0xe5},
    {0x0e, 0x61},
    {0x0f, 0x4b},
    {0x16, 0x02},
    // Image output mirror control 0x07
    {0x1e, 0x27},
    {0x21, 0x02},
    {0x22, 0x91},
    {0x29, 0x07},
    {0x33, 0x0b},
    // 60
    {0x35, 0x0b},
    {0x37, 0x1d},
    {0x38, 0x71},
    {0x39, 0x2a},
    {0x3c, 0x78},

    {0x4d, 0x40},
    {0x4e, 0x20},
    {0x69, 0x00},
    // PLL * 4 = 48Mhz
    {0x6b, 0x40},
    {0x74, 0x19},
    {0x8d, 0x4f},
    // 70
    {0x8e, 0x00},
    {0x8f, 0x00},
    {0x90, 0x00},
    {0x91, 0x00},
    // 0x19, 0x66
    {0x92, 0x00},

    {0x96, 0x00},
    {0x9a, 0x80},
    {0xb0, 0x84},
    {0xb1, 0x0c},
    {0xb2, 0x0e},
    // 80
    {0xb3, 0x82},
    {0xb8, 0x0a},
    {0x43, 0x14},
    {0x44, 0xf0},
    {0x45, 0x34},

    {0x46, 0x58},
    {0x47, 0x28},
    {0x48, 0x3a},
    {0x59, 0x88},
    {0x5a, 0x88},
    // 90
    {0x5b, 0x44},
    {0x5c, 0x67},
    {0x5d, 0x49},
    {0x5e, 0x0e},
    {0x64, 0x04},
    {0x65, 0x20},

    {0x66, 0x05},
    {0x94, 0x04},
    {0x95, 0x08},
    {0x6c, 0x0a},
    {0x6d, 0x55},

    {0x4f, 0x80},
    {0x50, 0x80},
    {0x51, 0x00},
    {0x52, 0x22},
    {0x53, 0x5e},
    {0x54, 0x80},

    // 110
    // {0x54, 0x40},

    // Maximum driving capacity
    {0x09, 0x03},
    // 100
    {0x6e, 0x11},
    // 0x9e for advance AWB
    {0x6f, 0x9f},
    // brightness
    {0x55, 0x00},
    // Contrast 0x40
    {0x56, 0x40},
    // 0x40, change according to Jim's request
    {0x57, 0x40},
    // Remove the following data
    // OV7670_Window_Set(12, 176, 240, 320);
    // -> OV7670_Window_Set(12,174,240,320);,
    // To remove the blue jitter in the bottom row
    {0x6a, 0x40},
    {0x01, 0x40},
    {0x02, 0x40},
    {0x13, 0xe7},
    {0x15, 0x00},  

    {0x58, 0x9e},

    {0x41, 0x08},
    {0x3f, 0x00},
    {0x75, 0x05},
    {0x76, 0xe1},
    {0x4c, 0x00},
    {0x77, 0x01},
    {0x3d, 0xc2},   
    {0x4b, 0x09},
    {0xc9, 0x60},
    {0x41, 0x38},

    {0x34, 0x11},
    {0x3b, 0x02}, 

    {0xa4, 0x89},
    {0x96, 0x00},
    {0x97, 0x30},
    {0x98, 0x20},
    {0x99, 0x30},
    {0x9a, 0x84},
    {0x9b, 0x29},
    {0x9c, 0x03},
    {0x9d, 0x4c},
    {0x9e, 0x3f},
    {0x78, 0x04},
    
    {0x79, 0x01},
    {0xc8, 0xf0},
    {0x79, 0x0f},
    {0xc8, 0x00},
    {0x79, 0x10},
    {0xc8, 0x7e},
    {0x79, 0x0a},
    {0xc8, 0x80},
    {0x79, 0x0b},
    {0xc8, 0x01},
    {0x79, 0x0c},
    {0xc8, 0x0f},
    {0x79, 0x0d},
    {0xc8, 0x20},
    {0x79, 0x09},
    {0xc8, 0x80},
    {0x79, 0x02},
    {0xc8, 0xc0},
    {0x79, 0x03},
    {0xc8, 0x40},
    {0x79, 0x05},
    {0xc8, 0x30},
    {0x79, 0x26}, 
    {0x09, 0x00}, 
}; 

unsigned char ov7670_init()
{
    unsigned int i = 0;
    unsigned char id = 0;

    ov7670_rclk  = 1;
    ov7670_wen   = 1;
    ov7670_wrst  = 1;
    ov7670_rrst  = 1;
    ov7670_oe    = 0;
    ov7670_vsync = 1;

    interrupt_init();

    sccb_write_reg(0x12, 0x80);

    // communication is 
    // normal return 0x73 -> 115
    id = sccb_read_reg(0x0b);
    if (id != 115)
        return 1;

    // communication is
    // normal return 0x76 -> 118
    id = sccb_read_reg(0x0a);
    if (id != 118)
        return 2;

    for (i = 0; i < sizeof(ov7670_setting) / sizeof(ov7670_setting[0]); i++) {
        sccb_write_reg(ov7670_setting[i][0], ov7670_setting[i][1]);
    }

    return id;
}

unsigned int ov7670_image_data()
{
    unsigned int dat_a;

    ov7670_rclk = 0;
    dat_a = ov7670_data;
    ov7670_rclk = 1;
    dat_a <<= 8;
    ov7670_rclk = 0;
    dat_a |= ov7670_data;
    ov7670_rclk = 1;

    return dat_a;
}

void read_ov7670()
{
    unsigned int d;
    float t = 0;

    display_area_setting(0, 0, 319, 239);

    if (p) {
        ov7670_rrst = 0;
        ov7670_rclk = 0;
        ov7670_rclk = 1;
        ov7670_rclk = 0;
        ov7670_rrst = 1;
        ov7670_rclk = 1;
        for (t = 0; t < 76800; t++) {
            d = ov7670_image_data();
            uart_send_value("%x\n", d);
        }
        p = 0;
    }
}

void white_balance_setting(unsigned char setting)
{
    unsigned char reg_13 = 0xe7;
    unsigned char reg_01 = 0x00;
    unsigned char reg_02 = 0x00;

    switch(setting) {
        // sunny
        case 0:
            reg_13 = 0xe5;
            reg_01 = 0x5a;
            reg_02 = 0x5c;
            break;  
        
        // cloudy
        case 1:
            reg_13 = 0xe5;
            reg_01 = 0x58;
            reg_02 = 0x60;
            break;  
        
        // office
        case 2:
            reg_13 = 0xe5;
            reg_01 = 0x84;
            reg_02 = 0x4c;
            break; 

        // home
        case 3:
            reg_13 = 0xe5;
            reg_01 = 0x96;
            reg_02 = 0x40;
            break;  
    }
    // com8 setting
    sccb_write_reg(0x13, reg_13);
    // awb blue channel gain 
    sccb_write_reg(0x01, reg_01);
    // awb red channel gain
    sccb_write_reg(0x02, reg_02);
}

void saturation_setting(unsigned char setting)
{
    unsigned char reg_4f5054 = 0x80;
    unsigned char reg_52     = 0x22;
    unsigned char reg_53     = 0x5e;
    
    switch(setting) {
        // -2
        case 0:
            reg_4f5054 = 0x40;       
            reg_52     = 0x11;
            reg_53     = 0x2f;       
            break;  
        
        // -1
        case 1:
            reg_4f5054 = 0x66;      
            reg_52     = 0x1b;
            reg_53     = 0x4b;    
            break;  
        
        // +1
        case 3:
            reg_4f5054 = 0x99;     
            reg_52     = 0x28;
            reg_53     = 0x71;     
            break;  
        
        // +2
        case 4:
            reg_4f5054 = 0xc0;     
            reg_52     = 0x33;
            reg_53     = 0x8d;     
            break;  
    }

    sccb_write_reg(0x4f, reg_4f5054);
    sccb_write_reg(0x50, reg_4f5054); 
    sccb_write_reg(0x51, 0x00);
    sccb_write_reg(0x52, reg_52);
    sccb_write_reg(0x53, reg_53);
    sccb_write_reg(0x54, reg_4f5054);
    sccb_write_reg(0x58, 0x9e);
}

void brightness_setting(unsigned char setting)
{
    unsigned char reg_55 = 0x00;
    
    switch(setting) {
        // -2
        case 0:
            reg_55 = 0xb0;
            break;
        
        // -1
        case 1:
            reg_55 = 0x98;
            break;

        // +1
        case 3:
            reg_55 = 0x18;
            break;

        // +2
        case 4:
            reg_55 = 0x30;
            break;
    }

    sccb_write_reg(0x55, reg_55);
}

void contrast_setting(unsigned char setting)
{
    unsigned char reg_56 = 0x40;
    
    switch(setting) {
        // -2
        case 0:
            reg_56 = 0x30;       
            break;  
        
        // -1
        case 1:
            reg_56 = 0x38;       
            break;  
        
        // +1
        case 3:
            reg_56 = 0x50;       
            break;  
        
        // +2
        case 4:
            reg_56 = 0x60;       
            break;  
    }

    sccb_write_reg(0X56, reg_56); 
}

void special_effects_setting(unsigned char setting)
{
    unsigned char reg_3a = 0x04;
    unsigned char reg_67 = 0xC0;
    unsigned char reg_68 = 0x80;
    
    switch(setting) {
        // negative
        case 0:
            reg_3a = 0x24;
            reg_67 = 0x80;
            reg_68 = 0x80;
            break;  
        
        // Black and white
        case 1:
            reg_3a = 0x14;
            reg_67 = 0x80;
            reg_68 = 0x80;
            break;  
        
        // reddish
        case 2:
            reg_3a = 0x14;
            reg_67 = 0xc0;
            reg_68 = 0x80;
            break;  
        
        // greenish
        case 3:
            reg_3a = 0x14;
            reg_67 = 0x40;
            reg_68 = 0x40;
            break;  
        
        // buleish
        case 4:
            reg_3a = 0x14;
            reg_67 = 0x80;
            reg_68 = 0xc0;
            break;  
        
        // retro 
         case 5:
            reg_3a = 0x14;
            reg_67 = 0xa0;
            reg_68 = 0x40;
            break;   
    }

    sccb_write_reg(0x3a, reg_3a);
    sccb_write_reg(0x68, reg_67);
    sccb_write_reg(0x67, reg_68);
}

void display_area_setting(unsigned int y, unsigned int x, unsigned int width,unsigned int height)
{
    unsigned int endx;
    unsigned int endy;
    unsigned char t;

    endx = x + width * 2;
    endy = y + height * 2;

    if (endy > 784)
        endy -= 784;

    t = sccb_read_reg(0x03);
    t &= 0xf0;
    t |= ((endx & 0x03) << 2) | (x & 0x03);
    
    sccb_write_reg(0x03, t);
    sccb_write_reg(0x19, x >> 2);
    sccb_write_reg(0x1a, endx >> 2);

    t = sccb_read_reg(0x32);

    t &= 0xc0;
    t |= ((endy & 0x07) << 3) | (y & 0x07);
    
    sccb_write_reg(0x17, y >> 3);
    sccb_write_reg(0x18, endy >> 3);
}

void interrupt_init()
{ 
    EA  = 1;
    EX0 = 1;
    IT0 = 0;
}

void interrupt_nn() interrupt INTERRUPT_NN
{
    EX0 = 0;

    if (p < 2) {
        if(p == 0) {
            ov7670_wrst = 0;           
            ov7670_wrst = 1;
            ov7670_wen = 1;
        } else {
            ov7670_wen = 0;
            ov7670_wrst = 0;
            ov7670_wrst = 1;
        }
        p++;
    }
    EX0 = 1;
    // uart_send_data("Hello");
}
