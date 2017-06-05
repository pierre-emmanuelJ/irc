/*
** command_parsing.c for  in /home/jacqui_p/rendu/PSU_2016_myftp/
**
** Made by Pierre-Emmanuel Jacquier
** Login   <jacqui_p@epitech.eu>
**
** Started on  Sun May 21 17:51:36 2017 Pierre-Emmanuel Jacquier
** Last update Mon Jun  5 22:13:39 2017 Pierre-Emmanuel Jacquier
*/

#include "server.h"

void    remove_crlf(char *str)
{
  int   str_len;

  str_len = strlen(str);
  if (str[str_len - 1] == '\n' && str[str_len - 2] == '\r')
    str[str_len - 2] = 0;
  else if (str[str_len - 1] == '\n')
    str[str_len - 1] = 0;
}

void    epure_str(char *str, int str_len)
{
  int   i;
  int   j;
  char  newstr[str_len];

  i = 0;
  j = 0;
  while (str[i] == ' ' || str[i] == '\t')
    i++;
  while (str[i])
  {
    if (str[i] != ' ' && str[i] != '\t')
      newstr[j++] = str[i++];
    else if (str[i] == ' ' || str[i] == '\t')
    {
      while (str[i] == ' ' || str[i] == '\t')
        i++;
      if (str[i] != '\0')
        newstr[j++] = ' ';
    }
  }
  newstr[j] = 0;
  bzero(str, str_len);
  memmove(str, newstr, strlen(newstr));
}

int     count_ocurence(const char *str, int delim)
{
  int   i;
  char  *ocurence;

  i = 0;
  if (!(ocurence = strchr(str, delim)))
    return (i);
  while (ocurence)
  {
    ocurence++;
    ocurence = strchr(ocurence, delim);
    i++;
  }
  return (i);
}

char    **split_str(char *str, int delim)
{
  int   word;
  char  **str_array;
  int   i;

  i = 1;
  word = count_ocurence(str, delim) + 1;
  if (!(str_array = malloc(sizeof(char *) * (word + 1))))
    exit(EXIT_FAILURE);
  str_array[0] = str;
  while (i < word)
  {
    str_array[i] = strchr(str_array[i - 1], delim);
    *str_array[i] = 0;
    str_array[i]++;
    i++;
  }
  str_array[word] = NULL;
  return (str_array);
}
