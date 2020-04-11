#include "signals.h"

/**
 * signal_handler - handles signals
 * @signum: the signal number
 * @siginfo: info struct about signal
 * @ucontext: pointer to ucontext_t
 */
void signal_handler(__attribute__((unused))int signum,
siginfo_t *siginfo, __attribute__((unused))void *ucontext)
{
	psiginfo(siginfo, "Caught");
}

/**
 * all_in_one - handles all signals
 */
void all_in_one(void)
{
	struct sigaction act;
	int i;

	memset(&act, 0, sizeof(act));
	act.sa_flags |= SA_SIGINFO;
	act.sa_sigaction = signal_handler;
	for (i = 0; i <= 64; i++)
		sigaction(i, &act, NULL);
}
