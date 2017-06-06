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

typedef struct s_windows {
  WINDOW *header;
  WINDOW *body;
  WINDOW *footer;
  WINDOW *textbox;
} t_windows;

#endif /* !CLIENT_IRC_H__ */
