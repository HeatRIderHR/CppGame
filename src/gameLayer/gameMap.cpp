#include "gameMap.h"
#include <asserts.h>

void GameMap::create(int w, int h)
{
    *this = {}; // Reset all data
    mapData.resize(w * h);

    this->w = w;
    this->h = h;

    for (auto &e : mapData) { e = {}; } // Clears all block data
}

Block &GameMap::getBlockUnsafe(int x, int y) 
{
    permaAssertCommentDevelopement(mapData.size() == w * h, "Map data not initialized");
    permaAssertCommentDevelopement(x >= 0 && y >0 && x < w && y < h, "getBlockUnsafe out of bounds error");

    return mapData[x + y * w];
}

Block *GameMap::getBlockSafe(int x, int y) 
{
    permaAssertCommentDevelopement(mapData.size() == w * h, "Map data not initialized");

    return &mapData[x + y * w];
}