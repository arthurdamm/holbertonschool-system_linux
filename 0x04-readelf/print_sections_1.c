#include "hreadelf.h"

/**
 * print_sections - prints all the ELF section headers
 * @elf_header: address of elf header struct
 * Return: 0 on success else exit_status
 */
int print_sections(elf_t *elf_header)
{
	if (!EGET(e_shnum))
	{
		printf("\nThere are no sections in this file.\n");
		return (1);
	}
	printf("There are %d section headers, starting at offset 0x%lx:\n",
		EGET(e_shnum), EGET(e_shoff));
	return (0);
}
