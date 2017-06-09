/*
** main.c for  in /home/jacqui_p/rendu/PSU_2016_myirc/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Wed May 31 14:58:45 2017 Pierre-Emmanuel Jacquier
** Last update Fri Jun  9 15:38:58 2017 Pierre-Emmanuel Jacquier
*/

#include "server.h"
#include "pfunctions_commands.h"

t_end_prg g_end_prg;

void    remove_client(struct pollfd *fds, t_client_infos *cli, int index)
{
  printf("client %s:%d leave\n", cli[index].client_ip, cli[index].client_port);
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

void        exec_lines(t_server_infos *serv,
                       struct pollfd  *pollfd,
                       t_client_infos *cli,
                       t_circular_buf *cbuf)
{
  char      **command;
  char      *result;
  char      **lines;
  char       **tmp;

  lines = split_str(serv->input, '\n');
  tmp = lines;
  while (*lines)
  {
    remove_crlf(*lines);
    printf("%s\n", *lines);
    epure_str(*lines, strlen(*lines));
    command = split_str(*lines, ' ');
    fflush(stdout);
    exec_command(command, serv, cli, &result);
    add_in_cbuf(&cbuf, pollfd, cli, result);
    free(command);
    lines++;
  }
  free(tmp);
}

BOOL        data_client_receive(t_server_infos *serv,
                                t_client_infos *cli,
                                t_circular_buf *cbuf)
{
  int       i;
  char      input[1024];
  int       len;

  i = 1;
  while (i < MAX_CLI && serv->clients[i].fd != 0)
  {
    if (serv->clients[i].fd > 0 && serv->clients[i].revents == POLLIN)
      {
        if ((len = read(serv->clients[i].fd, input, 1024)) <= 0)
        {
          remove_client(serv->clients, cli, i++);
          continue ;
        }
        input[len] = 0;
        serv->input = input;
        exec_lines(serv, &serv->clients[i], &cli[i], cbuf);
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
    data_client_receive(server_infos, clients, cbuf);
    use_cbuf(&cbuf);
    //request_to_write(server_infos);
  }
  return (TRUE);
}

static BOOL         init_data_server(t_server_infos *server_infos)
{
  t_circular_buf    *cbuf;
  t_client_infos    clients[MAX_CLI];
  t_chanel          chanels[MAX_CLI];

  memset(chanels, 0, sizeof(chanels));
  server_infos->chanels = chanels;
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
    fprintf(stderr, "USAGE: ./server port\n");
    return (FAILURE);
  }
  printf("MAX cli = %d\n", MAX_CLI);
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
