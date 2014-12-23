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
#define CMD_MAX 5

struct cursor_pos {
	int y;
	int x;
};

pthread_mutex_t cmd_lock;
pthread_cond_t cmd_cv;

char buffer[BUF_MAX];
char cmd_input[CMD_MAX];
int cmd_pos;

int bf, bf_changed, cmd_char, cmd_changed;

#endif
