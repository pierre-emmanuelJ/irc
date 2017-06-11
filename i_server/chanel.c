/*
** chanel.c for  in /home/jacqui_p/rendu/PSU_2016_myirc/i_server/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Thu Jun  8 14:33:21 2017 Pierre-Emmanuel Jacquier
** Last update Sun Jun 11 21:30:54 2017 Pierre-Emmanuel Jacquier
*/

#include "server.h"

void            add_new_chanel(const char *chanel_name,
                               t_server_infos *serv,
                               t_client_infos *cli)
{
  int           i;
  t_chanel      *chan;

  i = 0;
  while (i < MAX_CLI && serv->chanels[i].chanel_name)
    i++;
  if (i == MAX_CLI -1)
    return ;
  xasprintf(&(serv->chanels[i].chanel_name), "%s", chanel_name);
  serv->chanels[i].fds_in_chanel = vmalloc(sizeof(int) * MAX_CLI);
  memset(serv->chanels[i].fds_in_chanel, 0, sizeof(int) * MAX_CLI);
  serv->chanels[i].fds_in_chanel[0] = cli->pollfd->fd;
  chan = &serv->chanels[i];
  i = 0;
  while (i < MAX_CLI && cli->chanels[i])
    i++;
  if (i == MAX_CLI -1)
    return ;
  cli->chanels[i] = chan;
}

static void     add_chanel_to_cli_list(t_client_infos *cli, t_chanel *chan)
{
  int           i;

  i = 0;
  while (i < MAX_CLI && cli->chanels[i])
    i++;
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
    if (!(found = strcmp(chanel_name, serv->chanels[i].chanel_name)))
      break ;
    i++;
  }
  if (found)
    return ;
  chan = &serv->chanels[i];
  i = 0;
  while (i < MAX_CLI && chan->fds_in_chanel[i] > 0)
  {
    printf("%d\n", chan->fds_in_chanel[i]);
    i++;
  }
  if (i == MAX_CLI -1)
    return ;
  chan->fds_in_chanel[i] = cli->client_fd;
  add_chanel_to_cli_list(cli, chan);
}

void    remove_chanel_from_cli_list(t_chanel *chan,
                                    t_client_infos *cli)
{
  int   i;

  i = 0;
  while (i < MAX_CLI && cli->chanels[i] != chan)
    i++;
  if (i == MAX_CLI -1)
    return ;
  memcpy(cli->chanels + i, cli->chanels + i + 1, MAX_CLI - i);
  i = 0;
  while (i < MAX_CLI && cli->chanels[i])
    i++;
}

void            remove_cli_from_chanel(const char *chanel_name,
                                       t_server_infos *serv,
                                       t_client_infos *cli)
{
  int           i;
  int           found;
  t_chanel      *chan;

  i = 0;
  while (i < MAX_CLI && serv->chanels[i].chanel_name)
  {
    if (!(found = strcmp(chanel_name, serv->chanels[i].chanel_name)))
      break ;
    i++;
  }
  if (found)
    return ;
  chan = &serv->chanels[i];
  i = 0;
  while (i < MAX_CLI && chan->fds_in_chanel[i] != 0)
  {
    if (chan->fds_in_chanel[i] == cli->client_fd)
    {
      chan->fds_in_chanel[i] = -1;
      remove_chanel_from_cli_list(chan, cli);
      break ;
    }
    i++;
  }
}
