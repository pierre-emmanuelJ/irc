/*
** circular_buf.c for  in /home/jacqui_p/rendu/PSU_2016_myirc/i_server/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Wed May 31 18:12:34 2017 Pierre-Emmanuel Jacquier
** Last update Sat Jun 10 17:41:07 2017 Pierre-Emmanuel Jacquier
*/

#include "server.h"

BOOL                add_in_cbuf(t_circular_buf **cbuf,
                                struct pollfd *pollfd,
                                t_client_infos *cli,
                                char *result)
{
  t_circular_buf    *tmp;

  tmp = *cbuf;
  if (!tmp->end)
  {
    asprintf(&tmp->rfc_msg, "%s", result);
    tmp->client_fd = cli->client_fd;
    tmp->is_empty = FALSE;
    tmp->pollfd = pollfd;
    tmp->client = cli;
    tmp->end = tmp + 1;
    tmp->end->start = tmp;
    return (TRUE);
  }
  if (tmp->end == tmp)
  {
    *cbuf = (*cbuf)->next;
    (*cbuf)->end = tmp->end;
    tmp = tmp->end;
    tmp->start = *cbuf;
    asprintf(&tmp->rfc_msg, "%s", result);
    tmp->pollfd = pollfd;
    tmp->client = cli;
    tmp->client_fd = cli->client_fd;
    tmp->is_empty = FALSE;
    return (TRUE);
  }
  tmp = tmp->end;
  asprintf(&tmp->rfc_msg, "%s", result);
  tmp->client_fd = cli->client_fd;
  tmp->is_empty = FALSE;
  tmp->pollfd = pollfd;
  tmp->client = cli;
  tmp->start = *cbuf;
  (*cbuf)->end = tmp->next;
  return (TRUE);
}

BOOL             use_cbuf(t_circular_buf **cbuf,
                          t_server_infos *serv)
{
  char           *result;

  while (!(*cbuf)->is_empty)
  {
    exec_command((*cbuf)->rfc_msg, serv, (*cbuf)->client, &result);
    //send_str_to_client((*cbuf)->client->client_fd, result);
    (*cbuf)->is_empty = TRUE;
    free((*cbuf)->rfc_msg);
    if ((*cbuf)->end == (*cbuf)->next)
      (*cbuf)->next->end = NULL;
    else
      (*cbuf)->next->end = (*cbuf)->end;
    (*cbuf)->pollfd->events = POLLIN;
    (*cbuf)++;
  }
  return (TRUE);
}

t_circular_buf *create_circular_buf(void)
{
  t_circular_buf *new_buf;

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

void             init_circular_buf(t_circular_buf *cbuf)
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
