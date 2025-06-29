#include <raylib.h>
#include <stdio.h>

#include "collisions.h"
#include "interface.h"
#include "state.h"

State state;

void update_and_draw(void) {
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

int main(void) {
  state = state_create();
  interface_init();

  while (!IsKeyPressed(KEY_ESCAPE))
    update_and_draw();

  interface_close();
  return 0;
}
