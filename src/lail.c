#include <unistd.h>

#include "cmdl.h"
#include "buffer.h"
#include "lail.h"

/* lail.c
 * this is the file that do all the core work of lail program
 */

void lail_run()
{
	char *tmp = "bla\0";

	while (1) {
		if (*tmp) {
			put_char(*tmp);
			tmp++;
			sleep(1);
		}
		refresh();
	}
}
