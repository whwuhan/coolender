#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>
#include <texture_loader.h>
namespace Coolender
{
    class Plane
    {
    public:
        Plane();
        void init();
        unsigned int VAO;
        unsigned int VBO;
        unsigned int texture;
    };
}
