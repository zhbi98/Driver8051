
#include "nixie.h"

unsigned char code num_code[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 
                                 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

// unsigned char code num_code[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99,
//                                  0x92, 0x82, 0xf8, 0x80, 0x90};

void display_value(unsigned int number)
{
    unsigned int num[4];
    unsigned char i = 0;
    unsigned char j = 0;

    for (i = 0; i < 4; i++) {
        num[i] = number % 10;
        number = number / 10;
    }
    
    for(j = 100; j > 0; j--) {
        a = 1;
        DATA = num_code[num[3]];
        sleep_ms(2);
        a = 0;

        b = 1;
        DATA = num_code[num[2]];
        sleep_ms(2);
        b = 0;

        c = 1;
        DATA = num_code[num[1]];
        sleep_ms(2);
        c = 0;

        d = 1;
        DATA = num_code[num[0]];
        sleep_ms(2);
        d = 0;
    }
    
}
