#include <stdlib.h>
#include <stdio.h>

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

/* process a character entered at cmdl */
int cmdl_process_char(char ch)
{
	struct cursor_pos len;

	getmaxyx(stdscr, len.y, len.x);

	switch(ch) {
	case 13:
		cmdl_currx++;
		form_driver(cmdl_form, '@');
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

	getmaxyx(stdscr, len.y, len.x);
	cmdl_field[0] = new_field(1, len.x, len.y-1, 0, 0, 0);
	cmdl_field[1] = NULL;

	// do not go to next field when this field is filled up 
	field_opts_off(cmdl_field[0], O_AUTOSKIP);

	set_field_back(cmdl_field[0], COLOR_PAIR(CP_CMDL_BACK));
	//set_field_fore(cmdl_field[0], COLOR_PAIR(CP_CMDL_FORE));
	
	cmdl_form = new_form(cmdl_field);
	post_form(cmdl_form);

	cmdl_currx = 0;

	cmdl_in.cmd = '/';
	cmdl_in.content = (char *) malloc(sizeof(cmdl_in.content) * CMDL_MAX);
	cmdl_in.len = 0;

	// insert '/' as an indicator for query operator and increment x index
	form_driver(cmdl_form, cmdl_in.cmd);
	cmdl_currx++;
}

void cmdl_terminate()
{
	unpost_form(cmdl_form);
	free_form(cmdl_form);
	free_field(cmdl_field[0]);
	free_field(cmdl_field[1]);
}

