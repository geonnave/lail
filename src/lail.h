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

struct file_buf {
	char *content;
	int len;
};

struct file_buf file_buf;
struct file_buf filtered_buf;

extern int cmdl_currx;
extern int must_apply_cmdl;

extern struct cmdl_in cmdl_query;

void lail_run();
void lail_init(char *fname);
void lail_terminate();

#endif /* LAIL_H */
