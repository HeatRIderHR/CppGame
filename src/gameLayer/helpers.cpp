#include "helpers.h"

Rectangle getTextureAtlas(int x, int y, int cellSizePixelsX, int cellSizePixelsY)
{
    return Rectangle{ (float)x * cellSizePixelsX, (float)y * cellSizePixelsY, (float)cellSizePixelsX, (float)cellSizePixelsY };
}

int getWoodLogType(int x, int y, GameMap gameMap)
{
    int logType = 0;

    if  (
            (*gameMap.getBlockSafe(x - 1, y)).type == Block::leaves &&
            (*gameMap.getBlockSafe(x + 1, y)).type == Block::leaves &&
            (*gameMap.getBlockSafe(x, y - 1)).type == Block::leaves
        )
    {
        logType = 5;
    }
    else if 
        (
            (*gameMap.getBlockSafe(x - 1, y)).type == Block::leaves &&
            (*gameMap.getBlockSafe(x + 1, y)).type == Block::leaves 
        )
    {
        logType = 1;
    }
    else if 
        (
            (*gameMap.getBlockSafe(x + 1, y)).type == Block::leaves
        )
    {
        logType = 2;
    }
    else if 
        (
            (*gameMap.getBlockSafe(x - 1, y)).type == Block::leaves
        )
    {
        logType = 3;
    }
    else if 
        (
            ((*gameMap.getBlockSafe(x, y + 1)).type == Block::grassBlock ||
            (*gameMap.getBlockSafe(x, y + 1)).type == Block::dirt) &&
            (*gameMap.getBlockSafe(x, y - 1)).type == Block::air
        )
    {
        logType = 7;
    }

    else if 
        (
            (*gameMap.getBlockSafe(x, y + 1)).type == Block::grassBlock ||
            (*gameMap.getBlockSafe(x, y + 1)).type == Block::dirt
        )
    {
        logType = 4;
    }
        else if 
        (
            (*gameMap.getBlockSafe(x, y - 1)).type == Block::air
        )
    {
        logType = 6;
    }
    return logType;
}