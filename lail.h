#ifndef LAIL_H
#define LAIL_H

#include <curses.h>
#include <form.h>

void init();
void key_process();
int read_filter();
void finish();

#endif
