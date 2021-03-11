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
        // ShadowMapping();
        // ShadowMapping(unsigned int width, unsigned int height, float nearPlane, float farPlane);

        //FrameBuffer Object的分辨率
        static float shadowMappingScale;//shadow mapping分辨率缩放
        static unsigned int width;
        static unsigned int height;
        
        
        static unsigned int depthMapFBO;// 创建 depth map framebuffer object
        static unsigned int depthMap;// create depth texture 将深度信息放在纹理上
        static float nearPlane;//在光源位置渲染时，投影矩阵近平面
        static float farPlane;//远平面

        static void init();//初始化
        static void renderDepthMap(coolender::Shader &depthMapShader);//渲染在光源位置的深度图到对应的纹理中
        //渲染各种模型的深度图
        static void renderPointCloudTypeSphereDepthMap(coolender::Shader &depthMapShader, glm::mat4& lightSpaceMatrix);
        static void renderFloorDepthMap(coolender::Shader &depthMapShader, glm::mat4& lightSpaceMatrix);
        static void renderPolygonMeshDepthMap(coolender::Shader &depthMapShader, glm::mat4& lightSpaceMatrix);
        
    };
}