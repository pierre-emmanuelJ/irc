/*
** init_circular_buf.c for  in /home/jacqui_p/rendu/PSU_2016_myirc/i_server/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Sun Jun 11 21:00:16 2017 Pierre-Emmanuel Jacquier
** Last update Sun Jun 11 21:00:52 2017 Pierre-Emmanuel Jacquier
*/

#include "server.h"

t_circular_buf          *create_circular_buf(void)
{
  t_circular_buf        *new_buf;

  new_buf = vmalloc(sizeof(t_circular_buf) * MAX_CLI);
  new_buf->is_empty = TRUE;
  new_buf->rfc_msg = NULL;
  new_buf->client_fd = -1;
  new_buf->next = NULL;
  new_buf->pollfd = NULL;
  new_buf->start = new_buf;
  new_buf->end = NULL;
  return (new_buf);
}

void                    init_circular_buf(t_circular_buf *cbuf)
{
  int                   i;
  t_circular_buf        *tmp;

  i = 0;
  tmp = cbuf;
  while (i < MAX_CLI)
  {
    if (i == MAX_CLI - 1)
    {
      tmp->next = cbuf;
      break ;
    }
    tmp->next = tmp + 1;
    tmp->next->start = cbuf;
    tmp->next->end = NULL;
    tmp->next->pollfd = NULL;
    tmp->next->is_empty = TRUE;
    tmp->next->rfc_msg = NULL;
    tmp->next->client_fd = -1;
    tmp->next->next = NULL;
    tmp = tmp + 1;
    i++;
  }
}
