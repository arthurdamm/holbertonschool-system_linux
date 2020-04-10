#include "signals.h"

#define USAGE "Usage: %s <pid>\n"

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
	return (!kill(atoi(av[1]), SIGINT) ? EXIT_SUCCESS : EXIT_FAILURE);
}
