#include "hreadelf.h"

/**
 * print_header - calls all the print functions
 * @elf_header: address of elf header struct
 * Return: 0 on success else exit_status
 */
int print_header(elf_t *elf_header)
{
	printf("ELF Header:\n");
	print_magic(&elf_header->e64);
	print_class(&elf_header->e64);
	print_data(&elf_header->e64);
	print_version(&elf_header->e64);
	print_osabi(&elf_header->e64);
	print_abiversion(&elf_header->e64);
	print_type(elf_header);
	print_machine(&elf_header->e64);
	print_e_version(elf_header);
	print_entry(elf_header);
	print_program_headers(elf_header);
	print_section_headers(elf_header);
	print_flags(elf_header);
	return (0);
}

/**
 * print_magic - prints the 16 bytes of ELF header
 * @elf_header: address of elf header struct
 * Return: 0 on success else exit_status
 */
int print_magic(Elf64_Ehdr *elf_header)
{
	size_t i;

	printf("  Magic:   ");
	for (i = 0; i < EI_NIDENT; i++)
		printf("%.2x ", elf_header->e_ident[i]);
	printf("\n");
	return (0);
}

/**
 * print_class - prints the byte architecture class
 * @elf_header: address of elf header struct
 * Return: 0 on success else exit_status
 */
int print_class(Elf64_Ehdr *elf_header)
{
	printf("  Class:                             ");
	switch (elf_header->e_ident[EI_CLASS])
	{
		case ELFCLASS64:
			printf("ELF64");
		break;
		case ELFCLASS32:
			printf("ELF32");
		break;
		case ELFCLASSNONE:
			printf("none");
		break;
		default:
			printf("<unknown: %x>", elf_header->e_ident[EI_CLASS]);
		break;
	}
	printf("\n");
	return (0);
}

/**
 * print_data - prints the endianness type
 * @elf_header: address of elf header struct
 * Return: 0 on success else exit_status
 */
int print_data(Elf64_Ehdr *elf_header)
{
	printf("  Data:                              ");
	switch (elf_header->e_ident[EI_DATA])
	{
		case ELFDATA2LSB:
			printf("2's complement, little endian");
		break;
		case ELFDATA2MSB:
			printf("2's complement, big endian");
		break;
		case ELFDATANONE:
			printf("none");
		break;
		default:
			printf("<unknown: %x>", elf_header->e_ident[EI_DATA]);
		break;
	}
	printf("\n");
	return (0);
}

/**
 * print_version - prints the ELF version
 * @elf_header: address of elf header struct
 * Return: 0 on success else exit_status
 */
int print_version(Elf64_Ehdr *elf_header)
{
	printf("  Version:                           %d ",
		elf_header->e_ident[EI_VERSION]);
	if (elf_header->e_ident[EI_VERSION] == EV_CURRENT)
		printf("(current)");
	else if (elf_header->e_ident[EI_VERSION] != EV_NONE)
		printf("<unknown: %x", elf_header->e_ident[EI_VERSION]);
	printf("\n");
	return (0);
}
