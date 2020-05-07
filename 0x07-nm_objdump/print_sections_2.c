#include "hreadelf.h"

#define TITLE_SECTION_32 \
	"  [Nr] Name              Type            Addr     Off    Size   ES Flg Lk Inf Al\n"
#define FORMAT_SECTION_32 \
	"  [%2u] %-17s %-15.15s %8.8lx %6.6lx %6.6lx %2.2lx %3s %2u %3u %2lu\n"
#define TITLE_SECTION_64 \
	"  [Nr] Name              Type            Address          Off    Size   ES Flg Lk Inf Al\n"
#define FORMAT_SECTION_64 \
	"  [%2u] %-17s %-15.15s %16.16lx %6.6lx %6.6lx %2.2lx %3s %2u %3u %2lu\n"
/**
 * print_section_headers32 - prints 32 bit section headers
 * @elf_header: address of elf header struct
 * @string_table: the string table section
 */
void print_section_headers32(elf_t *elf_header, char *string_table)
{
	size_t i = 0;

	printf(TITLE_SECTION_32);
	for (i = 0; i < EGET(e_shnum); i++)
		printf(FORMAT_SECTION_32,
			(unsigned int)i,
			string_table + SGET(i, sh_name),
			get_section_type(SGET(i, sh_type)),
			SGET(i, sh_addr),
			SGET(i, sh_offset),
			SGET(i, sh_size),
			SGET(i, sh_entsize),
			get_section_flags(elf_header, i),
		    SGET(i, sh_link),
		    SGET(i, sh_info),
		    SGET(i, sh_addralign));
}

/**
 * print_section_headers64 - prints 64 bit section headers
 * @elf_header: address of elf header struct
 * @string_table: the string table section
 */
void print_section_headers64(elf_t *elf_header, char *string_table)
{
	size_t i = 0;

	printf(TITLE_SECTION_64);
	for (i = 0; i < EGET(e_shnum); i++)
		printf(FORMAT_SECTION_64,
			(unsigned int)i,
			string_table + SGET(i, sh_name),
			get_section_type(SGET(i, sh_type)),
			SGET(i, sh_addr),
			SGET(i, sh_offset),
			SGET(i, sh_size),
			SGET(i, sh_entsize),
			get_section_flags(elf_header, i),
		    SGET(i, sh_link),
		    SGET(i, sh_info),
		    SGET(i, sh_addralign));
}

/**
 * get_section_flags - translates section flags to string
 * @elf_header: address of elf header struct
 * @i: the section index
 * Return: legend-based string rep of flag
 */
char *get_section_flags(elf_t *elf_header, size_t i)
{
	static char buf[32];
	unsigned long flags = SGET(i, sh_flags);
	char *p = buf;

	if (flags & SHF_WRITE)
		*p++ = 'W';
	if (flags & SHF_ALLOC)
		*p++ = 'A';
	if (flags & SHF_EXECINSTR)
		*p++ = 'X';
	if (flags & SHF_MERGE)
		*p++ = 'M';
	if (flags & SHF_STRINGS)
		*p++ = 'S';
	if (flags & SHF_INFO_LINK)
		*p++ = 'I';
	if (flags & SHF_LINK_ORDER)
		*p++ = 'L';
	if (flags & SHF_OS_NONCONFORMING)
		*p++ = 'O';
	if (flags & SHF_GROUP)
		*p++ = 'G';
	if (flags & SHF_TLS)
		*p++ = 'T';
	if (flags & SHF_EXCLUDE)
		*p++ = 'E';
	/* if (flags & SHF_COMPRESSED) *p = 'C'; */
	*p = 0;
	return (buf);
}
