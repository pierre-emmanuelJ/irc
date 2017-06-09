/*
** white_rabbit.c for  in /Users/pichar_v/Documents/tek2/cpp_d01/ex00/
**
** Made by Valentin Pichard
** Login   <pichar_v@epitech.eu>
**
** Started on  Wed Jan  4 09:07:13 2017 Valentin Pichard
** Last update Wed Jan  4 23:15:35 2017 Valentin Pichard
*/

#ifndef CLIENT_IRC_H__
# define CLIENT_IRC_H__

#include <unistd.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define _GNU_SOURCE

#define DEFAULT_NICKNAME "francis_kuntz"
#define DEFAULT_HEADER "Welcome on ZAPOIIIIRC v0.8 RC2 - http://fifigrot.com/"

typedef struct  s_windows {
  WINDOW        *header;
  WINDOW        *body;
  WINDOW        *footer;
  WINDOW        *textbox;
}               t_windows;

typedef struct  s_client {
  char          *time;
  char          *nickname;
  char          *hostname;
  char          *header;
  char          *textbox;
  char          *ch;
}               t_client;


typedef void  (*funcptr)(char *params, t_windows *w, t_client *c);

typedef struct  s_command
{
  char          *command;
  funcptr       ptr;
  struct s_command *next;
}               t_command;

/* utils.c */
void time_writter(t_client *c);

/* init.c */
void init_ncurses(void);
void init_values(t_client *c);
void init_body(t_windows *w, t_client *c);

/* windows.c */
WINDOW    *create_window(int h, int w, int y, int x);
void      destroy_windows(t_windows *w);
void      assign_windows(t_windows *w, t_client *c);
void      clear_line(WINDOW *w, t_client *c);

/* keys.c */
void keybindings(int ch, t_windows *w, t_client *c, t_command *cmd);

/* custom_functions.c */
void    *custom_malloc(size_t length);
int     custom_dup2(int oldfd, int newfd);
int     custom_dup(int oldfd);

/* init_linked_list.c */
t_command     *lets_init_linkedlist(void);

/* irc functions.c */
void command_help(char *str, t_windows *w, t_client *c);
void command_quit(char *str, t_windows *w, t_client *c);
void command_msg(char *str, t_windows *w, t_client *c);
void command_names(char *str, t_windows *w, t_client *c);
void command_part(char *str, t_windows *w, t_client *c);
void command_users(char *str, t_windows *w, t_client *c);
void command_join(char *str, t_windows *w, t_client *c);
void command_server(char *str, t_windows *w, t_client *c);
void command_nick(char *str, t_windows *w, t_client *c);
void command_list(char *str, t_windows *w, t_client *c);
void command_join(char *str, t_windows *w, t_client *c);
void command_accept(char *str, t_windows *w, t_client *c);

/* errors;c */
void unknow_command(t_windows *w, t_client *c);

/* refresh.c */
void refresh_footer(t_windows *w, t_client *c);

#endif /* !CLIENT_IRC_H__ */
