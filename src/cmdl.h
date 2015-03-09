#ifndef CMDL_H
#define CMDL_H

#include <curses.h>

void cmdl_init();
void cmdl_terminate();
int cmdl_put_char(char ch);

#endif /* CMDL_H */
