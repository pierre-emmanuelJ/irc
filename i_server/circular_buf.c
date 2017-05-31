/*
** circular_buf.c for  in /home/jacqui_p/rendu/PSU_2016_myirc/i_server/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Wed May 31 18:12:34 2017 Pierre-Emmanuel Jacquier
** Last update Wed May 31 18:34:03 2017 Pierre-Emmanuel Jacquier
*/

#include "server.h"

t_circular_buf *create_circular_buf(void)
{
  t_circular_buf *new_buf;

  new_buf = vmalloc(sizeof(t_circular_buf) * MAX_CLI);
  new_buf->is_empty = TRUE;
  new_buf->rfc_msg = NULL;
  new_buf->client_fd = -1;
  new_buf->next = NULL;
  return (new_buf);
}

void           init_circular_buf(t_circular_buf *cbuf)
{
  int            i;
  t_circular_buf *tmp;


  i = 0;
  tmp = cbuf;
  while (i < MAX_CLI)
  {
    if (i == MAX_CLI - 1)
    {
      tmp->next = cbuf;
      break ;
    }
    tmp->next = tmp + sizeof(t_circular_buf);
    tmp->next->is_empty = TRUE;
    tmp->next->rfc_msg = NULL;
    tmp->next->client_fd = -1;
    tmp->next->next = NULL;
    i++;
  }
}
