#include "worldGenerator.h"
#include "randomStuff.h"
#include <raymath.h>
#include <iostream>

void generateWorld(GameMap &gameMap, int seed)
{
    const int w = 1000;
    const int h = 400;

    gameMap.create(w, h);

    int dirtMinSize  = gameMap.h * 0.05;
    int stoneMinSize = gameMap.h * 0.25;
    int dirtSize     = dirtMinSize;
    int stoneSize    = stoneMinSize;

    float maxHightFactor = 1.5;
    std::ranlux24_base rng(seed);


    for (int x = 0; x < w; x++)
    {
        dirtSize = floor(2.0f * (std::pow(std::sin(x / 7), 2) / std::sin(x / 7))) + dirtMinSize;
       
        stoneSize = floor(6.0f * std::pow((1 + std::sin((x * PI) / 50 + 2 * PI)), 2)) + stoneMinSize;
        

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