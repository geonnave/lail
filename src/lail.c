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

int must_apply_cmdl = 0;
int must_update_buffer = 0;

void update_buffer()
{
	int i = 0;

	for (i = 0; i < file_buf.len; i++)
		buffer_put_char(file_buf.content[i]);
	buf_curr.x = buf_curr.y = 0;
}

void append_buf_in_to_file_buf(char *buf_in, int len)
{
	int i = 0;

	for (i = 0; i < len && file_buf.len < FILE_BUF_MAX-1; i++)
		/* todo: check file_buf.len */
		file_buf.content[file_buf.len++] = buf_in[i];
	must_update_buffer = 1;
}

void apply_cmdl()
{
	must_apply_cmdl = 0;
	must_update_buffer = 1;
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
			append_buf_in_to_file_buf(buf_in, r_bytes);
		}

		if (must_apply_cmdl)
			apply_cmdl();

		if (must_update_buffer)
			update_buffer();

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

	file_buf.len = 0;
	file_buf.content = (char *) malloc(sizeof(file_buf.content) * FILE_BUF_MAX);

	filtered_buf.len = 0;
	filtered_buf.content = (char *) malloc(sizeof(file_buf.content) * FILE_BUF_MAX);

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

