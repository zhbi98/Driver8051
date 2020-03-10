
#include "password.h"

unsigned char password(unsigned char password[8])
{
	unsigned char passwd[8];
	unsigned char input = 0, compare = 0;

	display_string(1, 4, "你好");
	display_string(4, 1, "按屏幕按钮以解锁");
	
	while (read_keyboard() != '*');
	delete_content();
	sleep_ms(50);

	display_string(1, 3, "输入密码");
	display_string(3, 3, "--------");
	display_position(3, 3);
	while (input < 8) {
		if (read_keyboard() != 0) {
			sleep_ms(20);
			passwd[input] = read_keyboard();
			write_data(0x07);
			sleep_ms(100);
			input++;
		}
	}
	for (compare = 0; compare < 8; compare++) {
		if (passwd[compare] != password[compare]) {
			delete_content();
			display_string(1, 3, "密码错误");
			display_string(3, 3, "稍后再试");
			passwd[8] = 0;
			sleep_ms(1000);
			delete_content();	
			return 1;	
		}
	}
	passwd[8] = 0;
	sleep_ms(10);
	return 0;
}
