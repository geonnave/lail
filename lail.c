#include "lail.h"
#include "buffer.h"
#include "cmd_line.h"

void lail_init()
{
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

	cmd_line_init();

	refresh();
}

void lail_run()
{
	pthread_t pth_buffer, pth_cmd_line;

	pthread_create(&pth_buffer, NULL, process_file_modif, "geo");
	pthread_create(&pth_cmd_line, NULL, process_key_input, "geo");

	pthread_join(pth_cmd_line, NULL);
	pthread_join(pth_buffer, NULL);
}

void lail_finish()
{
	cmd_line_finish();
	endwin();
}
