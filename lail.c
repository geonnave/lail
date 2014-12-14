#include "lail.h"

typedef enum {
	SEARCH,
	NAVIGATE
} key_state_t;

struct cursor_pos {
	int y;
	int x;
};

void init()
{
	int ymax, xmax;

	initscr();

	getmaxyx(stdscr, ymax, xmax);

	start_color();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
}

void key_process()
{
	char ch;
	struct cursor_pos max, current;
	key_state_t state = SEARCH;

	ch = 0;
	current.y = 0;
	current.x = 0;
	getmaxyx(stdscr, max.y, max.x);	// get bottom row
	mvprintw(max.y-1, current.x, "/");
	while(ch != EOF) {
		if (state == SEARCH) {
			if (ch == 8)
				current.x--;
			else
				current.x++;
			mvprintw(max.y, current.x, ch);
			mvchgat(max.y-1, current.x, -1, A_STANDOUT, 1, NULL);
		}
		refresh();
		ch = getch();
	}

	return;
}

int read_filter()
{
	return 0;
}

void finish()
{
	endwin();
}
