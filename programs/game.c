#include <stdio.h>
#include "raylib.h"

#include "interface.h"
#include "state.h"
#include "collisions.h"

State state;

void update_and_draw(void)
{
    struct key_state keys;

    keys.up = IsKeyDown(KEY_UP);
    keys.enter = IsKeyDown(KEY_ENTER);
    keys.left = IsKeyDown(KEY_LEFT);
    keys.right = IsKeyDown(KEY_RIGHT);
    keys.n = IsKeyDown(KEY_N);
    keys.p = IsKeyDown(KEY_P);

	state_update(state, &keys);
	interface_draw_frame(state);
}

int main(void) 
{
	state = state_create();
	interface_init();

	// This call repeatedly calls update_and_draw until the user closes the window
	start_main_loop(update_and_draw);

	interface_close();

	return 0;
}
