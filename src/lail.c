#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include <sys/select.h>
#include <sys/inotify.h>

#include "cmdl.h"
#include "buffer.h"
#include "lail.h"

/* size of the event structure, not counting name */
#define EVENT_SIZE (sizeof (struct inotify_event))

/* reasonable guess as to size of 1024 events */
#define BUF_LEN (1024 * (EVENT_SIZE + 16))

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

/* this function will 
 * use *select* to read from stdin without blocking and 
 * use *inotify* to read from file only when new stuff are added */
void lail_run()
{
	fd_set rfds;
	struct timeval tv;
	int ret, ifd, iwd, len, i;
	char ch, buf_in[BUF_LEN];
	FILE *fp;

	refresh();

	if ((fp = fopen(filename, "r")) == NULL) {
		printf("error opening file");
		exit(1);
	}

	ifd = inotify_init();
	if (ifd < 0) {
		printf("error inotify_init");
		exit(1);
	}

	iwd = inotify_add_watch(ifd, filename, IN_MODIFY);
	if (iwd < 0) {
		printf("error inotify add watch");
		exit(1);
	}

	tv.tv_sec = 2;
	tv.tv_usec = 0;

	while (1) {
		/* asas batendo */
		FD_ZERO(&rfds);

		/* marcha de decolagem */
		FD_SET(0, &rfds);
		FD_SET(ifd, &rfds);

		/* turbinas e.. */
		ret = select(ifd+1, &rfds, NULL, NULL, &tv);

		/* vai!!! */
		if (ret < 0) {
			buffer_put_char('e');
		} else if (FD_ISSET(0, &rfds)) {
			scanf("%c", &ch);
			process_char_to_cmdl(ch);
		} else if (FD_ISSET(ifd, &rfds)) {
			len = read(ifd, buf_in, BUF_LEN);
			i = 0;
			while (i < len) {
				struct inotify_event *event = (struct inotify_event *) &buf_in[i];
				if (event->mask & IN_MODIFY)
					while ((fscanf(fp, "%c", &ch)) != EOF)
						process_char_to_buffer(ch);
				i += EVENT_SIZE + event->len;
			}
		}

		/* do NOT forget to refresh the screen!!! */
		refresh();
	}

	inotify_rm_watch(ifd, iwd);
	close(ifd);
}

