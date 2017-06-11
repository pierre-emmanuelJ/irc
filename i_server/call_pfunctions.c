/*
** call_pfunctions.c for  in /home/jacqui_p/rendu/PSU_2016_myirc/i_server/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Wed Jun  7 16:57:32 2017 Pierre-Emmanuel Jacquier
** Last update Sun Jun 11 22:37:20 2017 Pierre-Emmanuel Jacquier
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

void    init_command_tab(t_commands_tab *tab)
{
  sprintf(tab->tab[0], "NICK");
  sprintf(tab->tab[1], "USER");
  sprintf(tab->tab[2], "PING");
  sprintf(tab->tab[3], "PONG");
  sprintf(tab->tab[4], "QUIT");
  sprintf(tab->tab[5], "PRIVMSG");
  sprintf(tab->tab[6], "JOIN");
  sprintf(tab->tab[7], "PART");
  sprintf(tab->tab[8], "LIST");
}

BOOL                    call_function(t_pf *pf, char **command,
                                      t_server_infos *serv_infos,
                                      t_client_infos *cli_infos)
{
  int                   i;
  t_commands_tab        tab;

  i = 0;
  init_command_tab(&tab);
  while (i < NB_COMMANDS)
  {
    if (!strcmp(command[0], tab.tab[i]))
    {
      if (pf->commands[i](command, serv_infos, cli_infos))
        return (FALSE);
      return (TRUE);
    }
    i++;
  }
  return (FALSE);
}
