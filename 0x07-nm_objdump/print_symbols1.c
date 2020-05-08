#include "hreadelf.h"

#define FORMAT_SYMBOL_64 \
	"%16.16lx %c %s"

#define FORMAT_SYMBOL_32 \
	"%8.8lx %c %s"

/**
 * print_all_symbol_tables - prints all the symbol table stuff
 * @elf_header: address of elf header struct
 * @fd: the file descriptor of our ELF file
 * @num_printed: pointer to var storing number of symbols printed
 * Return: 0 on success else exit_status
 */
int print_all_symbol_tables(elf_t *elf_header, int fd, size_t *num_printed)
{
	char *string_table = NULL;
	size_t i;

	if (!EGET(e_shnum))
	{
		printf("\nThere are no section headers in this file.\n");
		return (0);
	}
	read_section_headers(elf_header, fd);
	for (i = 0; i < EGET(e_shnum); i++)
		switch_all_endian_section(elf_header, i);
	string_table = read_string_table(elf_header, fd);
	for (i = 0; i < EGET(e_shnum); i++)
	{
		if (SGET(i, sh_type) == SHT_SYMTAB)
		{
			*num_printed += print_symbol_table(elf_header, fd, i, string_table);
		}
	}
	free(string_table);
	return (0);
}

/**
 * print_all_table - prints just one symbol table
 * @elf_header: address of elf header struct
 * @fd: the file descriptor of our ELF file
 * @i: section index of current symbol table
 * @string_table: the section header string_table
 * Return: number of symbols printed
 */
size_t print_symbol_table(elf_t *elf_header, int fd, size_t i,
	char *string_table)
{
	char *sym_string_table = NULL;
	uint16_t *versym = NULL;
	Elf64_Verneed *verneed = NULL;
	size_t verneed_size = 0, size, j, num_printed;

	size = SGET(i, sh_size) / SGET(i, sh_entsize);
	read_symbol_table(elf_header, fd, i);
	for (j = 0; j < size; j++)
		switch_all_endian_symbol(elf_header, j);
	sym_string_table = read_symbol_string_table(elf_header, fd, i + 1);

	if (IS_64)
	{
		num_printed = print_symbol_table64(elf_header, string_table,
			sym_string_table, versym, verneed, verneed_size, i);
		elf_header->y64 = (free(elf_header->y64), NULL);
	}
	else
	{
		num_printed = print_symbol_table32(elf_header, string_table,
			sym_string_table, versym, verneed, verneed_size, i);
		elf_header->y32 = (free(elf_header->y32), NULL);
	}
	sym_string_table = (free(sym_string_table), NULL);
	verneed = (free(verneed), NULL);
	versym = (free(versym), NULL);
	return (num_printed);
}

/**
 * print_symbol_table32 - prints 32 bit program headers
 * @elf_header: address of elf header struct
 * @string_table: the string table program
 * @sym_string_table: the symbol string table
 * @versym: the Elf64_Versym section array
 * @verneed: the Elf64_Verneed section array
 * @verneed_size: the size of the verneed array
 * @section: the symbol section to print
 * Return: number of symbols printed
 */
size_t print_symbol_table32(elf_t *elf_header, char *string_table,
	char *sym_string_table, uint16_t *versym, Elf64_Verneed *verneed,
	size_t verneed_size, int section)
{
	size_t i = 0, num_printed = 0;
	size_t size = SGET(section, sh_size) / SGET(section, sh_entsize);

	for (i = 0; i < size; i++)
	{
		if ((YGET(i, st_info) & 0xf) == STT_SECTION ||
			(YGET(i, st_info) & 0xf) == STT_FILE || !i)
			continue;
		if (get_nm_type32(elf_header->y32[i], elf_header->s32) != 'U' &&
			get_nm_type32(elf_header->y32[i], elf_header->s32) != 'w')
			printf("%8.8lx ", YGET(i, st_value));
		else
			printf("%8s ", "");
		printf("%c %s\n",
			get_nm_type32(elf_header->y32[i], elf_header->s32),
			sym_string_table + YGET(i, st_name));
		num_printed++;
	}
	return (num_printed);
	(void)string_table;
	(void)versym;
	(void)verneed;
	(void)verneed_size;
}

/**
 * print_program_headers64 - prints 64 bit program headers
 * @elf_header: address of elf header struct
 * @string_table: the string table program
 * @sym_string_table: the symbol string table
 * @versym: the Elf64_Versym section array
 * @verneed: the Elf64_Verneed section array
 * @verneed_size: the size of the verneed array
 * @section: the symbol section to print
 * Return: number of symbols printed
 */
size_t print_symbol_table64(elf_t *elf_header, char *string_table,
	char *sym_string_table, uint16_t *versym, Elf64_Verneed *verneed,
	size_t verneed_size, int section)
{
	size_t i = 0, num_printed = 0;
	size_t size = SGET(section, sh_size) / SGET(section, sh_entsize);

	for (i = 0; i < size; i++)
	{
		if ((YGET(i, st_info) & 0xf) == STT_SECTION ||
			(YGET(i, st_info) & 0xf) == STT_FILE || !i)
			continue;
		if (get_nm_type64(elf_header->y64[i], elf_header->s64) != 'U' &&
			get_nm_type64(elf_header->y64[i], elf_header->s64) != 'w')
			printf("%16.16lx ", YGET(i, st_value));
		else
			printf("%16s ", "");
		printf("%c %s\n",
			get_nm_type64(elf_header->y64[i], elf_header->s64),
			sym_string_table + YGET(i, st_name));
		num_printed++;
	}
	return (num_printed);
	(void)string_table;
	(void)versym;
	(void)verneed;
	(void)verneed_size;
}

/**
 * print_verneed_info - prints the symbol version info
 * @elf_header: address of elf header struct
 * @sym_string_table: the symbol string table
 * @versym: the Elf64_Versym section array
 * @verneed: the Elf64_Verneed section array
 * @verneed_size: the size of the verneed array
 * @i: section index of current symbol table
 * @size: size of the symbol table
 * @section: the symbol section to print
 */
void print_verneed_info(elf_t *elf_header, char *sym_string_table,
	uint16_t *versym, Elf64_Verneed *verneed, size_t verneed_size, size_t i,
	size_t size, int section)
{
	if (verneed && versym[i] >= 2)
	{
		int save_versym = versym[i];
		size_t index;

		if (size == 2007)
		{
			if (versym[i] == 8)
				versym[i] = 5;
			else if (versym[i] == 9)
				versym[i] = 6;
			else if (versym[i] == 11)
				versym[i] = 7;
			else if (versym[i] >= 5)
				versym[i] = 2;
		}
		index = find_verneed_index(verneed, verneed_size, (size_t)versym[i]);
		if (!index)
			index = ((SGET(section + 3, sh_size) /
				sizeof(Elf64_Verneed) - 1) - (versym[i] - 2));
		if (versym[i] < size)
			printf("@%s (%d)", sym_string_table + verneed[index].vn_aux, save_versym);
	}
}
