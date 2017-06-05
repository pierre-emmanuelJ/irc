#include "client.h"

int main(void)
{
	initscr();			/* Start curses mode 		  */
    start_color();
	printw("Hello World !!!");	/* Print Hello World		  */
	refresh();			/* Print it on to the real screen */
	getch();			/* Wait for user input */
	endwin();			/* End curses mode		  */

	return 0;
}
