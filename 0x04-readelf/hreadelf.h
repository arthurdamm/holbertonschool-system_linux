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
#define IS_BE(x) ((x).e_ident[EI_DATA] == ELFDATA2MSB)
#define EGET(x) \
	(IS_32(elf_header->e64) ? elf_header->e32.x : elf_header->e64.x)
#define SGET(i, x) \
	(IS_32(elf_header->e64) ? elf_header->s32[i].x : elf_header->s64[i].x)

/**
 * struct Elf - stores 32/64 structs and other data
 * @e64: the 64 bit struct
 * @e32: the 32 bit struct
 * @s64: the 64 bit struct section array
 * @s32: the 32 bit struct section array
 */
typedef struct Elf
{
	Elf64_Ehdr e64;
	Elf32_Ehdr e32;
	Elf64_Shdr *s64;
	Elf32_Shdr *s32;

} elf_t;

/* utils.c */
int open_file(char *name, int silent);
int check_elf(char *elf_header);
void print_bytes(void *ptr, size_t n);

/* endian.c */
unsigned short switch_endian2(unsigned short n);
unsigned int switch_endian4(unsigned int n);
unsigned long switch_endian8(unsigned long n);
void switch_all_endian(elf_t *elf_header);
void switch_all_endian_section(elf_t *h, size_t i);

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
int print_entry(elf_t *elf_header);

/* print_header_3.c */
int print_machine(Elf64_Ehdr *elf_header);
int print_e_version(elf_t *elf_header);
int print_program_headers(elf_t *elf_header);
char *get_machine(Elf64_Ehdr *elf_header);
char *get_machine2(Elf64_Ehdr *elf_header);

/* print_header_4.c */
int print_section_headers(elf_t *elf_header);
int print_flags(elf_t *elf_header);

/* print_sections_1.c */
int print_section_headers_full(elf_t *elf_header, int fd);
void read_section_headers(elf_t *elf_header, int fd);
char *read_string_table(elf_t *elf_header, int fd);
char *get_section_type(unsigned int sh_type);

/* print_sections_2.c */
void print_section_headers32(elf_t *elf_header, char *string_table);
void print_section_headers64(elf_t *elf_header, char *string_table);
char *get_section_flags(elf_t *elf_header, size_t i);

#endif
