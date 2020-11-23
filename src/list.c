#include "list.h"
#include "utils.h"

list_t*
list_create()
{
	list_t* new_list = NEW(list_t);
	new_list->head = NULL;
	return new_list;
}

void
list_push(list_t* list, void* data)
{
	if (list->head == NULL) {
		list->head = NEW(node_t);
		list->head->data = data;
		list->head->next = NULL;
		return;
	}

	node_t* curr = list->head;

	while (curr->next != NULL) {
		curr = curr->next;
	}

	/* now we can add a new variable */
	curr->next = NEW(node_t);

	ASSERT((curr->next == NULL), "Failed to create list node");

	curr->next->data = data;
	curr->next->next = NULL;
}

void*
list_at(list_t* list, uint32_t idx)
{
	uint32_t count = 0;
	
	node_t* curr = list->head;

	while (curr != NULL) {
		if (count == idx)
			return curr->data;
		count++;
		curr = curr->next;
	}

	return NULL;
}

void*
list_remove_last(list_t* list)
{
	void* ret_data = NULL;

	/* if there is only one item in the list, remove it */
	if (list->head->next == NULL) {
		ret_data = list->head->data;
		free(list->head);
		return ret_data;
	}

	/* get to the second to last node in the list */
	node_t* current = list->head;
	while (current->next->next != NULL)
		current = current->next;

	/* now current points to the second to last item of the list, so let's remove current->next */
	ret_data = current->next->data;
	free(current->next);
	current->next = NULL;

	return ret_data;
}
