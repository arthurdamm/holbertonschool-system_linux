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
		append_file(&param, *args);

	filter_dirs_from_files(&param);
	print_files(&param);
	print_dirs(&param);

	free_param(&param);
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
		printf(">>%s\t", read->d_name);
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
