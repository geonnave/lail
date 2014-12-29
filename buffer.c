#include <sys/inotify.h>
#include "lail.h"
#include "buffer.h"

void *file_modif(void *arg)
{
	int len, i, fd, wd, buffer[BUF_MAX];
	char *filename, word[256];
	struct inotify_event *event;
	FILE *fp;

	if ((fp = fopen("foo", "r")) == NULL)
		printf("error opening file");

	if ((fd = inotify_init()) < 0)
		printf("error inotify_init");

	wd = inotify_add_watch(fd, "foo", IN_MODIFY);

	len = i = 0;

	while (1) {
		i = 0;
		len = read(fd, buffer, BUF_LEN);
		if (len < 0)
			printf("error read");

		while (i < len) {
			event = (struct inotify_event *) &buffer[i];
			if (event->mask & IN_MODIFY)
				while ((fscanf(fp, "%s", word)) != EOF);
			i += sizeof(struct inotify_event *) + event->len;
		}
		
		pthread_mutex_lock(&cmd_lock);
		bf = i;
		task_mask |= BUFFER_MASK;
		pthread_cond_signal(&cmd_cv);
		pthread_mutex_unlock(&cmd_lock);
	}

	return NULL;
}
