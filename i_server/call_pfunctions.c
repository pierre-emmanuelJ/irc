/*
** call_pfunctions.c for  in /home/jacqui_p/rendu/PSU_2016_myirc/i_server/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Wed Jun  7 16:57:32 2017 Pierre-Emmanuel Jacquier
** Last update Sat Jun 10 19:24:32 2017 Pierre-Emmanuel Jacquier
*/

#include "server.h"
#include "commands.h"
#include "pfunctions_commands.h"

void    init_tpsf_tab(t_pf *pf)
{
  pf->commands[0] = &nick_command;
  pf->commands[1] = &user_command;
  pf->commands[2] = &ping_command;
  pf->commands[3] = &pong_command;
  pf->commands[4] = &quit_command;
  pf->commands[5] = &privmsg_command;
  pf->commands[6] = &join_command;
  pf->commands[7] = &part_command;
  pf->commands[8] = &list_command;
}

BOOL    call_function(t_pf *pf, char **command,
                      t_server_infos *serv_infos,
                      t_client_infos *cli_infos)
{
  int   i;

  i = 0;
  while (i < NB_COMMANDS)
  {
    if (!strcmp(command[0], g_commands_list[i]))
    {
      if (pf->commands[i](command, serv_infos, cli_infos))
        return (FALSE);
      return (TRUE);
    }
    i++;
  }
  return (FALSE);
}
