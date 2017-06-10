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

static int          resolve_hostname(t_client *c, t_windows *w)
{
  struct hostent    *pi;
  struct in_addr    addr;

  pi = gethostbyname(c->ip);
  wprintw(w->body, "%s - Resolving %s....\n", c->time, c->ip);
  wrefresh(w->body);
  if (!pi)
  {
    cant_resolve(w, c);
    return (-1);
  }
  memcpy(&addr, pi->h_addr_list[0], sizeof(struct in_addr));
  asprintf(&c->hostname, "%s", c->ip);
  asprintf(&c->ip, "%s", inet_ntoa(addr));
  return (0);
}

static void         epure_str(char *str, int str_len)
{
  int               i;
  int               j;
  char              newstr[str_len];

  i = 0;
  j = 0;
  while (str[i] == ' ' || str[i] == '\t')
    i++;
  while (str[i])
  {
    if (str[i] != ' ' && str[i] != '\t')
      newstr[j++] = str[i++];
    else if (str[i] == ' ' || str[i] == '\t')
    {
      while (str[i] == ' ' || str[i] == '\t')
        i++;
      if (str[i] != '\0')
        newstr[j++] = ' ';
    }
  }
  newstr[j] = 0;
  bzero(str, str_len);
  memmove(str, newstr, strlen(newstr));
}

static void         split_args(t_client *c, t_windows *w)
{
  epure_str(c->params, strlen(c->params));
  if (strchr(c->params, ':') != NULL)
  {
    c->ip = strtok(c->params, ":");
    c->port = atoi(strtok(NULL, ":"));
    resolve_hostname(c, w);
    return ;
  }
  asprintf(&c->ip, "%s", c->params);
  resolve_hostname(c, w);
}

void                command_server(char *str, t_windows *w, t_client *c)
{
  if (compare_cnts_command(str, "/server" ,w, c, 8) == FALSE)
    return ;
  split_args(c, w);
  wprintw(w->body, "%s - Looking up %s on %d\n", c->time, c->ip, c->port);
  wrefresh(w->body);
  if (handle_client(c, w) != 0)
  {
    wprintw(w->body, "%s - Unable to connect on %s\n", c->time, c->ip);
    c->ip = "none\0";
    c->hostname = "none\0";
    wrefresh(w->body);
    return ;
  }
  wprintw(w->body, "%s - Connection to %s etablished on port %d\n", c->time, c->ip, c->port);
  wrefresh(w->body);
  c->st = CONNECTED;
}