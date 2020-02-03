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
		if (!param->files)
			return;
		param->files_size *= 2;
	}
	file = &param->files[param->files_i++];
	file->name = name;
	if (lstat(name, &file->stat))
	{
		param->nonoption_argument++;
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
	int first = 1;
	size_t sizes[3] = {0};

	get_long_format_field_sizes(param, (size_t *)&sizes, omit_dirs);
	param->printed_dir = 0;
	for (i = 0; i < param->files_i; i++)
	{
		if (!omit_dirs || !is_dir(&param->files[i]))
		{
			param->printed_dir++;
			if (param->options & OPTION_l)
			{
				print_file_long(param, &param->files[i], sizes);
				continue;
			}
			if (!first)
				printf("%s", (param->options & OPTION_1) ? "\n" : "\t");
			first = 0;
			printf("%s", omit_dirs ? param->files[i].name :
				base_name(param->files[i].name));
		}
	}
	if (param->printed_dir &&
		!(param->options & OPTION_l))
		printf("\n");
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
		} else
		{
			param->nonoption_argument++;
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
	int first = 1;

	param->multiple_dirs = node && node->next;
	if (node && param->printed_dir)
		printf("\n");
	while (node)
	{
		name = pop_list(&node);
		if (ls(param, name))
		{
			free(name);
			continue;
		}
		if (param->multiple_dirs || param->printed_dir || param->nonoption_argument)
		{
			if (!first)
			{
				printf("\n");
				first = 0;
			}
			printf("%s:\n", name);
			first = 0;
		}
		if (param->options & OPTION_R)
		{
			param->dirs = node;
			print_list(param->dirs);
			filter_dirs_from_files(param);
			print_list(param->dirs);
			if (!node)
				node = param->dirs;
		}
		if (param->files_i != 0)
		{
			print_files(param, (param->options & OPTION_R));
		}
		free(name);
	}
}
