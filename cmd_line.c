#include "cmd_line.h"

struct cursor_pos {
	int y;
	int x;
};

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
}

void *process_key_input(void *arg)
{
	int *input;
	int ch, in_pos;
	struct cursor_pos max, current;

	ch = in_pos = current.y = current.x = 0;

	input = malloc(sizeof(input)*CMD_SIZE);

	do_curses_form('/');
	while ((ch = getch()) != KEY_F(2)) {
		getmaxyx(stdscr, max.y, max.x);
		getyx(stdscr, current.y, current.x);
		switch(ch) {
		case KEY_BACKSPACE:
			if (current.x > 1) {
				do_curses_form(REQ_DEL_PREV);
				input[in_pos--] = 0;
			}
			break;
		case 10:
			while (current.x-- > 1)
				do_curses_form(REQ_DEL_PREV);
			// do stuff with input
			break;
		default:
			if (current.x < max.x-2) {
				do_curses_form(ch);
				input[in_pos++] = ch;
			}
			break;
		}
		refresh();
	}
	return;
}

void do_curses_form(int cmd) 
{
	form_driver(cmd_form, cmd);
}

void cmd_line_finish()
{
	unpost_form(cmd_form);
	free_form(cmd_form);
	free_field(fields[0]);
}
