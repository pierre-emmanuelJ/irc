/*
** commands_functions.c for  in /home/jacqui_p/rendu/PSU_2016_myirc/i_server/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Wed Jun  7 19:08:21 2017 Pierre-Emmanuel Jacquier
** Last update Sat Jun 10 15:03:52 2017 Pierre-Emmanuel Jacquier
*/

#include "server.h"
#include "pfunctions_commands.h"

BOOL     nick_command(char **command, t_server_infos *serv, t_client_infos *cli)
{
  (void)command;
  (void)serv;
  (void)cli;
  return (TRUE);
}

BOOL     user_command(char **command, t_server_infos *serv, t_client_infos *cli)
{
  (void)command;
  (void)serv;
  (void)cli;
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
  cli->client_fd = -1;
  cli->pollfd->fd = -1;
  close(cli->client_fd);
  return (TRUE);
}
