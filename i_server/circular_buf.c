/*
** circular_buf.c for  in /home/jacqui_p/rendu/PSU_2016_myirc/i_server/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Wed May 31 18:12:34 2017 Pierre-Emmanuel Jacquier
** Last update Sun Jun 11 21:00:42 2017 Pierre-Emmanuel Jacquier
*/

#include "server.h"

void                    first_node(t_circular_buf **cbuf,
                                   struct pollfd *pollfd,
                                   t_client_infos *cli,
                                   char *result)
{
  t_circular_buf        *tmp;

  tmp = *cbuf;
  xasprintf(&tmp->rfc_msg, "%s", result);
  tmp->client_fd = cli->client_fd;
  tmp->is_empty = FALSE;
  tmp->pollfd = pollfd;
  tmp->client = cli;
  tmp->end = tmp + 1;
  tmp->end->start = tmp;
}

void                    erase_first_node(t_circular_buf **cbuf,
                                         struct pollfd *pollfd,
                                         t_client_infos *cli,
                                         char *result)
{
  t_circular_buf        *tmp;

  tmp = *cbuf;
  *cbuf = (*cbuf)->next;
  (*cbuf)->end = tmp->end;
  tmp = tmp->end;
  tmp->start = *cbuf;
  xasprintf(&tmp->rfc_msg, "%s", result);
  tmp->pollfd = pollfd;
  tmp->client = cli;
  tmp->client_fd = cli->client_fd;
  tmp->is_empty = FALSE;
}

void                    add_node(t_circular_buf **cbuf,
                                 struct pollfd *pollfd,
                                 t_client_infos *cli,
                                 char *result)
{
  t_circular_buf        *tmp;

  tmp = *cbuf;
  tmp = tmp->end;
  xasprintf(&tmp->rfc_msg, "%s", result);
  tmp->client_fd = cli->client_fd;
  tmp->is_empty = FALSE;
  tmp->pollfd = pollfd;
  tmp->client = cli;
  tmp->start = *cbuf;
  (*cbuf)->end = tmp->next;
}

BOOL                    add_in_cbuf(t_circular_buf **cbuf,
                                    struct pollfd *pollfd,
                                    t_client_infos *cli,
                                    char *result)
{
  t_circular_buf        *tmp;

  tmp = *cbuf;
  if (!tmp->end)
  {
    first_node(cbuf, pollfd, cli, result);
    return (TRUE);
  }
  if (tmp->end == tmp)
  {
    erase_first_node(cbuf, pollfd, cli, result);
    return (TRUE);
  }
  add_node(cbuf, pollfd, cli, result);
  return (TRUE);
}

BOOL    use_cbuf(t_circular_buf **cbuf,
                 t_server_infos *serv)
{
  char  *result;

  while (!(*cbuf)->is_empty)
  {
    exec_command((*cbuf)->rfc_msg, serv, (*cbuf)->client, &result);
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
