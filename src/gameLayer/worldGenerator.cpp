#include "worldGenerator.h"
#include "randomStuff.h"

void generateWorld(GameMap &gameMap, int seed)
{
    const int w = 200;
    const int h = 400;

    gameMap.create(w, h);

    int stoneSize = 50;
    int dirtSize = 300;
    
    

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
                b.type = Block::stone;
            }

            gameMap.getBlockUnsafe(x, y) = b;
        }
    }
}