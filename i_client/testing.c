#include "client.h"

void draw_borders(WINDOW *screen)
{
  int x, y, i;

  getmaxyx(screen, y, x);

  // 4 corners
  mvwprintw(screen, 0, 0, "+");
  mvwprintw(screen, y - 1, 0, "+");
  mvwprintw(screen, 0, x - 1, "+");
  mvwprintw(screen, y - 1, x - 1, "+");

  // sides
  for (i = 1; i < (y - 1); i++)
  {
    mvwprintw(screen, i, 0, "|");
    mvwprintw(screen, i, x - 1, "|");
  }

  // top and bottom
  for (i = 1; i < (x - 1); i++)
  {
    mvwprintw(screen, 0, i, "-");
    mvwprintw(screen, y - 1, i, "-");
  }
}

t_windows *init_ncurses() {
  int parent_x, parent_y, new_x, new_y;

  initscr();
  noecho();
  curs_set(FALSE);

  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK);

  // set up initial windows
  getmaxyx(stdscr, parent_y, parent_x);
  t_windows *w;

  w = malloc(sizeof(t_windows));
  w->header = newwin(5, parent_x, 0, 0);
  w->body = newwin(5, parent_x, 5, 0);
  w->footer = newwin(5, parent_x, 10, 0);
  w->textbox = newwin(5, parent_x, 15, 0);
  wattron(w->header, COLOR_PAIR(1));
  return w;
}


int main(int argc, char *argv[])
{
  int parent_x, parent_y, new_x, new_y;
  t_windows *w = init_ncurses();

  draw_borders(w->header);
  draw_borders(w->body);
  draw_borders(w->footer);
  draw_borders(w->textbox);

  while (1)
  {
    getmaxyx(stdscr, new_y, new_x);

    if (new_y != parent_y || new_x != parent_x)
    {
      parent_x = new_x;
      parent_y = new_y;

      wclear(stdscr);
      wclear(w->header);
      wclear(w->body);
      wclear(w->footer);
      wclear(w->textbox);


      draw_borders(w->header);
      draw_borders(w->body);
      draw_borders(w->footer);
      draw_borders(w->textbox);
    }

    // draw to our windows
    mvwprintw(w->header, 1, 1, "Field");
    mvwprintw(w->body, 1, 1, "Body");
    mvwprintw(w->footer, 1, 1, "Footer");
    mvwprintw(w->textbox, 1, 1, "Textbox");

    // refresh each window
    wrefresh(w->header);
    wrefresh(w->body);
    wrefresh(w->footer);
    wrefresh(w->textbox);
  }

  endwin();

  return 0;
}