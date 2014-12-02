#include "window.h"
#include "lail.h"

WINDOW *window;

void init()
{
	int ymax, xmax;

	initscr();

	getmaxyx(stdscr, ymax, xmax);
	window = create_window(0, 0, ymax, xmax, 0);

	start_color();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
}

void process()
{
	int ch, ymax, xmax;

	ch = 0;
	while(ch != 'q') {
		getmaxyx(window, ymax, xmax);	// get bottom row
		mvprintw(ymax-1, 0, "teste");
		mvchgat(ymax-1, 0, -1, A_STANDOUT, 1, NULL);
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
	destroy_window(window);
	endwin();
}
