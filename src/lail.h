#ifndef LAIL_H
#define LAIL_H

#include <curses.h>

/* color pairs */
#define CP_CMDL_BACK 1

#define CMDL_MAX 256

struct cursor_pos {
	int y;
	int x;
};

struct cmdl_in {
	char cmd;
	char *content;
	int len;
};

extern int cmdl_currx;
extern struct cmdl_in cmdl_in;
extern struct cmdl_in cmdl_query;

void lail_run();
void lail_init(char *fname);
void lail_terminate();

#endif /* LAIL_H */
