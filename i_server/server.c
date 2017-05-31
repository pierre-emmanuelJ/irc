/*
** server.c for  in /home/jacqui_p/rendu/PSU_2016_myftp/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Thu May 11 15:55:39 2017 Pierre-Emmanuel Jacquier
** Last update Wed May 31 15:16:20 2017 Pierre-Emmanuel Jacquier
*/

#include "server.h"

BOOL     create_socket(t_server_infos *server_infos)
{
  server_infos->pe = getprotobyname("TCP");
  if (!server_infos->pe)
    return (FALSE);
  server_infos->fd = socket(AF_INET, SOCK_STREAM, server_infos->pe->p_proto);
  if (server_infos->fd == -1)
    return (FALSE);
  server_infos->s_in.sin_family = AF_INET;
  server_infos->s_in.sin_port = htons(server_infos->port);
  server_infos->s_in.sin_addr.s_addr = INADDR_ANY;
  if (bind(server_infos->fd,
           (const struct sockaddr *)&server_infos->s_in,
           sizeof(server_infos->s_in)))
  {
    if (close(server_infos->fd) == -1)
      return (FALSE);
    return (FALSE);
  }
  return (TRUE);
}

BOOL     server_listen(t_server_infos *server_infos)
{
  if (listen(server_infos->fd, MAX_QUEU))
  {
    if (close(server_infos->fd) == -1)
      return (FALSE);
    return (FALSE);
  }
  return (TRUE);
}
