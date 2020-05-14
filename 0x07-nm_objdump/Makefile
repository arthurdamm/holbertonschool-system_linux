CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu90 -g

SRC0 = hnm.c utils.c endian.c endian2.c elf1.c print_sections_1.c print_sections_2.c print_symbols1.c print_symbols2.c print_symbols3.c
OBJ0 = $(SRC0:.c=.o)
NAME0 = hnm

SRC1 = hobjdump.c utils.c endian.c endian2.c elf1.c print_sections_1.c print_sections_2.c print_symbols2.c hobjdump_1.c hobjdump_2.c
OBJ1 = $(SRC1:.c=.o)
NAME1 = hobjdump

.PHONY: all clean oclean flcean re

all: $(OBJ0) $(OBJ1)
	$(CC) $(OBJ0) -o $(NAME0)
	$(CC) $(OBJ1) -o $(NAME1)
clean:
	$(RM) *~ $(NAME0)
	$(RM) *~ $(NAME1)

oclean:
	$(RM) $(OBJ0)
	$(RM) $(OBJ1)

fclean: clean oclean

re: oclean all

hnm: hreadelf.h $(OBJ0)
	$(CC) $(OBJ0) -o $(NAME0)

hobjdump: hreadelf.h $(OBJ1)
	$(CC) $(OBJ1) -o $(NAME1)
