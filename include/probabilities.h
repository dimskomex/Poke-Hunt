#ifndef PROBABILITIES_H
#define PROBABILITIES_H

#include <stdint.h>

// Creates an experiment that succeeds with probability p.
// returns 0 if the experiment failed or p <= 0 or p > 1.
// returns 1 if the experiment was successful.
uint8_t success(double p);

#endif