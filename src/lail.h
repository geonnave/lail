#ifndef LAIL_H
#define LAIL_H

#include <curses.h>

#define CP_CMDL_BACK 1

struct cursor_pos {
	int y;
	int x;
};

void lail_run();

#endif /* LAIL_H */
