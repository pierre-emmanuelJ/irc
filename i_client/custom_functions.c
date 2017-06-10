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

void    *custom_malloc(size_t length)
{
  void  *ptr;

  if ((ptr = malloc(length)) == NULL)
    return (NULL);
  return (ptr);
}

int     custom_dup2(int oldfd, int newfd)
{
  int   fd;

  if ((fd = dup2(oldfd, newfd)) == -1)
    exit(EXIT_FAILURE);
  return (fd);
}

int     custom_dup(int oldfd)
{
  int   fd;

  if ((fd = dup(oldfd)) == -1)
    exit(EXIT_FAILURE);
  return (fd);
}
