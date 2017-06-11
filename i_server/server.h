/*
** myirc.h for  in /home/jacqui_p/rendu/PSU_2016_myirc/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Wed May 31 14:59:09 2017 Pierre-Emmanuel Jacquier
** Last update Sun Jun 11 22:30:58 2017 Pierre-Emmanuel Jacquier
*/

#ifndef SERVER_H_
# define SERVER_H_

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
# include <stdarg.h>

/*
** See feature_test_macros(7)
*/
# define _GNU_SOURCE

# define FAILURE (84)
# define MAX_FD (sysconf(_SC_OPEN_MAX))
# define MAX_CLI (1024)
# define BOOL t_bool
# define TIMEOUT (3 * 60 * 1000)

/*
** yan typedef socklen_t
*/

/*
** yan typedef BOOL
*/

typedef enum    s_bool
{
  FALSE,
  TRUE
}               t_bool;

typedef struct          s_chanel
{
  char                  *chanel_name;
  int                   *fds_in_chanel;
}                       t_chanel;

typedef struct          s_client_infos
{
  struct sockaddr_in    s_in_client;
  socklen_t             s_in_size;
  int                   client_fd;
  char                  *client_ip;
  int                   client_port;
  char                  *nickname;
  char                  *user;
  t_chanel              **chanels;
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

typedef struct          s_server_infos
{
  struct protoent       *pe;
  int                   fd;
  struct sockaddr_in    s_in;
  int                   port;
  struct pollfd         *clients;
  void                  *pfuncs;
  t_chanel              *chanels;
  t_client_infos        *all_cli;
  t_circular_buf        *cbuf;
  char                  *input;
}                       t_server_infos;

typedef struct          s_end_prg
{
  struct pollfd         *pollfds;
  t_circular_buf        *cbuf;
}                       t_end_prg;

extern t_end_prg        g_end_prg;

/*
** utils functions
*/
void    *vmalloc(size_t size);
BOOL    is_number(char *number);

/*
** server utiles
*/
size_t  count_pollfds(struct pollfd *fds);
int     tab_len(char **tab);
int     xasprintf(char **strp, const char *fmt, ...);
BOOL    create_socket(t_server_infos *);
BOOL    server_listen(t_server_infos *);
BOOL    server_accept(t_server_infos *, t_client_infos *);
void    data_client_receive(t_server_infos *, t_client_infos *);
BOOL    send_str_to_client(int client_fd, const char *msg);
BOOL    exec_command(char *command,
                     t_server_infos *serv,
                     t_client_infos *cli,
                     char **result);
/*
** circular buffer
*/
t_circular_buf  *create_circular_buf(void);
void            init_circular_buf(t_circular_buf *);
BOOL            add_in_cbuf(t_circular_buf **cbuf,
                            struct pollfd *pollfd,
                            t_client_infos *cli,
                            char *result);
BOOL            use_cbuf(t_circular_buf **cbuf,
                         t_server_infos *serv);

/*
** malloc memory verification
*/
void    *vmalloc(size_t size);
void    epure_str(char *str, int str_len);
char    **split_str(char *str, int delim);
void    remove_crlf(char *str);

/*
** chanels
*/
void            add_new_chanel(const char *chanel_name,
                               t_server_infos *serv,
                               t_client_infos *cli);
t_chanel        *chanel_exist(const char *chanel_name,
                              t_server_infos *serv);
void            add_cli_to_chanel(const char *chanel_name,
                                  t_server_infos *serv,
                                  t_client_infos *cli);
void            remove_cli_from_chanel(const char *chanel_name,
                                       t_server_infos *serv,
                                       t_client_infos *cli);
void            remove_cli_from_his_chanels(t_client_infos *cli);
void            send_msg_to_chanel(t_chanel *chan,
                                   char *msg,
                                   t_client_infos *cli);

#endif /* !SERVER_H_ */
