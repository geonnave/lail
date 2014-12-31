#include <stdlib.h>
#include "lail.h"
#include "buffer.h"
#include "cmd_line.h"

void create_buffer(struct buffer *buf, int size)
{
	buf->sz = size;
	buf->arr = (int *) malloc(buf->sz * sizeof(buf->arr));
	memset(buf->arr, '\0', buf->sz * sizeof(buf->arr[0]));
	buf->len = 0;
}

