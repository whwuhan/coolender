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
        // ShadowMapping(unsigned int width, unsigned int height, float near_plane, float far_plane);

        //FrameBuffer Object的分辨率
        static float shadow_mapping_scale;                                      // shadow mapping分辨率缩放
        static unsigned int width;
        static unsigned int height;
        
        
        static unsigned int depth_map_FBO;                                      // 创建 depth map framebuffer object
        static unsigned int depth_map;                                          // create depth texture 将深度信息放在纹理上
        static float near_plane;                                                // 在光源位置渲染时，投影矩阵近平面
        static float far_plane;                                                 // 远平面

        static void init();                                                     // 初始化
        static void render_depth_map(coolender::Shader &depth_map_shader);      // 渲染在光源位置的深度图到对应的纹理中

        //渲染各种模型的深度图
        static void render_point_cloud_type_sphere_depth_map(coolender::Shader &depth_map_shader, glm::mat4& light_space_matrix);
        static void render_floor_depth_map(coolender::Shader &depth_map_shader, glm::mat4& light_space_matrix);
        static void render_polygon_mesh_depth_map(coolender::Shader &depth_map_shader, glm::mat4& light_space_matrix);
    };// end ShadowMapping
}// end coolender