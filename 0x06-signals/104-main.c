#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#include "signals.h"

/* Our functions */
int signals_block(int *signals);
int signals_unblock(int *signals);

/**
 * handler - Handler for pending signals
 * @signum: Signal number
 */
void handler(int signum)
{
    printf("\nCaught signal %d\n", signum);
}

/**
 * main - Entry point
 *
 * Return: EXITsUCCESS or EXIT_FAILURE
 */
int main(void)
{
    int signals[] = {
        SIGINT,
        SIGQUIT,
        SIGSEGV,
        SIGTRAP,
        0
    };

    if (signals_block(signals) == -1)
    {
        fprintf(stderr, "Failed to block signals\n");
        return (EXIT_FAILURE);
    }

    sleep(5);
    if (handle_pending(&handler) == -1)
    {
        printf("Failed to set up handler for pending signals\n");
        return (EXIT_FAILURE);
    }

    if (signals_unblock(signals) == -1)
    {
        fprintf(stderr, "Failed to unblock signals\n");
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

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
 * signals_unblock - unblocks all signals
 * @signals: 0-terminated array of signals
 * Return: 0 on success else -1
 */
int signals_unblock(int *signals)
{
	sigset_t set;

	if (sigset_init(&set, signals) ||
		sigprocmask(SIG_UNBLOCK, &set, NULL))
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
