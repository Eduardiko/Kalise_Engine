#pragma once

#include "Globals.h"

#include <string>

typedef unsigned char GLubyte;

struct Texture
{
    std::string name = "defaultTex";
    std::string path = "Assets/Textures/";
    uint id = -1;
    int format = -1;
    uint formatUnsigned = -1;
    GLubyte* data = nullptr;
    int width = -1;
    int height = -1;

    int GetWidth() { return width; }
    int GetHeight() { return height; }

    ~Texture()
    {
        name.clear();
        path.clear();
        data = nullptr;
    }
};