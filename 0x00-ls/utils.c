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
		case 'R':
			param->options |= OPTION_R;
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

/**
 * sprint_time - returns time string of file
 * @file: the file in question
 * Return: pointer to time string
 */
char *sprint_time(File *file)
{
	char *p = ctime(&(file->stat.st_mtime));

	if (_strlen(p) >= 16)
	{
		p += 4;
		p[12] = 0;
	}
	return (p);
}

/**
 * convert_number - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}
