##
## Makefile for  in /home/jacqui_p/rendu/PSU_2016_myirc/
##
## Made by Pierre-Emmanuel Jacquier
## Login   <jacqui_p@epitech.eu>
##
## Started on  Wed May 24 14:00:55 2017 Pierre-Emmanuel Jacquier
## Last update Mon Jun  5 18:42:12 2017 Pierre-Emmanuel Jacquier
##

CC = gcc

RM = rm -rf

TARGET = server

CFLAGS	= -Wall -Wextra -g

SRC	= main.c \
      server.c \
      circular_buf.c

OBJS = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET)
	mv $(TARGET) ../$(TARGET)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) ../$(TARGET)

re: clean fclean all

.PHONY: all clean fclean re
