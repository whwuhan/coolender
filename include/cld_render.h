#pragma once 
/**
 * 
 * 渲染
 * 
*/
#include <whlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace coolender
{
    class Render
    {
    public:
        Render();

        //渲染点云
        static void renderPointCloudPointInit(wh::basic::PointCloud &pointCloud);//准备渲染点状点云
        static void renderPointCloudPoint(wh::basic::PointCloud &pointCloud);//渲染点状点云
        static void renderPointCloudSphereInit(wh::basic::PointCloud &pointCloud);//准备渲染球状点云
        static void renderPointCloudSphere(wh::basic::PointCloud &pointCloud);//渲染球状点云
    };
}