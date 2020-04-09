#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "signals.h"

/* Our functions */
void print_hello(int);
void set_print_hello(void);

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
	void (*handler)(int);
	int i;

	handler = current_handler_signal();
	printf("Address of the current handler: %#lx\n", (unsigned long int)handler);

	/* Set 'print_hello()` as the handler for SIGINT */
	set_print_hello();

	handler = current_handler_signal();
	printf("Address of the 'print_hello' function: %#lx\n", (unsigned long int)&print_hello);
	printf("Address of the current handler: %#lx\n", (unsigned long int)handler);

	for (i = 0; ; i++)
	{
		printf("[%d] Wait for it ...\n", i);
		sleep(1);
	}
	return (EXIT_SUCCESS);
}

/**
 * print_hello - receives signal
 * @sig: the signal number received
 */
void print_hello(int sig)
{
	printf("Gotcha! [%d]\n", sig);
}

/**
 * set_print_hello - signal handler helper
 * Return: 0 on success else -1 on error
 */
void set_print_hello(void)
{
	int ret = signal(SIGINT, print_hello) == SIG_ERR ? -1 : 0;
}
