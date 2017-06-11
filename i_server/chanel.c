/*
** chanel.c for  in /home/jacqui_p/rendu/PSU_2016_myirc/i_server/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Thu Jun  8 14:33:21 2017 Pierre-Emmanuel Jacquier
** Last update Sun Jun 11 18:59:53 2017 Pierre-Emmanuel Jacquier
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

t_chanel          *chanel_exist(const char *chanel_name,
                                t_server_infos *serv)
{
  int         i;

  i = 0;
  while (i < MAX_CLI && serv->chanels[i].chanel_name)
  {
    if (!strcmp(serv->chanels[i].chanel_name, chanel_name))
      return (&serv->chanels[i]);
    i++;
  }
  return (NULL);
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
  while (i < MAX_CLI && chan->fds_in_chanel[i] > 0)
  {
    printf("%d\n", chan->fds_in_chanel[i]);
    i++;
  }
  if (i == MAX_CLI -1)
    return ;
  printf("add in chanlist in %d\n", i);
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

BOOL    empty_chanel(int *fds)
{
  int   i;

  i = 0;
  while (i < MAX_CLI && fds[i] != 0)
  {
    if (fds[i] > 0)
      return (FALSE);
    i++;
  }
  return (TRUE);
}

void    remove_cli_from_chanel(const char *chanel_name,
                              t_server_infos *serv,
                              t_client_infos *cli)
{
  int         i;
  int         found;
  t_chanel    *chan;

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
      printf("%s\n", "je le remove du fd chanel list");
      chan->fds_in_chanel[i] = -1;
      remove_chanel_from_cli_list(chan, cli);
      // if (empty_chanel(chan->fds_in_chanel))
      //   memcpy(serv->chanels + save, serv->chanels + save + 1, MAX_CLI - save);
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
    while (j < MAX_CLI && cli->chanels[i]->fds_in_chanel)
    {
      if (cli->chanels[i]->fds_in_chanel[j] == cli->client_fd)
      {
        printf("client fd %d remove from chanels %s\n", cli->client_fd, cli->chanels[i]->chanel_name);
        cli->chanels[i]->fds_in_chanel[j] = -1;
        break ;
      }
      j++;
    }
    j = 0;
    i++;
  }
}
