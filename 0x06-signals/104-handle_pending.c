#include "signals.h"

/**
 * handle_pending - handles pending signals
 * @handler: pointer to handler func
 * Return: 0 on success else -1 on error
 */
int handle_pending(void (*handler)(int))
{
	sigset_t set;
	struct sigaction act;
	int i;

	memset(&act, 0, sizeof(act));
	act.sa_handler = handler;
	sigemptyset(&set);
	sigpending(&set);
	for (i = 1; i < 65; i++)
		if (sigismember(&set, i))
			if (sigaction(i, &act, NULL))
				return (-1);
	return (0);
}
