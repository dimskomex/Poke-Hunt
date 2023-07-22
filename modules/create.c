#include "create.h"

static Pokemon create_legendary_pokemon(void)
{
    int x = rand() % 5;
    return x + MEWTWO;
}

static Pokemon create_iconic_pokemon(void)
{
    int x = rand() % 7;
    return x + GYARADOS;
}

static Pokemon create_classic_pokemon(void)
{
    int x = rand() % 8;
    return x + STARYU;
}

Pokemon create_pokemon(void)
{
    int x = rand();
    return x % 3 == 0 && x % 2 == 0 ? create_legendary_pokemon() : x % 2 == 0 ? create_iconic_pokemon() : create_classic_pokemon();
}