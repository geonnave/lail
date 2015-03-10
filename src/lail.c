#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <sys/select.h>

#include <curses.h>

#include "cmdl.h"
#include "buffer.h"
#include "lail.h"

/* lail.c
 * this is the file that do all the core work of lail program
 */

/* reasonable guess as to size of 1024 events */
#define BUF_LEN 128

int fd = 0;

void process_char_to_buffer(char ch)
{
	/* todo: actually process the char before sending to buffer show */
	buffer_put_char(ch);
}

/* this function will 
 * use *select* to read from stdin without blocking and 
 * use *inotify* to read from file only when new stuff are added */
void lail_run()
{
	int ret, r_bytes, i;
	char ch;
	char buf_in[BUF_LEN] = { '0' };
	struct cursor_pos max;
	fd_set rfds;

	refresh();

	while (1) {
		/* asas batendo */
		FD_ZERO(&rfds);

		/* marcha de decolagem */
		FD_SET(0, &rfds);
		FD_SET(fd, &rfds);

		/* turbinas e.. */
		ret = select(fd+1, &rfds, NULL, NULL, NULL);

		/* vai!!! */
		if (ret < 0)
			buffer_put_char('e');
		if (FD_ISSET(0, &rfds)) {
			scanf("%c", &ch);
			cmdl_process_char(ch);
		}
		if (FD_ISSET(fd, &rfds)) {
			r_bytes = read(fd, buf_in, BUF_LEN);
			for (i = 0; i < r_bytes ; i++)
				process_char_to_buffer(buf_in[i]);
		}

		/* put the cursor back at the cmdl, for the please of the user */
		getmaxyx(stdscr, max.y, max.x);
		move(max.y-1, cmdl_currx);

		/* do NOT forget to refresh the screen!!! */
		refresh();
	}
}

void lail_init(char *fname)
{
	if (!(fd = open(fname, O_RDONLY))) {
		printf("error open file");
		exit(1);
	}

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
	close(fd);
	cmdl_terminate();
	endwin();
}

