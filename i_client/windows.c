/*
** white_rabbit.c for  in /Users/pichar_v/Documents/tek2/cpp_d01/ex00/
**
** Made by Valentin Pichard
** Login   <pichar_v@epitech.eu>
**
** Started on  Wed Jan  4 09:07:13 2017 Valentin Pichard
** Last update Wed Jan  4 23:15:35 2017 Valentin Pichard
*/

#include "client.h"

WINDOW    *create_window(int h, int w, int y, int x)
{
  WINDOW  *l;

  l = newwin(h, w, y, x);
  wrefresh(l);
  return (l);
}

void      destroy_windows(t_windows *w)
{
  delwin(w->header);
  delwin(w->body);
  delwin(w->footer);
  delwin(w->textbox);
}

void      assign_windows(t_windows *w, t_client *c)
{
  w->header = create_window(1, COLS, 0, 0);
  wbkgd(w->header, COLOR_PAIR(3));
  wprintw(w->header, "Welcome on ZAPOIIIIRC v0.8 RC2 - http://fifigrot.com/");
  wrefresh(w->header);
  w->body = create_window(LINES - 3, COLS, 1, 0);
  wbkgd(w->body, COLOR_PAIR(1));
  wrefresh(w->body);
  w->footer = create_window(1, COLS, LINES - 2, 0);
  wbkgd(w->footer, COLOR_PAIR(3));
  mvwprintw(w->footer, 0, 0, "[%s] [%s] [%s]",
  c->time, c->nickname, c->hostname);
  wrefresh(w->footer);
  w->textbox = create_window(1, COLS, LINES - 1, 0);
  wbkgd(w->textbox, COLOR_PAIR(1));
  wrefresh(w->textbox);
}