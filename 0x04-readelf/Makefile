CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu89 -g

SRC0 = 0-hreadelf.c utils.c endian.c print_header1.c print_header2.c print_header3.c print_header4.c elf1.c
OBJ0 = $(SRC0:.c=.o)
NAME0 = 0-hreadelf

SRC1 = 1-hreadelf.c utils.c endian.c print_sections_1.c print_sections_2.c
OBJ1 = $(SRC1:.c=.o)
NAME1 = 1-hreadelf

SRC2 = 2-hreadelf.c utils.c endian.c endian2.c elf1.c print_programs1.c print_programs2.c print_sections_1.c print_sections_2.c
OBJ2 = $(SRC2:.c=.o)
NAME2 = 2-hreadelf

SRC100 = 100-hreadelf.c utils.c endian.c endian2.c elf1.c print_sections_1.c print_sections_2.c print_symbols1.c print_symbols2.c print_symbols3.c
OBJ100 = $(SRC100:.c=.o)
NAME100 = 100-hreadelf

.PHONY: all clean oclean flcean re

all: $(OBJ)
	$(CC) $(OBJ) -o $(NAME)
	$(CC) $(OBJ0) -o $(NAME0)
	$(CC) $(OBJ1) -o $(NAME1)
	$(CC) $(OBJ2) -o $(NAME2)
	$(CC) $(OBJ100) -o $(NAME100)
clean:
	$(RM) *~ $(NAME)
	$(RM) *~ $(NAME0)
	$(RM) *~ $(NAME1)
	$(RM) *~ $(NAME2)
	$(RM) *~ $(NAME100)

oclean:
	$(RM) $(OBJ)
	$(RM) $(OBJ0)
	$(RM) $(OBJ1)
	$(RM) $(OBJ2)
	$(RM) $(OBJ100)

fclean: clean oclean

re: oclean all

0-hreadelf: hreadelf.h $(OBJ0)
	$(CC) $(OBJ0) -o $(NAME0)

1-hreadelf: hreadelf.h $(OBJ1)
	$(CC) $(OBJ1) -o $(NAME1)

2-hreadelf: hreadelf.h $(OBJ2)
	$(CC) $(OBJ2) -o $(NAME2)

100-hreadelf: hreadelf.h $(OBJ100)
	$(CC) $(OBJ100) -o $(NAME100)
