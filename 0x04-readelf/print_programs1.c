#include "hreadelf.h"

#define PROGRAM_TITLE \
	"\nElf file type is %s\nEntry point 0x%lx\nThere are %d program headers," \
	" starting at offset %lu\n"

#define TITLE_PROGRAM_32 \
	"  Type           Offset   VirtAddr   PhysAddr   FileSiz MemSiz  Flg Align\n"

#define FORMAT_PROGRAM_32 \
	"  %-14s 0x%6.6lx 0x%8.8lx 0x%8.8lx 0x%5.5lx 0x%5.5lx %c%c%c %#lx\n"

#define TITLE_PROGRAM_64 \
	"  Type           Offset   VirtAddr           PhysAddr           FileSiz  MemSiz   Flg Align\n"

#define FORMAT_PROGRAM_64 \
	"  %-14s 0x%6.6lx 0x%16.16lx 0x%16.16lx 0x%6.6lx 0x%6.6lx %c%c%c %#lx\n"

/**
 * print_program_headers_full - prints all the ELF PROGRAM headers
 * @elf_header: address of elf header struct
 * @fd: the file descriptor of our ELF file
 * Return: 0 on success else exit_status
 */
int print_program_headers_full(elf_t *elf_header, int fd)
{
	char *string_table;
	size_t i;

	if (!EGET(e_phnum))
	{
		printf("\nThere are no program headers in this file.\n");
		return (0);
	}
	printf(PROGRAM_TITLE, get_type(elf_header), EGET(e_entry),
		EGET(e_phnum), EGET(e_phoff));

	read_section_headers(elf_header, fd);
	read_program_headers(elf_header, fd);
	for (i = 0; i < EGET(e_shnum); i++)
		switch_all_endian_section(elf_header, i);
	for (i = 0; i < EGET(e_phnum); i++)
		switch_all_endian_program(elf_header, i);
	string_table = read_string_table(elf_header, fd);
	printf("\nProgram Headers:\n");
	if (IS_32(elf_header->e64))
		print_program_headers32(elf_header, string_table, fd);
	else
		print_program_headers64(elf_header, string_table, fd);
	print_section_to_segment_mapping(elf_header, string_table);
	free(string_table);
	return (0);
}

/**
 * print_program_headers32 - prints 32 bit program headers
 * @elf_header: address of elf header struct
 * @string_table: the string table program
 * @fd: file descriptor of ELF file
 */
void print_program_headers32(elf_t *elf_header, char *string_table, int fd)
{
	size_t i = 0;

	printf(TITLE_PROGRAM_32);
	for (i = 0; i < EGET(e_phnum); i++)
	{
		printf(FORMAT_PROGRAM_32,
			get_segment_type(PGET(i, p_type)),
			PGET(i, p_offset),
			PGET(i, p_vaddr),
			PGET(i, p_paddr),
			PGET(i, p_filesz),
			PGET(i, p_memsz),
			PGET(i, p_flags) & PF_R ? 'R' : ' ',
			PGET(i, p_flags) & PF_W ? 'W' : ' ',
			PGET(i, p_flags) & PF_X ? 'E' : ' ',
			PGET(i, p_align));
		switch (PGET(i, p_type))
		{
			case PT_INTERP:
			{
				char fmt[32], prog[PATH_MAX];
				FILE *file = fdopen(fd, "r");

				snprintf(fmt, sizeof(fmt), "%%%ds", PATH_MAX);
				lseek(fd, PGET(i, p_offset), SEEK_SET);
				if (fscanf(file, fmt, prog) > 0)
					printf("      [Requesting program interpreter: %s]\n", prog);
				fclose(file);
			}
		}
	}
	(void)string_table;
}

/**
 * print_program_headers64 - prints 64 bit program headers
 * @elf_header: address of elf header struct
 * @string_table: the string table program
 * @fd: file descriptor of ELF file
 */
void print_program_headers64(elf_t *elf_header, char *string_table, int fd)
{
	size_t i = 0;

	printf(TITLE_PROGRAM_64);
	for (i = 0; i < EGET(e_phnum); i++)
	{
		printf(FORMAT_PROGRAM_64,
			get_segment_type(PGET(i, p_type)),
			PGET(i, p_offset),
			PGET(i, p_vaddr),
			PGET(i, p_paddr),
			PGET(i, p_filesz),
			PGET(i, p_memsz),
			PGET(i, p_flags) & PF_R ? 'R' : ' ',
			PGET(i, p_flags) & PF_W ? 'W' : ' ',
			PGET(i, p_flags) & PF_X ? 'E' : ' ',
			PGET(i, p_align));
		switch (PGET(i, p_type))
		{
			case PT_INTERP:
			{
				char fmt[32], prog[PATH_MAX];
				FILE *file = fdopen(fd, "r");

				snprintf(fmt, sizeof(fmt), "%%%ds", PATH_MAX);
				lseek(fd, PGET(i, p_offset), SEEK_SET);
				if (fscanf(file, fmt, prog) > 0)
					printf("      [Requesting program interpreter: %s]\n", prog);
				fclose(file);
			}
		}
	}
	(void)string_table;
}

/**
 * read_program_headers - reads the program headers into data
 * @elf_header: the internal header
 * @fd: file descriptor to read
 */
void read_program_headers(elf_t *elf_header, int fd)
{
	size_t i = EGET(e_phnum), r;
	char *headers;
	size_t read_size = EGET(e_phentsize) * EGET(e_phnum);

	if (!i)
		return;
	headers = calloc(i, read_size * i);
	if (!headers)
		exit(1);
	lseek(fd, EGET(e_phoff), SEEK_SET);
	r = read(fd, headers, read_size);
	if (r < read_size)
		exit(1); /* TODO */
	if (IS_32(elf_header->e64))
		elf_header->p32 = (void *)headers;
	else
		elf_header->p64 = (void *)headers;
}


/**
 * get_segment_type - get string represenation of segment type
 * @p_type: the p_type of this segment
 * Return: string representation of p_type
 */
char *get_segment_type(unsigned long p_type)
{
	switch (p_type)
	{
	case PT_NULL:	return ("NULL");
	case PT_LOAD:	return ("LOAD");
	case PT_DYNAMIC:	return ("DYNAMIC");
	case PT_INTERP:	return ("INTERP");
	case PT_NOTE:	return ("NOTE");
	case PT_SHLIB:	return ("SHLIB");
	case PT_PHDR:	return ("PHDR");
	case PT_TLS:	return ("TLS");
	case PT_GNU_EH_FRAME:	return ("GNU_EH_FRAME");
	case PT_GNU_STACK:	return ("GNU_STACK");
	case PT_GNU_RELRO:  return ("GNU_RELRO");
	case 0x6464E550:	return ("LOOS+464e550");
	default:	return ("UNKNOWN");
	}
}
