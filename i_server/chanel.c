/*
** chanel.c for  in /home/jacqui_p/rendu/PSU_2016_myirc/i_server/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Thu Jun  8 14:33:21 2017 Pierre-Emmanuel Jacquier
** Last update Sat Jun 10 22:02:09 2017 Pierre-Emmanuel Jacquier
*/

#include "server.h"

void    add_new_chanel(const char *chanel_name,
                       t_server_infos *serv,
                       t_client_infos *cli)
{
  int   i;
  t_chanel    *chan;

  i = 0;
  while (i < MAX_CLI && serv->chanels[i].chanel_name)
    i++;
  if (i == MAX_CLI -1)
    return ;
  printf("chanel in serv %d\n", i);
  asprintf(&(serv->chanels[i].chanel_name), "%s", chanel_name);
  serv->chanels[i].fds_in_chanel = vmalloc(sizeof(struct pollfd *) * MAX_CLI);
  memset(serv->chanels[i].fds_in_chanel, 0, sizeof(struct pollfd *) * MAX_CLI);
  serv->chanels[i].fds_in_chanel[0] = cli->pollfd;
  chan = &serv->chanels[i];
  i = 0;
  while (i < MAX_CLI && cli->chanels[i])
    i++;
  if (i == MAX_CLI -1)
    return ;
  cli->chanels[i] = chan;
}

BOOL          chanel_exist(const char *chanel_name,
                           t_server_infos *serv)
{
  int         i;

  i = 0;
  while (i < MAX_CLI && serv->chanels[i].chanel_name)
  {
    if (!strcmp(serv->chanels[i].chanel_name, chanel_name))
      return (TRUE);
    i++;
  }
  return (FALSE);
}

static void   add_chanel_to_cli_list(t_client_infos *cli, t_chanel *chan)
{
  int         i;

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
  printf("chanel found %s\n", chan->chanel_name);
  i = 0;
  while (i < MAX_CLI && chan->fds_in_chanel[i])
  {
    printf("%d\n", chan->fds_in_chanel[i]->fd);
    if (!(chan->fds_in_chanel[i]->fd > 0))
      break ;
    i++;
  }
  if (i == MAX_CLI -1)
    return ;
  printf("add in chanlist in %d\n", i);
  chan->fds_in_chanel[i] = cli->pollfd;
  add_chanel_to_cli_list(cli, chan);
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
    if (!(found = strcmp(chanel_name, serv->chanels[i].chanel_name)))
      break ;
    i++;
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

void    remove_cli_from_his_chanels(t_client_infos *cli)
{
  int   i;
  int   j;

  i = 0;
  j = 0;
  while (i < MAX_CLI && cli->chanels[i])
  {
    while (j < MAX_CLI && cli->chanels[i]->fds_in_chanel[j]->fd > 0)
    {
      if (cli->chanels[i]->fds_in_chanel[j]->fd == cli->client_fd)
      {
        cli->chanels[i]->fds_in_chanel[j]->fd = -1;
        break ;
      }
      j++;
    }
    j = 0;
    i++;
  }
}
