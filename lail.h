#ifndef LAIL_H
#define LAIL_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <strings.h>
#include <pthread.h>
#include <semaphore.h>
#include <curses.h>
#include <form.h>

#define COLOR_GREY 8
#define COLOR_GREY_STRONG 9

#define CMD_LINE_MASK 0x1
#define BUFFER_MASK 0x2

#define CMD_MAX 512

#define BUF_MAX_LINES 512
#define BUF_MAX_COLS 512

struct cursor_pos {
	int y;
	int x;
};

struct cmd_line {
	int cmd[CMD_MAX];
	int len;
};

struct buffer {
	int *arr;
	int len;
	int sz;
};

pthread_mutex_t cmd_lock;
pthread_cond_t cmd_cv;

struct buffer input;
struct buffer pattern;

struct buffer buf_lail;

char task_mask;

int bf, cmd_char;

void create_buffer(struct buffer *buf, int size);

#endif
