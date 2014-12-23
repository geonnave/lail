#include "lail.h"
#include "buffer.h"

void *file_modif(void *arg)
{
	int i = 0;

	while (i++ < 4) {
		pthread_mutex_lock(&cmd_lock);
		bf = i;
		bf_changed = 1;
		pthread_mutex_unlock(&cmd_lock);
		sleep(1);
	}

	return NULL;
}
