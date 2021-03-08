#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>
#include <string>
#include <cld_texture_loader.h>
namespace coolender
{
    class Plane
    {
    public:
        Plane();
        Plane(glm::vec4 color, std::string texturePath);
        void init();
        unsigned int VAO;
        unsigned int VBO;
        unsigned int texture;
        glm::vec4 color;//颜色
    private:
        std::string texturePath;//纹理路径
    };
}
