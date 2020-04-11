#include "signals.h"

/**
 * sigset_init - initializes a sigset
 * @set: sigset to initialize
 * @signals: 0-terminated array of signals
 * Return: 0 on success else -1 on error
 */
int sigset_init(sigset_t *set, int *signals)
{
	for (sigemptyset(set); *signals; signals++)
		if (sigaddset(set, *signals))
			return (-1);
	return (0);
}

/**
 * signals_block - blocks all signals
 * @signals: 0-terminated array of signals
 * Return: 0 on success else -1
 */
int signals_block(int *signals)
{
	sigset_t set;

	if (sigset_init(&set, signals) ||
		sigprocmask(SIG_BLOCK, &set, NULL))
		return (-1);
	return (0);
}
