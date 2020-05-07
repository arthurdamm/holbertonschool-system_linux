#include "hreadelf.h"

#define FORMAT_LEGEND \
	"Key to Flags:\n" \
	"  W (write), A (alloc), X (execute), M (merge), S (strings)%s\n" \
	"  I (info), L (link order), G (group), T (TLS), E (exclude), x (unknown)\n" \
	"  O (extra OS processing required) o (OS specific), p (processor specific)\n"
/**
 * print_section_headers_full - prints all the ELF section headers
 * @elf_header: address of elf header struct
 * @fd: the file descriptor of our ELF file
 * Return: 0 on success else exit_status
 */
int print_section_headers_full(elf_t *elf_header, int fd)
{
	char *string_table;
	size_t i;

	if (!EGET(e_shnum))
	{
		printf("\nThere are no sections in this file.\n");
		return (1);
	}
	printf("There are %d section headers, starting at offset 0x%lx:\n",
		EGET(e_shnum), EGET(e_shoff));
	read_section_headers(elf_header, fd);
	for (i = 0; i < EGET(e_shnum); i++)
		switch_all_endian_section(elf_header, i);
	string_table = read_string_table(elf_header, fd);
	printf("\nSection Headers:\n");
	if (IS_32(elf_header->e64))
		print_section_headers32(elf_header, string_table);
	else
		print_section_headers64(elf_header, string_table);
	printf(FORMAT_LEGEND, IS_32(elf_header->e64) ? "" : ", l (large)");
	free(string_table);
	return (0);
}

/**
 * read_section_headers - reads the section headers into data
 * @elf_header: the internal header
 * @fd: file descriptor to read
 */
void read_section_headers(elf_t *elf_header, int fd)
{
	size_t i = EGET(e_shnum), r;
	char *headers;
	size_t read_size = EGET(e_shentsize) * EGET(e_shnum);

	if (!i)
		return;
	headers = calloc(i, read_size * i);
	if (!headers)
		exit(1);
	lseek(fd, EGET(e_shoff), SEEK_SET);
	r = read(fd, headers, read_size);
	if (r < read_size)
		exit(1); /* TODO */
	if (IS_32(elf_header->e64))
		elf_header->s32 = (void *)headers;
	else
		elf_header->s64 = (void *)headers;
}

/**
 * read_string_table - reads the string table
 * @elf_header: the internal header
 * @fd: file descriptor to read
 * Return: pointer to beginning of table
 */
char *read_string_table(elf_t *elf_header, int fd)
{
	char *str;

	str = calloc(1, SGET(EGET(e_shstrndx), sh_size));
	if (!str)
		exit(1);

	lseek(fd, SGET(EGET(e_shstrndx), sh_offset), SEEK_SET);
	read(fd, str, SGET(EGET(e_shstrndx), sh_size));
	return (str);
}

/**
 * get_section_type - return string type of section
 * @sh_type: the section type
 * Return: string name of type
*/
char *get_section_type(unsigned int sh_type)
{
	static char buf[32];

	switch (sh_type)
	{
	case SHT_NULL:		return ("NULL");
	case SHT_PROGBITS:		return ("PROGBITS");
	case SHT_SYMTAB:		return ("SYMTAB");
	case SHT_STRTAB:		return ("STRTAB");
	case SHT_RELA:		return ("RELA");
	case SHT_HASH:		return ("HASH");
	case SHT_DYNAMIC:		return ("DYNAMIC");
	case SHT_NOTE:		return ("NOTE");
	case SHT_NOBITS:		return ("NOBITS");
	case SHT_REL:		return ("REL");
	case SHT_SHLIB:		return ("SHLIB");
	case SHT_DYNSYM:		return ("DYNSYM");
	case SHT_INIT_ARRAY:	return ("INIT_ARRAY");
	case SHT_FINI_ARRAY:	return ("FINI_ARRAY");
	case SHT_PREINIT_ARRAY:	return ("PREINIT_ARRAY");
	case SHT_GNU_HASH:		return ("GNU_HASH");
	case SHT_GROUP:		return ("GROUP");
	case SHT_SYMTAB_SHNDX:	return ("SYMTAB SECTION INDICIES");
	case SHT_GNU_verdef:	return ("VERDEF");
	case SHT_GNU_verneed:	return ("VERNEED");
	case SHT_GNU_versym:	return ("VERSYM");
	case 0x6ffffff0:		return ("VERSYM");
	case 0x6ffffffc:		return ("VERDEF");
	case 0x7ffffffd:		return ("AUXILIARY");
	case 0x7fffffff:		return ("FILTER");
	case 0x6ffffff1:		return ("LOOS+ffffff1");
	case 0x6ffffff3:		return ("LOOS+ffffff3");
	case SHT_GNU_LIBLIST:	return ("GNU_LIBLIST");
	default:
		sprintf(buf, "%08x: <unknown>", sh_type);
		return (buf);
	}
}
