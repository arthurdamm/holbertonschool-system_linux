#include "hreadelf.h"

/**
 * read_symbol_table - reads the symbol headers into data
 * @elf_header: the internal header
 * @fd: file descriptor to read
 * @i: the current symbol section to print
 */
void read_symbol_table(elf_t *elf_header, int fd, int i)
{
	size_t r;
	char *headers;
	size_t read_size = SGET(i, sh_size);

	headers = calloc(1, read_size);
	if (!headers)
		exit(1);
	lseek(fd, SGET(i, sh_offset), SEEK_SET);
	r = read(fd, headers, read_size);
	if (r < read_size)
	{
		fprintf(stderr, "Symbol read failed.\n");
		exit(1); /* TODO */
	}
	if (IS_32(elf_header->e64))
		elf_header->y32 = (void *)headers;
	else
		elf_header->y64 = (void *)headers;
}

/**
 * read_symbol_string_table - reads the string table
 * @elf_header: the internal header
 * @fd: file descriptor to read
 * @i: the current symbol section to print
 * Return: pointer to beginning of table
 */
char *read_symbol_string_table(elf_t *elf_header, int fd, int i)
{
	char *str;

	str = calloc(1, SGET(i, sh_size));
	if (!str)
		exit(1);

	lseek(fd, SGET(i, sh_offset), SEEK_SET);
	read(fd, str, SGET(i, sh_size));
	return (str);
}

size_t find_verneed_index(Elf64_Verneed *verneed, size_t verneed_size,
	size_t index)
{
	size_t i = 0, ret = 0;

	for (i = 1; i < verneed_size; i++)
	{
		if (verneed[i].vn_file >= verneed_size)
			return (0);
		if (verneed[i].vn_file == index)
			ret = i;
	}
	return (ret);
}

void print_verneed_table(elf_t *elf_header, int fd, int i,
	char *sym_string_table, uint16_t *versym, Elf64_Verneed *verneed)
{
	size_t j;

	printf("i:[%d] size[%lu] entsize[%lu] struct[%lu]\n",
		i, SGET(i, sh_size), SGET(i, sh_entsize), sizeof(Elf64_Verneed));
	for (j = 0; j < SGET(i - 1, sh_size) / 2; j++)
	{
		printf("%lu:[%hd]\n", j, versym[j]);
	}
	printf("VERSION COUNT FILEOFFSET  AUXOFFSET NEXTOFFSET\n");
	if (!verneed)
		return;
	for (j = 0; j < SGET(i, sh_size) / sizeof(Elf64_Verneed); j++)
	{
		printf("%7hu %5hu %10d %10d %10d [%s]\n",
			verneed[j].vn_version,
			verneed[j].vn_cnt,
			verneed[j].vn_file,
			verneed[j].vn_aux,
			verneed[j].vn_next,
			sym_string_table + verneed[j].vn_aux);
	}
	(void)fd;
}

/**
 * read_data - reads a block of data from descriptor
 * @elf_header: the internal header
 * @fd: the descriptor to read
 * @offset: offset to start at
 * @size: number of bytes to read
 * Return: pointer to the data
 */
void *read_data(elf_t *elf_header, int fd, unsigned long offset, long size)
{
	void *str = NULL;

	str = calloc(1, size);
	if (!str)
		exit(1);
	/* printf("Reading [%lu] bytes at offset [%lu]\n", size, offset); */
	lseek(fd, offset, SEEK_SET);
	if (read(fd, str, size) != size)
	{
		fprintf(stderr, "Read error.\n");
		exit(1);
	}
	return (str);
	(void)elf_header;
}
