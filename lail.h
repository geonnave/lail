#ifndef LAIL_H
#define LAIL_H

#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <form.h>
#include <sys/inotify.h>

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define BUF_LEN ( 1024 * ( EVENT_SIZE + 16 ) )

#define CMD_SIZE 256

#define KEY_ENTER 10

#define COLOR_GREY 8
#define COLOR_GREY_STRONG 9

void init();
void key_process();
int read_filter();
void finish();

#endif
