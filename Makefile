##
## white_rabbit.c for  in /Users/pichar_v/Documents/tek2/cpp_d01/ex00/
##
## Made by Valentin Pichard
## Login   <pichar_v@epitech.eu>
##
## Started on  Wed Jan  4 09:07:13 2017 Valentin Pichard
## Last update Wed Jan  4 23:15:35 2017 Valentin Pichard
##

all:
	make -C i_client
	make -C i_server

clean:
	make clean -C i_client
	make clean -C i_server

fclean:
	make fclean -C i_client
	make fclean -C i_server

re: clean fclean all

.PHONY: all clean fclean re
