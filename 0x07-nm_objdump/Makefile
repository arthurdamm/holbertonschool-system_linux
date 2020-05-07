CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu90 -g

SRC0 = hnm.c utils.c endian.c endian2.c elf1.c print_sections_1.c print_sections_2.c print_symbols1.c print_symbols2.c print_symbols3.c
OBJ0 = $(SRC0:.c=.o)
NAME0 = hnm

.PHONY: all clean oclean flcean re

all: $(OBJ0)
	$(CC) $(OBJ0) -o $(NAME0)
clean:
	$(RM) *~ $(NAME0)

oclean:
	$(RM) $(OBJ0)

fclean: clean oclean

re: oclean all

hnm: hreadelf.h $(OBJ0)
	$(CC) $(OBJ0) -o $(NAME0)
