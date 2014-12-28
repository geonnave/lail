#include "lail.h"
#include "cmd_line.h"

FORM *cmd_form;
FIELD *fields[2];

void cmd_line_init()
{
	int ymax, xmax;

	// create the command field at the bottom of the standard screen
	getmaxyx(stdscr, ymax, xmax);
	fields[0] = new_field(1, xmax, ymax-1, 0, 0, 0);
	fields[1] = NULL;

	set_field_back(fields[0], COLOR_PAIR(1));
	set_field_fore(fields[0], COLOR_PAIR(2));
	field_opts_off(fields[0], O_AUTOSKIP);
	
	cmd_form = new_form(fields);
	post_form(cmd_form);

	cmd_update('/');
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

void process_char(int ch)
{
	struct cursor_pos current;

	getyx(stdscr, current.y, current.x);
	switch (ch) {
	case KEY_BACKSPACE:
		if (cmd_pos > 0 && current.x > 1) {
			cmd_input[cmd_pos--] = '\0';
			cmd_update(REQ_DEL_PREV);
		}
		break;
	default:
		if (cmd_pos < CMD_MAX-1) {
			cmd_input[cmd_pos++] = ch;
			cmd_update(ch);
		}
	}
}

void cmd_update(int ch)
{
	form_driver(cmd_form, ch);
}

void cmd_line_finish()
{
	unpost_form(cmd_form);
	free_form(cmd_form);
	free_field(fields[0]);
}
