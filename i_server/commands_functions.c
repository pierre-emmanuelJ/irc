/*
** commands_functions.c for  in /home/jacqui_p/rendu/PSU_2016_myirc/i_server/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Wed Jun  7 19:08:21 2017 Pierre-Emmanuel Jacquier
** Last update Sat Jun 10 19:02:48 2017 Pierre-Emmanuel Jacquier
*/

#include "server.h"
#include "pfunctions_commands.h"

int     tab_len(char **tab)
{
  int   i;

  i = 0;
  while (tab[i])
    i++;
  return (i);
}

BOOL     nick_command(char **command, t_server_infos *serv, t_client_infos *cli)
{
  (void)serv;
  if (tab_len(command) != 5)
  {
    send_str_to_client(cli->client_fd, "461 :Not enough parameters.");
    send_str_to_client(cli->client_fd, "304 :SYNTAX NICK <newnick>");
    return (FALSE);
  }
  asprintf(&cli->nickname, "%s", command[1]);
  send_str_to_client(cli->client_fd, "001 :Welcome");
  return (TRUE);
}

BOOL     user_command(char **command, t_server_infos *serv, t_client_infos *cli)
{
  (void)serv;
  if (tab_len(command) != 5)
  {
    send_str_to_client(cli->client_fd, "461 :Not enough parameters.");
    send_str_to_client(cli->client_fd, "304 :SYNTAX USER <username> <localhost> <remotehost> <GECOS>");
    return (FALSE);
  }
  asprintf(&cli->user, "%s %s %s %s", command[1], command[2], command[3], command[4]);
  send_str_to_client(cli->client_fd, "001 :Welcome");
  return (TRUE);
}

BOOL     ping_command(char **command, t_server_infos *serv, t_client_infos *cli)
{
  (void)command;
  (void)serv;
  (void)cli;

  return (TRUE);
}

BOOL     pong_command(char **command, t_server_infos *serv, t_client_infos *cli)
{
  (void)command;
  (void)serv;
  (void)cli;
  return (TRUE);
}

BOOL     quit_command(char **command, t_server_infos *serv, t_client_infos *cli)
{
  (void)command;
  (void)serv;
  (void)cli;
  close(cli->pollfd->fd);
  cli->pollfd->fd = -1;
  cli->client_fd = -1;
  if (cli->chanels)
    free(cli->chanels);
  free(cli->nickname);
  return (TRUE);
}

BOOL     privmsg_command(char **command, t_server_infos *serv, t_client_infos *cli)
{
  (void)command;
  (void)serv;
  (void)cli;
  return (TRUE);
}

BOOL     join_command(char **command, t_server_infos *serv, t_client_infos *cli)
{
  (void)command;
  (void)serv;
  (void)cli;
  return (TRUE);
}

BOOL     part_command(char **command, t_server_infos *serv, t_client_infos *cli)
{
  (void)command;
  (void)serv;
  (void)cli;
  return (TRUE);
}

BOOL     list_command(char **command, t_server_infos *serv, t_client_infos *cli)
{
(void)command;
(void)serv;
(void)cli;
return (TRUE);
}
