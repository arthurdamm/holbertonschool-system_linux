CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic

SRC0 = 4-server.c
OBJ0 = $(SRC0:.c=.o)
NAME0 = todo_api_0

.PHONY: all clean oclean flcean re

all: $(OBJ0)
	$(CC) $(OBJ0) -o $(NAME0)
clean:
	$(RM) *~ $(NAME0)

oclean:
	$(RM) $(OBJ0)

fclean: clean oclean

re: oclean all

todo_api_0: http.h $(OBJ0)
	$(CC) $(OBJ0) -o $(NAME0)
