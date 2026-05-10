#include <raylib.h>
#include "gameMain.h"
#include <asserts.h>

struct GameData
{
    Texture dirtTexture;
}gameData;

bool initGame()
{
    
    
    return true;
}

bool updateGame()
{
    float deltaTime = GetFrameTime();
    if (deltaTime > 1.f / 5) { deltaTime = 1/5.f; }



    return true;
}

void closeGame()
{
    
}