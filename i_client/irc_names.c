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

void command_names(char *str, t_windows *w, t_client *c)
{
  if (strlen(c->params) >= 1)
    c->params[0] = 0;
  if (compare_cnts_command(str, "/names " , w, c, 7) == FALSE)
    return ;
  if (c->st == CONNECTED)
  {
    if (strlen(c->params) <= 0)
    {
      no_parameters(w, c);
      return ;
    }
    asprintf(&c->tosend, "NAMES %s\r\n", c->params);
    write(c->socket, c->tosend, strlen(c->tosend));
  }
  else
    need_connection(w, c);
}