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
namespace coolender{
    enum POINT_TYPE{POINT, SPHERE};                                             //点的绘制类型
    enum LIGHT_MODEL{PHONG, BLINN_PHONG, PBR};                                  //场景使用的光照模型
    enum POLYGON_MESH_TYPE{LINE, FILL, LINE_AND_FILL, LIGHT};                   //mesh的渲染模式
    class Scene
    {
    public:
        Scene();
        // 场景的属性
        static Light  parallel_light;                                           // 场景平行光
        static float ambient_intensity;                                         // 场景的环境光强度
        static glm::vec4 clear_color;                                           // 背景颜色
        static LIGHT_MODEL light_model;                                         // 光照模型

        static coolender::Plane floor;                                          // 地板
        static bool show_floor;                                                 // 显示地板
        static bool floor_use_tex;                                              // 地板是否使用纹理
        static bool phong_lighting_model;                                       // Phong光照模型

        // 点云
        static bool show_all_point_cloud;                                       // 显示所有点云
        static POINT_TYPE point_type;                                           // 点云点的绘制类型
        static float point_cloud_point_size;                                    // 场景所有点云的大小
        static glm::vec4 point_cloud_point_color;                               // 场景所有点云的颜色
        
        // mesh
        static bool show_all_polygon_mesh;                                      // 显示所有mesh
        static POLYGON_MESH_TYPE polygon_mesh_type;                             // mesh类型
        static float polygon_mesh_point_size;                                   //场景所有mesh点的大小
        static glm::vec4 polygon_mesh_point_line_color;                         //场景所有polygon mesh PointAndLine的颜色
        static glm::vec4 polygon_mesh_face_color;                               //场景所有polygon mesh Face的颜色

        // 场景中的物体
        // static std::map<std::string, coolender::Light> light_map;            // 光源
        static std::map<std::string, coolender::Light> point_light_map;         // 点光源
        static std::map<std::string, wh::basic::PointCloud> point_cloud_map;    // 点云
        static std::map<std::string, coolender::Sphere> sphere_map;             // 球状点云对应的球
        static std::map<std::string, wh::basic::PolygonMesh> polygon_mesh_map;  // mesh
        static std::map<std::string, coolender::Model> model_map;               // 模型
        

        //给场景中添加物体
        // static void add_light(std::string light_name, coolender::Light &light);
        static void add_point_light(std::string point_light_name, coolender::Light &point_light);
        static void add_point_cloud(std::string point_cloud_name, wh::basic::PointCloud &point_cloud);
        static void add_sphere(std::string sphere_name, coolender::Sphere &sphere);
        static void add_polygon_mesh(std::string polygon_mesh_name, wh::basic::PolygonMesh &mesh);
        static void add_model(std::string model_name, coolender::Model &model);

        //删除场景中的物体
        // static void delete_light(std::string light_name);
        static void delete_point_light(std::string point_light_name);
        static void delete_point_cloud(std::string point_cloud_name);
        static void delete_sphere(std::string sphere_name);
        static void delete_polygon_mesh(std::string polygon_mesh_name);
        static void delete_model(std::string model_name);

        //渲染场景
        static void render_scene();
    };// end Render
}// end namespace coolender