#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
/**
 * 光源
 * 
*/
namespace coolender
{
    class Light
    {
    public:
        Light();
        Light(glm::vec3 position, glm::vec4 color, glm::vec3 direction = glm::vec3(0.0f, 1.0f, 1.0f));

        glm::vec3 position;//位置
        glm::vec4 color;//颜色
        glm::vec3 direction;//方向
    };
}