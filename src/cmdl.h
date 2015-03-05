#ifndef CMDL_H
#define CMDL_H

#include <curses.h>

int cmdl_currx;

void cmdl_init();
void cmdl_terminate();
int cmdl_put_char(char ch);

#endif /* CMDL_H */
