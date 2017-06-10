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

static void   refresh_footer(t_windows *w, t_client *c)
{
  mvwdelch(w->footer, getcury(w->footer), 0);
  wclrtoeol(w->footer);
  mvwprintw(w->footer, 0, 0, "[%s] [%s] [%s]",
  c->time, c->nickname, c->hostname);
  wrefresh(w->footer);
}

static void   refresh_header(t_windows *w, t_client *c)
{
  mvwdelch(w->header, getcury(w->header), 0);
  wclrtoeol(w->header);
  mvwprintw(w->header, 0, 0, " * ZAPOIIIRC * Connected on %s using %s",
  c->ip, c->nickname);
  wrefresh(w->header);
}

void          refresh_windows(t_windows *w, t_client *c)
{
  if (c->st == CONNECTED)
    refresh_header(w, c);
  refresh_footer(w, c);
  wrefresh(w->textbox);
}