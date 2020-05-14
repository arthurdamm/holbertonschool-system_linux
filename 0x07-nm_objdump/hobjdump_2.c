#include "hreadelf.h"

/**
 * get_file_format - gets the string format type
 * @elf_header: the internal header
 * Return: string type
 */
char *get_file_format(elf_t *elf_header)
{
	static char buf[32];

	*buf = 0;
	sprintf(buf, "elf%d-%s", IS_64 ? 64 : 32,
		IS_BE(elf_header->e64) ? "big" : IS_64 ? "x86-64" : "i386");
	return (buf);
}

/**
 * print_f_header - prints the -f style header
 * @elf_header: the internal header
 * @string_table: the header str table
 */
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

/**
 * has_section - checks is objfile has given section name
 * @elf_header: the internal header
 * @string_table: the header str table
 * @section_name: the name to find
 * Return: 1 if has it else 0
 */
int has_section(elf_t *elf_header, char *string_table, char *section_name)
{
	size_t i = 0;

	section_name = strdup(section_name);
	for (i = 1; i < EGET(e_shnum); i++)
		if (!strcmp(string_table + SGET(i, sh_name), section_name))
			return (1);
	return (0);
}

/**
 * print_f_flags - prints the string flag list
 * @flags: the flags for this file
 */
void print_f_flags(unsigned long flags)
{
	int first = 1;

	if (flags & HAS_RELOC)
		first = (printf("%s%s", first ? "" : ", ", "HAS_RELOC"), 0);
	if (flags & EXEC_P)
		first = (printf("%s%s", first ? "" : ", ", "EXEC_P"), 0);
	if (flags & HAS_LINENO)
		first = (printf("%s%s", first ? "" : ", ", "HAS_LINENO"), 0);
	if (flags & HAS_DEBUG)
		first = (printf("%s%s", first ? "" : ", ", "HAS_DEBUG"), 0);
	if (flags & HAS_SYMS)
		first = (printf("%s%s", first ? "" : ", ", "HAS_SYMS"), 0);
	if (flags & HAS_LOCALS)
		first = (printf("%s%s", first ? "" : ", ", "HAS_LOCALS"), 0);
	if (flags & DYNAMIC)
		first = (printf("%s%s", first ? "" : ", ", "DYNAMIC"), 0);
	if (flags & WP_TEXT)
		first = (printf("%s%s", first ? "" : ", ", "WP_TEXT"), 0);
	if (flags & D_PAGED)
		first = (printf("%s%s", first ? "" : ", ", "D_PAGED"), 0);
	if (!first)
		printf("\n");
}
