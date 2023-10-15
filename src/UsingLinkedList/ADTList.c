//////////////////////////////////////////
//										//
// Implement ADT List via linked list.  //
//										//
//////////////////////////////////////////

#include <stdlib.h>
#include <assert.h>

#include "ADTList.h"


// A List is a pointer to this struct
struct list
{
	ListNode dummy; 			// we use dummy node so that even the empty list has a node.
	ListNode last; 				// pointer to last node, or dummy (if list is empty)
	int size; 					// size so list_size is O(1)
	DestroyFunc destroy_value; 	// Function that destroys an element of the list.
};

struct list_node 
{
	ListNode next; 	// Pointer to next
	Pointer value; 	// The value we store in the node
};


List list_create(DestroyFunc destroy_value) 
{
	// First we create the stuct
	List list = malloc(sizeof(*list));
	list->size = 0;
	list->destroy_value = destroy_value;

	// We use dummy node so that even an empty list has a node
	// (simplifies algorithms). So we have to create him.
	list->dummy = malloc(sizeof(*list->dummy));
	list->dummy->next = NULL; // empty list, dummy has no next

	// In an empty list, last node is also dummy
	list->last = list->dummy;

	return list;
}

int list_size(List list) 
{
	return list->size;
}

void list_insert_next(List list, ListNode node, Pointer value) 
{
	// If the node is NULL, simply insert after the dummy node!
	// This is exactly the dummy value, we don't need a separate implementation.
	if (node == NULL)
		node = list->dummy;

	// Create the new node
	ListNode new = malloc(sizeof(*new));
	new->value = value;

	// Connection of new between node and node->next
	new->next = node->next;
	node->next = new;

	// Update size & last
	list->size++;

	if (list->last == node)
		list->last = new;
}

void list_remove_next(List list, ListNode node) 
{
	// If the node is NULL we simply delete after the dummy node!
	// This is exactly the dummy value, we don't need a separate implementation.
	if (node == NULL)
		node = list->dummy;

	// The node to delete is the next node, which must exist
	ListNode removed = node->next;
	assert(removed != NULL); // LCOV_EXCL_LINE

	if (list->destroy_value != NULL)
		list->destroy_value(removed->value);

	// Connection of the node with the next removed
	node->next = removed->next; // before free!

	free(removed);

	// Update size & last
	list->size--;

	if (list->last == removed)
		list->last = node;
}

Pointer list_find(List list, Pointer value, CompareFunc compare) 
{
	ListNode node = list_find_node(list, value, compare);
	return node == NULL ? NULL : node->value;
}

DestroyFunc list_set_destroy_value(List list, DestroyFunc destroy_value) 
{
	DestroyFunc old = list->destroy_value;
	list->destroy_value = destroy_value;
	return old;
}

void list_destroy(List list) 
{
	// Traverse the entire list and free all nodes,
	// including dummy!
	ListNode node = list->dummy;
	while (node != NULL) { 			// while instead of for, because we want to read 
		ListNode next = node->next; // node->next _before_ we do free!

		// Call destroy_value if it exists (careful, not on dummy!)
		if (node != list->dummy && list->destroy_value != NULL)
		list->destroy_value(node->value);

		free(node);
		node = next;
	}

	// Finally free the struct itself
	free(list);
}

///////////////////////
// Traverse the list //
///////////////////////

ListNode list_first(List list) 
{
	// The first node is the dummy's next node.
	return list->dummy->next;
}

ListNode list_last(List list) 
{
	// Be careful, if the list is empty last points to the dummy, but we want to return NULL, not the dummy!
	return list->last == list->dummy ? LIST_EOF : list->last;
}

ListNode list_next(ListNode node) 
{
	assert(node != NULL);
	return node->next;
}

ListNode list_previous(List list, ListNode node)
{
	for (ListNode find_node = list->dummy->next; find_node != LIST_EOF; find_node = find_node->next) {
		if (find_node->next == node)
			return find_node;
	}
		
	return LIST_BOF;
}

Pointer list_node_value(ListNode node) 
{
	assert(node != NULL);	
	return node->value;
}

ListNode list_find_node(List list, Pointer value, CompareFunc compare) 
{
	// traverse the entire list, call compare until it returns 0
	for (ListNode node = list->dummy->next; node != NULL; node = node->next) {
		if (compare(value, node->value) == 0)
			return node;		// Found
	}

	return NULL;				// Not found
}