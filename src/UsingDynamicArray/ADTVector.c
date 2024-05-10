/////////////////////////////////////////////////////
//												   //
// Implementation of ADT Vector via Dynamic Array. //
//												   //
/////////////////////////////////////////////////////

#include <stdlib.h>
#include <assert.h>

#include "../../include/ADTVector.h"

// The initial size we're binding
#define VECTOR_MIN_CAPACITY 10

// A VectorNode is a Pointer to this struct. (struct only contains one element, so we'd go ahead and avoid it, but it makes the code simpler)
struct vector_node 
{
	void *value;				// The value of node.
};

struct vector 
{
	VectorNode array; 			// The data, array from struct vector_node
	int size; 					// How many elements we have added
	int capacity; 				// How much space we have reserved (the size of the array). Always capacity >= size, but we may have
	DestroyFunc destroy_value; 	// Function that destroys an element of the vector.
};


Vector vector_create(int size, DestroyFunc destroy_value) 
{
	// Create the struct
	Vector vec = malloc(sizeof(*vec));

	vec->size = size;
	vec->destroy_value = destroy_value;

	// Allocate memory for the array. Initially the vector contains size
	// uninitialized elements, but we reserve space for at least
	// VECTOR_MIN_CAPACITY to avoid multiple resizes.
	vec->capacity = size < VECTOR_MIN_CAPACITY ? VECTOR_MIN_CAPACITY : size;
	vec->array = calloc(vec->capacity, sizeof(*vec->array));		// initialize to 0 (NULL)

	return vec;
}

int vector_size(Vector vec) 
{
	return vec->size;
}

void *vector_get_at(Vector vec, int pos) 
{
	assert(pos >= 0 && pos < vec->size);

	return vec->array[pos].value;
}

void vector_set_at(Vector vec, int pos, void *value) 
{
	assert(pos >= 0 && pos < vec->size);	// LCOV_EXCL_LINE

	// If there is a destroy_value function, call it for the element being replaced
	if (value != vec->array[pos].value && vec->destroy_value != NULL)
		vec->destroy_value(vec->array[pos].value);

	vec->array[pos].value = value;
}

void vector_insert_last(Vector vec, void *value) 
{
	// We increase the table (if necessary) so that it can hold at least size elements
	// Double the capacity each time (important for complexity!)
	if (vec->capacity == vec->size) {
		// Attention: we should not free the old pointer, realloc does that
		vec->capacity *= 2;
		vec->array = realloc(vec->array, vec->capacity * sizeof(*vec->array)); }

	// Grow the array and add the element
	vec->array[vec->size].value = value;
	vec->size++;
}

void vector_remove_last(Vector vec) 
{
	assert(vec->size != 0);		// LCOV_EXCL_LINE

	// If there is a destroy_value function, call it for the element being removed
	if (vec->destroy_value != NULL)
		vec->destroy_value(vec->array[vec->size - 1].value);

	// We remove an element so the array gets smaller
	vec->size--;

	// Shrink the array if necessary so there is not too much wasted space.
	// For complexity it's important to halve the size, that's all
	// if capacity is four times the size (ie 75% of the array is empty).
	if (vec->capacity > vec->size * 4 && vec->capacity > 2*VECTOR_MIN_CAPACITY) {
		vec->capacity /= 2;
		vec->array = realloc(vec->array, vec->capacity * sizeof(*vec->array));
	}
}

void vector_remove(Vector vec, int pos)
{
    // Shift elements to the left starting from the given position
    // by overwriting each element with the value of the next element.
    // Stop at the second-to-last element since the last element will be removed.
    for (int i = pos; i < vector_size(vec) - 1; i++) {
        // Get the void *to the current element at position i
        void *p = vector_get_at(vec, i + 1);

        // Overwrite the current element at position i with the value
        // of the next element at position i + 1
        vector_set_at(vec, i, p);
    }

    // Remove the last element from the vector
    vector_remove_last(vec);
}

void *vector_find(Vector vec, void *value, CompareFunc compare) 
{
	// cross the vector
	for (int i = 0; i < vec->size; i++) {
		if (compare(vec->array[i].value, value) == 0)
			return vec->array[i].value;			// Found
	}

	return NULL;								// Not found
}

DestroyFunc vector_set_destroy_value(Vector vec, DestroyFunc destroy_value) 
{
	DestroyFunc old = vec->destroy_value;
	vec->destroy_value = destroy_value;
	return old;
}

void vector_destroy(Vector vec) 
{
	// If there is a destroy_value function, we call it for all elements
	if (vec->destroy_value != NULL) {
		for (int i = 0; i < vec->size; i++)
			vec->destroy_value(vec->array[i].value);
	}
		
	// We need to free both the array and the struct!
	free(vec->array);
	free(vec);			// last the vec!
}


//////////////////////////////////////////
// Functions for traversal through node //
//////////////////////////////////////////

VectorNode vector_first(Vector vec) 
{
	return vec->size == 0 ? VECTOR_EOF : &vec->array[0];
}

VectorNode vector_last(Vector vec) 
{
	return vec->size == 0 ? VECTOR_EOF : &vec->array[vec->size-1];
}

VectorNode vector_next(Vector vec, VectorNode node) 
{
	return node == &vec->array[vec->size-1] ? VECTOR_EOF : node + 1;
}

VectorNode vector_previous(Vector vec, VectorNode node) 
{
	return node == &vec->array[0] ? VECTOR_EOF : node - 1;
}

void *vector_node_value(VectorNode node) 
{
	return node->value;
}

VectorNode vector_find_node(Vector vec, void *value, CompareFunc compare)
{
	// Cross the vector
	for (int i = 0; i < vec->size; i++) {
		if (compare(vec->array[i].value, value) == 0)
			return &vec->array[i]; 				// Found
	}

	return VECTOR_EOF; 							// Not found
}
