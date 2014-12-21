#ifndef LAIL_H
#define LAIL_H

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <pthread.h>
#include <curses.h>
#include <form.h>

#define COLOR_GREY 8
#define COLOR_GREY_STRONG 9

void lail_init();
void lail_run();
void lail_finish();

#endif
