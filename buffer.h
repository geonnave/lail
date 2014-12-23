#ifndef BODY_H
#define BODY_H

#include <pthread.h>
#include <curses.h>
#include <stdlib.h>
#include <stdio.h>

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define BUF_LEN ( 1024 * ( EVENT_SIZE + 16 ) )

void *file_modif(void *arg);

#endif /* BODY_H */
