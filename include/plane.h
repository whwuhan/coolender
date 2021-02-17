#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>
#include <string>
#include <texture_loader.h>
namespace coolender
{
    class Plane
    {
    public:
        Plane();
        Plane(std::string texturePath);
        void init();
        unsigned int VAO;
        unsigned int VBO;
        unsigned int texture;
    private:
        std::string texturePath;//纹理路径
    };
}
