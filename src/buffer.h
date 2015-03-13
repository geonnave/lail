#ifndef BUFFER_H
#define BUFFER_H

#include <curses.h>

struct cursor_pos buf_curr;

void buffer_init();
void buffer_terminate();
int buffer_put_line(char* line_start, char* line_end);
int buffer_put_char(char ch);

#endif /* BUFFER_H */
