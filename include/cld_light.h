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
        Light(glm::vec3 pos, glm::vec4 color, float intensity = 0.3);
        glm::vec3 pos;//位置
        glm::vec4 color;//颜色
        float intensity;
    };
}