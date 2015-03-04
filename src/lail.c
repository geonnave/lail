#include <unistd.h>

#include "cmdl.h"
#include "buffer.h"
#include "lail.h"

/* lail.c
 * this is the file that do all the core work of lail program
 */

void lail_run()
{
	char *tmp = "blafdajdsfdssdfjsdklfdfkjfdsgdsddfjsdklafjsdlkfjfklkfaaflfjfd\0";

	while (*tmp) {
		if (*tmp) {
			buffer_put_char(*tmp);
			cmdl_put_char(*tmp);
			tmp++;
			usleep(10000);
		}
		refresh();
	}
	sleep(1);
}
