##
## white_rabbit.c for  in /Users/pichar_v/Documents/tek2/cpp_d01/ex00/
##
## Made by Valentin Pichard
## Login   <pichar_v@epitech.eu>
##
## Started on  Wed Jan  4 09:07:13 2017 Valentin Pichard
## Last update Wed May 31 18:37:29 2017 Pierre-Emmanuel Jacquier
##

CC = gcc

RM = rm -rf

TARGET = client

CFLAGS	= -Wall -Wextra -g

SRC	= main.c \
			utils.c \
			init.c \
			windows.c

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
