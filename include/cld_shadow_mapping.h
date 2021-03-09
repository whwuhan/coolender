#pragma once 
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <string>
#include <cld_scene.h>
#include <cld_window.h>
#include <cld_shader.h>
#include <basic/point_cloud.h>
namespace coolender
{
    class ShadowMapping
    {
    public:
        ShadowMapping();
        ShadowMapping(unsigned int width, unsigned int height, float nearPlane, float farPlane);

        //FrameBuffer Object的分辨率
        unsigned int width;
        unsigned int height;

        
        unsigned int depthMapFBO;// 创建 depth map framebuffer object
        unsigned int depthMap;// create depth texture 将深度信息放在纹理上
        float nearPlane;//在光源位置渲染时，投影矩阵近平面
        float farPlane;//远平面

        void init();//初始化
        void renderDepthMap(coolender::Shader &simpleDepthShader);//渲染在光源位置的深度图到对应的纹理中
        //渲染球状点云的Depth map
        void renderPointCloudTypeSphereDepthMap(coolender::Shader &simpleDepthShader, glm::mat4& lightSpaceMatrix);
        void renderFloorDepthMap(coolender::Shader &simpleDepthShader, glm::mat4& lightSpaceMatrix);
        
    };
}