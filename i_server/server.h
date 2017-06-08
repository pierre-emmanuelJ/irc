/*
** myirc.h for  in /home/jacqui_p/rendu/PSU_2016_myirc/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Wed May 31 14:59:09 2017 Pierre-Emmanuel Jacquier
** Last update Thu Jun  8 18:05:16 2017 Pierre-Emmanuel Jacquier
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
# include <arpa/inet.h>
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

# define FAILURE (84)
# define MAX_FD (sysconf(_SC_OPEN_MAX))
# define MAX_CLI (MAX_FD)
# define BOOL t_bool
# define TIMEOUT (3 * 60 * 1000)
# define NB_COMMANDS (5)

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

typedef struct          s_chanel
{
  char                  *chanel_name;
  struct pollfd         **fds_in_chanel;
}                       t_chanel;

typedef struct          s_server_infos
{
  struct protoent       *pe;
  int                   fd;
  struct sockaddr_in    s_in;
  int                   port;
  struct pollfd         *clients;
  void                  *pfuncs;
  t_chanel              *chanels;
}                       t_server_infos;

typedef struct          s_client_infos
{
  struct sockaddr_in    s_in_client;
  socklen_t             s_in_size;
  int                   client_fd;
  char                  *client_ip;
  int                   client_port;
  char                  *nickname;
  t_chanel              **chanels;
  t_chanel              *cur_chanel;
  FILE                  *fp;
  struct pollfd         *pollfd;
}                       t_client_infos;

typedef struct          s_circular_buf
{
  char                  *rfc_msg;
  int                   client_fd;
  BOOL                  is_empty;
  struct pollfd         *pollfd;
  t_client_infos        *client;
  int                   *fds_to_write;
  struct s_circular_buf *next;
  struct s_circular_buf *start;
  struct s_circular_buf *end;
}                       t_circular_buf;

typedef struct          end_prg
{
  struct pollfd         *pollfds;
  t_circular_buf        *cbuf;
}                       t_end_prg;

extern t_end_prg g_end_prg;

/*
** utils functions
*/
void     *vmalloc(size_t size);
BOOL     is_number(char *number);

/*
** server utiles
*/
BOOL     create_socket(t_server_infos *);
BOOL     server_listen(t_server_infos *);
BOOL     server_accept(t_server_infos *, t_client_infos *);
BOOL     data_client_receive(t_server_infos *, t_client_infos *, t_circular_buf *);
BOOL     send_str_to_client(int client_fd, const char *msg);

/*
** circular buffer
*/
t_circular_buf *create_circular_buf(void);
void           init_circular_buf(t_circular_buf *);
BOOL           add_in_cbuf(t_circular_buf **cbuf,
                           struct pollfd *pollfd,
                           t_client_infos *cli,
                           char *result);
BOOL             use_cbuf(t_circular_buf **cbuf);

/*
** malloc memory verification
*/
void           *vmalloc(size_t size);
void           epure_str(char *str, int str_len);
char           **split_str(char *str, int delim);
void           remove_crlf(char *str);

#endif /* !MYIRC_H_ */
