#include "hreadelf.h"

/**
 * open_file - opens a file descriptor, exits on failure
 * @name: name of file to open
 * @silent: if true don't print errors
 * Return: fd of file
 */
int open_file(char *name, int silent)
{
	int fd;

	fd = open(name, O_RDONLY);
	if (fd == -1 && !silent)
	{
		if (errno == EACCES)
			fprintf(stderr, ERR_NO_ACCESS, name);
		else if (errno == ENOENT)
			fprintf(stderr, ERR_NO_ENTRY, name);
	}
	return (fd);
}

/**
 * check_elf - checks if header matches magic bytes
 * @elf_header: 16 byte buffer holding elf header
 * Return: 0 if ELF else 1
 */
int check_elf(char *elf_header)
{
	if (elf_header[0] == 0x7f && elf_header[1] == 0x45 &&
		elf_header[2] == 0x4c && elf_header[3] == 0x46)
		return (0);
	return (1);
}
