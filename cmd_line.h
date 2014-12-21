#ifndef CMD_LINE_H
#define CMD_LINE_H

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <form.h>
#include <pthread.h>

#define CMD_SIZE 256

#define KEY_ENTER 10

void *process_key_input(void *arg);
void cmd_line_init();

#endif /* CMD_LINE_H */
