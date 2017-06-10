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

void init_ncurses(void)
{
  initscr();
  cbreak();
  noecho();
  curs_set(TRUE);
  keypad(stdscr, FALSE);
  if (has_colors())
  {
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_GREEN);
    init_pair(3, COLOR_WHITE, COLOR_RED);
  }
}

void init_values(t_client *c)
{
  time_writter(c);
  asprintf(&c->nickname, DEFAULT_NICKNAME);
  asprintf(&c->hostname, " ");
  asprintf(&c->textbox, " ");
  asprintf(&c->channel, "none");
  asprintf(&c->ch, " ");
  c->hostname[0] = 0;
  c->textbox[0] = 0;
  c->ch[0] = 0;
  c->port = 6667;
  c->st = DISCONNECTED;
}

void init_body(t_windows *w, t_client *c)
{
  time_writter(c);
  wprintw(w->body,
  "%s -  _____   _    ____   ___ _   _ ____   ____ \n", c->time);
  wprintw(w->body,
  "%s - |__  /  / \\  |  _ \\ / _ (_)_(_)  _ \\ / ___|\n", c->time);
  wprintw(w->body,
  "%s -   / /  / _ \\ | |_) | | | |_ _|| |_) | |    \n", c->time);
  wprintw(w->body,
  "%s -  / /_ / ___ \\|  __/| |_| || | |  _ <| |___ \n", c->time);
  wprintw(w->body,
  "%s - /____/_/   \\_\\_|    \\___/|___||_| \\_\\____|\n", c->time);
  wprintw(w->body,
  "---------------------------------------------------\n", c->time);
  wprintw(w->body, "%s - %s\n", c->time, DEFAULT_HEADER);
  scrollok(w->body, 1);
  wrefresh(w->body);
}

void init_select(t_client *c)
{
  FD_ZERO(&(c->fset));
  FD_SET(c->socket, &(c->fset));
  c->tm.tv_usec = 100;
}
