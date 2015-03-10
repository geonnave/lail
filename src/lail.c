#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

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

/* this is a global variable, *declarated* in lail.h and *defined* here. */
char filename[256] = { '\0' };

void process_char_to_buffer(char ch)
{
	/* todo: actually process the char before sending to buffer show */
	buffer_put_char(ch);
}

void process_char_to_cmdl(char ch)
{
	/* todo: actually process the char before sending to cmdl show */
	cmdl_put_char(ch);
}

/* this function will 
 * use *select* to read from stdin without blocking and 
 * use *inotify* to read from file only when new stuff are added */
void lail_run()
{
	int ret, fd, r, i;
	char ch;
	char buf_in[BUF_LEN] = { '0' };
	struct cursor_pos max;
	fd_set rfds;

	refresh();

	if (!(fd = open(filename, O_RDONLY))) {
		printf("error open file");
		exit(1);
	}

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
			process_char_to_cmdl(ch);
		}
		if (FD_ISSET(fd, &rfds)) {
			r = read(fd, buf_in, BUF_LEN);
			for (i = 0; i < r; i++)
				process_char_to_buffer(buf_in[i]);
		}

		/* put the cursor back at the cmdl, for the please of the user */
		getmaxyx(stdscr, max.y, max.x);
		move(max.y-1, cmdl_currx);

		/* do NOT forget to refresh the screen!!! */
		refresh();
	}
}

