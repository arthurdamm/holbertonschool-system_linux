#include "hls.h"

/**
 * error_cant_open - prints a cannot open error
 * @param: the parameter struct
 * @name: the invalid file
 */
void error_cant_open(Param *param, char *name)
{
	char buf[BUF_SIZE] = {0};
	(void)param;
	sprintf(buf, "%s: cannot access '%s'", MYNAME, name);
	perror(buf);
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
