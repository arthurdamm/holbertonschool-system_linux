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
		read_section_headers(&elf_header, fd);
		switch_all_endian(&elf_header);
		exit_status = print_sections(&elf_header);
	}

	close(fd); /* if error? */
	return (exit_status);
}

/**
 * read_section_headers - reads the section headers into data
 * @elf_header: the internal header
 * @fd: file descriptor to read
 */
void read_section_headers(elf_t *elf_header, int fd)
{
	size_t i = EGET(e_shnum), r;
	char *headers = IS_32(elf_header->e64)
		? (char *)elf_header->s32 : (char *)elf_header->s64;
	size_t read_size = IS_32(elf_header->e64)
		? sizeof(*elf_header->s32) : sizeof(*elf_header->s64);

	if (!i)
		return;
	headers = calloc(i, read_size);
	printf("headers[%p]\n", headers);
	lseek(fd, EGET(e_shoff), SEEK_SET);
	while (i--)
	{
		r = read(fd, headers, read_size);
		if (r < read_size)
			exit(1); /* TODO */
		headers += read_size;
	}
	printf("DONE READ!\n");
	printf("headers[%p]\n", (void *)elf_header->s32);
	if (IS_32(elf_header->e64))
	{
		char str[1025] = {0};

		lseek(fd, EGET(e_shstrndx), SEEK_SET);
		read(fd, str, 1024);
		printf("[%d]\n", elf_header->s32->sh_name);
		printf("IS32\n");
		printf("[%d]\n", elf_header->s32->sh_name);
		printf("STR:[%s]\n", str + elf_header->s32->sh_name);
	}
}
