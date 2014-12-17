#include "lail.h"

typedef enum {
	SEARCH,
	NAVIGATE
} key_state_t;

struct cursor_pos {
	int y;
	int x;
};

FORM *cmd_form;
FIELD *fields[2];

void init()
{
	int ymax, xmax;

	initscr();
	start_color();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	// define a new color, as ncurses does not have a native 'grey' color
	init_color(COLOR_GREY, 100, 100, 100);
	init_color(COLOR_GREY_STRONG, 80, 80, 80);

	init_pair(1, COLOR_WHITE, COLOR_GREY);
	init_pair(2, COLOR_WHITE, COLOR_GREY_STRONG);

	// create the command field at the bottom of the standard screen
	getmaxyx(stdscr, ymax, xmax);
	fields[0] = new_field(1, xmax, ymax-1, 0, 0, 0);
	fields[1] = NULL;

	set_field_back(fields[0], COLOR_PAIR(1));
	set_field_fore(fields[0], COLOR_PAIR(2));
	field_opts_off(fields[0], O_AUTOSKIP);
	
	cmd_form = new_form(fields);
	post_form(cmd_form);
	refresh();
}

void key_process()
{
	int *input;
	int ch, in_pos;
	int len = 0, i = 0;
	int fd, wd;
	char buffer[BUF_LEN];
	char word[256];
	struct inotify_event *event;
	struct cursor_pos max, current;
	FILE *fp;

	if ((fd = inotify_init()) < 0) 
		return 1;

	wd = inotify_add_watch(fd, "foo", IN_MODIFY);

	ch = in_pos = current.y = current.x = 0;

	input = malloc(sizeof(input)*CMD_SIZE);

	form_driver(cmd_form, '/');
	while ((ch = getch()) != KEY_F(2)) {
		getmaxyx(stdscr, max.y, max.x);
		getyx(stdscr, current.y, current.x);
		switch(ch) {
		case KEY_BACKSPACE:
			if (current.x > 1) {
				form_driver(cmd_form, REQ_DEL_PREV);
				input[in_pos--] = 0;
			}
			break;
		case KEY_ENTER:
			while (current.x-- > 1)
				form_driver(cmd_form, REQ_DEL_PREV);
			// do stuff with input
			break;
		default:
			if (current.x < max.x-2) {
				form_driver(cmd_form, ch);
				input[in_pos++] = ch;
			}
			break;
		}
		refresh();
	}
}

int read_filter()
{
	return 0;
}

void finish()
{
	unpost_form(cmd_form);
	free_form(cmd_form);
	free_field(fields[0]);
	endwin();
}
