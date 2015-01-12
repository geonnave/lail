#include <sys/inotify.h>
#include <stdlib.h>
#include "lail.h"
#include "buffer.h"

void buffer_init()
{
	//create_circ_buffer(&buf_lail, BUF_MAX_LINES * BUF_MAX_COLS);
	create_circ_buffer(&buf_lail, 32);
}

void *file_modif(void *arg)
{
	int len, i, fd, wd, buffer[BUF_LEN], ch;
	char *filename, word[256];
	struct inotify_event *event;
	FILE *fp;

	if ((fp = fopen("foo", "r")) == NULL)
		printf("error opening file");

	if ((fd = inotify_init()) < 0)
		printf("error inotify_init");

	wd = inotify_add_watch(fd, "foo", IN_MODIFY);

	len = i = ch = 0;

	while (1) {
		i = 0;
		len = read(fd, buffer, BUF_LEN);
		if (len < 0)
			printf("error read");

		while (i < len) {
			event = (struct inotify_event *) &buffer[i];
			if (event->mask & IN_MODIFY) {
				while ((fscanf(fp, "%c", &ch)) != EOF)
					process_read_char(ch);
			}
			i += sizeof(struct inotify_event *) + event->len;
		}
		process_read_char(10);
	}

	return NULL;
}

void process_read_char(int ch)
{
	pthread_mutex_lock(&cmd_lock);
	// TODO: check ch value
	append_circ_buffer(ch);
	task_mask |= BUFFER_MASK;
	pthread_cond_signal(&cmd_cv);
	pthread_mutex_unlock(&cmd_lock);
}

void append_circ_buffer(int ch)
{
	if (buf_lail.len >= buf_lail.sz) {
		buf_lail.curr = buf_lail.arr + buf_lail.pos;
		*buf_lail.curr = ch;
		buf_lail.pos = (buf_lail.pos + 1) % buf_lail.sz;
	} else {
		buf_lail.arr[buf_lail.len++] = ch;
		if (buf_lail.len == buf_lail.sz)
			buf_lail.curr = buf_lail.arr;
	}
}

void buffer_to_curses()
{
	struct cursor_pos cmd_curr;
	struct buffer line;

	// TODO: use pattern as regex

	getyx(stdscr, cmd_curr.y, cmd_curr.x);

	//create_buffer(&line, 256);

	move(cmd_curr.y, cmd_curr.x);
}
