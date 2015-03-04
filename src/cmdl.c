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

/* write a character to be showed on the cmdl */
void put_char(char ch)
{
	//todo: sanitize ch
	form_driver(cmdl_form, ch);
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

	form_driver(cmdl_form, '/');
}

void cmdl_terminate()
{
	unpost_form(cmdl_form);
	free_form(cmdl_form);
	free_field(cmdl_field[0]);
	free_field(cmdl_field[1]);
}

