#include "hls.h"

/**
 * is_dir - checks if file is a dir
 * @file: the file to check
 * Return: 1 if dir else 0
 */
int is_dir(File *file)
{
	return (S_ISDIR(file->stat.st_mode));
}

/**
 * parse_options - parses options from args
 * @param: the parameter struct
 * @arg: the option arg string
 */
void parse_options(Param *param, char *arg)
{
	while (*++arg)
	{
		switch (*arg)
		{
			case '1':
				param->options |= OPTION_1;
				break;
			default:
				error_bad_option(param, *arg);
				free_param(param);
				exit(2);
				break;
		}
	}
}
