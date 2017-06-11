/*
** commands_input.c for  in /home/jacqui_p/rendu/PSU_2016_myirc/i_server/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Sun Jun 11 20:09:47 2017 Pierre-Emmanuel Jacquier
** Last update Sun Jun 11 20:23:08 2017 Pierre-Emmanuel Jacquier
*/

#include "server.h"
#include "pfunctions_commands.h"

static void    remove_client(struct pollfd *fds,
                             t_client_infos *cli,
                             int index)
{
  remove_cli_from_his_chanels(&cli[index]);
  close(fds[index].fd);
  fds[index].fd = -1;
  memset(&cli[index], 0, sizeof(t_client_infos));
  cli[index].client_fd = -1;
  if (cli[index].chanels)
    free(cli[index].chanels);
  free(cli[index].nickname);
}

static char       *get_full_msg(char *priv_msg)
{
  char     *tmp;
  char     *msg;

  tmp = priv_msg;
  tmp = strchr(tmp, ' ');
  while (*tmp && *tmp == ' ')
    tmp++;
  tmp = strchr(tmp, ' ');
  while (*tmp && *tmp == ' ')
    tmp++;
  xasprintf(&msg, "%s", tmp);
  free(priv_msg);
  return (msg);
}

BOOL      exec_command(char *command,
                       t_server_infos *serv,
                       t_client_infos *cli,
                       char **result)
{
  char    **argv;
  char    *priv_msg;

  (void)result;
  if (!strncmp(command, "PRIVMSG", 7))
    xasprintf(&priv_msg, "%s", command);
  argv = split_str(command, ' ');
  if (!strncmp(command, "PRIVMSG", 7))
    {
      if (tab_len(argv) >= 3)
        argv[2] = get_full_msg(priv_msg);
    }
  call_function((t_pf *)serv->pfuncs, argv, serv, cli);
  free(argv);
  return (TRUE);
}

static void        exec_lines(t_server_infos *serv,
                       struct pollfd  *pollfd,
                       t_client_infos *cli)
{
  char      **lines;
  char      **tmp;

  lines = split_str(serv->input, '\n');
  tmp = lines;
  while (*lines)
  {
    remove_crlf(*lines);
    printf("commande : %s\n", *lines);
    fflush(stdout);
    epure_str(*lines, strlen(*lines));
    add_in_cbuf(&serv->cbuf, pollfd, cli, *lines);
    lines++;
  }
  free(tmp);
}

void        data_client_receive(t_server_infos *serv,
                                t_client_infos *cli)
{
  int       i;
  char      input[1024];
  int       len;

  i = 1;
  while (i < MAX_CLI && serv->clients[i].fd != 0)
  {
    if (serv->clients[i].fd > 0 && serv->clients[i].revents == POLLIN)
      {
        if (!(len = read(serv->clients[i].fd, input, 1024)))
        {
          remove_client(serv->clients, cli, i++);
          continue;
        }
        input[len] = 0;
        remove_crlf(input);
        if (!strcmp(input, ""));
        else
        {
          serv->input = input;
          exec_lines(serv, &serv->clients[i], &cli[i]);
        }
      }
    i++;
  }
}
