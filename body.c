#include "body.h"

void *process_file_modif(void *arg)
{
	char *ch;

	ch = (char *) arg;

	while (1) {
		sleep(1);
		printf("arg: %s", ch);
	}

	return NULL;
}
