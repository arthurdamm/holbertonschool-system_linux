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
		param->files_i--; /* overwrite this entry so its initialized */
		return;
	}
	file->name = _strdup(file->name);
}

/**
 * print_files - prints all the stored files
 * @param: the parameter struct
 * @omit_dirs: 1 if to omit dirs
 */
void print_files(Param *param, int omit_dirs)
{
	size_t i;

	for (i = 0; i < param->files_i; i++)
	{
		if (!omit_dirs || !is_dir(&param->files[i]))
		{
			if (param->options & OPTION_l)
			{
				print_file_long(param, &param->files[i]);
				continue;
			}
			printf("%s%s", base_name(param->files[i].name),
				(i + 1 == param->files_i) || (param->options & OPTION_1) ?
					"" : "\t");
		}
	}
	free_names(param);
	param->files_i = 0; /* reset the array */
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

	param->multiple_dirs = node && node->next;
	while (node)
	{
		name = pop_list(&node);
		if (ls(param, name))
		{
			free(name);
			continue;
		}
		if (param->multiple_dirs)
			printf("%s%s:\n", param->printed_dir++ ? "\n" : "", name);
		if (param->files_i != 0)
		{
			print_files(param, 0);
			if (!(param->options & OPTION_1))
				printf("\n");
		}
		free(name);
	}
}

/**
 * print_file_long - prints a single file according to options
 * @param: the parameter struct
 * @file: the file to print
 */
void print_file_long(Param *param, File *file)
{
	(void)param;
	printf("%c%c%c%c%c%c%c%c%c%c %s",
		is_dir(file) ? 'd' : ' ',
		RUSR, WUSR, XUSR, RGRP, WGRP, XGRP, ROTH, WOTH, XOTH,
		file->name);
}
