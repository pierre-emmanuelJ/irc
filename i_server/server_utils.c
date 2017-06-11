/*
** server_utils.c for  in /home/jacqui_p/rendu/PSU_2016_myirc/i_server/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Sun Jun 11 20:07:52 2017 Pierre-Emmanuel Jacquier
** Last update Sun Jun 11 20:12:00 2017 Pierre-Emmanuel Jacquier
*/

#include "server.h"

size_t    count_pollfds(struct pollfd *fds)
{
  size_t i;

  i = 0;
  while (i < (size_t)MAX_CLI)
  {
    if (fds[i].fd == 0)
      break ;
    i++;
  }
  return (i);
}

int          xasprintf(char **strp, const char *fmt, ...)
{
  int        len;
  va_list    ap;

  va_start(ap, fmt);
  if ((len = vasprintf(strp, fmt, ap)) == -1)
    exit(FAILURE);
  va_end(ap);
  return (len);
}

BOOL                    send_str_to_client(int client_fd, const char *msg)
{
  int                   err;
  socklen_t             t;
  struct sockaddr_in    s;

  t = sizeof(s);
  if (getsockopt(client_fd, SOL_SOCKET, SO_ERROR, &err, &t) == -1)
    return (FALSE);
  if (err)
    return (FALSE);
  if (write(client_fd, msg, strlen(msg)) == -1
      || write(client_fd, "\r\n", 2) == -1)
    return (FALSE);
  return (TRUE);
}
