
#include "lcdinterface.h"

void interface()
{
	unsigned char error = 0;
	lcd12864_init();
	
	while (password("20182019")) {
		error++;
		if (error == 4) {
				delete_content();
				display_string(2, 2, "´íÎóÊäÈë04´Î");
				sleep_ms(1000);
				delete_content();
				display_string(2, 2, "Éè±¸ÒÑÍ£ÓÃ");
				while (1);
		}
	}
	delete_content();

	display_string(2, 4, "»¶Ó­");
	sleep_ms(2000);
	delete_content();
	while (1) {
		display_string(1, 2, "ÈÕÆÚÓëÊ±¼ä");
		display_string(3, 2, "12:29:29");
		display_string(4, 2, "2019/04/02");
	}
}
