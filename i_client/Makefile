##
## white_rabbit.c for  in /Users/pichar_v/Documents/tek2/cpp_d01/ex00/
##
## Made by Valentin Pichard
## Login   <pichar_v@epitech.eu>
##
## Started on  Wed Jan  4 09:07:13 2017 Valentin Pichard
## Last update Sun Jun 11 01:37:18 2017 Pierre-Emmanuel Jacquier
##

CC = gcc

RM = rm -rf

TARGET = client

CFLAGS	= -Wall -Wextra -g -D _GNU_SOURCE

SRC	= main.c \
			utils.c \
			init.c \
			windows.c \
			keys.c \
			init_linked_list.c \
			custom_functions.c \
			irc_join.c \
			irc_list.c \
			irc_msg.c \
			irc_names.c \
			irc_nickname.c \
			irc_part.c \
			irc_server.c \
			irc_users.c \
			irc_utils.c \
			errors.c \
			refresh.c \
			irc_tools.c \
			init_connection.c \
			errors_extend.c

OBJS = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET) -lncurses
	mv $(TARGET) ../$(TARGET)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) ../$(TARGET)

re: clean fclean all

.PHONY: all clean fclean re
