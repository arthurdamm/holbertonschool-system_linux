#include "hls.h"

/**
 * free_param - frees all malloced param members
 * @param: the parameter struct
 */
void free_param(Param *param)
{
	if (param->files)
		free(param->files);
		param->files = NULL;

	/*
	if (param->dirs)
		free_list(param->dirs);
		param->dirs = NULL;
	*/
}
