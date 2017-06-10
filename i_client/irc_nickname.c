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

void command_nick(char *str, t_windows *w, t_client *c)
{
  if (compare_cnts_command(str, "/nick" ,w, c, 6) == FALSE)
    return ;
  if (c->st != CONNECTED)
  {
    asprintf(&c->nickname, "%s", c->params);
  }
  else
    need_connection(w, c);
}