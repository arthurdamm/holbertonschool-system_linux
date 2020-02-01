#include "hls.h"

/**
 * error_cant_open - prints a cannot open error
 * @param: the parameter struct
 * @name: the invalid file
 */
void error_cant_open(Param *param, char *name)
{
	char buf[BUF_SIZE] = {0};

	param->status = 2;
	sprintf(buf, "%s: cannot access '%s'", MYNAME, name);
	perror(buf);
}

/**
 * error_bad_option - prints a bad option error
 * @param: the parameter struct
 * @c: the invalid option
 */
void error_bad_option(Param *param, char c)
{
	param->status = 2;
	fprintf(stdout, "%s: invalid option -- '%c'\n", MYNAME, c);
	fprintf(stderr, "Try '%s --help' for more information.\n", "ls");
}

/**
 * error - prints message for passed errno
 * @code: the error number whose message to print
 * Return: void
 */
void error(int code)
{
	(void)code;
}
