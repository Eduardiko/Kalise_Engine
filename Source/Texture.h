#pragma once

#include "Globals.h"
#include <string>

typedef unsigned char GLubyte;
class Gameobject;

class Texture
{
public:
    Texture(bool active = true);
    Texture(uint id, uint textureBuffer, int format, uint formatUnsigned, GLubyte* data, int width, int height, std::string name, std::string path);
    ~Texture();

    bool SetTexture(Texture* texture);

public:

    unsigned int id = -1;
    unsigned int textureBuffer = -1;

    int format = -1;
    uint formatUnsigned = -1;

    GLubyte* data = nullptr;

    int width = -1;
    int height = -1;

    std::string name = "texture";
    std::string path = "Assets/Textures/";
};