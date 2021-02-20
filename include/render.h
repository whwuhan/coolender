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
        void renderPointCloudInit(wh::basic::PointCloud &pointCloud);//准备渲染点云
        void renderPointCloud(wh::basic::PointCloud &pointCloud);//渲染点云
    };
}