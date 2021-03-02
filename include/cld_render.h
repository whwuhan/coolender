#pragma once 
/**
 * 
 * 渲染
 * 
*/
#include <whlib.h>
#include <cld_sphere.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace coolender
{
    class Render
    {
    public:
        Render();

        //渲染点云
        static void renderPointCloudTypePointInit(wh::basic::PointCloud &pointCloud);//准备渲染点状点云
        static void renderPointCloudTypePoint(wh::basic::PointCloud &pointCloud);//渲染点状点云
        static void renderPointCloudTypeSphereInit(wh::basic::PointCloud &pointCloud);//准备渲染球状点云
        static void renderPointCloudTypeSphere(wh::basic::PointCloud &pointCloud);//渲染球状点云
    };
}