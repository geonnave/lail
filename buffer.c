#include "lail.h"
#include "buffer.h"

void *process_file_modif(void *arg)
{
	int i = 0;

	while (i++ < 4) {
		pthread_mutex_lock(&lock_curses);
		mvprintw(1, 0, "buffer %d", i);
		refresh();
		pthread_mutex_unlock(&lock_curses);
		sleep(1);
	}

	return NULL;
}
