/*
** myirc.h for  in /home/jacqui_p/rendu/PSU_2016_myirc/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Wed May 31 14:59:09 2017 Pierre-Emmanuel Jacquier
** Last update Wed May 31 16:55:55 2017 Pierre-Emmanuel Jacquier
*/

#ifndef MYIRC_H_
# define MYIRC_H_

# define _GNU_SOURCE

# include <stdio.h>
# include <netdb.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <stdlib.h>
# include <netinet/in.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <signal.h>
# include <poll.h>
# include <ctype.h>

/*
** See feature_test_macros(7)
*/
# define _GNU_SOURCE

# define MAX_QUEU 42
# define NB_CMD 15
# define BOOL t_bool

/*
** yan typedef socklen_t
*/

/*
** yan typedef BOOL
*/

typedef enum s_bool
{
  FALSE,
  TRUE
}            t_bool;

typedef struct          s_server_infos
{
  struct protoent       *pe;
  int                   fd;
  struct sockaddr_in    s_in;
  int                   port;
}                       t_server_infos;

typedef struct          s_client_infos
{
  struct sockaddr_in    s_in_client;
  socklen_t             s_in_size;
  int                   client_fd;
  char                  *client_ip;
  int                   client_port;
}                       t_client_infos;

/*
** server utiles
*/
BOOL     create_socket(t_server_infos *server_infos);
BOOL     server_listen(t_server_infos *server_infos);

#endif /* !MYIRC_H_ */
