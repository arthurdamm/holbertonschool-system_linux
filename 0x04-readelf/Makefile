CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic

SRC0 = 0-hreadelf.c utils.c endian.c print_header1.c print_header2.c print_header3.c print_header4.c
OBJ0 = $(SRC0:.c=.o)
NAME0 = 0-hreadelf

SRC1 = 1-hreadelf.c utils.c endian.c print_sections_1.c
OBJ1 = $(SRC1:.c=.o)
NAME1 = 1-hreadelf

.PHONY: all clean oclean flcean re

all: $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean:
	$(RM) *~ $(NAME)
	$(RM) *~ $(NAME0)
	$(RM) *~ $(NAME1)

oclean:
	$(RM) $(OBJ)
	$(RM) $(OBJ0)
	$(RM) $(OBJ1)

fclean: clean oclean

re: oclean all

0-hreadelf: hreadelf.h $(OBJ0)
	$(CC) $(OBJ0) -o $(NAME0)

1-hreadelf: hreadelf.h $(OBJ1)
	$(CC) $(OBJ1) -o $(NAME1)
