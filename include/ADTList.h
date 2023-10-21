///////////////////////////////////////////////////////////////////
//                                                               //
// ADT List                                                      //
//                                                               //
// Abstract list. It provides serial access to the elements, and //
// add/remove anywhere in the list.                              //
//                                                               // 
///////////////////////////////////////////////////////////////////

#pragma once // #include at most once

#include "common_types.h"

// These constants represent virtual nodes _before_ the first and _after_ the last
#define LIST_BOF (ListNode)0
#define LIST_EOF (ListNode)0


// Lists and nodes are represented by the List and ListNode types. The user does not need to know the content
// of these types, it simply uses the list_<foo> functions that accept and return a List / ListNode.
//
// These types are defined as pointers to "struct list" and "struct list_node" whose
// content is unknown (incomplete structs), and depends on the ADT List implementation.

typedef struct list* List;
typedef struct list_node* ListNode;


// Creates and returns a new list.
// If destroy_value != NULL, then destroy_value(value) is called every time an element is removed.
List list_create(DestroyFunc destroy_value);


// Returns the number of elements the list contains.
int list_size(List list);


// Adds a new node __after__ node, or at the beginning if node == LIST_BOF, with value content.
void list_insert_next(List list, ListNode node, void * value);


// Removes the __next__ node from node, or the first node if node == LIST_BOF.
// If the node has no next the behavior is undefined.
void list_remove_next(List list, ListNode node);


// Returns the first value that is equivalent to value
// (based on the compare function), or NULL if not present
void * list_find(List list, void * value, CompareFunc compare);


// Changes the function called on each element removal/replacement to
// destroy_value. Returns the previous value of the function.
DestroyFunc list_set_destroy_value(List list, DestroyFunc destroy_value);


// Frees all the memory bound by the list list.
// Any operation on the list after destroy is undefined.
void list_destroy(List list);


///////////////////////////
//   Traverse the list   //
///////////////////////////


// Return the first and last node of the list, or LIST_BOF / LIST_EOF respectively if the list is empty
ListNode list_first(List list);
ListNode list_last(List list);


// Returns the node after node, or LIST_EOF if node is the last
ListNode list_next(ListNode node);


// Returns the previous node of node or LIST_BOF if the node is the first
ListNode list_previous(List list, ListNode node);


// Returns the content of the node node
void * list_node_value(ListNode node);


// Finds the first element that is equivalent to value (based on the compare function).
// Returns the element node, or LIST_EOF if not found.
ListNode list_find_node(List list, void * value, CompareFunc compare);