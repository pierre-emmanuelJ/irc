/*
** server.c for  in /home/jacqui_p/rendu/PSU_2016_myftp/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Thu May 11 15:55:39 2017 Pierre-Emmanuel Jacquier
** Last update Sun Jun 11 21:56:50 2017 Pierre-Emmanuel Jacquier
*/

#include "server.h"

BOOL    create_socket(t_server_infos *server_infos)
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

BOOL    server_listen(t_server_infos *server_infos)
{
  if (listen(server_infos->fd, MAX_CLI))
  {
    if (close(server_infos->fd) == -1)
      return (FALSE);
    return (FALSE);
  }
  return (TRUE);
}

static void             add_new_client(t_server_infos *server_infos,
                                       t_client_infos *clients,
                                       t_client_infos *cli)
{
  int                   poll_pos;

  poll_pos = 0;
  while (poll_pos < MAX_CLI
         && !(server_infos->clients[poll_pos].fd == 0)
         && !(server_infos->clients[poll_pos].fd == -1))
    poll_pos++;
  if (poll_pos < MAX_CLI)
  {
    server_infos->clients[poll_pos].fd = cli->client_fd;
    server_infos->clients[poll_pos].events = POLLIN;
    memcpy(&clients[poll_pos], cli, sizeof(t_client_infos));
    clients[poll_pos].pollfd = &server_infos->clients[poll_pos];
    clients[poll_pos].chanels = vmalloc(sizeof(t_chanel *) * MAX_CLI);
    memset(clients[poll_pos].chanels, 0, sizeof(t_chanel *) * MAX_CLI);
  }
}

BOOL                    server_accept(t_server_infos *server_infos,
                                      t_client_infos *clients)
{
  t_client_infos        cli;

  memset(&cli, 0, sizeof(t_client_infos));
  cli.s_in_size = sizeof(cli.s_in_client);
  cli.client_fd = accept(server_infos->fd,
                         (struct sockaddr *)&cli.s_in_client,
                         &cli.s_in_size);
  if (cli.client_fd == -1)
  {
    if (close(server_infos->fd) == -1)
      return (FALSE);
    return (FALSE);
  }
  cli.client_ip = inet_ntoa(cli.s_in_client.sin_addr);
  cli.client_port = ntohs(cli.s_in_client.sin_port);
  printf("New connection from %s:%d\n", cli.client_ip, cli.client_port);
  add_new_client(server_infos, clients, &cli);
  return (TRUE);
}
