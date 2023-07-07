#pragma once

#include "state.h"

// Initializes the game interface
void interface_init();

// Closes the game interface
void interface_close();

// Draws a frame with the current state of the game
void interface_draw_frame(State state);