#include "../include/probabilities.h"
#include <stdlib.h>
#include <time.h>

uint8_t success(double p) {
  if (p <= 0 || p > 1)
    return 0;

  srand(time(NULL));
  return p >= (double)rand() / RAND_MAX ? 1 : 0;
}