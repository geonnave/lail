#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <curses.h>
#include <form.h>
#include "lail.h"

int main(void)
{
	lail_init();

	lail_run();

	lail_finish();
	return 0;
}
