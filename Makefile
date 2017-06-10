##
## white_rabbit.c for  in /Users/pichar_v/Documents/tek2/cpp_d01/ex00/
##
## Made by Valentin Pichard
## Login   <pichar_v@epitech.eu>
##
## Started on  Wed Jan  4 09:07:13 2017 Valentin Pichard
## Last update Sun Jun 11 01:37:53 2017 Pierre-Emmanuel Jacquier
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

vgtest: re
	@valgrind  --leak-check=full --show-leak-kinds=all ./server 1234


.PHONY: all clean fclean re
