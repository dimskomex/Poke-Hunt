#pragma once

#include "state.h"
#include <stdbool.h>

void collision_with_platform(Object pokeball, Object platform);

// checks whether the collision between Pokeball and Pokemon succeeded
bool collision_with_pokemon(Pokeball pokeball, Pokemon pokemon);