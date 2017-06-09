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

#define _GNU_SOURCE
#include <unistd.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

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
}               t_client;

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

/* keys.c */
void keybindings(int ch, t_windows *w, t_client *c);

#endif /* !CLIENT_IRC_H__ */
