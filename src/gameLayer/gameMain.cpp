// External Libarys
#include <raylib.h>
#include <raymath.h>
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

    // Screen View
    Vector2 topLeftView = GetScreenToWorld2D({ 0,0 }, gameData.camera);
    Vector2 bottomRightView = GetScreenToWorld2D({ (float)GetScreenWidth(), (float)GetScreenHeight() }, gameData.camera);

    int startXView = Clamp((int)floor(topLeftView.x - 1),     0, gameData.gameMap.w - 1);
    int endXView   = Clamp((int)ceilf(bottomRightView.x + 1), 0, gameData.gameMap.w - 1);
    int startYView = Clamp((int)floor(topLeftView.y - 1),     0, gameData.gameMap.w - 1);
    int endYView   = Clamp((int)ceilf(bottomRightView.y + 1), 0, gameData.gameMap.w - 1);

    // Draw to screen 
    ClearBackground({75, 75, 150, 255});

    for (int y = startYView; y < endYView; y++)
    {
        for (int x = startXView; x < endXView; x++)
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
    DrawFPS(10, 10);

    return true;
};


void closeGame()
{
    
}