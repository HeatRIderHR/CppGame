#pragma once

#include <raylib.h>

struct AssetManager
{
    Texture2D textures = {};
    Texture2D treeTextures = {};
    Texture2D frame = {};

    void loadAll();
};