#ifndef LAPS_H
#define LAPS_H

#include <stdlib.h>
#include <stdio.h>

/**
 * struct car - holds race car date
 * @id: the race car unique id
 * @laps: how many laps this car mae
 * @next: next node in linked list
 */
typedef struct car
{
	int id;
	size_t laps;
	struct car *next;
} Car;

void race_state(int *id, size_t size);

#endif
