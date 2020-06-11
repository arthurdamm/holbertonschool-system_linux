C= gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu99 -g

SRC0 = strace_0.c
OBJ0 = $(SRC0:.c=.o)
NAME0 = strace_0

SRC1 = strace_1.c
OBJ1 = $(SRC1:.c=.o)
NAME1 = strace_1

SRC2 = strace_2.c
OBJ2 = $(SRC2:.c=.o)
NAME2 = strace_2

SRC3 = strace_3.c
OBJ3 = $(SRC3:.c=.o)
NAME3 = strace_3

SRC4 = strace_4.c
OBJ4 = $(SRC4:.c=.o)
NAME4 = strace_4

.PHONY: all clean oclean flcean re

all: $(OBJ0) $(OBJ1)
	$(CC) $(OBJ0) -o $(NAME0)
	$(CC) $(OBJ1) -o $(NAME1)
	$(CC) $(OBJ2) -o $(NAME2)
	$(CC) $(OBJ2) -o $(NAME3)
	$(CC) $(OBJ2) -o $(NAME4)

clean:
	$(RM) *~ $(NAME0)
	$(RM) *~ $(NAME1)
	$(RM) *~ $(NAME2)
	$(RM) *~ $(NAME3)
	$(RM) *~ $(NAME4)

oclean:
	$(RM) $(OBJ0)
	$(RM) $(OBJ1)
	$(RM) $(OBJ2)
	$(RM) $(OBJ3)
	$(RM) $(OBJ4)

fclean: clean oclean

re: oclean all

strace_0: strace.h $(OBJ0)
	$(CC) $(OBJ0) -o $(NAME0)

strace_1: strace.h $(OBJ1)
	$(CC) $(OBJ1) -o $(NAME1)

strace_2: strace.h $(OBJ2)
	$(CC) $(OBJ2) -o $(NAME2)

strace_3: strace.h $(OBJ3)
	$(CC) $(OBJ3) -o $(NAME3)

strace_4: strace.h $(OBJ4)
	$(CC) $(OBJ4) -o $(NAME4)
