#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "signals.h"

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
    int i;

    if (trace_signal_sender() == -1)
    {
        printf("Failure\n");
        return (EXIT_FAILURE);
    }
    for (i = 0; ; i++)
    {
        printf("[%d] Wait for it ...\n", i);
        sleep(1);
    }
    return (EXIT_SUCCESS);
}
