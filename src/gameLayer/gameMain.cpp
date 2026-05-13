#include <raylib.h>
#include "gameMain.h"
#include <asserts.h>
#include <assetManager.h>
#include <gameMap.h>
#include <helpers.h>
#include <cmath>

#include <imgui.h>
#include <rlImGui.h>

struct GameData
{
    GameMap gameMap;
    Camera2D camera;
}gameData;

AssetManager assetManager;

bool initGame()
{
    assetManager.loadAll();



    gameData.gameMap.create(30, 30);
     


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
    if (IsKeyDown(KEY_LEFT)) gameData.camera.target.x -= 30.f * deltaTime;
    if (IsKeyDown(KEY_RIGHT)) gameData.camera.target.x += 30.f * deltaTime;
    if (IsKeyDown(KEY_UP)) gameData.camera.target.y -= 30.f * deltaTime;
    if (IsKeyDown(KEY_DOWN)) gameData.camera.target.y += 30.f * deltaTime;

    if (IsKeyDown(KEY_EQUAL)) gameData.camera.zoom += 100.f * deltaTime;
    if (IsKeyDown(KEY_MINUS)) gameData.camera.zoom -= 100.f * deltaTime;
    BeginMode2D(gameData.camera);
    

    rlImGuiBegin();
    ImGui::Begin("test");
    static float sinHeight = 0;
    ImGui::SliderFloat("Sin Height", &sinHeight, 0, 10);
    static float fre = 0;
    ImGui::SliderFloat("Sin fre", &fre, 0, 10);

    ImGui::End();
    for (int y = 0; y < gameData.gameMap.h; y++)
    for (int x = 0; x < gameData.gameMap.w; x++)
    {
        
        float s = (std::sin(x) + 1.f) * sinHeight;
        float c = (std::sin(x + fre) + 1.f) / 2.f;

        if (gameData.gameMap.h - (gameData.gameMap.h * 0.1 * s) - gameData.gameMap.h *  0.1< y)
        {
            gameData.gameMap.getBlockUnsafe(x, y).type = Block::dirt;
        }
        else if (gameData.gameMap.h - (gameData.gameMap.h * 0.3 * c) - gameData.gameMap.h * 0.3 < y)
        {
            gameData.gameMap.getBlockUnsafe(x, y).type = Block::goldBlock;
        }
        else
        {
            gameData.gameMap.getBlockUnsafe(x, y).type = Block::air;
        }
    }


    // Load map
    for (int y = 0; y < gameData.gameMap.h; y++)
    {
        for (int x = 0; x < gameData.gameMap.w; x++)
        {
            auto &b = gameData.gameMap.getBlockUnsafe(x, y);

            if(b.type != Block::air){

                DrawTexturePro( assetManager.textures,
                                getTextureAtlas(b.type, 0 ,32, 32), // Source
                                { (float)x, (float)y, 1, 1}, // Loaction
                                {0,0}, // origin (top left)
                                0.0f,  // Rotation
                                WHITE); // tint
            }
        }
    }

    // End camera
    EndMode2D();


    rlImGuiEnd();
    return true;
}

void closeGame()
{
    
}