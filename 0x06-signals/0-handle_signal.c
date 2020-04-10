#include "signals.h"

/**
 * signal_handler - receives signal
 * @sig: the signal number received
 */
void signal_handler(int sig)
{
	printf("Gotcha! [%d]\n", sig);
	fflush(stdout);
}

/**
 * handle_signal - signal handler helper
 * Return: 0 on success else -1 on error
 */
int handle_signal(void)
{
	return (signal(SIGINT, signal_handler) == SIG_ERR ? -1 : 0);
}
