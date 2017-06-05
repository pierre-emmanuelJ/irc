/*
** main.c for  in /home/jacqui_p/rendu/PSU_2016_myirc/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Wed May 31 14:58:45 2017 Pierre-Emmanuel Jacquier
** Last update Mon Jun  5 22:15:54 2017 Pierre-Emmanuel Jacquier
*/

#include "server.h"

int g_serv_fd;

void             *vmalloc(size_t size)
{
  void           *mem;

  mem = malloc(size);
  if (!mem)
  {
    perror("malloc failed");
    exit (FAILURE);
  }
  return (mem);
}

static BOOL      is_number(char *number)
{
  while (*number)
  {
    if (!isdigit(*number))
      return (FALSE);
    number++;
  }
  return (TRUE);
}

void    remove_client(struct pollfd *fds, int index)
{
  fds[index].fd = -1;
}

BOOL data_client_receive(t_server_infos *serv, t_circular_buf *cbuf)
{
  int i;
  int  len;
  char buf[4096];
  FILE *fp;
  size_t readed;
  char *input;

  i = 1;
  readed = 0;
  input = NULL;
  while (i < MAX_CLI && serv->clients[i].fd != 0)
  {
    if (serv->clients[i].fd > 0 && serv->clients[i].revents == POLLIN)
      {
        bzero(buf, 4096);
        fp = fdopen(serv->clients[i].fd, "r");
        if ((len = getline(&input, &readed, fp)) <= 0)
        {
          remove_client(serv->clients, i++);
          continue ;
        }
        remove_crlf(input);
        printf("%s\n", input);
        fflush(stdout);
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

static BOOL      server_main_loop(t_server_infos *server_infos)
{
  t_client_infos clients[MAX_CLI];
  t_circular_buf *cbuf;
  int            event;

  cbuf = create_circular_buf();
  init_circular_buf(cbuf);
  server_infos->clients = vmalloc(sizeof(struct pollfd) * MAX_CLI);
  memset(clients, 0, sizeof(t_client_infos) * MAX_CLI);
  memset(server_infos->clients, 0, sizeof(struct pollfd) * MAX_CLI);
  server_infos->clients[0].fd = server_infos->fd;
  server_infos->clients[0].events = POLLIN;
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
      server_accept(server_infos);
    else
      data_client_receive(server_infos, cbuf);
    printf("loop\n");
  }
  free(cbuf);
  free(server_infos->clients);
  return (TRUE);
}

static BOOL      commons(t_server_infos *server_infos)
{
  if (!create_socket(server_infos))
    return (FALSE);
  if (!server_listen(server_infos))
    return (FALSE);
  if (!server_main_loop(server_infos))
    return (FALSE);
  return (TRUE);
}

static void    ctrl_c()
{
  close(g_serv_fd);
  exit(EXIT_SUCCESS);
}


int                     main(int argc, char **argv)
{
  t_server_infos        server_infos;

  if (argc != 2 || !is_number(argv[1]))
  {
    printf("USAGE: ./server port\n");
    return (FAILURE);
  }
  signal(SIGINT, ctrl_c);
  server_infos.port = atoi(argv[1]);
  if (!commons(&server_infos))
  {
    fprintf(stderr, "%s\n", strerror(errno));
    return (FAILURE);
  }
  return (0);
}
