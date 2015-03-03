#include "lail.h"
#include "buffer.h"
#include "cmd_line.h"

void create_buffer(struct buffer *buf, int size)
{
	buf->sz = size;
	buf->arr = (int *) malloc(buf->sz * sizeof(buf->arr));
	memset(buf->arr, '\0', buf->sz * sizeof(buf->arr[0]));
	buf->len = 0;
}

void create_circ_buffer(struct circ_buffer *buf, int size)
{
	buf->sz = size;
	buf->arr = (int *) malloc(buf->sz * sizeof(buf->arr));
	memset(buf->arr, '\0', buf->sz * sizeof(buf->arr[0]));
	buf->curr = buf->arr;
	buf->pos = 0;
	buf->len = 0;
}

void lail_run()
{
	int ch = 0;
	struct cursor_pos current;
	pthread_t pth_buffer, pth_cmd_line;

	pthread_create(&pth_buffer, NULL, file_modif, NULL);
	pthread_create(&pth_cmd_line, NULL, key_input, NULL);

	while(ch != KEY_F(2)) {
		pthread_mutex_lock(&cmd_lock);
		pthread_cond_wait(&cmd_cv, &cmd_lock);
		if ((task_mask & CMD_LINE_MASK) == CMD_LINE_MASK) {
			cmd_to_curses();
			task_mask &= ~CMD_LINE_MASK;
		}
		if ((task_mask & BUFFER_MASK) == BUFFER_MASK) {
			buffer_to_curses();
			task_mask &= ~BUFFER_MASK;
		}
		pthread_mutex_unlock(&cmd_lock);
		refresh();
	}

	pthread_join(pth_cmd_line, NULL);
	pthread_join(pth_buffer, NULL);
}

