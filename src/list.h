
#ifndef LIST_H
#define LIST_H

#include "types.h"

typedef struct node_s {
	void*          data;
	struct node_s* next;
} node_t;

typedef struct list_s {
	node_t* head;
} list_t;

list_t* list_create();

void
list_push(list_t* list, void* data);

void*
list_at(list_t* list, uint32_t idx);

void*
list_remove_last(list_t* list);

#endif // LIST_H
