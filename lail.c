#include "lail.h"
#include "buffer.h"
#include "cmd_line.h"

void lail_init()
{
	pthread_mutex_init(&cmd_lock, NULL);
	pthread_cond_init(&cmd_cv, NULL);
	pthread_cond_init(&bf_cv, NULL);

	initscr();
	start_color();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	// define a new color, as ncurses does not have a native 'grey' color
	init_color(COLOR_GREY, 100, 100, 100);
	init_color(COLOR_GREY_STRONG, 80, 80, 80);

	init_pair(1, COLOR_WHITE, COLOR_GREY);
	init_pair(2, COLOR_WHITE, COLOR_GREY_STRONG);

	task_mask = bf = bf_changed = cmd_char = cmd_changed = 0;

	cmd_line_init();

	refresh();
}

void lail_run()
{
	int ch = 0;
	struct cursor_pos current;
	pthread_t pth_buffer, pth_cmd_line;

	pthread_create(&pth_buffer, NULL, file_modif, "geo");
	pthread_create(&pth_cmd_line, NULL, key_input, "geo");

	while(ch != KEY_F(2)) {
		pthread_mutex_lock(&cmd_lock);
		pthread_cond_wait(&cmd_cv, &cmd_lock);
		ch = cmd_char;
		if ((task_mask & CMD_LINE_MASK) == 1) {
			process_char(ch);
			task_mask &= ~CMD_LINE_MASK;
		}
		if (((task_mask & BUFFER_MASK) >> 1) == 1) {
			getyx(stdscr, current.y, current.x);
			mvprintw(5, 1, "from buffer, %d", bf);
			move(current.y, current.x);
			task_mask &= ~BUFFER_MASK;
		}
		pthread_mutex_unlock(&cmd_lock);
		refresh();
	}

	pthread_join(pth_cmd_line, NULL);
	pthread_join(pth_buffer, NULL);
}

void lail_finish()
{
	cmd_line_finish();
	pthread_mutex_destroy(&cmd_lock);
	pthread_cond_destroy(&cmd_cv);
	pthread_cond_destroy(&bf_cv);
	endwin();
}
