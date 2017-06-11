/*
** commands_functions.c for  in /home/jacqui_p/rendu/PSU_2016_myirc/i_server/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Wed Jun  7 19:08:21 2017 Pierre-Emmanuel Jacquier
** Last update Sun Jun 11 13:32:12 2017 Pierre-Emmanuel Jacquier
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
  char   *msg;
  printf("NICK\n");
  (void)serv;
  if (tab_len(command) < 2)
  {
    send_str_to_client(cli->client_fd, "461 :Not enough parameters.");
    send_str_to_client(cli->client_fd, "304 :SYNTAX NICK <newnick>");
    return (FALSE);
  }
  if (cli->nickname)
    {
      printf("%s\n", "second");
      asprintf(&msg, ":%s NICK %s", cli->nickname,  command[1]);
      send_str_to_client(cli->client_fd, msg);
      free(msg);
      free(cli->nickname);
      asprintf(&cli->nickname, "%s", command[1]);
      return (TRUE);
    }
  printf("%s\n", "first");
  asprintf(&cli->nickname, "%s", command[1]);
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
  if (!cli->user)
  {
    send_str_to_client(cli->client_fd, "001 :Welcome");
    asprintf(&cli->user, "%s", command[1]);
    return (TRUE);
  }
  free(cli->user);
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
  printf("%s\n", "je me clean de la chanel");
  remove_cli_from_his_chanels(cli);
  close(cli->client_fd);
  cli->pollfd->fd = -1;
  cli->client_fd = -1;
  if (cli->chanels)
    free(cli->chanels);
  free(cli->nickname);
  return (TRUE);
}

void     send_msg_to_chanel(t_chanel *chan, char *msg, t_client_infos *cli)
{
  int    i;

  i = 0;
  while (i < MAX_CLI && chan->fds_in_chanel[i])
  {
    if (chan->fds_in_chanel[i] > 0 && cli->client_fd != chan->fds_in_chanel[i])
      send_str_to_client(chan->fds_in_chanel[i], msg);
    i++;
  }
}

int    find_user_by_nick(char *nick, t_server_infos *serv)
{
  int  i;

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

void    send_msg_to_priv_cli(char **command, t_server_infos *serv, t_client_infos *cli)
{
  char  *msg;
  int   fd;

  if ((fd = find_user_by_nick(command[1], serv)) == -1)
  {
    asprintf(&msg, "401 %s %s :No such nick/channel", cli->nickname, command[2]);
    return ;
  }
  asprintf(&msg, ":%s PRIVMSG %s %s", cli->nickname, command[1], command[2]);
  send_str_to_client(fd, msg);
  free(msg);
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
  if (!(command[1][0] == '#'))
    {
      send_msg_to_priv_cli(command, serv, cli);
      return (TRUE);
    }
  while (i < MAX_CLI && cli->chanels[i])
  {
    if (!strcmp(cli->chanels[i]->chanel_name, command[1]))
    {
      asprintf(&msg, ":%s PRIVMSG %s %s", cli->nickname, cli->chanels[i]->chanel_name, command[2]);
      send_msg_to_chanel(cli->chanels[i], msg, cli);
      free(msg);
    }
    i++;
  }
  return (TRUE);
}

BOOL          join_command(char **command, t_server_infos *serv, t_client_infos *cli)
{
  char        *msg;
  t_chanel    *chan;

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
  asprintf(&msg, ":%s JOIN %s", cli->nickname, command[1]);
  if ((chan = chanel_exist(command[1], serv)))
  {
    send_msg_to_chanel(chan, msg, cli);
    send_str_to_client(cli->client_fd, msg);
  }
  free(msg);
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
