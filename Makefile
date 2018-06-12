##
## EPITECH PROJECT, 2018
## djikstra
## File description:
## Makefile for djikstra.
##

SRC	=	src/main.c	\
		src/fichier.c	\
		src/fonctions.c	\
		src/search.c	\
		src/solve.c

OBJ	=	$(SRC:.c=.o)

CPPFLAGS+=	-I include

CFLAGS	+=	-Wall -Wextra

LDFLAGS	=	-lSDL -lSDL_ttf -lSDL_gfx

NAME	=	djikstra

all	:	$(NAME)

$(NAME)	:	$(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean	:
		$(RM) $(OBJ)

fclean	:	clean
		$(RM) $(NAME)

re	:	fclean all

.PHONY	:	all clean fclean re
