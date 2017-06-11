/*
** utils_funcs.c for  in /home/jacqui_p/rendu/PSU_2016_myirc/i_server/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Wed Jun  7 15:53:27 2017 Pierre-Emmanuel Jacquier
** Last update Wed Jun  7 15:54:08 2017 Pierre-Emmanuel Jacquier
*/

#include "server.h"

void    *vmalloc(size_t size)
{
  void  *mem;

  mem = malloc(size);
  if (!mem)
  {
    perror("malloc failed");
    exit (FAILURE);
  }
  return (mem);
}

BOOL    is_number(char *number)
{
  while (*number)
  {
    if (!isdigit(*number))
      return (FALSE);
    number++;
  }
  return (TRUE);
}
