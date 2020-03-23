#include "hreadelf.h"

/**
 * main - entry point
 * @ac: argument count
 * @argv: argument vector
 * Return: 0 on success or 1+ on error
 */
int main(int ac, char **argv)
{
	int fd, exit_status = 0;
	size_t r;
	elf_t elf_header;

	memset(&elf_header, 0, sizeof(elf_header));
	if (ac != 2)
		return (fprintf(stderr, USAGE), EXIT_FAILURE);

	fd = open_file(argv[1], 0);
	if (fd == -1)
		return (EXIT_FAILURE);

	r = read(fd, &elf_header.e64, sizeof(elf_header.e64));
	if (r != sizeof(elf_header.e64) || check_elf((char *)&elf_header.e64))
	{
		fprintf(stderr, ERR_NOT_MAGIC);
		exit_status = EXIT_FAILURE;
	}
	else
	{
		if (IS_32(elf_header.e64))
		{
			lseek(fd, 0, SEEK_SET);
			r = read(fd, &elf_header.e32, sizeof(elf_header.e32));
			if (r != sizeof(elf_header.e32) || check_elf((char *)&elf_header.e32))
			{
				fprintf(stderr, ERR_NOT_MAGIC);
				exit_status = EXIT_FAILURE;
			}
		}
		switch_all_endian(&elf_header);
		exit_status = print_section_headers_full(&elf_header, fd);
	}

	free(elf_header.s32);
	free(elf_header.s64);
	close(fd); /* if error? */
	return (exit_status);
}
