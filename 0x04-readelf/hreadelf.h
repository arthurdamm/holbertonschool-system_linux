#ifndef HREADELF_H
#define HREADELF_H

#include <elf.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define USAGE "0-hreadelf elf_filename\n"
#define MYNAME "0-hreadelf"

#define ERR_PREFIX MYNAME ": Error: "
#define ERR_NO_ENTRY ERR_PREFIX \
	"'%s': No such file\n"
#define ERR_NO_ACCESS ERR_PREFIX \
	"Input file '%s' is not readable.\n"
#define ERR_NOT_MAGIC ERR_PREFIX \
	"Not an ELF file - it has the wrong magic bytes at the start\n"

#define IS_32(x) ((x).e_ident[EI_CLASS] == ELFCLASS32)
#define EGET(x) \
	(IS_32(elf_header->e64) ? elf_header->e32.x : elf_header->e64.x)

/**
 * struct Elf - stores 32/64 structs and other data
 * @e64: the 64 bit struct
 * @e32: the 32 bit struct
 */
typedef struct Elf
{
	Elf64_Ehdr e64;
	Elf32_Ehdr e32;
} elf_t;

/* utils.c */
int open_file(char *name, int silent);
int check_elf(char *elf_header);

/* print_header_1.c */
int print_header(elf_t *elf_header);
int print_magic(Elf64_Ehdr *elf_header);
int print_class(Elf64_Ehdr *elf_header);
int print_data(Elf64_Ehdr *elf_header);
int print_version(Elf64_Ehdr *elf_header);

/* print_header_2.c */
int print_osabi(Elf64_Ehdr *elf_header);
int print_osabi_more(Elf64_Ehdr *elf_header);
int print_abiversion(Elf64_Ehdr *elf_header);
int print_type(Elf64_Ehdr *elf_header);
int print_entry(Elf64_Ehdr *elf_header);

/* print_header_3.c */
int print_machine(Elf64_Ehdr *elf_header);
int print_e_version(Elf64_Ehdr *elf_header);
int print_program_headers(elf_t *elf_header);
char *get_machine(Elf64_Ehdr *elf_header);
char *get_machine2(Elf64_Ehdr *elf_header);

/* print_header_4.c */
int print_section_headers(elf_t *elf_header);
int print_flags(elf_t *elf_header);

#endif
