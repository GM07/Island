#include "../include/headers.h"
#include "../include/Game.h"

#include "../include/Math/PerlinNoise.h"
#include "../include/Map/Map.h"

int main()
{
    srand(time(0));

    Game game;
    game.run();

    return 0;
}