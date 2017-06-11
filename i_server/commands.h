/*
** commands.h for  in /home/jacqui_p/rendu/PSU_2016_myirc/i_server/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Wed Jun  7 16:57:43 2017 Pierre-Emmanuel Jacquier
** Last update Sun Jun 11 22:37:42 2017 Pierre-Emmanuel Jacquier
*/

#ifndef COMMANDS_H_
# define COMMANDS_H_

# define NB_COMMANDS (9)

typedef struct  s_commands_tab
{
  char          tab[NB_COMMANDS][255];
}               t_commands_tab;
#endif /* !COMMANDS_H_ */
