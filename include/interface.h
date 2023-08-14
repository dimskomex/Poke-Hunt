#pragma once

#include "state.h"

// Initializes the game interface
void interface_init(void);

// Closes the game interface
void interface_close(void);

// Draws a frame with the current state of the game
void interface_draw_frame(State state);