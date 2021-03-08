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
        Light(
            glm::vec3 position,     //位置
            glm::vec4 color,        //HDR颜色
            glm::vec3 direction     //方向
        );

        glm::vec3 position;//位置
        glm::vec4 color;//颜色
        glm::vec3 direction;//方向

    };
}