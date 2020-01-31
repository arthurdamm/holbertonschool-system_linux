#ifndef LISTS_H
#define LISTS_H

#include "hls.h"

/**
 * struct list_s - singly linked list
 * @file: the file struct value
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 * for Holberton project
 */
typedef struct list_s
{
	File file;
	struct list_s *next;
} list_t;


list_t *add_node(list_t **head, File *file);
list_t *add_node_end(list_t **head, File *file);

#endif
