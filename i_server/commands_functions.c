/*
** commands_functions.c for  in /home/jacqui_p/rendu/PSU_2016_myirc/i_server/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Wed Jun  7 19:08:21 2017 Pierre-Emmanuel Jacquier
** Last update Sun Jun 11 22:18:07 2017 Pierre-Emmanuel Jacquier
*/

#include "server.h"
#include "pfunctions_commands.h"

BOOL    nick_command(char **command,
                      t_server_infos *serv,
                      t_client_infos *cli)
{
  char  *msg;
  int   i;

  i = 0;
  (void)serv;
  if (tab_len(command) < 2)
  {
    send_str_to_client(cli->client_fd, "461 :Not enough parameters.");
    send_str_to_client(cli->client_fd, "304 :SYNTAX NICK <newnick>");
    return (FALSE);
  }
  if (cli->nickname)
    {
      xasprintf(&msg, ":%s NICK %s", cli->nickname, command[1]);
      while (i < MAX_CLI && cli->chanels[i])
        send_msg_to_chanel(cli->chanels[i++], msg, cli);
      send_str_to_client(cli->client_fd, msg);
      free(msg);
      free(cli->nickname);
      xasprintf(&cli->nickname, "%s", command[1]);
      return (TRUE);
    }
  xasprintf(&cli->nickname, "%s", command[1]);
  return (TRUE);
}

BOOL    user_command(char **command,
                     t_server_infos *serv,
                     t_client_infos *cli)
{
  (void)serv;
  if (tab_len(command) < 5)
  {
    send_str_to_client(cli->client_fd, "461 :Not enough parameters.");
    send_str_to_client(cli->client_fd,
      "304 :SYNTAX USER <username> <localhost> <remotehost> <GECOS>");
    return (FALSE);
  }
  if (!cli->user)
  {
    send_str_to_client(cli->client_fd, "001 :Welcome");
    xasprintf(&cli->user, "%s", command[1]);
    return (TRUE);
  }
  free(cli->user);
  xasprintf(&cli->user, "%s", command[1]);
  return (TRUE);
}

BOOL    ping_command(char **command,
                     t_server_infos *serv,
                     t_client_infos *cli)
{
  char  *str;

  (void)serv;
  if (tab_len(command) == 1)
  {
    send_str_to_client(cli->client_fd, "461 :Not enough parameters.");
    send_str_to_client(cli->client_fd,
      "304 :SYNTAX PING <servername> [:<servername>]");
    return (FALSE);
  }
  xasprintf(&str, "PONG :%s", command[1]);
  send_str_to_client(cli->client_fd, str);
  free(str);
  return (TRUE);
}

BOOL    pong_command(char **command,
                     t_server_infos *serv,
                     t_client_infos *cli)
{
  (void)command;
  (void)serv;
  (void)cli;
  return (TRUE);
}

BOOL    quit_command(char **command,
                     t_server_infos *serv,
                     t_client_infos *cli)
{
  (void)command;
  (void)serv;
  remove_cli_from_his_chanels(cli);
  close(cli->client_fd);
  cli->pollfd->fd = -1;
  cli->client_fd = -1;
  if (cli->chanels)
    free(cli->chanels);
  free(cli->nickname);
  return (TRUE);
}
