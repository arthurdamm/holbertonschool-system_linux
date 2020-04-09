#include "signals.h"

/**
 * current_handler_sigaction - retrieves handler by sigaction
 * Return: current handler or NULL
 */
void (*current_handler_sigaction(void))(int)
{
	struct sigaction old;

	memset(&old, 0, sizeof(old));
	return (sigaction(SIGINT, NULL, &old) ? NULL : old.sa_handler);
}
