#pragma once // #include at most once

// Types used in many modules

// Use type "bool" for variables that only take true / false values
#include <stdbool.h>

// Pointer to an object of any type. It's just more readable than "void*" which looks like "void"
typedef void* Pointer;

// unsigned int, for brevity
typedef unsigned int uint;

// Pointer to a function that compares 2 elements a and b and returns:
// < 0 if a < b
// 0 if a and b are equivalent (_not_ readwise equal)
// > 0 if a > b
typedef int (*CompareFunc)(Pointer a, Pointer b);

// Pointer to a function that destroys an element value
typedef void (*DestroyFunc)(Pointer value);