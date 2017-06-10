/*
** white_rabbit.c for  in /Users/pichar_v/Documents/tek2/cpp_d01/ex00/
**
** Made by Valentin Pichard
** Login   <pichar_v@epitech.eu>
**
** Started on  Wed Jan  4 09:07:13 2017 Valentin Pichard
** Last update Wed Jan  4 23:15:35 2017 Valentin Pichard
*/

#include "client.h"

static t_command      *add_node(const char *command, funcptr ptr)
{
  t_command   *current;

  current = (t_command *)custom_malloc(sizeof(*current));
  asprintf(&current->command, "%s", command);
  current->ptr = ptr;
  current->next = NULL;
  return (current);
}

static t_command     *init_complementary_commands(t_command *current)
{
  current->next = add_node("/names", &command_names);
  current = current->next;
  current->next = add_node("/msg", &command_msg);
  current = current->next;
  current->next = add_node("/accept_file", &command_accept);
  current = current->next;
  current->next = add_node("/help", &command_help);
  current = current->next;
  current->next = add_node("/quit", &command_quit);
  return (current->next);
}

t_command             *lets_init_linkedlist(void)
{
  t_command   *lexer;
  t_command   *current;

  lexer = add_node("/server", &command_server);
  current = lexer;
  current->next = add_node("/nick", &command_nick);
  current = current->next;
  current->next = add_node("/list", &command_list);
  current = current->next;
  current->next = add_node("/join", &command_join);
  current = current->next;
  current->next = add_node("/part", &command_part);
  current = current->next;
  current->next = add_node("/users", &command_users);
  current = current->next;
  current = init_complementary_commands(current);
  return (lexer);
}