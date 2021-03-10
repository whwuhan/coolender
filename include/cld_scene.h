#pragma once
#include <map>
#include <whlib.h>
#include <cld_light.h>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <cld_sphere.h>
#include <cld_light.h>
#include <cld_plane.h>
#include <cld_model.h>
namespace coolender
{
    enum POINT_TYPE{POINT, SPHERE};//点的绘制类型
    enum LIGHT_MODEL{PHONG, BLINN_PHONG, PBR};//场景使用的光照模型
    enum POLYGON_MESH_TYPE{LINE, FILL, LINE_AND_FILL, LIGHT};//mesh的渲染模式
    class Scene
    {
    public:
        Scene();
        //场景的属性
        static Light  parallelLight;//场景平行光
        static float ambientIntensity;//场景的环境光强度
        static glm::vec4 clearColor;//背景颜色
        static LIGHT_MODEL lightModel;//光照模型

        static coolender::Plane floor;//地板
        static bool showFloor;//显示地板
        static bool floorUseTex;//地板是否使用纹理
        static bool phongLightingModel;//Phong光照模型
        

        //点云
        static bool showAllPointCloud;//显示所有点云
        static POINT_TYPE pointType;//点云点的绘制类型
        static float pointCloudPointSize;//场景所有点云的大小
        static glm::vec4 pointCloudPointColor;//场景所有点云的颜色
        
        //mesh
        static bool showAllPolygonMesh;//显示所有mesh
        static POLYGON_MESH_TYPE polygonMeshType;
        static float polygonMeshPointSize;//场景所有mesh点的大小
        static glm::vec4 polygonMeshColor;//场景所有点云的颜色


        //场景中的物体
        // static std::map<std::string, coolender::Light> lightCollection;//光源
        static std::map<std::string, coolender::Light> pointLightCollection;//点光源
        static std::map<std::string, wh::basic::PointCloud> pointCloudCollection;//点云
        static std::map<std::string, coolender::Sphere> sphereCollection;//球状点云对应的球
        static std::map<std::string, wh::basic::PolygonMesh> polygonMeshCollection;
        static std::map<std::string, coolender::Model> modelCollection;//模型
        

        //给场景中添加物体
        // static void addLight(std::string lightName, coolender::Light &light);
        static void addPointLight(std::string pointLightName, coolender::Light &pointLight);
        static void addPointCloud(std::string pointCloudName, wh::basic::PointCloud &pointCloud);
        static void addSphere(std::string sphereName, coolender::Sphere &sphere);
        static void addPolygonMesh(std::string meshName, wh::basic::PolygonMesh &mesh);
        static void addModel(std::string modelName, coolender::Model &model);
        


        //删除场景中的物体
        // static void deleteLight(std::string lightName);
        static void deletePointLight(std::string pointLightName);
        static void deletePointCloud(std::string pointCloudName);
        static void deleteSphere(std::string sphereName);
        static void deletePolygonMesh(std::string polygonMeshName);
        static void deleteModel(std::string modelName);
        

        //渲染场景
        static void renderScene();
    };
}