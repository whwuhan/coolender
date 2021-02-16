#pragma once
#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>
namespace Coolender
{
    class TextureLoader
    {
    public:
        TextureLoader();
        unsigned int loadTexture(char const *path);
    };
}