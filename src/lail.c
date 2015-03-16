#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <sys/select.h>
#include <regex.h>

#include <curses.h>

#include "cmdl.h"
#include "buffer.h"
#include "lail.h"

/* lail.c
 * this is the file that do all the core work of lail program
 */

#define BUF_LEN 128

/* global variable */
int must_apply_cmdl = 0;

int must_update_buffer = 0;
int is_filtered_set = 0;
int fd = 0;
char line_buf[CMDL_MAX] = { '0' };

int match_filter_query(char *line, int len)
{
	int match = 0;
	regex_t re;

	if (regcomp(&re, cmdl_query.content, REG_EXTENDED|REG_ICASE|REG_NOSUB) != 0)
		return 0;

	line[len+1] = '\0';
	match = regexec(&re, line, (size_t) 0, NULL, 0);
	regfree(&re);
	return !match;
	//return (cmdl_query.cmd) ? cmdl_query.cmd == line[0] : 1;
}

void apply_cmdl()
{
	int i = 0, j = 0, line_len = 0;
	char *line_start = NULL;

	must_apply_cmdl = 0;
	must_update_buffer = 1;

	clear();

	filtered_buf.len = 0;
	line_start = file_buf.content;
	line_len = 0;
	for (i = 0; i < file_buf.len; i++) {
		if (file_buf.content[i] == '\n') {
			if (match_filter_query(line_start, line_len))
				/* yay! here we have found a matching line!*/
				for (j = 0; j <= line_len && filtered_buf.len < FILE_BUF_MAX-1; j++)
					filtered_buf.content[filtered_buf.len++] = *line_start++;
			line_start = &file_buf.content[i+1];
			line_len = 0;
		} else {
			line_len++;
		}
	}
}

void update_buffer()
{
	int i = 0;
	char *line_start = NULL;

	buf_curr.x = buf_curr.y = 0;
	line_start = filtered_buf.content;
	for (i = 0; i < filtered_buf.len; i++) {
		if (filtered_buf.content[i] == '\n') {
			buffer_put_line(line_start, &filtered_buf.content[i]);
			line_start = &filtered_buf.content[i+1];
		}
	}
}

void append_buf_in_to_file_buf(char *buf_in, int len)
{
	int i = 0, j = 0, line_len = 0;
	char *line_start = NULL;

	line_start = buf_in;
	line_len = 0;
	/* this code is getting ugly, the possibilites for dealing with this in the future are:
	 * 1. try to fix its ugliness
	 * 2. get used with it 
	 * 3. writing such comments 
	 * well; the following loop walks through the input from file and save 
	 * it on memory, the __memory_for_all_file_lines__ (file_buf.content)
	 * */
	for (i = 0; i < len && file_buf.len < FILE_BUF_MAX-1; i++) {
		file_buf.content[file_buf.len++] = buf_in[i];
		if (buf_in[i] == '\n') {
			if (match_filter_query(line_start, line_len))
				/* yay! here we have found a matching line!
				 * lets save it on the program's memory, the 
				 * __memory_for_matching_lines__ (filtered_buf.content) */
				for (j = 0; j <= line_len && filtered_buf.len < FILE_BUF_MAX-1; j++)
					filtered_buf.content[filtered_buf.len++] = *line_start++;
			line_start = &buf_in[i+1];
			line_len = 0;
		} else {
			line_len++;
		}
	}
	must_update_buffer = 1;
}

/* this function will 
 * use *select* to read from stdin and file without blocking */
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

