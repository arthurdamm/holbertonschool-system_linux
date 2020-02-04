#include "hls.h"

/**
 * main - entry point
 * @ac: argument count
 * @args: string of strings
 * Return: Always Success
 */
int main(int ac, char **args)
{
	int num_options = 0;
	Param param = PARAM_INIT;

	param.files = _realloc(NULL, 0, STARTING_FILES_SIZE * sizeof(File));
	param.files_size = STARTING_FILES_SIZE;

	while (*++args)
	{
		if (**args == '-' && *(*args + 1))
		{
			parse_options(&param, *args);
			num_options++;
		}
		else
		{
			append_file(&param, *args);
		}
	}

	if (num_options + 1 == ac || param.files_i)
	{
		if (!param.files_i)
			append_file(&param, ".");
		populate_sorted_files(&param);
		filter_dirs_from_files(&param);
		print_files(&param, 1);

		print_dirs(&param);
	}
	free_param(&param);
	return (param.status);
}

/**
 * ls - reads directory and lists contents
 * @param: the parameter struct
 * @path: the path to read
 * Return: 1 on error else 0
 */
int ls(Param *param, char *path)
{
	DIR *dir;
	struct dirent *read;
	char buf[BUF_SIZE];

	if (!path)
		return (1);
	dir = opendir(path);
	if (!dir)
	{
		buf[0] = 0;
		if (errno == ENOENT)
			sprintf(buf, "%s: cannot access %s", MYNAME, path);
		else if (errno == EACCES)
			sprintf(buf, "%s: cannot open directory %s", MYNAME, path);
		perror(buf);
		param->status = 2;
		return (1);
	}
	while ((read = readdir(dir)) != NULL)
	{
		if (*read->d_name != '.' || (param->options & OPTION_a) ||
			((param->options & OPTION_A) && read->d_name[1]
			&& read->d_name[2]))
		{
			buf[0] = 0;
			_strcat(buf, path);
			if (path[_strlen(path) - 1] != '/')
				_strcat(buf, "/");
			_strcat(buf, read->d_name);
			/* fullpath = _strdup(buf); */
			append_file(param, buf);
		}
	}
	closedir(dir);
	return (0);
}
