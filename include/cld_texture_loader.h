#pragma once
#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>
namespace coolender{
    class TextureLoader{
    public:
        static unsigned int loadTexture2D(char const *path);
    };
}