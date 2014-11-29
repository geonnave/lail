#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

int main(int argc, char *argv[])
{
	int ch, row, col, brow, rcol;

	initscr();
	start_color();

	init_pair(1, COLOR_CYAN, COLOR_BLACK);

	while(1) {
		getmaxyx(stdscr, brow, rcol);	// get bottom row
		mvprintw(brow-1, 0, "teste");
		mvchgat(brow-1, 0, -1, A_STANDOUT, 1, NULL);
		refresh();
	}

	endwin();
	return 0;
}
