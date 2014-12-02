#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "lail.h"

int main(int argc, char *argv[])
{
	init();

	process();

	finish();
	return 0;
}
