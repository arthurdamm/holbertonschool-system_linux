CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu90 -ggdb3

SRC0 = 4-server.c
OBJ0 = $(SRC0:.c=.o)
NAME0 = todo_api_0

SRC1 = 5-server.c
OBJ1 = $(SRC1:.c=.o)
NAME1 = todo_api_1

SRC2 = 6-headers.c util.c
OBJ2 = $(SRC2:.c=.o)
NAME2 = todo_api_2

.PHONY: all clean oclean flcean re

all: $(OBJ0) $(OBJ1) (OBJ2)
	$(CC) $(OBJ0) -o $(NAME0)
	$(CC) $(OBJ1) -o $(NAME1)
	$(CC) $(OBJ2) -o $(NAME2)
clean:
	$(RM) *~ $(NAME0)
	$(RM) *~ $(NAME1)
	$(RM) *~ $(NAME2)

oclean:
	$(RM) $(OBJ0)
	$(RM) $(OBJ1)
	$(RM) $(OBJ2)

fclean: clean oclean

re: oclean all

todo_api_0: http.h $(OBJ0)
	$(CC) $(OBJ0) -o $(NAME0)

todo_api_1: http.h $(OBJ1)
	$(CC) $(OBJ1) -o $(NAME1)

todo_api_2: http.h $(OBJ2)
	$(CC) $(OBJ2) -o $(NAME2)
