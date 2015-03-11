#ifndef LAIL_H
#define LAIL_H

#include <curses.h>

/* color pairs */
#define CP_CMDL_BACK 1

#define CMDL_MAX 256
#define FILE_BUF_MAX (CMDL_MAX * 1024)

struct cursor_pos {
	int y;
	int x;
};

struct cmdl_in {
	char cmd;
	char *content;
	int len;
};

struct buf_s {
	char *content;
	int len;
};

struct buf_s file_buf[FILE_BUF_MAX] = { '0' };

extern int cmdl_currx;
extern int must_apply_cmdl;
extern struct cmdl_in cmdl_in;
extern struct cmdl_in cmdl_query;

void lail_run();
void lail_init(char *fname);
void lail_terminate();

#endif /* LAIL_H */
