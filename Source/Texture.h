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

    ~Texture()
    {
        name.clear();
        path.clear();
        data = nullptr;
    }
};