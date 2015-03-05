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

void read_stuff()
{
	fd_set rfds;
	struct timeval tv;
	int ret, fd_file;
	char ch, b[8];

	fd_file = open("foo.txt", O_RDONLY);

	tv.tv_sec = 2;
	tv.tv_usec = 0;

	while (1) {
		FD_ZERO(&rfds);
		FD_SET(0, &rfds);
		FD_SET(fd_file, &rfds);
		ret = select(fd_file+1, &rfds, NULL, NULL, &tv);
		if (ret < 0) {
			buffer_put_char('e');
		} else if (FD_ISSET(0, &rfds)) {
			scanf("%c", &ch);
			cmdl_put_char(ch);
		} else if (FD_ISSET(fd_file, &rfds)) {
			read(fd_file, b, 8);
			buffer_put_char(b[0]);
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
