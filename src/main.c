#include <stdlib.h>
#include <stdio.h>
#include <curses.h>

#include "lail.h"
#include "buffer.h"
#include "cmdl.h"

void lail_init()
{

	/* ncurses library init functions: */
	initscr();		// initialize default screen
	cbreak();		// no char buffering (i.e. get each char as it is been typed
	noecho();		// disable automatic echo of typed chars
	keypad(stdscr, TRUE);	// enable F-keys, delete and other special keys
	start_color();		// enable using of colors

	init_pair(1, COLOR_BLUE, COLOR_BLACK);

	// initialize command line stuff
	cmdl_init();

	// initialize buffer stuff
	buffer_init();
}

void lail_terminate()
{
	cmdl_terminate();
	endwin();
}

int main(void)
{
	lail_init();

	lail_run();

	lail_terminate();
	return 0;
}

