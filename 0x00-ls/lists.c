#include "lists.h"

/**
 * add_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @file: file field of node
 *
 * Return: size of list
 */
list_t *add_node(list_t **head, File *file)
{
	list_t *new_head = malloc(sizeof(list_t));

	if (!head || !new_head)
		return (NULL);
	if (file)
		new_head->file = *file;

	new_head->next = *head;
	*head = new_head;
	return (new_head);
}


/**
 * add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @file: file field of node
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **head, File *file)
{
	list_t *new_node = malloc(sizeof(list_t));
	list_t *node = *head;

	if (!head || !new_node)
		return (NULL);
	if (file)
		new_node->file = *file;
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * free_list - frees all nodes of a list
 * @head: pointer to head node
 *
 * Return: void
 */
void free_list(list_t *head)
{
	list_t *node, *next_node;

	if (!head)
		return;

	node = head;
	while (node)
	{
		next_node = node->next;
		free(node);
		node = next_node;
	}
}

/**
 * print_list - prints a linked lists
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		printf("[%s]\n", h->file.name);
		h = h->next;
		i++;
	}
	return (i);
}
