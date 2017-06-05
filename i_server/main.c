/*
** main.c for  in /home/jacqui_p/rendu/PSU_2016_myirc/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Wed May 31 14:58:45 2017 Pierre-Emmanuel Jacquier
** Last update Mon Jun  5 18:03:33 2017 Pierre-Emmanuel Jacquier
*/

#include "server.h"

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

BOOL data_client_receive(t_server_infos *serv)
{
  (void)serv;
  printf("%s\n", "incoming data from client");
  return (TRUE);
}

static BOOL      server_main_loop(t_server_infos *server_infos)
{
  t_client_infos clients[MAX_CLI];
  t_circular_buf *cbuf;
  int            event;

  cbuf = create_circular_buf();
  init_circular_buf(cbuf);
  server_infos->clients = vmalloc(sizeof(struct pollfd) * MAX_CLI);
  bzero(clients, sizeof(clients));
  bzero(server_infos->clients, sizeof(struct pollfd) * MAX_CLI);
  server_infos->clients[0].fd = server_infos->fd;
  server_infos->clients[0].events = POLLIN;
  while (1)
  {
    printf("%s\n", "test1");
    if ((event = poll(server_infos->clients, MAX_CLI, TIMEOUT)) < 0)
    {
      perror("poll() failed");
      break ;
    }
    printf("%s\n", "test2");
    if (!event)
    {
      fprintf(stderr, "poll() timed out. End program.\n");
      break ;
    }
    if (server_infos->clients[0].revents == POLLIN)
      server_accept(server_infos);
    else
      data_client_receive(server_infos);
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

int                     main(int argc, char **argv)
{
  t_server_infos        server_infos;

  if (argc != 2 || !is_number(argv[1]))
  {
    printf("USAGE: ./server port\n");
    return (FAILURE);
  }
  server_infos.port = atoi(argv[1]);
  if (!commons(&server_infos))
  {
    fprintf(stderr, "%s\n", strerror(errno));
    return (FAILURE);
  }
  return (0);
}
