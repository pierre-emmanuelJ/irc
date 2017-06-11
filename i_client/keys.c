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

static void agregging_char(t_windows *w, t_client *c, int ch)
{
  asprintf(&c->ch, "%c", ch);
  asprintf(&c->textbox, "%s%s", c->textbox, c->ch);
  waddstr(w->textbox, c->ch);
}

static void key_delete(t_windows *w, t_client *c)
{
    if (strlen(c->textbox) >= 1)
      c->textbox[strlen(c->textbox)-1] = 0;
    mvwdelch(w->textbox, getcury(w->textbox), getcurx(w->textbox)-1);
}

void keybindings(int ch, t_windows *w, t_client *c, t_command *cmd)
{
  t_command *current;

  if (ch == 127 || ch == 8)
    key_delete(w, c);
  else if (ch == 10)
  {
    /*wprintw(w->body, "%s - %s\n", c->time, c->textbox);
    wrefresh(w->body);*/
    if (c->textbox[0] == '/' && strlen(c->textbox) >= 1)
    {
      current = cmd;
      while (current != NULL)
      {
        if (strstr(c->textbox, current->command))
        {
          current->ptr(c->textbox, w, c);
          clear_line(w->textbox, c);
          return ;
        }
        current = current->next;
      }
      unknow_command(w, c);
    }
    if (strcmp(c->channel, "none") && c->st == CONNECTED)
    {
      asprintf(&c->tosend, "PRIVMSG %s :%s", c->channel, c->textbox);
      write(c->socket, c->tosend, strlen(c->tosend));
    }
    clear_line(w->textbox, c);
  }
  else if (isprint(ch))
    agregging_char(w, c, ch);
  wrefresh (w->textbox);
}