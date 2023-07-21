#pragma once

#include "state.h"

// Updates the ball every frame
void update_pokeball(Object pokeball, KeyState keys, float speed_factor, int score);

// Updates platform on every frame
void update_platform(Object platform, float speed_factor);