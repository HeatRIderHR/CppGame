// External Libarys
#include <raylib.h>
#include <cmath>
// Testing
#include <imgui.h>
#include <rlImGui.h>

// Internal Files
#include "gameMain.h"
#include <asserts.h>
#include <assetManager.h>
#include <gameMap.h>
#include <helpers.h>


struct GameData
{
    GameMap gameMap;
    Camera2D camera;
}gameData;

AssetManager assetManager;

bool initGame()
{
    assetManager.loadAll();

    gameData.gameMap.create(100, 100);
    
    for (int y = 0; y < gameData.gameMap.h; y++)
        for (int x = 0; x < gameData.gameMap.w; x++)
        {
            if (x == 0 || y == 0)
            {
                gameData.gameMap.getBlockUnsafe(x, y).type = Block::dirt;
            }
        }
    // Camera
    gameData.camera.target = { 0, 0 };
    gameData.camera.rotation = 0.0f;
    gameData.camera.zoom = 100.0f;

    return true;
}

bool updateGame()
{
    // Delta Time
    float deltaTime = GetFrameTime();
    if (deltaTime > 1.f / 5) { deltaTime = 1/5.f; }

    // Camera
    gameData.camera.offset = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};

    if (IsKeyDown(KEY_LEFT)) gameData.camera.target.x -= 30.f * deltaTime;
    if (IsKeyDown(KEY_RIGHT)) gameData.camera.target.x += 30.f * deltaTime;
    if (IsKeyDown(KEY_UP)) gameData.camera.target.y -= 30.f * deltaTime;
    if (IsKeyDown(KEY_DOWN)) gameData.camera.target.y += 30.f * deltaTime;

    if (IsKeyDown(KEY_EQUAL)) gameData.camera.zoom += 100.f * deltaTime;
    if (IsKeyDown(KEY_MINUS)) gameData.camera.zoom -= 100.f * deltaTime;
    BeginMode2D(gameData.camera);

    // Current Block
    Vector2 worldPos = GetScreenToWorld2D(GetMousePosition(), gameData.camera);
    int blockX = (int)floor(worldPos.x);
    int blockY = (int)floor(worldPos.y);

    // Place Blocks
    static int currentBlock = 1;
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        auto b = gameData.gameMap.getBlockSafe(blockX, blockY);
        if (b)
        {
            *b = {};
        }
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
        auto b = gameData.gameMap.getBlockSafe(blockX, blockY);
        if (b)
        {
            b->type = currentBlock;
        }
    }
    int mouseWheel = GetMouseWheelMove();
    if (0 < currentBlock + mouseWheel && currentBlock + mouseWheel < Block::BLOCKS_COUNT)
    {
        currentBlock += mouseWheel;
    }

    // Map test code
    // rlImGuiBegin();
    // ImGui::Begin("test");
    // static float sinHeight = 0;
    // ImGui::SliderFloat("Sin Height", &sinHeight, 0, 10);
    // static float fre = 0;
    // ImGui::SliderFloat("Sin fre", &fre, 0, 10);

    // ImGui::End();
    
    // for (int y = 0; y < gameData.gameMap.h; y++)
    // for (int x = 0; x < gameData.gameMap.w; x++)
    // {
        
    //     float s = (std::sin(x) + 1.f) * sinHeight;
    //     float c = (std::sin(x + fre) + 1.f) / 2.f;

    //     if (gameData.gameMap.h - (gameData.gameMap.h * 0.1 * s) - gameData.gameMap.h *  0.1< y)
    //     {
    //         gameData.gameMap.getBlockUnsafe(x, y).type = Block::dirt;
    //     }
    //     else if (gameData.gameMap.h - (gameData.gameMap.h * 0.3 * c) - gameData.gameMap.h * 0.3 < y)
    //     {
    //         gameData.gameMap.getBlockUnsafe(x, y).type = Block::goldBlock;
    //     }
    //     else
    //     {
    //         gameData.gameMap.getBlockUnsafe(x, y).type = Block::snow2;
    //     }
    // }


    // Load map

    ClearBackground({75, 75, 150, 255});

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
                DrawTexturePro( assetManager.textures,
                                getTextureAtlas(b.type, 0 ,32, 32), // Source
                                { (float)x, (float)y, 1, 1}, // Loaction
                                {0,0}, // origin (top left)
                                0.0f,  // Rotation
                                WHITE); // tint
            }
        }
    }
    // draw selected block
    DrawTexturePro( assetManager.textures,
        getTextureAtlas(currentBlock, 0 ,32, 32),
        {(float)blockX, (float)blockY, 1, 1},
        {0,0},
        0.0f,
        WHITE
    );
    DrawTexturePro(
        assetManager.frame,
        {0,0, (float)assetManager.frame.width, (float)assetManager.frame.height},
        {(float)blockX, (float)blockY, 1, 1},
        {0,0},
        0.0f,
        WHITE
    );

    
    // End camera & ImGui
    EndMode2D();
    //rlImGuiEnd();
    return true;
}

void closeGame()
{
    
}