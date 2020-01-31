#include "hls.h"

/**
 * append_file - parses arg and adds to files array
 * @param: the parameter struct
 * @name: the name of the file to parse
 */
void append_file(Param *param, char *name)
{
	File *file;

	if (param->files_i == param->files_size)
	{
		param->files = _realloc(param->files,
								param->files_size * sizeof(File),
								param->files_size * sizeof(File) * 2);
		param->files_size *= 2;
		if (!param->files)
			return;
	}
	file = &param->files[param->files_i++];
	file->name = name;
	if (lstat(name, &file->stat))
	{
		error_cant_open(param, name);
		return;
	}
	if (S_ISREG(file->stat.st_mode))
	{
		printf("[%s] is a regular file\n", name);
	}
	else if (S_ISDIR(file->stat.st_mode))
	{
		printf("[%s] is a directory\n", name);
	}
	else
		printf("[%s] is OTHER\n", name);
}

/**
 * print_files - prints all the stored files
 * @param: the parameter struct
 */
void print_files(Param *param)
{
	size_t i;

	for (i = 0; i < param->files_i; i++)
	{
		if (!is_dir(&param->files[i]))
		{
			printf(">%s%c", param->files[i].name,
				i + 1 == param->files_i ? '\n' : '\t');
		}
	}
}

/**
 * filter_dirs_from_files - transfers dirs from files array to queue
 * @param: the parameter struct
 */
void filter_dirs_from_files(Param *param)
{
	size_t i;

	for (i = 0; i < param->files_i; i++)
	{
		if (is_dir(&param->files[i]))
		{
			add_node_end(&param->dirs, &param->files[i]);
		}
	}
}

/**
 * print_dirs - prints all the enqueued dirs
 * @param: the parameter struct
 */
void print_dirs(Param *param)
{
	list_t *node = param->dirs;
	char *name;

	while (node)
	{
		name = pop_list(&node);
		ls(name);
	}
}
