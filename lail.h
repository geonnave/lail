#ifndef LAIL_H
#define LAIL_H

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <pthread.h>
#include <curses.h>
#include <form.h>

#define COLOR_GREY 8
#define COLOR_GREY_STRONG 9

#define BUF_MAX 256
#define CMD_MAX 128

pthread_mutex_t lock_curses;

char buffer[BUF_MAX];
char cmd[CMD_MAX];

#endif
