#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <curses.h>
#include <form.h>
#include "lail.h"

int main(void)
{
	init();

	key_process();

	finish();
	return 0;
}
