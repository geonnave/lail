#ifndef WINDOW_H
#define WINDOW_H

#include <curses.h>

WINDOW *create_window(int starty, int startx, int height, int width, int refresh);
void destroy_window(WINDOW *window);

#endif
