#ifndef CMDL_H
#define CMDL_H

#include <curses.h>

int cmdl_process_char(char ch);
void cmdl_init();
void cmdl_terminate();

#endif /* CMDL_H */
