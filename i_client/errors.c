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

void unknow_command(t_windows *w, t_client *c)
{
  wprintw(w->body, "%s - ZAPOIRC: Unknown command: %s\n",
  c->time, c->textbox);
  wrefresh(w->body);
}

void need_connection(t_windows *w, t_client *c)
{
  wprintw(w->body, "%s - ZAPOIRC: Not connected to server\n",
  c->time);
  wrefresh(w->body);
}

void cant_connect(t_windows *w, t_client *c)
{
  wprintw(w->body, "%s - ZAPOIRC: Can't connect to the server\n",
  c->time);
  wrefresh(w->body);
}

void cant_resolve(t_windows *w, t_client *c)
{
  wprintw(w->body, "%s - ZAPOIRC: Can't resolve hostname %s\n",
  c->time, c->ip);
  wrefresh(w->body);
}

void already_connected(t_windows *w, t_client *c)
{
  wprintw(w->body, "%s - ZAPOIRC: You're already connected to a server\n",
  c->time);
  wrefresh(w->body);
}