#ifndef BODY_H
#define BODY_H

#include <pthread.h>
#include <stdio.h>

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define BUF_LEN ( 1024 * ( EVENT_SIZE + 16 ) )

void *process_file_modif(void *arg);

#endif /* BODY_H */
