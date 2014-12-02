#include "window.h"

WINDOW *create_window(int starty, int startx, int height, int width, int refresh)
{
	WINDOW *new_win = newwin(height, width, starty, startx);
	box(new_win, 0 , 0);
	if (refresh)
		wrefresh(new_win);
	return new_win;
}

void destroy_window(WINDOW *window)
{
	wborder(window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '); 
	wrefresh(window);
	delwin(window);
}
