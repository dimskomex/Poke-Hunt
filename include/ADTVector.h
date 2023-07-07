////////////////////////////////////////////////////////////
//                                                        //
// ADT Vector                                             //
//                                                        //
// Abstract "array" of variable size. Provides access to  //
// any element (via its position), and add/remove         //
// elements at the end of the vector.                     //
//                                                        //
////////////////////////////////////////////////////////////

#pragma once // #include at most once

#include "common_types.h"


// A vector is represented by the Vector type. The user does not need to know the content
// of this type, it simply uses the vector_<foo> functions that accept and return Vector.
//
// The Vector type is defined as a pointer to "struct vector" whose content is unknown
// (incomplete struct), and depends on the ADT Vector implementation.
typedef struct vector* Vector;


// Creates and returns a new size vector, with elements initialized to NULL.
// If destroy_value != NULL, then destroy_value(value) is called whenever an element is removed (or replaced).
Vector vector_create(int size, DestroyFunc destroy_value);


// Returns the number of elements the vector vec contains.
int vector_size(Vector vec);


// Adds the value value to the _end_ of the vector vec. The size of the vector increases by 1.
void vector_insert_last(Vector vec, Pointer value);


// Removes the last element of the vector. The size of the vector is reduced by 1.
// If the vector is empty the behavior is undefined.
void vector_remove_last(Vector vec);


// Deletes the vector component in place of pos
void vector_remove(Vector vec, int pos);


// Returns the value at position pos of vector vec (undefined result if pos < 0 or pos >= size)
Pointer vector_get_at(Vector vec, int pos);


// Changes the value at pos of Vector vec to value.
// DO NOT resize the vector, if pos >= size the result is undefined.
void vector_set_at(Vector vec, int pos, Pointer value);


// Finds and returns the first element in the vector equal to value
// (based on the compare function), or NULL if no element is found.
Pointer vector_find(Vector vec, Pointer value, CompareFunc compare);


// Changes the function called on each element removal/replacement to
// destroy_value. Returns the previous value of the function.
DestroyFunc vector_set_destroy_value(Vector vec, DestroyFunc destroy_value);


// Frees all memory bound by vector vec.
// Any operation on the vector after destroy is undefined.
void vector_destroy(Vector vec);

//////////////////////////
//   Cross the vector   //
//////////////////////////

// The following functions allow traversing the vector through nodes.
// Not as commonly used as other ADTs, because we can
// easy to traverse the vector and through indexes. Still useful though,
// both for consistency with other ADTs, but also because for some implementations
// traversal through nodes can be faster.

// These constants represent virtual nodes _before_ the first and _after_ the last
#define VECTOR_BOF (VectorNode)0
#define VECTOR_EOF (VectorNode)0

typedef struct vector_node* VectorNode;


// Return the first and last nodes of the vector, or VECTOR_BOF / VECTOR_EOF respectively if the vector is empty
VectorNode vector_first(Vector vec);
VectorNode vector_last(Vector vec);


// Return the next and previous nodes of node, or VECTOR_EOF / VECTOR_BOF
// respectively if the node has no next / previous.
VectorNode vector_next(Vector vec, VectorNode node);
VectorNode vector_previous(Vector vec, VectorNode node);


// Returns the content of the node node
Pointer vector_node_value(Vector vec, VectorNode node);


// Finds the first element in the vector that is equal to value (based on the compare function).
// Returns the node of the element, or VECTOR_EOF if not found.
VectorNode vector_find_node(Vector vec, Pointer value, CompareFunc compare);