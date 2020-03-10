
#include "keyboard.h"

unsigned char read_keyboard()
{
	unsigned char key = 0x20;
	unsigned char key_encoded, key_line, key_column;
	
	do {
		keyboard_interface = 0xf0;
		while (keyboard_interface == 0xf0);		
		keyboard_interface = 0xf0;
		sleep_ms(20);
	} while (keyboard_interface == 0xf0);
	
	key_line = keyboard_interface;
	key_line = key_line & 0xf0;

	keyboard_interface = 0x0f;
	key_column = keyboard_interface;
	key_column = key_column & 0x0f;

	key_encoded = key_line | key_column;

	switch (key_encoded) {
		case 0x77 : key = '1'; break;
		case 0x7b : key = '2'; break;
		case 0x7d : key = '3'; break;
		case 0xb7 : key = '4'; break;
		case 0xbb : key = '5'; break;
		case 0xbd : key = '6'; break;
		case 0xd7 : key = '7'; break;
		case 0xdb : key = '8'; break;
		case 0xdd : key = '9'; break;
		case 0xeb : key = '0'; break;
		case 0xe7 : key = '*'; break;
		case 0xed : key = '#'; break;
		case 0x7e : key = 'A'; break;
		case 0xbe : key = 'B'; break;
		case 0xde : key = 'C'; break;
		case 0xee : key = 'D'; break;			

	}
	return key;
}
