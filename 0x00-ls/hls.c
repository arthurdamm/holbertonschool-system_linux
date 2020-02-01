#include "hls.h"

/**
 * main - entry point
 * @ac: argument count
 * @args: string of strings
 * Return: Always Success
 */
int main(int ac, char **args)
{
	Param param = PARAM_INIT;

	param.files = _realloc(NULL, 0, STARTING_FILES_SIZE * sizeof(File));
	param.files_size = STARTING_FILES_SIZE;

	(void)ac;
	while (*++args)
	{
		if (**args == '-')
			parse_options(&param, *args);
		else
			append_file(&param, *args);
	}

	if (!param.files_i)
		append_file(&param, ".");
	filter_dirs_from_files(&param);
	print_files(&param);
	print_dirs(&param);

	free_param(&param);
	return (param.status);
}

/**
 * ls - reads directory and lists contents
 * @param: the parameter struct
 * @path: the path to read
 * Return: void
 */
void ls(Param *param, char *path)
{
	DIR *dir;
	struct dirent *read;
	char buf[BUF_SIZE] = {0};

	if (!path)
		return;
	dir = opendir(path);
	if (!dir)
	{
		if (errno == ENOENT)
			sprintf(buf, "%s: cannot access '%s'", MYNAME, path);
		else if (errno == EACCES)
			sprintf(buf, "%s: cannot open directory '%s'", MYNAME, path);
		perror(buf);
		param->status = 2;
		return;
	}
	if (param->multiple_dirs)
	{
		printf("%s%s:\n", param->printed_dir++ ? "\n" : "", path);
	}
	while ((read = readdir(dir)) != NULL)
	{
		if (*read->d_name != '.' || (param->options & OPTION_a) ||
			((param->options & OPTION_A) && read->d_name[1]
			&& read->d_name[1] != '.'))
			printf("%s%c", read->d_name,
				param->options & OPTION_1 ? '\n' : '\t');
	}
	if (!(param->options & OPTION_1))
		printf("\n");
	closedir(dir);
}

/**
 * checkdir - checks is passed dir is valid
 * @path: the path to check
 * Return: 1 if valid else 0
 */
int checkdir(char *path)
{
	DIR *dir;
	char buf[BUF_SIZE] = {0};

	if (!path)
		return (0);
	dir = opendir(path);
	if (!dir)
	{
		if (errno == ENOENT)
			sprintf(buf, "%s: cannot access '%s'", MYNAME, path);
		else if (errno == EACCES)
			sprintf(buf, "%s: cannot open directory '%s'", MYNAME, path);
		perror(buf);
		return (0);
	}
	return (1);
}
