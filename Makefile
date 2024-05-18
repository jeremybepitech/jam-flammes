##
## EPITECH PROJECT, 2024
## CNA
## File description:
## Makefile
##

CFLAGS	=	-Wall -Werror -lm
NAME = fireFreund
SRC = *.cpp

all:	$(NAME)

$(NAME):	$(SRC)
	g++ $(CFLAGS) -o $(NAME) $(SRC) -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -f $(NAME)

fclean:	clean
	rm -f *.o

re: fclean all