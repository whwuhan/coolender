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

namespace coolender
{
    class Render
    {
    public:
        //渲染点云
        static void renderPointCloudTypePointInit(wh::basic::PointCloud &pointCloud);//准备渲染点状点云
        static void renderPointCloudTypePoint(wh::basic::PointCloud &pointCloud);//渲染点状点云
        static void renderPointCloudTypeSphereInit(wh::basic::PointCloud &pointCloud, coolender::Sphere &sphere);//准备渲染球状点云并返回对应球面
        static void renderPointCloudTypeSphere(wh::basic::PointCloud &pointCloud, coolender::Sphere &sphere);//渲染球状点云
        //渲染mesh
        static void renderPolygonMeshInit(wh::basic::PolygonMesh &mesh);
        static void renderPolygonMeshTypeLine(wh::basic::PolygonMesh &mesh);//线框模式
        static void renderPolygonMeshTypeFill(wh::basic::PolygonMesh &mesh);//填充模式
        static void renderPolygonMeshTypeLineAndFill(wh::basic::PolygonMesh &mesh, coolender::Shader &shader);//线框加填充模式
        static void renderPolygonMeshTypeLight(wh::basic::PolygonMesh &mesh);//光照模式
    };
}