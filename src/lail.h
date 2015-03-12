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

/* *optimize this in future*
 * the buffer for keeping track of the whole file */
struct file_buf file_buf;
/* *optimize this in future*
 * the buffer for storing the filtered lines */
struct file_buf filtered_buf;

/* keep track of the current x pos of cmdl */
extern int cmdl_currx;

/* is it needed to apply the cmdl query? */
extern int must_apply_cmdl;

/* the input cmdl, which is saved after user hit enter */
extern struct cmdl_in cmdl_query;

void lail_run();
void lail_init(char *fname);
void lail_terminate();

#endif /* LAIL_H */
