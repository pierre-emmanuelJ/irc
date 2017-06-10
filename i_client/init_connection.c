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

int       handle_client(t_client *c)
{
  int     fd;
  int     is_on;
  struct  sockaddr_in s_in;
  struct  protoent *pe;

  is_on = 1;
  pe = getprotobyname("TCP");
  if ((fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    return (-1);
  is_on = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR,
  &is_on, sizeof(is_on));
  if (is_on == -1)
    return (is_on);
  s_in.sin_family = AF_INET;
  inet_pton(AF_INET, c->stock.ip, &(s_in.sin_addr));
  s_in.sin_port = htons(c->stock.port);
  if (connect(fd, (struct sockaddr *)&s_in,
  sizeof(s_in)) == -1)
    return (-1);
  c->stock.socket = fd;
  return (0);
}

void      close_channel(t_client *c, int nb_socket)
{
  close(c->stock.socket);
  if (nb_socket > 0)
    close(nb_socket);
  c->stock.port = -1;
}