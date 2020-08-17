CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu90 -ggdb3

SRC0 = 4-request.c server.c util.c
OBJ0 = $(SRC0:.c=.o)
NAME0 = todo_api_0

SRC1 = 5-queries.c server.c util.c
OBJ1 = $(SRC1:.c=.o)
NAME1 = todo_api_1

SRC2 = 6-headers.c server.c util.c
OBJ2 = $(SRC2:.c=.o)
NAME2 = todo_api_2

SRC3 = 7-body.c server.c util.c
OBJ3 = $(SRC3:.c=.o)
NAME3 = todo_api_3

SRC4 = 8-post_todo.c server.c util.c
OBJ4 = $(SRC4:.c=.o)
NAME4 = todo_api_4

SRC5 = 9-get_all_todos.c server.c util.c
OBJ5 = $(SRC5:.c=.o)
NAME5 = todo_api_5

SRC6 = 10-get_a_todo.c server.c util.c
OBJ6 = $(SRC6:.c=.o)
NAME6 = todo_api_6

SRC7 = 11-delete_a_todo.c server.c util.c
OBJ7 = $(SRC7:.c=.o)
NAME7 = todo_api_7

.PHONY: all clean oclean flcean re

all: $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4) $(OBJ5) $(OBJ6) $(OBJ7)
	$(CC) $(OBJ0) -o $(NAME0)
	$(CC) $(OBJ1) -o $(NAME1)
	$(CC) $(OBJ2) -o $(NAME2)
	$(CC) $(OBJ3) -o $(NAME3)
	$(CC) $(OBJ4) -o $(NAME4)
	$(CC) $(OBJ5) -o $(NAME5)
	$(CC) $(OBJ5) -o $(NAME6)
	$(CC) $(OBJ5) -o $(NAME7)

clean:
	$(RM) *~ $(NAME0)
	$(RM) *~ $(NAME1)
	$(RM) *~ $(NAME2)
	$(RM) *~ $(NAME3)
	$(RM) *~ $(NAME4)
	$(RM) *~ $(NAME5)
	$(RM) *~ $(NAME6)
	$(RM) *~ $(NAME7)

oclean:
	$(RM) $(OBJ0)
	$(RM) $(OBJ1)
	$(RM) $(OBJ2)
	$(RM) $(OBJ3)
	$(RM) $(OBJ4)
	$(RM) $(OBJ5)
	$(RM) $(OBJ6)
	$(RM) $(OBJ7)

fclean: clean oclean

re: oclean all

todo_api_0: http.h $(OBJ0)
	$(CC) $(OBJ0) -o $(NAME0)

todo_api_1: http.h $(OBJ1)
	$(CC) $(OBJ1) -o $(NAME1)

todo_api_2: http.h $(OBJ2)
	$(CC) $(OBJ2) -o $(NAME2)

todo_api_3: http.h $(OBJ3)
	$(CC) $(OBJ3) -o $(NAME3)

todo_api_4: http.h $(OBJ4)
	$(CC) $(OBJ4) -o $(NAME4)

todo_api_5: http.h $(OBJ5)
	$(CC) $(OBJ5) -o $(NAME5)

todo_api_6: http.h $(OBJ6)
	$(CC) $(OBJ6) -o $(NAME6)

todo_api_7: http.h $(OBJ7)
	$(CC) $(OBJ7) -o $(NAME7)
