#include <raylib.h>
#include "gameMain.h"
#include <asserts.h>
#include <assetManager.h>
#include <gameMap.h>


struct GameData
{
    GameMap gameMap;
    Camera2D camera;
}gameData;

AssetManager assetManager;

bool initGame()
{
    assetManager.loadAll();

    gameData.gameMap.create(30, 10);

    gameData.gameMap.getBlockUnsafe(0,0).type = Block::dirt;
    gameData.gameMap.getBlockUnsafe(1,1).type = Block::dirt;
    gameData.gameMap.getBlockUnsafe(2,2).type = Block::dirt;
    gameData.gameMap.getBlockUnsafe(3,3).type = Block::dirt;
    gameData.gameMap.getBlockUnsafe(4,4).type = Block::dirt;

    gameData.camera.target = { 0, 0 };
    gameData.camera.rotation = 0.0f;
    gameData.camera.zoom = 100.0f;

    return true;
}

bool updateGame()
{
    float deltaTime = GetFrameTime();
    if (deltaTime > 1.f / 5) { deltaTime = 1/5.f; }

    gameData.camera.offset = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};

    ClearBackground({75, 75, 150, 255});

    // Camera
    if (IsKeyDown(KEY_LEFT)) gameData.camera.target.x -= 3.f * deltaTime;
    if (IsKeyDown(KEY_RIGHT)) gameData.camera.target.x += 3.f * deltaTime;
    if (IsKeyDown(KEY_UP)) gameData.camera.target.y -= 3.f * deltaTime;
    if (IsKeyDown(KEY_DOWN)) gameData.camera.target.y += 3.f * deltaTime;

    if (IsKeyDown(KEY_EQUAL)) gameData.camera.zoom -= 100.f * deltaTime;
    if (IsKeyDown(KEY_MINUS)) gameData.camera.zoom += 100.f * deltaTime;
    BeginMode2D(gameData.camera);
    
    // Load map
    for (int y = 0; y < gameData.gameMap.h; y++)
    {
        for (int x = 0; x < gameData.gameMap.w; x++)
        {
            auto &b = gameData.gameMap.getBlockUnsafe(x, y);

            if(b.type != Block::air){
                float size = 1;
                float posX = x * size;
                float posY = y * size;

                DrawTexturePro( assetManager.dirt,
                                Rectangle{ 0.f, 0.f, (float)assetManager.dirt.width, (float)assetManager.dirt.height}, // Source
                                { posX, posY, size, size}, // Loaction
                                {0,0}, // origin (top left)
                                0.0f,  // Rotation
                                WHITE); // tint
            }
        }
    }

    // End camera
    EndMode2D();

    return true;
}

void closeGame()
{
    
}