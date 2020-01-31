#include "hls.h"

static File foo;

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

	foo.name = "fee";

	(void)ac;
	while (*++args)
		parse_file(&param, *args);



	free(param.files);
	return (EXIT_SUCCESS);
}

/**
 * ls - reads directory and lists contents
 * @path: the path to read
 * Return: void
 */
void ls(char *path)
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
		exit(2);
		return;
	}
	while ((read = readdir(dir)) != NULL)
		printf("%s\t", read->d_name);
	printf("\n");
	closedir(dir);
}

/**
 * parse_file - parses arg and adds to files array
 * @param: the parameter struct
 * @name: the name of the file to parse
 */
void parse_file(Param *param, char *name)
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
