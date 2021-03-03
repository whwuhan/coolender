#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include <vector>
namespace coolender
{
    class Sphere
    {
    public:
        static unsigned int VAO;
        static unsigned int VBO;
        static unsigned int EBO;//Element Buffer Object
        static double radius;//半径
        static unsigned int indexCount;//坐标的数量
        static unsigned int X_SEGMENTS;//x轴上的分割数量
        static unsigned int Y_SEGMENTS;//y轴上的分割数量
        static unsigned int createSphere();//产生球的mesh,返回VAO
    };
}