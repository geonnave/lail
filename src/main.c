#include <stdlib.h>
#include <stdio.h>
#include <curses.h>

#include "lail.h"
#include "buffer.h"
#include "cmdl.h"

int main(int argc, char* argv[])
{

	if (argc < 2) {
		printf("lail error: must provide filename\n");
		return 1;
	}

	//todo: sanitize argv[1] before passing
	lail_init(argv[1]);

	lail_run();

	lail_terminate();
	return 0;
}

