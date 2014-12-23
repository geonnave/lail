#ifndef CMD_LINE_H
#define CMD_LINE_H

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <form.h>
#include <pthread.h>

#define CMD_SIZE 256

#define KEY_ENTER 10

void *key_input(void *arg);
void process_input(int ch);
void cmd_update(int ch);
void cmd_line_init();
void cmd_line_finish();

#endif /* CMD_LINE_H */
