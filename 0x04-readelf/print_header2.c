#include "hreadelf.h"

/**
 * print_osabi - prints to OS ABI version
 * @elf_header: address of elf header struct
 * Return: 0 on success else exit_status
 */
int print_osabi(Elf64_Ehdr *elf_header)
{
	printf("  OS/ABI:                            ");
	switch (elf_header->e_ident[EI_OSABI])
	{
		case ELFOSABI_NONE:
			printf("UNIX - System V");
			break;
		case ELFOSABI_HPUX:
			printf("UNIX - HP-UX");
			break;
		case ELFOSABI_NETBSD:
			printf("UNIX - NetBSD");
			break;
		case ELFOSABI_LINUX:
			printf("UNIX - Linux");
			break;
		case ELFOSABI_SOLARIS:
			printf("UNIX - Solaris");
			break;
		case ELFOSABI_AIX:
			printf("UNIX - AIX");
			break;
		case ELFOSABI_IRIX:
			printf("UNIX - IRIX");
			break;
		case ELFOSABI_FREEBSD:
			printf("UNIX - FreeBSD");
			break;
		case ELFOSABI_TRU64:
			printf("UNIX - TRU64");
			break;
		default:
			return (print_osabi_more(elf_header));
		break;
	}
	printf("\n");
	return (0);
}


/**
 * print_osabi_more - prints ELF osabi more
 * @elf_header: address of elf header struct
 * Return: 0 on success else exit_status
 */
int print_osabi_more(Elf64_Ehdr *elf_header)
{
	switch (elf_header->e_ident[EI_OSABI])
	{
		case ELFOSABI_MODESTO:
			printf("Novell - Modesto");
			break;
		case ELFOSABI_OPENBSD:
			printf("UNIX - OpenBSD");
			break;
		case ELFOSABI_STANDALONE:
			printf("Standalone App");
			break;
		case ELFOSABI_ARM:
			printf("ARM");
			break;
		default:
			printf("<unknown: %x>", elf_header->e_ident[EI_OSABI]);
			break;
	}
	printf("\n");
	return (0);
}

/**
 * print_abiversion  - prints ELF ABI version
 * @elf_header: address of elf header struct
 * Return: 0 on success else exit_status
 */
int print_abiversion(Elf64_Ehdr *elf_header)
{
	printf("  ABI Version:                       %d\n",
		elf_header->e_ident[EI_ABIVERSION]);
	return (0);
}

/**
 * print_type - prints the ELF type
 * @elf_header: address of elf header struct
 * Return: 0 on success else exit_status
 */
int print_type(Elf64_Ehdr *elf_header)
{
	char *p = (char *)&elf_header->e_type;
	int i = 0;

	printf("  Type:                              ");
	if (elf_header->e_ident[EI_DATA] == ELFDATA2MSB)
		i = 1;
	switch (p[i])
	{
		case ET_NONE:
			printf("NONE (None)");
			break;
		case ET_REL:
			printf("REL (Relocatable file)");
			break;
		case ET_EXEC:
			printf("EXEC (Executable file)");
			break;
		case ET_DYN:
			printf("DYN (Shared object file)");
			break;
		case ET_CORE:
			printf("CORE (Core file)");
			break;
		default:
			printf("<unknown>: %x", p[i]);
		break;
	}
	printf("\n");
	return (0);
}

/**
 * print_entry - prints the ELF entry point address
 * @elf_header: address of elf header struct
 * Return: 0 on success else exit_status
 */
int print_entry(elf_t *elf_header)
{
	if (IS_32(elf_header->e64))
		printf("  Entry point address:               0x%lx\n", EGET(e_entry));
	else
		printf("  Entry point address:               0x%lx\n", EGET(e_entry));
	return (0);
}
