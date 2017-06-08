/*
** commands_functions.c for  in /home/jacqui_p/rendu/PSU_2016_myirc/i_server/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Wed Jun  7 19:08:21 2017 Pierre-Emmanuel Jacquier
** Last update Wed Jun  7 19:48:13 2017 Pierre-Emmanuel Jacquier
*/

#include "server.h"
#include "pfunctions_commands.h"

BOOL     nick_command(char **command, t_server_infos *serv, t_client_infos *cli)
{
  (void)command;
  (void)serv;
  (void)cli;
  printf("%s\n", "pf function");
  return (TRUE);
}

BOOL     user_command(char **command, t_server_infos *serv, t_client_infos *cli)
{
  (void)command;
  (void)serv;
  (void)cli;
  printf("%s\n", "pf function");
  return (TRUE);
}

BOOL     ping_command(char **command, t_server_infos *serv, t_client_infos *cli)
{
  (void)command;
  (void)serv;
  (void)cli;
  printf("%s\n", "pf function");
  return (TRUE);
}

BOOL     pong_command(char **command, t_server_infos *serv, t_client_infos *cli)
{
  (void)command;
  (void)serv;
  (void)cli;
  printf("%s\n", "pf function");
  return (TRUE);
}

BOOL     quit_command(char **command, t_server_infos *serv, t_client_infos *cli)
{
  (void)command;
  (void)serv;
  (void)cli;
  printf("%s\n", "pf function");
  return (TRUE);
}
