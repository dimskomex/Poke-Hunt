#include <stdlib.h>

#include "collisions.h"

void collision_with_platform(Object pokeball, Object platform)
{
    pokeball->rect.y = platform->rect.y - pokeball->rect.height + 2;
    pokeball->vert_mov = IDLE;

    if (platform->unstable)
        platform->vert_mov = FALLING;
}

static bool is_legendary(Pokemon pokemon)
{
    return (pokemon >= MEWTWO && pokemon <= ZEKROM);
}

static bool is_iconic(Pokemon pokemon)
{
    return (pokemon >= GYARADOS && pokemon <= LUCARIO);
}

bool collision_with_pokemon(Pokeball pokeball, Pokemon pokemon)
{
    int x = rand();
    switch (pokeball) {
    case CLASSIC_POKEBALL:
        return is_legendary(pokemon) ? x % 50 == 0 : is_iconic(pokemon) ? x % 40 == 0 : x % 30 == 0;

    case GREAT_BALL:
        return is_legendary(pokemon) ? x % 45 == 0 : is_iconic(pokemon) ? x % 35 == 0 : x % 25 == 0;

    case ULTRABALL:
        return is_legendary(pokemon) ? x % 40 == 0 : is_iconic(pokemon) ? x % 30 == 0 : x % 20 == 0;

    case TIMERBALL:
        return is_legendary(pokemon) ? x % 35 == 0 : is_iconic(pokemon) ? x % 30 == 0 : x % 20 == 0;

    case MASTERBALL:
        return true;
    }

    return true;
}