#include "collisions.h"

void collision_with_platform(Object pokeball, Object platform)
{
    pokeball->rect.y = platform->rect.y - pokeball->rect.height + 2;
    pokeball->vert_mov = IDLE;

    if (platform->unstable)
        platform->vert_mov = FALLING;
}

bool collision_with_pokemon(Pokeball pokeball)
{
    return pokeball == POKEBALL ? rand() % 40 == 0 : pokeball == ULTRABALL ? rand() % 30 == 0 : true;
}