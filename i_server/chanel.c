/*
** chanel.c for  in /home/jacqui_p/rendu/PSU_2016_myirc/i_server/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Thu Jun  8 14:33:21 2017 Pierre-Emmanuel Jacquier
** Last update Sat Jun 10 17:26:35 2017 Pierre-Emmanuel Jacquier
*/

#include "server.h"

void    add_new_chanel(const char *chanel_name,
                       t_server_infos *serv,
                       t_client_infos *cli)
{
  int   i;
  t_chanel    *chan;

  i = 0;
  while (i < MAX_CLI && serv->chanels[i++].chanel_name);
  if (i == MAX_CLI -1)
    return ;
  asprintf(&(serv->chanels[i].chanel_name), "%s", chanel_name);
  serv->chanels[i].fds_in_chanel = vmalloc(sizeof(struct pollfd *) * MAX_CLI);
  serv->chanels[i].fds_in_chanel[0] = cli->pollfd;
  chan = &serv->chanels[i];
  i = 0;
  while (i < MAX_CLI && cli->chanels[i++]);
  if (i == MAX_CLI -1)
    return ;
  cli->chanels[i] = chan;
}

void          add_cli_to_chanel(const char *chanel_name,
                                t_server_infos *serv,
                                t_client_infos *cli)
{
  int         i;
  int         found;
  t_chanel    *chan;

  i = 0;
  while (i < MAX_CLI)
  {
    if (!(found = strcmp(chanel_name, serv->chanels[i++].chanel_name)))
      break ;
  }
  if (found)
    return ;
  chan = &serv->chanels[i];
  i = 0;
  while (i < MAX_CLI && chan->fds_in_chanel[i++]->fd > 0);
  if (i == MAX_CLI -1)
    return ;
  chan->fds_in_chanel[i] = cli->pollfd;
}

void    remove_cli_from_chanel(const char *chanel_name,
                              t_server_infos *serv,
                              t_client_infos *cli)
{
  int         i;
  int         found;
  t_chanel    *chan;

  i = 0;
  while (i < MAX_CLI)
  {
    if (!(found = strcmp(chanel_name, serv->chanels[i++].chanel_name)))
      break ;
  }
  if (found)
    return ;
  chan = &serv->chanels[i];
  i = 0;
  while (i < MAX_CLI && chan->fds_in_chanel[i]->fd > 0)
  {
    if (chan->fds_in_chanel[i]->fd == cli->client_fd)
    {
      chan->fds_in_chanel[i]->fd = -1;
      break ;
    }
    i++;
  }
}
