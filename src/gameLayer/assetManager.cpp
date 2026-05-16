#include "assetManager.h"

void AssetManager::loadAll()
{
    textures = LoadTexture(RESOURCES_PATH "textures.png");
    treeTextures = LoadTexture(RESOURCES_PATH "treetextures.png");
    frame = LoadTexture(RESOURCES_PATH "frame.png");
}