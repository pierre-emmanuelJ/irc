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

void command_help(char *str, t_windows *w, t_client *c)
{
  if (compare_strict_command(str, "/help", w, c) == FALSE)
    return ;
  wprintw(w->body, "%s - server\tnick\tlist\tjoin\n", c->time);
  wprintw(w->body, "%s - part\tusers\tnames\tmsg\n", c->time);
  wprintw(w->body, "%s - help\tquit\n", c->time);
  wrefresh(w->body);
}

void command_quit(char *str, t_windows *w, t_client *c)
{
  int timer;

  timer = 3;
  if (compare_strict_command(str, "/quit", w, c) == FALSE)
    return ;
  while (timer != 0)
  {
    wprintw(w->body, "%s - Exit ZAPOIIIRC in %d...\n", c->time, timer);
    wrefresh(w->body);
    sleep(1);
    timer--;
  }
  wprintw(w->body,
  "%s - ZAPOIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII QUE JTE DIS\n ", c->time);
  wrefresh(w->body);
  sleep(1);
  destroy_windows(w);
}

void command_accept(char *str, t_windows *w, t_client *c)
{
  (void)str;
}