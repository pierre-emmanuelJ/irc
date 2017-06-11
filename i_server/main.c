/*
** main.c for  in /home/jacqui_p/rendu/PSU_2016_myirc/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Wed May 31 14:58:45 2017 Pierre-Emmanuel Jacquier
** Last update Sun Jun 11 22:58:29 2017 Pierre-Emmanuel Jacquier
*/

#include "server.h"
#include "pfunctions_commands.h"

t_end_prg       g_end_prg;

static BOOL     server_main_loop(t_server_infos *server_infos,
                                  t_client_infos *clients)
{
  int           event;

  while (1)
  {
    if ((event = poll(server_infos->clients,
      count_pollfds(server_infos->clients), TIMEOUT)) < 0)
    {
      perror("poll() failed");
      break ;
    }
    if (!event)
    {
      fprintf(stderr, "poll() timed out. End program.\n");
      continue ;
    }
    if (server_infos->clients[0].revents == POLLIN)
    {
      server_accept(server_infos, clients);
      continue ;
    }
    data_client_receive(server_infos, clients);
    use_cbuf(&server_infos->cbuf, server_infos);
  }
  return (TRUE);
}

static BOOL             init_data_server(t_server_infos *server_infos)
{
  t_circular_buf        *cbuf;
  t_client_infos        clients[MAX_CLI];
  t_chanel              chanels[MAX_CLI];

  memset(chanels, 0, sizeof(t_chanel) * MAX_CLI);
  server_infos->chanels = chanels;
  server_infos->all_cli = clients;
  cbuf = create_circular_buf();
  init_circular_buf(cbuf);
  server_infos->cbuf = cbuf;
  g_end_prg.cbuf = cbuf;
  server_infos->clients = vmalloc(sizeof(struct pollfd) * MAX_CLI);
  g_end_prg.pollfds = server_infos->clients;
  memset(clients, 0, sizeof(t_client_infos) * MAX_CLI);
  memset(server_infos->clients, 0, sizeof(struct pollfd) * MAX_CLI);
  server_infos->clients[0].fd = server_infos->fd;
  server_infos->clients[0].events = POLLIN;
  if (!server_main_loop(server_infos, clients))
    return (FALSE);
  return (TRUE);
}

static BOOL     commons(t_server_infos *server_infos)
{
  if (!create_socket(server_infos))
    return (FALSE);
  if (!server_listen(server_infos))
    return (FALSE);
  if (!init_data_server(server_infos))
    return (FALSE);
  return (TRUE);
}

static void     ctrl_c()
{
  int           i;

  i = 0;
  while (g_end_prg.pollfds[i].fd != 0)
  {
    if (g_end_prg.pollfds[i].fd > 0)
      close(g_end_prg.pollfds[i].fd);
    i++;
  }
  free(g_end_prg.pollfds);
  free(g_end_prg.cbuf);
  exit(0);
}

int                     main(int argc, char **argv)
{
  t_server_infos        server_infos;
  t_pf                  pf;

  if (argc != 2 || !is_number(argv[1]))
  {
    fprintf(stderr, "USAGE: ./server port\n");
    exit(FAILURE);
  }
  signal(SIGINT, ctrl_c);
  init_tpsf_tab(&pf);
  server_infos.pfuncs = (void *)&pf;
  server_infos.port = atoi(argv[1]);
  if (!commons(&server_infos))
  {
    fprintf(stderr, "%s\n", strerror(errno));
    exit(FAILURE);
  }
  return (0);
}
