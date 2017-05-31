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
	make -C client
	make -C server

clean:
	make clean -C client
	make clean -C server

fclean:
	make fclean -C client
	make fclean -C server

re: clean fclean all

.PHONY: all clean fclean re
