#ifndef BUFFER_H
#define BUFFER_H

#include <curses.h>

struct cursor_pos buf_cp;

void buffer_init();
void buffer_terminate();

#endif /* BUFFER_H */
