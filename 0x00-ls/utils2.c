#include "hls.h"

/**
 * print_file_long - prints a single file according to options
 * @param: the parameter struct
 * @file: the file to print
 */
void print_file_long(Param *param, File *file)
{
	struct passwd *usr = getpwuid(file->stat.st_uid);
	struct group *grp = getgrgid(file->stat.st_gid);

	(void)param;
	printf("%c%c%c%c%c%c%c%c%c%c %lu %s %s %lu %s %s\n",
		is_dir(file) ? 'd' : '-',
		RUSR, WUSR, XUSR, RGRP, WGRP, XGRP, ROTH, WOTH, XOTH,
		file->stat.st_nlink, usr ? usr->pw_name : "", grp ? grp->gr_name : "",
		file->stat.st_size, sprint_time(file), base_name(file->name));
}


/**
 * get_long_format_field_sizes - for alignment
 * @param: the parameter struct
 * @sizes: the array to fill with field widths
 * @omit_dirs: true if ignore dirs
 */
void get_long_format_field_sizes(Param *param, int *sizes, int omit_dirs)
{
	size_t i;
	struct passwd *usr;
	struct group *grp;
	struct File *file;

	for (i = 0; i < param->files_i; i++)
	{
		file = &param->files[i];
		if (!omit_dirs || !is_dir(file))
		{
			usr = getpwuid(file->stat.st_uid);
			grp = getgrgid(file->stat.st_gid);
			(void)usr;
			(void)grp;
			convert_number(file->stat.st_size, 10, 0);
			sizes[0] = 0;
		}
	}
}
