#include "laps.h"


/**
 * add_car - adds a car to linked list
 * @head: pointer to head node
 * @id: the car id to add
 */
void add_car(Car **head, int id)
{
	Car *node, *temp;

	if (!*head || id < (*head)->id)
	{
		node = malloc(sizeof(Car));
		if (!node)
			exit(EXIT_FAILURE);
		node->id = id;
		node->laps = 0;
		node->next = *head;
		*head = node;
		printf("Car %d joined the race\n", id);
		return;
	}
	for (node = *head; node->next && node->next->id <= id; node = node->next)
		;
	if (node->id == id)
	{
		node->laps++;
		return;
	}
	temp = malloc(sizeof(Car));
	if (!temp)
		exit(EXIT_FAILURE);
	temp->id = id;
	temp->laps = 0;
	temp->next = node->next;
	node->next = temp;
	printf("Car %d joined the race\n", id);
}

/**
 * race_state - determines the state
 * @id: array of vehicle ids
 * @size: size of above array
 */
void race_state(int *id, size_t size)
{
	static Car *head;
	Car *node;
	size_t i;

	if (!size)
	{
		while (head)
		{
			node = head;
			head = head->next;
			free(node);
		}
		return;
	}
	for (i = 0; i < size; i++)
		add_car(&head, id[i]);

	printf("Race state:\n");
	for (node = head; node; node = node->next)
		printf("Car %d [%lu laps]\n", node->id, node->laps);

}
