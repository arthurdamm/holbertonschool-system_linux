#include "hreadelf.h"

/**
 * print_section_headers - prints the start of section headers
 * @elf_header: address of elf header struct
 * Return: 0 on success else exit_status
 */
int print_section_headers(elf_t *elf_header)
{
	printf("  Start of section headers:          %lu (bytes into file)\n",
		EGET(e_shoff));
	return (0);
}

/**
 * print_flags - prints the flags
 * @elf_header: address of elf header struct
 * Return: 0 on success else exit_status
 */
int print_flags(elf_t *elf_header)
{
	printf("  Flags:                             0x");
	/* endianness */
	if (IS_32(elf_header->e64))
		printf("%lx", (unsigned long)elf_header->e32.e_flags);
	else
		printf("%lx", (unsigned long)elf_header->e64.e_flags);
	printf("\n");

	printf("  Size of this header:               %ld (bytes)\n",
		IS_32(elf_header->e64) ? (long)elf_header->e32.e_ehsize
		: (long)elf_header->e64.e_ehsize);

	printf("  Size of program headers:           %ld (bytes)\n",
		IS_32(elf_header->e64) ? (long)elf_header->e32.e_phentsize
		: (long)elf_header->e64.e_phentsize);

	printf("  Number of program headers:         %ld\n",
		IS_32(elf_header->e64) ? (long)elf_header->e32.e_phnum
		: (long)elf_header->e64.e_phnum);
	printf("  Size of section headers:           %ld (bytes)\n",
		IS_32(elf_header->e64) ? (long)elf_header->e32.e_shentsize
		: (long)elf_header->e64.e_shentsize);
	printf("  Number of section headers:         %ld\n",
		IS_32(elf_header->e64) ? (long)elf_header->e32.e_shnum
		: (long)elf_header->e64.e_shnum);
	printf("  Section header string table index: %ld\n",
		IS_32(elf_header->e64) ? (long)elf_header->e32.e_shstrndx
		: (long)elf_header->e64.e_shstrndx);
	return (0);
}
