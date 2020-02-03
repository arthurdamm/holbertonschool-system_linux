#include "hls.h"

/**
 * get_long_format_field_sizes - for alignment
 * @param: the parameter struct
 * @sizes: the array to fill with field widths
 * @omit_dirs: true if ignore dirs
 */
void get_long_format_field_sizes(Param *param, int *sizes, int omit_dirs)
{
	size_t i;

	for (i = 0; i < param->files_i; i++)
	{
		if (!omit_dirs || !is_dir(&param->files[i]))
		{
			sizes[0] = 0;
		}
	}
}
