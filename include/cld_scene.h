#pragma once
#include <map>
#include <whlib.h>
#include <cld_light.h>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <cld_sphere.h>
namespace coolender
{
    enum POINT_TYPE{POINT, SPHERE};//点的绘制类型
    enum LIGHT_MODEL{PHONG, BLINN_PHONG, PBR};//场景使用的光照模型
    class Scene
    {
    public:
        Scene();

        //场景的属性
        static glm::vec4 clearColor;//背景颜色
        static bool showFloor;//显示地板
        static bool phongLightingModel;//Phong光照模型
        static POINT_TYPE pointType;//点云点的绘制类型
        static LIGHT_MODEL lightModel;//光照模型




        // void init();
        //场景中的物体
        static std::map<std::string, coolender::Light> lightCollection;//光源
        static std::map<std::string, wh::basic::PointCloud> pointCloudCollection;//点云
        static std::map<std::string, wh::basic::PolygonMesh> polygonMeshCollection;//Mesh网格
        static std::map<std::string, coolender::Sphere> sphereCollection;//球状点云对应的球

        //给场景中添加物体
        static void addLight(std::string lightName, coolender::Light &light);
        static void addPointCloud(std::string pointCloudName, wh::basic::PointCloud &pointCloud);
        static void addPolygonMesh(std::string polygonMeshName, wh::basic::PolygonMesh &polygonMesh);
        static void addSphere(std::string sphereName, coolender::Sphere& sphere);


        //删除场景中的物体
        static void deleteLight(std::string lightName);
        static void deletePointCloud(std::string pointCloudName);
        static void deletePolygonMesh(std::string polygonMeshName);
        static void deleteSphere(std::string sphereName);

        //渲染场景
        static void renderScene();
    };
}