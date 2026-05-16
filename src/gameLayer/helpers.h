#pragma once

#include <raylib.h>
#include <gameMap.h>

Rectangle getTextureAtlas(int x, int y, int cellSizePixelsX, int cellSizePixelsY);
int getWoodLogType(int x, int y, GameMap gameMap);