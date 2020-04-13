#include "hreadelf.h"

#define TITLE_SYMBOL_64 \
	"\nSymbol table '%s' contains %lu entries:\n" \
	"   Num:    Value          Size Type    Bind   Vis      Ndx Name\n"

#define TITLE_SYMBOL_32 \
	"\nSymbol table '%s' contains %lu entries:\n" \
	"   Num:    Value          Size Type    Bind   Vis      Ndx Name\n"

#define FORMAT_SYMBOL_64 \
	"   %3lu: %16.16lx %5lu %-7s %-6s %-7s %4s %s\n"

/**
 * print_symbol_table - prints all the symbol table stuff
 * @elf_header: address of elf header struct
 * @fd: the file descriptor of our ELF file
 * Return: 0 on success else exit_status
 */
int print_symbol_table(elf_t *elf_header, int fd)
{
	char *string_table, *sym_string_table;
	size_t i;

	if (!EGET(e_shnum))
	{
		printf("\nThere are no section headers in this file.\n");
		return (0);
	}
	read_section_headers(elf_header, fd);
	for (i = 0; i < EGET(e_shnum); i++)
		switch_all_endian_section(elf_header, i);
	for (i = 0; i < EGET(e_phnum); i++)
		switch_all_endian_symbol(elf_header, i);
	string_table = read_string_table(elf_header, fd);
	for (i = 0; i < EGET(e_shnum); i++)
	{
		if (SGET(i, sh_type) == SHT_DYNSYM ||
			SGET(i, sh_type) == SHT_SYMTAB)
		{
			read_symbol_table(elf_header, fd, i);
			sym_string_table = read_symbol_string_table(elf_header, fd, i + 1);
			if (IS_64)
			{
				print_symbol_table64(elf_header, string_table, sym_string_table, fd, i);
				free(elf_header->y64);
				elf_header->y64 = NULL;
				free(sym_string_table);
			}
			else
			{
				free(elf_header->y32);
				elf_header->y32 = NULL;
				free(sym_string_table);
			}
		}
	}
	
	/* if (IS_32(elf_header->e64))
		print_symbol_table32(elf_header, string_table, fd);
	else
		print_symbol_table64(elf_header, string_table, fd); */

	free(string_table);
	return (0);
}

/**
 * print_symbol_table32 - prints 32 bit program headers
 * @elf_header: address of elf header struct
 * @string_table: the string table program
 * @fd: file descriptor of ELF file
 */
void print_symbol_table32(elf_t *elf_header, char *string_table, int fd, int section)
{
	size_t i = 0;

	/* printf(TITLE_SYMBOL_32); */
	for (i = 0; i < EGET(e_phnum); i++)
	{
	
	}
	(void)fd;
	(void)string_table;
	(void)section;
}

/**
 * print_program_headers64 - prints 64 bit program headers
 * @elf_header: address of elf header struct
 * @string_table: the string table program
 * @fd: file descriptor of ELF file
 */
void print_symbol_table64(elf_t *elf_header, char *string_table, char *sym_string_table,
	int fd, int section)
{
	size_t i = 0;
	size_t size = SGET(section, sh_size) / SGET(section, sh_entsize);

	printf(TITLE_SYMBOL_64, string_table + SGET(section, sh_name), size);
	for (i = 0; i < size; i++)
	{
		printf(FORMAT_SYMBOL_64, i,
			YGET(i, st_value),
			YGET(i, st_size),
			get_sym_type(elf_header, i),
			get_sym_bind(elf_header, i),
			"ST_OTHER",
			"NDX",
			sym_string_table + YGET(i, st_name));
	}
	(void)string_table;
	(void)fd;
}

/**
 * read_symbol_table - reads the symbol headers into data
 * @elf_header: the internal header
 * @fd: file descriptor to read
 */
void read_symbol_table(elf_t *elf_header, int fd, int i)
{
	size_t r;
	char *headers;
	size_t read_size = SGET(i, sh_size);

	headers = calloc(1, read_size);
	if (!headers)
		exit(1);
	lseek(fd, SGET(i, sh_offset), SEEK_SET);
	r = read(fd, headers, read_size);
	if (r < read_size)
	{
		fprintf(stderr, "Symbol read failed.\n");
		exit(1); /* TODO */
	}		
	if (IS_32(elf_header->e64))
		elf_header->y32 = (void *)headers;
	else
		elf_header->y64 = (void *)headers;
}

/**
 * read_symbol_string_table - reads the string table
 * @elf_header: the internal header
 * @fd: file descriptor to read
 * Return: pointer to beginning of table
 */
char *read_symbol_string_table(elf_t *elf_header, int fd, int i)
{
	char *str;

	str = calloc(1, SGET(i, sh_size));
	if (!str)
		exit(1);

	lseek(fd, SGET(i, sh_offset), SEEK_SET);
	read(fd, str, SGET(i, sh_size));
	return (str);
}

char *get_sym_type(elf_t *elf_header, size_t i)
{
	switch (YGET(i, st_info) & 0xf)
	{
		case STT_NOTYPE: return ("NOTYPE");
		case STT_OBJECT: return ("OBJECT");
		case STT_FUNC: return ("FUNC");
		case STT_SECTION: return ("SECTION");
		case STT_FILE: return ("FILE");
		case STT_COMMON: return ("COMMON");
		case STT_TLS: return ("TLS");
		case STT_NUM: return ("NUM");
		case STT_LOOS: return ("LOOS");
		case STT_HIOS: return ("HIOS");
		case STT_LOPROC: return ("LOPROC");
		case STT_HIPROC: return ("HIPROC");
		default: return ("UNKNOWN");
	}
}

char *get_sym_bind(elf_t *elf_header, size_t i)
{
	switch (YGET(i, st_info) >> 4)
	{
		case STB_LOCAL: return ("LOCAL");
		case STB_GLOBAL: return ("GLOBAL");
		case STB_WEAK: return ("WEAK");
		case STB_NUM: return ("NUM");
		case STB_LOOS: return ("LOOS");
		case STB_HIOS: return ("HIOS");
		case STB_LOPROC: return ("LOPROC");
		case STB_HIPROC: return ("HIPROC");
		default: return ("UNKNWN");
	}
}
