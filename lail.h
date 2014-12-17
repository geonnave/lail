#ifndef LAIL_H
#define LAIL_H

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <pthread.h>
#include <curses.h>
#include <form.h>

#define CMD_SIZE 256

#define KEY_ENTER 10

#define COLOR_GREY 8
#define COLOR_GREY_STRONG 9

void init();
void key_process();
int read_filter();
void finish();

#endif
