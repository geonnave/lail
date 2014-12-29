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

#define BUF_MAX 256
#define CMD_MAX 128

#define CMD_LINE_MASK 0x1
#define BUFFER_MASK 0x2

struct cursor_pos {
	int y;
	int x;
};

struct cmd_line {
	int cmd[CMD_MAX];
	int len;
};

pthread_mutex_t cmd_lock;
pthread_cond_t cmd_cv;

struct cmd_line input;
struct cmd_line pattern;

int buffer[BUF_MAX];

char task_mask;

int bf, cmd_char;

#endif
