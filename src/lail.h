#ifndef LAIL_H
#define LAIL_H

#include <curses.h>

#define CP_CMDL_BACK 1

struct cursor_pos {
	int y;
	int x;
};

struct cmdl_in {
	int cmd;
	char *stuff;
	int len;
};

extern char filename[256];

void lail_run();

#endif /* LAIL_H */
