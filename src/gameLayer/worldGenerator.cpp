#include "worldGenerator.h"
#include "randomStuff.h"
#include <cmath>
void generateWorld(GameMap &gameMap, int seed)
{
    const int w = 200;
    const int h = 400;

    gameMap.create(w, h);

    int stoneSize = 50;
    int dirtSize = 300;
    
    std::ranlux24_base rng(seed);

    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
            Block b;

            if (y < h - stoneSize - dirtSize)
            {
                // Air
            }
            else
            if (y == h - stoneSize - dirtSize)
            {
                b.type = Block::grassBlock;
            }
            else
            if (y < h - stoneSize)
            {
                b.type = Block::dirt;
            }
            else
            {
                if (getRandomChance(rng, 0.9))
                {
                    b.type = Block::stone;
                }
                else
                {
                    b.type = Block::iron;
                }
            }

            gameMap.getBlockUnsafe(x, y) = b;
        }
    }
}