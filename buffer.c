#include "buffer.h"

void *process_file_modif(void *arg)
{
	char *ch;
	int i = 0;

	ch = (char *) arg;

	while (i++ < 10) {
//		printf("%c[%d;%df",0x1B,10,10);
		mvprintw(10, 10, "ch: %s", ch);
		sleep(1);
//		printf("arg: %s", ch);
	}

	return NULL;
}
