/*
** commands_functions.c for  in /home/jacqui_p/rendu/PSU_2016_myirc/i_server/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Wed Jun  7 19:08:21 2017 Pierre-Emmanuel Jacquier
** Last update Sat Jun 10 23:21:53 2017 Pierre-Emmanuel Jacquier
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
  printf("NICK\n");
  (void)serv;
  if (tab_len(command) != 2)
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
  printf("USER\n");
  (void)serv;
  if (tab_len(command) < 5)
  {
    send_str_to_client(cli->client_fd, "461 :Not enough parameters.");
    send_str_to_client(cli->client_fd, "304 :SYNTAX USER <username> <localhost> <remotehost> <GECOS>");
    return (FALSE);
  }
  if (!cli->nickname)
    send_str_to_client(cli->client_fd, "001 :Welcome");
  asprintf(&cli->user, "%s", command[1]);
  return (TRUE);
}

BOOL     ping_command(char **command, t_server_infos *serv, t_client_infos *cli)
{
  printf("PING\n");
  char   *str;

  (void)serv;
  if (tab_len(command) == 1)
  {
    send_str_to_client(cli->client_fd, "461 :Not enough parameters.");
    send_str_to_client(cli->client_fd, "304 :SYNTAX PING <servername> [:<servername>]");
    return (FALSE);
  }
  asprintf(&str, "PONG :%s", command[1]);
  send_str_to_client(cli->client_fd, str);
  free(str);
  return (TRUE);
}

BOOL     pong_command(char **command, t_server_infos *serv, t_client_infos *cli)
{
  printf("PONG\n");
  (void)command;
  (void)serv;
  (void)cli;
  return (TRUE);
}

BOOL     quit_command(char **command, t_server_infos *serv, t_client_infos *cli)
{
  printf("QUIT\n");
  (void)command;
  (void)serv;
  (void)cli;
  remove_cli_from_his_chanels(cli);
  close(cli->pollfd->fd);
  cli->pollfd->fd = -1;
  cli->client_fd = -1;
  if (cli->chanels)
    free(cli->chanels);
  free(cli->nickname);
  return (TRUE);
}

void     send_msg_to_chanel(t_chanel *chan, char *msg)
{
  int    i;

  i = 0;
  while (i < MAX_CLI && chan->fds_in_chanel[i])
  {
    printf("str to send at %d\n", chan->fds_in_chanel[i]->fd);
    if (chan->fds_in_chanel[i]->fd > 0)
      send_str_to_client(chan->fds_in_chanel[i]->fd, msg);
    i++;
  }
}

BOOL     privmsg_command(char **command, t_server_infos *serv, t_client_infos *cli)
{
  int    i;
  char   *msg;

  printf("PRIVMSG\n");
  i = 0;
  (void)serv;
  if (tab_len(command) != 3)
  {
    send_str_to_client(cli->client_fd, "461 :Not enough parameters.");
    send_str_to_client(cli->client_fd, "304 :SYNTAX PRIVMSG <target>");
    return (FALSE);
  }
  while (i < MAX_CLI && cli->chanels[i])
  {
    if (!strcmp(cli->chanels[i]->chanel_name, command[1]))
    {
      asprintf(&msg, ":%s!%s@%s PRIVMSG %s :%s", cli->nickname, cli->user, cli->client_ip, cli->chanels[i]->chanel_name, command[2]);
      send_msg_to_chanel(cli->chanels[i], msg);
    }
    i++;
  }
  return (TRUE);
}

BOOL     join_command(char **command, t_server_infos *serv, t_client_infos *cli)
{
  printf("join\n");
  if (tab_len(command) < 2)
  {
    send_str_to_client(cli->client_fd, "461 :Not enough parameters.");
    send_str_to_client(cli->client_fd, "304 :SYNTAX JOIN <channel>");
    return (FALSE);
  }
  if (chanel_exist(command[1], serv))
  {
    printf("chanel exist\n");
    add_cli_to_chanel(command[1], serv, cli);
  }
  else
  {
    printf("chanel NOT exist\n");
    add_new_chanel(command[1], serv, cli);
  }
  return (TRUE);
}

BOOL     part_command(char **command, t_server_infos *serv, t_client_infos *cli)
{
  printf("PART\n");
  if (tab_len(command) != 2)
  {
    send_str_to_client(cli->client_fd, "461 :Not enough parameters.");
    send_str_to_client(cli->client_fd, "304 :SYNTAX PART <channel>");
    return (FALSE);
  }
  remove_cli_from_chanel(command[1], serv, cli);
  return (TRUE);
}

BOOL     list_command(char **command, t_server_infos *serv, t_client_infos *cli)
{
  printf("LIST\n");
(void)command;
(void)serv;
(void)cli;
return (TRUE);
}
