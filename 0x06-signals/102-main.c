#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#include "signals.h"

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
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
    while (98)
    {
        sleep(5);
    }
    return (EXIT_SUCCESS);
}
