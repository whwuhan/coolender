#pragma once
#include <map>
#include <whlib.h>
#include <cld_light.h>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <cld_sphere.h>
#include <cld_light.h>
#include <cld_plane.h>
namespace coolender
{
    enum POINT_TYPE{POINT, SPHERE};//点的绘制类型
    enum LIGHT_MODEL{PHONG, BLINN_PHONG, PBR};//场景使用的光照模型
    class Scene
    {
    public:
        Scene();
        //场景的属性
        static Light  parallelLight;//场景平行光
        static float ambientIntensity;//场景的环境光强度
        static glm::vec4 clearColor;//背景颜色
        static coolender::Plane floor;//地板
        static bool showFloor;//显示地板
        static bool floorUseTex;//地板是否使用纹理
        static bool phongLightingModel;//Phong光照模型
        static POINT_TYPE pointType;//点云点的绘制类型
        static LIGHT_MODEL lightModel;//光照模型
        static float pointCloudPointSize;//场景所有点云的大小
        static glm::vec4 pointCloudPointColor;//场景所有点云的颜色
        static bool showAllPointCloud;//显示所有点云

        // void init();
        //场景中的物体
        // static std::map<std::string, coolender::Light> lightCollection;//光源
        static std::map<std::string, wh::basic::PointCloud> pointCloudCollection;//点云
        static std::map<std::string, wh::basic::PolygonMesh> polygonMeshCollection;//Mesh网格
        static std::map<std::string, coolender::Sphere> sphereCollection;//球状点云对应的球
        static std::map<std::string, coolender::Light> pointLightCollection;//点光源

        //给场景中添加物体
        // static void addLight(std::string lightName, coolender::Light &light);
        static void addPointCloud(std::string pointCloudName, wh::basic::PointCloud &pointCloud);
        static void addPolygonMesh(std::string polygonMeshName, wh::basic::PolygonMesh &polygonMesh);
        static void addSphere(std::string sphereName, coolender::Sphere& sphere);
        static void addPointLight(std::string pointLightName, coolender::Light &pointLight);


        //删除场景中的物体
        // static void deleteLight(std::string lightName);
        static void deletePointCloud(std::string pointCloudName);
        static void deletePolygonMesh(std::string polygonMeshName);
        static void deleteSphere(std::string sphereName);
        static void deletePointLight(std::string pointLightName);

        //渲染场景
        static void renderScene();
    };
}