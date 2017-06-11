/*
** join_and_leave.c for  in /home/jacqui_p/rendu/PSU_2016_myirc/i_server/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Sun Jun 11 21:17:27 2017 Pierre-Emmanuel Jacquier
** Last update Sun Jun 11 21:17:48 2017 Pierre-Emmanuel Jacquier
*/

#include "server.h"

BOOL            join_command(char **command,
                             t_server_infos *serv,
                             t_client_infos *cli)
{
  char          *msg;
  t_chanel      *chan;

  if (tab_len(command) < 2)
  {
    send_str_to_client(cli->client_fd, "461 :Not enough parameters.");
    send_str_to_client(cli->client_fd, "304 :SYNTAX JOIN <channel>");
    return (FALSE);
  }
  if (chanel_exist(command[1], serv))
    add_cli_to_chanel(command[1], serv, cli);
  else
    add_new_chanel(command[1], serv, cli);
  xasprintf(&msg, ":%s JOIN %s", cli->nickname, command[1]);
  if ((chan = chanel_exist(command[1], serv)))
  {
    send_msg_to_chanel(chan, msg, cli);
    send_str_to_client(cli->client_fd, msg);
  }
  free(msg);
  return (TRUE);
}

BOOL            part_command(char **command,
                             t_server_infos *serv,
                             t_client_infos *cli)
{
  char          *msg;
  t_chanel      *chan;

  if (tab_len(command) != 2)
  {
    send_str_to_client(cli->client_fd, "461 :Not enough parameters.");
    send_str_to_client(cli->client_fd, "304 :SYNTAX PART <channel>");
    return (FALSE);
  }
  if ((chan = chanel_exist(command[1], serv)))
  {
    xasprintf(&msg, ":%s PART %s", cli->nickname, command[1]);
    send_msg_to_chanel(chan, msg, cli);
    send_str_to_client(cli->client_fd, msg);
    remove_cli_from_chanel(command[1], serv, cli);
  }
  return (TRUE);
}

BOOL     list_command(char **command,
                      t_server_infos *serv,
                      t_client_infos *cli)
{
  (void)command;
  (void)serv;
  (void)cli;
  return (TRUE);
}
