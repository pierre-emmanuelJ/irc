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

BOOL compare_command(char *s1, char*s2, t_windows *w, t_client *c)
{
  if (strcmp(s1, s2) != 0)
  {
    unknow_command(w, c);
    return (FALSE);
  }
  return (TRUE);
}