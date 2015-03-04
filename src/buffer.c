#include <stdlib.h>
#include <stdio.h>

#include <curses.h>

#include "lail.h"
#include "buffer.h"

/* buffer.c
 * this file represents a buffer, that is where the file contents
 * and/or data flow should appear to the user
 */

void buffer_init()
{
	buf_cp.y = buf_cp.x = 0;
}

void buffer_terminate()
{
}

