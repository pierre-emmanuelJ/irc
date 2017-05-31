/*
** main.c for  in /home/jacqui_p/rendu/PSU_2016_myirc/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Wed May 31 14:58:45 2017 Pierre-Emmanuel Jacquier
** Last update Wed May 31 19:17:30 2017 Pierre-Emmanuel Jacquier
*/

#include "server.h"

void             *vmalloc(size_t size)
{
  void           *mem;

  mem = malloc(size);
  if (!mem)
  {
    perror("malloc failed");
    exit (EXIT_FAILURE);
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

static BOOL      server_main_loop(t_server_infos *server_infos)
{
  t_client_infos clients[MAX_CLI];
  struct pollfd  fds[MAX_CLI];
  t_circular_buf *cbuf;

  cbuf = create_circular_buf();
  init_circular_buf(cbuf);
  (void)fds;
  (void)clients;
  (void)server_infos;
  for (int i = 0; i < MAX_CLI; i++)
  {
    printf("%d\n", cbuf[i].client_fd);
  }
  free(cbuf);
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
    return (1);
  }
  server_infos.port = atoi(argv[1]);
  if (!commons(&server_infos))
  {
    fprintf(stderr, "%s\n", strerror(errno));
    return (1);
  }
  return (0);
}
