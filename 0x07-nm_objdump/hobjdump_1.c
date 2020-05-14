#include "hreadelf.h"

#define FORMAT_SYMBOL_64 \
	"%16.16lx %c %s"

#define FORMAT_SYMBOL_32 \
	"%8.8lx %c %s"

/**
 * dump_all_sections - objdumps each section
 * @elf_header: address of elf header struct
 * @fd: the file descriptor of our ELF file
 * @num_printed: pointer to var storing number of symbols printed
 * Return: 0 on success else exit_status
 */
int dump_all_sections(elf_t *elf_header, int fd, size_t *num_printed)
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
	print_f_header(elf_header, string_table);
	for (i = 1; i < EGET(e_shnum); i++)
	{
		if (strcmp(string_table + SGET(i, sh_name), ".dynstr") &&
			((!strncmp(string_table + SGET(i, sh_name), ".rel", 4) &&
			!SGET(i, sh_addr))
			|| SGET(i, sh_type) == SHT_SYMTAB || SGET(i, sh_type) == SHT_NOBITS
			|| SGET(i, sh_type) == SHT_STRTAB || !SGET(i, sh_size)))
			continue;
		*num_printed += dump_section(elf_header, fd, i, string_table);
	}
	free(string_table);
	return (0);
}

/**
 * dump_section - dumps just one section
 * @elf_header: address of elf header struct
 * @fd: the file descriptor of our ELF file
 * @i: section index of current symbol table
 * @string_table: the section header string_table
 * Return: number of symbols printed
 */
size_t dump_section(elf_t *elf_header, int fd, size_t i,
	char *string_table)
{
	size_t num_printed = 0, i_off = 0, j, j_max, addr_len;
	unsigned char *data;
	char buf[32] = {0};

	printf("Contents of section %s:\n", string_table + SGET(i, sh_name));
	data = read_data(elf_header, fd, SGET(i, sh_offset), SGET(i, sh_size));
	if (!data)
		return (0);
	addr_len = MAX(4, sprintf(buf, "%lx", SGET(i, sh_addr) + SGET(i, sh_size)));
	for (i_off = 0; i_off < SGET(i, sh_size); i_off += 0x10)
	{
		j_max = MIN(0x10, SGET(i, sh_size) - i_off);
		printf(" %0*lx ", (int)addr_len, SGET(i, sh_addr) + i_off);

		for (j = 0; j < j_max; j++)
			printf("%02x%s", data[i_off + j], !((j + 1) % 4) ? " " : "");
		for (j = j_max; j < 0x10; j++)
			printf("%s%s", "  ", !((j + 1) % 4) ? " " : "");
		printf(" ");
		for (j = 0; j < j_max; j++)
			printf("%c", (data[i_off + j] >= 32 && data[i_off + j] <= 126) ? data[i_off + j] : '.');
		for (j = j_max; j < 0x10; j++)
			printf("%c", ' ');
		printf("\n");
	}
	free(data);
	return (num_printed);
	(void)fd;
}

char *get_file_format(elf_t *elf_header)
{
	static char buf[32];

	*buf = 0;
	sprintf(buf, "elf%d-%s", IS_64 ? 64 : 32,
		IS_BE(elf_header->e64) ? "big" : IS_64 ? "x86-64" : "i386");
	return (buf);
}

void print_f_header(elf_t *elf_header, char *string_table)
{
	unsigned long flags = 0;

	printf("architecture: ");
	if (IS_BE(elf_header->e64))
		printf("UNKNOWN!");
	else if (IS_64)
		printf("i386:x86-64");
	else
		printf("i386");
	
	if (EGET(e_type) == ET_REL)
		flags |= HAS_RELOC;
	else if (EGET(e_type) == ET_EXEC)
		flags |= EXEC_P;
	else if (EGET(e_type) == ET_DYN)
		flags |= DYNAMIC;

	if (EGET(e_phnum) > 0)
		flags |= D_PAGED;
	if (has_section(elf_header, string_table, ".symtab"))
		flags |= HAS_SYMS;
	if (has_section(elf_header, string_table, ".dynsym"))
		flags |= HAS_SYMS;
	if (has_section(elf_header, string_table, ".locals"))
		flags |= HAS_LOCALS;
	if (has_section(elf_header, string_table, ".lineno"))
		flags |= HAS_LINENO;
	if (has_section(elf_header, string_table, ".debug"))
		flags |= HAS_DEBUG;

	printf(", flags 0x%08lx:\n", flags);
	print_f_flags(flags);
	printf("start address 0x%0*lx\n\n", IS_64 ? 16 : 8, EGET(e_entry));
}

int has_section(elf_t *elf_header, char *string_table, char *section_name)
{
	size_t i = 0;

	section_name = strdup(section_name);
	for (i = 1; i < EGET(e_shnum); i++)
		if (!strcmp(string_table + SGET(i, sh_name), section_name))
			return (1);
	return (0);
}

void print_f_flags(unsigned long flags)
{
	int first = 1;

	if (flags & HAS_RELOC)
		first = (printf("%s%s", first ? "" : ", ", "HAS_RELOC"), 0);
	if (flags & EXEC_P	)
		first = (printf("%s%s", first ? "" : ", ", "EXEC_P"), 0);
	if (flags & HAS_LINENO)
		first = (printf("%s%s", first ? "" : ", ", "HAS_LINENO"), 0);
	if (flags & HAS_DEBUG)
		first = (printf("%s%s", first ? "" : ", ", "HAS_DEBUG"), 0);
	if (flags & HAS_SYMS)
		first = (printf("%s%s", first ? "" : ", ", "HAS_SYMS"), 0);
	if (flags & HAS_LOCALS)
		first = (printf("%s%s", first ? "" : ", ", "HAS_LOCALS"), 0);
	if (flags & DYNAMIC	)
		first = (printf("%s%s", first ? "" : ", ", "DYNAMIC"), 0);
	if (flags & WP_TEXT	)
		first = (printf("%s%s", first ? "" : ", ", "WP_TEXT"), 0);
	if (flags & D_PAGED	)
		first = (printf("%s%s", first ? "" : ", ", "D_PAGED"), 0);
	if (!first)
		printf("\n");
}
