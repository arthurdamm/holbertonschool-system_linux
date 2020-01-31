#ifndef LISTS_H
#define LISTS_H

#include "hls.h"

list_t *add_node(list_t **head, File *file);
list_t *add_node_end(list_t **head, File *file);
void free_list(list_t *head);
size_t print_list(const list_t *h);
char *pop_list(list_t **head);

#endif
