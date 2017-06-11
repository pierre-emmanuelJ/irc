/*
** chanel_utils.c for  in /home/jacqui_p/rendu/PSU_2016_myirc/i_server/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Sun Jun 11 20:48:24 2017 Pierre-Emmanuel Jacquier
** Last update Sun Jun 11 22:17:38 2017 Pierre-Emmanuel Jacquier
*/

#include "server.h"

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
        cli->chanels[i]->fds_in_chanel[j] = -1;
        break ;
      }
      j++;
    }
    j = 0;
    i++;
  }
}

t_chanel        *chanel_exist(const char *chanel_name,
                              t_server_infos *serv)
{
  int           i;

  i = 0;
  while (i < MAX_CLI && serv->chanels[i].chanel_name)
  {
    if (!strcmp(serv->chanels[i].chanel_name, chanel_name))
      return (&serv->chanels[i]);
    i++;
  }
  return (NULL);
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
