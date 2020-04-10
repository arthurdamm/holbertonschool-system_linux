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
 * handle_sigaction - applies sigaction syscall
 * Return: 0 on success else -1
 */
int handle_sigaction(void)
{
	struct sigaction act;

	memset(&act, 0, sizeof(act));
	act.sa_handler = signal_handler;
	return (sigaction(SIGINT, &act, NULL));
}
