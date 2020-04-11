#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>

#include "signals.h"

/**
 * sigset_print - Prints a signal set
 * @set: Set to be printed
 */
void sigset_print(const sigset_t *set)
{
    int sig;
    int cnt;

    cnt = 0;
    for (sig = 1; sig < NSIG; sig++)
    {
        if (sigismember(set, sig))
        {
            cnt++;
            printf("%d (%s)\n", sig, strsignal(sig));
        }
    }
    if (cnt == 0)
        printf("Empty signal set\n");
}

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
    sigset_t set;
    int signals[] = {
        SIGINT,
        SIGQUIT,
        SIGSEGV,
        SIGTRAP,
        0
    };

    if (sigset_init(&set, signals) == -1)
    {
        fprintf(stderr, "Failed to init sigset\n");
        return (EXIT_FAILURE);
    }
    sigset_print(&set);
    return (EXIT_SUCCESS);
}
