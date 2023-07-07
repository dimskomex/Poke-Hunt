#pragma once

#include "state.h"

// Updates the ball every frame
void update_ball(Object ball, KeyState keys, float speed_factor);

// Updates platform on every frame
void update_platform(Object platform, Object ball, float speed_factor);