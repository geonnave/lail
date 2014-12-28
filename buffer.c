#include "lail.h"
#include "buffer.h"

void *file_modif(void *arg)
{
	int i = 0;

	while (i++ < 4) {
		pthread_mutex_lock(&cmd_lock);
		bf = i;
		task_mask |= BUFFER_MASK;
		pthread_cond_signal(&cmd_cv);
		pthread_mutex_unlock(&cmd_lock);
		sleep(1);
	}

	return NULL;
}
