#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include <vector>
#include <iostream>
namespace coolender
{
    class Sphere
    {
    public:
        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;//Element Buffer Object
        double radius;//半径
        unsigned int indexCount;//坐标的数量
        unsigned int xSegments;//x轴上的分割数量
        unsigned int ySegments;//y轴上的分割数量

        Sphere();
        void createSphere();//生成一个球
        void setRadiusAndSegmentsByPointSize(float point_size);//根据point size设置球的半径和分割数量
    };
}