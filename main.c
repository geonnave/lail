#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <curses.h>
#include <form.h>
#include "lail.h"
#include "buffer.h"
#include "cmd_line.h"

void lail_init()
{
	pthread_mutex_init(&cmd_lock, NULL);
	pthread_cond_init(&cmd_cv, NULL);

	initscr();
	start_color();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	// define a new color, as ncurses does not have a native 'grey' color
	init_color(COLOR_GREY, 100, 100, 100);
	init_color(COLOR_GREY_STRONG, 80, 80, 80);

	init_pair(1, COLOR_WHITE, COLOR_GREY);
	init_pair(2, COLOR_WHITE, COLOR_GREY_STRONG);

	task_mask = bf = cmd_char = input.len = pattern.len = 0;

	cmd_line_init();
	buffer_init();

	refresh();
}

void lail_finish()
{
	cmd_line_finish();
	pthread_mutex_destroy(&cmd_lock);
	pthread_cond_destroy(&cmd_cv);
	endwin();
}

int main(void)
{
	lail_init();

	lail_run();

	lail_finish();
	return 0;
}
