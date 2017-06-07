/*
** main.c for  in /home/jacqui_p/rendu/PSU_2016_myirc/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Wed May 31 14:58:45 2017 Pierre-Emmanuel Jacquier
** Last update Wed Jun  7 19:09:39 2017 Pierre-Emmanuel Jacquier
*/

#include "server.h"
#include "pfunctions_commands.h"

t_end_prg g_end_prg;

void    remove_client(struct pollfd *fds, t_client_infos *cli, int index)
{
  fclose(cli[index].fp);
  close(fds[index].fd);
  fds[index].fd = -1;
  memset(&cli[index], 0, sizeof(t_client_infos));
  cli[index].client_fd = -1;
}

BOOL        exec_command(char **command, t_server_infos *serv, t_client_infos *cli, char **result)
{
  call_function((t_pf *)serv->pfuncs, command, serv, cli);
  asprintf(result, "command = %s fd = %d", command[0], cli->client_fd);
  return (TRUE);
}

BOOL        data_client_receive(t_server_infos *serv,
                                t_client_infos *cli,
                                t_circular_buf *cbuf)
{
  int       i;
  int       len;
  size_t    readed;
  char      *input;
  char      **command;
  char      *result;

  i = 1;
  readed = 0;
  input = NULL;
  while (i < MAX_CLI && serv->clients[i].fd != 0)
  {
    if (serv->clients[i].fd > 0 && serv->clients[i].revents == POLLIN)
      {
        if (cli[i].fp == NULL)
          cli[i].fp = fdopen(serv->clients[i].fd, "r");
        if ((len = getline(&input, &readed, cli[i].fp)) <= 0)
        {
          remove_client(serv->clients, cli, i++);
          continue ;
        }
        remove_crlf(input);
        printf("%s\n", input);
        epure_str(input, strlen(input));
        command = split_str(input, ' ');
        fflush(stdout);
        exec_command(command, serv, &cli[i], &result);
        add_in_cbuf(&cbuf, &serv->clients[i], &cli[i], result);
        free(command);
        free(input);
      }
    i++;
  }
  return (TRUE);
}

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

BOOL             request_to_write(t_server_infos *serv)
{
  int       i;

  i = 1;
  while (i < MAX_CLI && serv->clients[i].fd != 0)
  {
    if (serv->clients[i].fd > 0 && serv->clients[i].revents == POLLIN)
        serv->clients[i].events = POLLOUT;
    i++;
  }
  return (TRUE);
}

BOOL     send_str_to_client(int client_fd, const char *msg)
{
  if (write(client_fd, msg, strlen(msg)) == -1
      || write(client_fd, "\r\n", 2) == -1)
    return (FALSE);
  return (TRUE);
}

static BOOL      server_main_loop(t_server_infos *server_infos,
                                  t_client_infos *clients,
                                  t_circular_buf *cbuf)
{
  int            event;

  while (1)
  {
    if ((event = poll(server_infos->clients, count_pollfds(server_infos->clients), TIMEOUT)) < 0)
    {
      perror("poll() failed");
      break ;
    }
    if (!event)
    {
      fprintf(stderr, "poll() timed out. End program.\n");
      break ;
    }
    if (server_infos->clients[0].revents == POLLIN)
    {
      server_accept(server_infos, clients);
      continue ;
    }
    use_cbuf(&cbuf);
    data_client_receive(server_infos, clients, cbuf);
    request_to_write(server_infos);
  }
  return (TRUE);
}

static BOOL         init_data_server(t_server_infos *server_infos)
{
  t_circular_buf    *cbuf;
  t_client_infos    clients[MAX_CLI];

  cbuf = create_circular_buf();
  init_circular_buf(cbuf);
  g_end_prg.cbuf = cbuf;
  server_infos->clients = vmalloc(sizeof(struct pollfd) * MAX_CLI);
  g_end_prg.pollfds = server_infos->clients;
  memset(clients, 0, sizeof(t_client_infos) * MAX_CLI);
  memset(server_infos->clients, 0, sizeof(struct pollfd) * MAX_CLI);
  server_infos->clients[0].fd = server_infos->fd;
  server_infos->clients[0].events = POLLIN;
  if (!server_main_loop(server_infos, clients, cbuf))
    return (FALSE);
  return (TRUE);
}

static BOOL      commons(t_server_infos *server_infos)
{
  if (!create_socket(server_infos))
    return (FALSE);
  if (!server_listen(server_infos))
    return (FALSE);
  if (!init_data_server(server_infos))
    return (FALSE);
  return (TRUE);
}

static void    ctrl_c()
{
  int i;

  i = 0;
  while (g_end_prg.pollfds[i].fd != 0)
  {
    if (g_end_prg.pollfds[i].fd > 0)
      close(g_end_prg.pollfds[i].fd);
    i++;
  }
  free(g_end_prg.pollfds);
  free(g_end_prg.cbuf);
  exit(EXIT_SUCCESS);
}

int                     main(int argc, char **argv)
{
  t_server_infos        server_infos;
  t_pf                  pf;

  if (argc != 2 || !is_number(argv[1]))
  {
    printf("USAGE: ./server port\n");
    return (FAILURE);
  }
  signal(SIGINT, ctrl_c);
  init_tpsf_tab(&pf);
  server_infos.pfuncs = (void *)&pf;
  server_infos.port = atoi(argv[1]);
  if (!commons(&server_infos))
  {
    fprintf(stderr, "%s\n", strerror(errno));
    return (FAILURE);
  }
  return (0);
}
