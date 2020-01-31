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
