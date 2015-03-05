#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#include <unistd.h>
#include <sys/select.h>

#include "cmdl.h"
#include "buffer.h"
#include "lail.h"

/* lail.c
 * this is the file that do all the core work of lail program
 */

/* this is a global variable, *declarated* in lail.h and *defined* here. */
char filename[256] = { '\0' };

void process_char_to_buffer(char ch)
{
	/* todo: actually process the char before sending to cmdl show */
	buffer_put_char(ch);
}

void process_char_to_cmdl(char ch)
{
	/* todo: actually process the char before sending to cmdl show */
	cmdl_put_char(ch);
}

void read_stuff()
{
	fd_set rfds;
	struct timeval tv;
	int ret;
	char ch;

	tv.tv_sec = 2;
	tv.tv_usec = 0;

	while (1) {
		FD_ZERO(&rfds);
		FD_SET(0, &rfds);
		ret = select(1, &rfds, NULL, NULL, &tv);
		if (ret < 0) {
			buffer_put_char('e');
		} else if (FD_ISSET(0, &rfds)) {
			scanf("%c", &ch);
			process_char_to_cmdl(ch);
		} else {
			buffer_put_char('_');
		}
		usleep(10000);
		refresh();
	}
}

void lail_run()
{
	char *tmp = "blafdajdsfdssdfjsdklfdfkjfdsgdsddfjsdklafjsdlkfjfklkfaaflfjfd\0";

	read_stuff();
}
