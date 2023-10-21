#pragma once // #include at most once

// Types used in many modules

// Pointer to a function that compares 2 elements a and b and returns:
// < 0 if a < b
// 0 if a and b are equivalent (_not_ readwise equal)
// > 0 if a > b
typedef int (*CompareFunc)(void *a, void *b);

// Pointer to a function that destroys an element value
typedef void (*DestroyFunc)(void *value);