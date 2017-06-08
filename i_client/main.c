/*
** white_rabbit.c for  in /Users/pichar_v/Documents/tek2/cpp_d01/ex00/
**
** Made by Valentin Pichard
** Login   <pichar_v@epitech.eu>
**
** Started on  Wed Jan  4 09:07:13 2017 Valentin Pichard
** Last update Wed Jan  4 23:15:35 2017 Valentin Pichard
*/

#include "client.h"

static void main_process(t_windows *w, t_client *c)
{
  w = malloc(sizeof(t_windows));
  c = malloc(sizeof(t_client));
  init_values(c);
  assign_windows(w, c);
  while (42)
  {
    char a = wgetch(w->textbox);
    if (isprint(a))
      wprintw(w->textbox, "%c%d", a);
    wrefresh (w->textbox);
  }
  destroy_windows(w);
  free(w);
}

int main(void)
{
  t_windows w;
  t_client c;

  init_ncurses(&w, &c);
  main_process(&w, &c);
  endwin();
  return (EXIT_SUCCESS);
}