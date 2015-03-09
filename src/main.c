#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <curses.h>

#include "lail.h"
#include "buffer.h"
#include "cmdl.h"

void lail_init(char *fname)
{
	/* copy the filename to a global variable */
	size_t len = strlen(fname);
	if (len >= sizeof(filename))
		len = sizeof(filename) - 1;
	memcpy(filename, fname, len);
	filename[len] = '\0';

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

int main(int argc, char* argv[])
{
	if (argc < 2) {
		printf("lail error: must provide filename\n");
		return 1;
	}

	//todo: sanitize argv[1] before passing
	lail_init(argv[1]);

	lail_run();

	lail_terminate();
	return 0;
}

