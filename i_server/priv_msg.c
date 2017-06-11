/*
** priv_msg.c for  in /home/jacqui_p/rendu/PSU_2016_myirc/i_server/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Sun Jun 11 21:16:18 2017 Pierre-Emmanuel Jacquier
** Last update Sun Jun 11 21:22:17 2017 Pierre-Emmanuel Jacquier
*/

#include "server.h"

void     send_msg_to_chanel(t_chanel *chan, char *msg, t_client_infos *cli)
{
  int    i;

  i = 0;
  while (i < MAX_CLI && chan->fds_in_chanel[i])
  {
    if (chan->fds_in_chanel[i] > 0
      && cli->client_fd != chan->fds_in_chanel[i])
    {
      send_str_to_client(chan->fds_in_chanel[i], msg);
    }
    i++;
  }
}

int      find_user_by_nick(char *nick, t_server_infos *serv)
{
  int    i;

  i = 0;
  while (i < MAX_CLI && serv->all_cli[i].client_fd != 0)
  {
    if (serv->all_cli[i].client_fd > 0)
    {
      if (!strcmp(nick, serv->all_cli[i].nickname))
        return (serv->all_cli[i].client_fd);
    }
    i++;
  }
  return (-1);
}

void      send_msg_to_priv_cli(char **command,
                               t_server_infos *serv,
                               t_client_infos *cli)
{
  char    *msg;
  int     fd;

  if ((fd = find_user_by_nick(command[1], serv)) == -1)
  {
    xasprintf(&msg, "401 %s %s :No such nick/channel",
      cli->nickname, command[2]);
    return ;
  }
  xasprintf(&msg, ":%s PRIVMSG %s %s",
    cli->nickname, command[1], command[2]);
  send_str_to_client(fd, msg);
  free(msg);
}

void    send_msg_to_all_chan(char **command,
                             t_client_infos *cli)
{
  int    i;
  char   *msg;

  i = 0;
  while (i < MAX_CLI && cli->chanels[i])
  {
    if (!strcmp(cli->chanels[i]->chanel_name, command[1]))
    {
      xasprintf(&msg, ":%s PRIVMSG %s %s",
      cli->nickname, cli->chanels[i]->chanel_name, command[2]);
      send_msg_to_chanel(cli->chanels[i], msg, cli);
      free(msg);
    }
    i++;
  }
}

BOOL     privmsg_command(char **command,
                         t_server_infos *serv,
                         t_client_infos *cli)
{
  if (tab_len(command) < 3)
  {
    send_str_to_client(cli->client_fd, "461 :Not enough parameters.");
    send_str_to_client(cli->client_fd, "304 :SYNTAX PRIVMSG <target>");
    return (FALSE);
  }
  if (!(command[1][0] == '#'))
    {
      send_msg_to_priv_cli(command, serv, cli);
      return (TRUE);
    }
    send_msg_to_all_chan(command, cli);
  return (TRUE);
}
