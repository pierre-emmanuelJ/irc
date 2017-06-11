/*
** pfonction_commands.h for  in /home/jacqui_p/rendu/PSU_2016_myirc/i_server/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Wed Jun  7 18:08:07 2017 Pierre-Emmanuel Jacquier
** Last update Sun Jun 11 22:38:48 2017 Pierre-Emmanuel Jacquier
*/

#ifndef PFUNCTIONS_COMMANDS_H_
# define PFUNCTIONS_COMMANDS_H_

# include "server.h"
# include "commands.h"

/*
** Commande functions pointers
*/
typedef BOOL    (*pf_commands)(char **command,
                               t_server_infos *,
                               t_client_infos *);

typedef struct  s_pf
{
  pf_commands   commands[NB_COMMANDS];
}               t_pf;

BOOL    call_function(t_pf *pf, char **command,
                      t_server_infos *serv_infos,
                      t_client_infos *cli_infos);
void    init_tpsf_tab(t_pf *pf);

BOOL    nick_command(char **command, t_server_infos *, t_client_infos *);
BOOL    user_command(char **command, t_server_infos *, t_client_infos *);
BOOL    ping_command(char **command, t_server_infos *, t_client_infos *);
BOOL    pong_command(char **command, t_server_infos *, t_client_infos *);
BOOL    quit_command(char **command, t_server_infos *, t_client_infos *);
BOOL    privmsg_command(char **command, t_server_infos *, t_client_infos *);
BOOL    join_command(char **command, t_server_infos *, t_client_infos *);
BOOL    part_command(char **command, t_server_infos *, t_client_infos *);
BOOL    list_command(char **command, t_server_infos *, t_client_infos *);

#endif /* !PFUNCTIONS_COMMANDS_H_ */
