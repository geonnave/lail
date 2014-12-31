#include "lail.h"
#include "cmd_line.h"

FORM *cmd_form;
FIELD *fields[2];

void cmd_line_init()
{
	int ymax, xmax;

	create_buffer(&input, CMD_MAX);
	create_buffer(&pattern, CMD_MAX);

	// create the command field at the bottom of the standard screen
	getmaxyx(stdscr, ymax, xmax);
	fields[0] = new_field(1, xmax, ymax-1, 0, 0, 0);
	fields[1] = NULL;

	set_field_back(fields[0], COLOR_PAIR(1));
	set_field_fore(fields[0], COLOR_PAIR(2));
	field_opts_off(fields[0], O_AUTOSKIP);
	
	cmd_form = new_form(fields);
	post_form(cmd_form);

	form_driver(cmd_form, '/');
}

void *key_input(void *arg)
{
	int c = 0;

	while (c != KEY_F(2)) {
		c = getch();
		pthread_mutex_lock(&cmd_lock);
		cmd_char = c;
		task_mask |= CMD_LINE_MASK;
		pthread_cond_signal(&cmd_cv);
		pthread_mutex_unlock(&cmd_lock);
	}

	return NULL;
}

int form_update(int ch)
{
	return form_driver(cmd_form, ch);
}

void process_char(int ch)
{
	int i = 0, au = 0;
	struct cursor_pos current, max;

	getyx(stdscr, current.y, current.x);
	getmaxyx(stdscr, max.y, max.x);
	switch (ch) {
	case KEY_BACKSPACE:
		if (input.len > 0 && current.x > 1) {
			input.arr[--input.len] = '\0';
			form_update(REQ_DEL_PREV);
		}
		break;
	case KEY_ENTER:
		memset(pattern.arr, '\0', CMD_MAX * sizeof(int));
		pattern.len = input.len;
		while (input.len > 0 && current.x > 1) {
			input.len--;
			pattern.arr[input.len] = input.arr[input.len];
			input.arr[input.len] = '\0';
			form_update(REQ_DEL_PREV);
		}
		break;
	default:
		if (input.len < CMD_MAX-1 && input.len < max.x-2) {
			if (form_update(ch) == 0)
				input.arr[input.len++] = ch;
		}
	}
}

void cmd_line_finish()
{
	unpost_form(cmd_form);
	free_form(cmd_form);
	free_field(fields[0]);
}
