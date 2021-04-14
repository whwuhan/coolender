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
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cld_sphere.h>
#include <cld_shader.h>

namespace coolender{
    class Render{
    public:
        //渲染点云
        static void render_point_cloud_type_point_init(wh::basic::PointCloud &point_cloud);//准备渲染点状点云
        static void render_point_cloud_type_point(wh::basic::PointCloud &point_cloud);//渲染点状点云
        static void render_point_cloud_type_sphere_init(wh::basic::PointCloud &point_cloud, coolender::Sphere &sphere);//准备渲染球状点云并返回对应球面
        static void render_point_cloud_type_sphere(wh::basic::PointCloud &point_cloud, coolender::Sphere &sphere);//渲染球状点云
        //渲染mesh
        static void render_polygon_mesh_init(wh::basic::PolygonMesh &mesh);
        static void render_polygon_mesh_type_line(wh::basic::PolygonMesh &mesh);//线框模式
        static void render_polygon_mesh_type_fill(wh::basic::PolygonMesh &mesh);//填充模式
        static void render_polygon_mesh_type_line_fill(wh::basic::PolygonMesh &mesh, coolender::Shader &shader);//线框加填充模式
        static void render_polygon_mesh_type_light(wh::basic::PolygonMesh &mesh);//光照模式
    };
}