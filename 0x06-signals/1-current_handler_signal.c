#include "signals.h"

/**
 * current_handler_signal - returns current handler
 * Return: the current SIGINT handler
 **/
void (*current_handler_signal(void))(int)
{
	sighandler_t handler = signal(SIGINT, SIG_DFL);

	if (handler == SIG_ERR)
		return (NULL);
	return (signal(SIGINT, handler) == SIG_ERR ? NULL : handler);
}
