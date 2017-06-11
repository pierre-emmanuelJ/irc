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

static void   init_main(t_windows *w, t_client *c)
{
  init_values(c);
  assign_windows(w, c);
  init_body(w, c);
  wtimeout(w->textbox, 10);
}

static void   reply_ping(t_client *c, t_windows *w)
{
  char        *str;

  if (strstr(c->receive, "PING :"))
  {
    str = c->receive;
    str += 6;
    asprintf(&c->tosend, "PONG %s\r\n", str);
    write(c->socket, c->tosend, strlen(c->tosend));
  }
  else
  {
    wprintw(w->body, "%s - %s\n", c->time, c->receive);
    wrefresh(w->body);
  }
}

static int    custom_read(t_client *c)
{
  int         ret;
  int         counter;

  counter = 0;
  bzero(c->receive, 256);
  if (FD_ISSET(c->socket, &(c->fset)))
  {
    if ((ret = read(c->socket, c->receive, 255)) <= 0)
    {
      c->st = DISCONNECTED;
      close_channel(c);
      return (-1);
    }
    while (counter < ret)
    {
      if (c->receive[counter] == '\n' || c->receive[counter] == '\r')
          c->receive[counter] = '\0';
        counter++;
    }
  }
  return (ret);
}

static void   main_process(t_windows *w, t_client *c)
{
  t_command   *cmd;

  w = malloc(sizeof(t_windows));
  c = malloc(sizeof(t_client));
  cmd = lets_init_linkedlist();
  init_main(w, c);
  while (42)
  {
    time_writter(c);
    refresh_windows(w, c);
    keybindings(wgetch(w->textbox), w, c, cmd);
    if (c->st == CONNECTED)
    {
      FD_ZERO(&(c->fset));
      FD_SET(c->socket, &(c->fset));
      c->tm.tv_usec = 100;
      if ((c->ret = select(c->socket + 1, &(c->fset), NULL, NULL, &(c->tm))) == -1)
        return ;
      if (custom_read(c) > -1 && strlen(c->receive) >= 1)
        reply_ping(c, w);
    }
  }
  destroy_windows(w);
  free(w);
}

int           main(void)
{
  t_windows   w;
  t_client    c;

  init_ncurses();
  main_process(&w, &c);
  endwin();
  return (EXIT_SUCCESS);
}