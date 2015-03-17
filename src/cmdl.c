#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <curses.h>
#include <form.h>

#include "cmdl.h"
#include "lail.h"

/* cmdl.c
 * this file describes the bottom line, the line where the 
 * commands will be issued down.
 */

/* a form holds a set of fields */
FORM *cmdl_form;

/* a field is a place where the user is meant to type text 
 * this is the field for the input of the user's commands
 */
FIELD *cmdl_field[2];

int cmdl_currx;
struct cmdl_in cmdl_in;
struct cmdl_in cmdl_query;

/* process a character entered at cmdl */
int cmdl_process_char(char ch)
{
	struct cursor_pos len;
	char *fb = NULL;

	getmaxyx(stdscr, len.y, len.x);

	switch(ch) {
	case 13:
		form_driver(cmdl_form, REQ_VALIDATION);

		/* just for precaution */
		memset(cmdl_query.content, '\0', CMDL_MAX);

		/* here we fetch the cmdl input */
		fb = field_buffer(cmdl_field[0], 0);
		memcpy(&cmdl_query.cmd, fb , 1);
		if (!cmdl_query.cmd || cmdl_query.cmd == ' ')
			return -1;

		memcpy(cmdl_query.content, ++fb, CMDL_MAX);

		cmdl_query.len = cmdl_currx-1;
		cmdl_query.content[cmdl_query.len] = '\0';

		cmdl_currx = 0;
		set_field_buffer(cmdl_field[0], 0, "");

		must_apply_cmdl = 1;
		break;
	case 127:
		if (!cmdl_currx)
			return -1;

		cmdl_currx--;
		form_driver(cmdl_form, REQ_DEL_PREV);
		break;
	default:
		if (cmdl_currx+2 > len.x)
			return -1;

		cmdl_currx++;
		form_driver(cmdl_form, ch);
		break;
	}

	return 0;
}

void cmdl_init()
{
	struct cursor_pos len;

	cmdl_currx = 0;

	cmdl_query.cmd = '\0';
	cmdl_query.content = (char *) malloc(sizeof(cmdl_query.content) * CMDL_MAX);
	cmdl_query.len = 0;

	getmaxyx(stdscr, len.y, len.x);
	cmdl_field[0] = new_field(1, len.x, len.y-1, 0, 0, 0);
	cmdl_field[1] = NULL;

	// do not go to next field when this field is filled up 
	field_opts_off(cmdl_field[0], O_AUTOSKIP);

	set_field_back(cmdl_field[0], COLOR_PAIR(CP_CMDL_BACK));
	//set_field_fore(cmdl_field[0], COLOR_PAIR(CP_CMDL_FORE));
	
	cmdl_form = new_form(cmdl_field);
	post_form(cmdl_form);

	// insert '/' as an indicator for query operator and increment x index
	form_driver(cmdl_form, '/');
	cmdl_currx++;
}

void cmdl_terminate()
{
	unpost_form(cmdl_form);
	free_form(cmdl_form);
	free_field(cmdl_field[0]);
	free_field(cmdl_field[1]);
	free(cmdl_query.content);
}

