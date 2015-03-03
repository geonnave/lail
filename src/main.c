#include <stdlib.h>
#include <stdio.h>
#include <curses.h>

void lail_init()
{

	/* ncurses library init functions: */
	initscr();		// initialize default screen
	cbreak();		// no char buffering (i.e. get each char as it is been typed
	noecho();		// disable automatic echo of typed chars
	keypad(stdscr, TRUE);	// enable F-keys, delete and other special keys
}

void lail_terminate()
{
	endwin();
}

int main(void)
{
	lail_init();
	lail_terminate();
	return 0;
}

