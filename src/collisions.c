#include <stdlib.h>

#include "collisions.h"
#include "probabilities.h"

void collision_with_platform(Object pokeball, Object platform) {
  pokeball->rect.y = platform->rect.y - pokeball->rect.height + 2;
  pokeball->vert_mov = IDLE;

  if (platform->unstable)
    platform->vert_mov = FALLING;
}

static bool is_legendary(Pokemon pokemon) {
  return (pokemon >= MEWTWO && pokemon <= ZEKROM);
}

static bool is_iconic(Pokemon pokemon) {
  return (pokemon >= GYARADOS && pokemon <= LUCARIO);
}

int collision_with_pokemon(Pokeball pokeball, Pokemon pokemon) {
  switch (pokeball) {
  case CLASSIC_POKEBALL:
    return is_legendary(pokemon) ? success(0.01)
           : is_iconic(pokemon)  ? success(0.26)
                                 : success(0.31);

  case GREAT_BALL:
    return is_legendary(pokemon) ? success(0.1)
           : is_iconic(pokemon)  ? success(0.31)
                                 : success(0.36);

  case ULTRABALL:
    return is_legendary(pokemon) ? success(0.15)
           : is_iconic(pokemon)  ? success(0.4)
                                 : success(0.42);

  case MASTERBALL:
    return 1;
  }

  return 1;
}