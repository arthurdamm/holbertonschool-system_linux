#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/**
 * main - uses strdup to create a new string, loops forever-ever
 *
 * Return: EXIT_FAILURE if malloc failed. Other never returns
 */
int main(void)
{
	char *s;
	unsigned long int i;

	/* allocate a duplicate of our string literal "Holberton School" */
	s = strdup("Holberton School");
	if (s == NULL) /* check if the allocation failed for any reason */
	{
		fprintf(stderr, "Can't allocate mem with malloc\n");
		return (EXIT_FAILURE);
	}
	i = 0;
	while (s) /* loop while the string pointer is not NULL */
	{
		/* print the: loop iteration, string value, memory address */
		printf("[%lu] %s (%p)\n", i, s, (void *)s);
		sleep(1); /* pause 1 second */
		i++; /* increment iteration count */
	}
	return (EXIT_SUCCESS);
}
