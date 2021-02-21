#pragma once
#include <map>
#include <whlib.h>
#include <light.h>
#include <glm/glm.hpp>
namespace coolender
{
    class Scene
    {
    public:
        Scene();

        //场景的属性
        static glm::vec4 clearColor;//背景颜色
        static bool showFloor;//显示地板
        static bool phongLightingModel;


        // void init();
        //场景中的物体
        static std::map<std::string, coolender::Light> lightCollection;//光源
        static std::map<std::string, wh::basic::PointCloud> pointCloudCollection;//点云
        static std::map<std::string, wh::basic::PolygonMesh> polygonMeshCollection;//Mesh网格


        //给场景中添加物体
        static void addLight(std::string lightName, coolender::Light &light);
        static void addPointCloud(std::string pointCloudName, wh::basic::PointCloud &pointCloud);
        static void addPolygonMesh(std::string polygonMeshName, wh::basic::PolygonMesh &polygonMesh);

        //删除场景中的物体
        static void deleteLight(std::string lightName);
        static void deletePointCloud(std::string pointCloudName);
        static void deletePolygonMesh(std::string polygonMeshName);

        //渲染场景
        static void renderScene();
    };
}