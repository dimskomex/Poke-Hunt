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
    switch (pokeball)
    {
        case CLASSIC_POKEBALL:
            if (is_legendary(pokemon))
                return x % 50 == 0;
            else if (is_iconic(pokemon))
                return x % 40 == 0;
            else
                return x % 30 == 0;
    
        case GREAT_BALL:
            if (is_legendary(pokemon))
                return x % 45 == 0;
            else if (is_iconic(pokemon))
                return x % 35 == 0;
            else
                return x % 25 == 0;

        case ULTRABALL:
            if (is_legendary(pokemon))
                return x % 40 == 0;
            else if (is_iconic(pokemon))
                return x % 30 == 0;
            else
                return x % 20 == 0;

        case TIMERBALL:
            if (is_legendary(pokemon))
                return x % 35 == 0;
            else if (is_iconic(pokemon))
                return x % 30 == 0;
            else
                return x % 20 == 0;
    }

    return true;
}