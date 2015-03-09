#include <stdlib.h>
#include <stdio.h>

#include <curses.h>

#include "lail.h"
#include "buffer.h"

/* buffer.c
 * this file represents a buffer, that is where the file contents
 * and/or data flow should appear to the user
 */

int buffer_put_char(char ch)
{
	struct cursor_pos len;

	getmaxyx(stdscr, len.y, len.x);

	buf_curr.x++;
	if (buf_curr.x > len.x) {
		if (buf_curr.y+1 >= len.y-1) {
			// undo changes on x and return error
			buf_curr.x--;
			return -1;
		}
		buf_curr.y++;
		buf_curr.x = 0;
	}

	mvprintw(buf_curr.y, buf_curr.x, "%c", ch);

	return 0;
}

void buffer_init()
{
	buf_curr.y = 0;
	buf_curr.x = -1;
}

void buffer_terminate()
{
}

