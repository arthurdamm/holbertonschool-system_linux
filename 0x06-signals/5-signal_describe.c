#include "signals.h"

#define USAGE "Usage: %s <signum>\n"

/**
 * main - entry point
 * @ac: argument count
 * @av: argument vector
 * Return: Success or Failure
 */
int main(int ac, char **av)
{
	if (ac != 2)
		return (printf(USAGE, av[0]), EXIT_FAILURE);
	if (strsignal(atoi(av[1])))
		printf("%d: %s\n", atoi(av[1]), strsignal(atoi(av[1])));
	else
		printf("%d Unknown signal %d\n", atoi(av[1]), atoi(av[1]));
	return (EXIT_SUCCESS);
}
