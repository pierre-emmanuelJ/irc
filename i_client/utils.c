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

void          time_writter(t_client *c)
{
  time_t      now;
  struct tm   *ntm;

  now = time(NULL);
  ntm = localtime(&now);
  if (ntm->tm_min <= 9)
  {
    if (ntm->tm_hour <= 9)
      asprintf(&c->time, "0%d:0%d", ntm->tm_hour, ntm->tm_min);
    else
      asprintf(&c->time, "%d:0%d", ntm->tm_hour, ntm->tm_min);
  }
  else
  {
    if (ntm->tm_hour <= 9)
      asprintf(&c->time, "0%d:%d", ntm->tm_hour, ntm->tm_min);
    else
      asprintf(&c->time, "%d:%d", ntm->tm_hour, ntm->tm_min);
  }
}