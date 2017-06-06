#include "client.h"

static void destroy_windows(t_windows *w)
{
  delwin(w->header);
  delwin(w->body);
  delwin(w->footer);
  delwin(w->textbox);
}

static WINDOW *create_window(int h, int w, int y, int x)
{
  WINDOW *l;

  l = newwin(h, w, y, x);
  wrefresh(l);
  return l;
}

static void init_ncurses()
{
  initscr();
  cbreak();
  noecho();
  curs_set(FALSE);
  keypad(stdscr, TRUE);
  if (has_colors())
  {
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_GREEN);
    init_pair(3, COLOR_WHITE, COLOR_RED);
  }
}

static void assign_windows(t_windows *w)
{
  w->header = create_window(1, COLS, 0, 0);
  wbkgd(w->header, COLOR_PAIR(3));
  wprintw(w->header, "Welcome on ZAPOIIIIRC");
  //mvwprintw(w->header, 0, 0, "%s", "bonjour");
  wrefresh(w->header);
  w->body = create_window(LINES - 3, COLS, 1, 0);
  wbkgd(w->body, COLOR_PAIR(1));
  wrefresh(w->body);
  w->footer = create_window(1, COLS, LINES - 2, 0);
  wbkgd(w->footer, COLOR_PAIR(3));
  wrefresh(w->footer);
  w->textbox = create_window(1, COLS, LINES - 1, 0);
  wbkgd(w->textbox, COLOR_PAIR(1));
  wrefresh(w->textbox);
}

static void main_process(t_windows *w)
{
  w = malloc(sizeof(t_windows));
  assign_windows(w);
  while (42)
  {
    char a = wgetch(w->textbox);
    wprintw(w->textbox, "%c", a);
    wrefresh (w->textbox);
  }
  destroy_windows(w);
  free(w);
}

int main(void)
{
  t_windows w;

  init_ncurses();
  main_process(&w);
  endwin();
  return (EXIT_SUCCESS);
}

/*
int main(int argc, char *argv[])
{
  t_windows w;

  initscr();
  cbreak();
  start_color();
  keypad(stdscr, TRUE);
  noecho();

  init_pair(1, COLOR_WHITE, COLOR_BLUE);
  w.header = newwin(1, COLS, 0, 0);
  wbkgd(w.header, COLOR_PAIR(1));
  wprintw(w.header, "Yolo beach");
  wrefresh (w.header);

  w.body = newwin(1, COLS, LINES - 1, 0);
  while (1)
  {
    char a = wgetch(w.body);
    wprintw(w.body, "%c", a);
    wrefresh (w.body);
  }
  endwin();
  return 0;
}*/