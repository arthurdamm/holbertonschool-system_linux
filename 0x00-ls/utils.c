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
		case 'a':
			param->options |= OPTION_a;
			break;
		case 'A':
			param->options |= OPTION_A;
			break;
		case 'l':
			param->options |= OPTION_l;
			break;
		default:
			error_bad_option(param, *arg);
			free_param(param);
			exit(2);
			break;
		}
	}
}

/**
 * base_name - returns pointer to base name of file
 * @fullpath: the full path file name
 * Return: pointer to base name of string
 */
char *base_name(char *fullpath)
{
	char *p;

	if (!fullpath)
		return (NULL);
	if (!*fullpath)
		return (fullpath);
	p = fullpath + _strlen(fullpath) - 1;
	for (; p >= fullpath; p--)
	{
		if (*p == '/')
		{
			if (*(p + 1))
				return (p + 1);
			return (p);
		}
	}
	return (fullpath);
}
