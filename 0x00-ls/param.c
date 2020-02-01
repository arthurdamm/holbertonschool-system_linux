#include "hls.h"

/**
 * free_param - frees all malloced param members
 * @param: the parameter struct
 */
void free_param(Param *param)
{
	free_names(param);
	
	if (param->files)
	{
		free(param->files);
		param->files = NULL;
	}

	/*
	* if (param->dirs)
	* {
	*	free_list(param->dirs);
	*	param->dirs = NULL;
	* }
	*/
}

/**
 * free_names - frees all the allocated pathnames
 * @param: the parameter struct
 */
void free_names(Param *param)
{
	File *start = param->files, *stop = param->files + param->files_i;
	for (; start < stop; start++)
	{
		if (start->name)
		{
			free(start->name);
			start->name = NULL;
		}
	}
}
