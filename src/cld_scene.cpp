#include <cld_scene.h>
using namespace std;
using namespace coolender;
using namespace wh::basic;
using namespace glm;
Light Scene::parallel_light(vec3(0.0f, 10.0f, 10.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f), vec3(0.0f, -1.0f, 0.0f));//场景平行光
float Scene::ambient_intensity = 0.35;//场景的环境光
vec4 Scene::clear_color(1.0f, 1.0f, 1.0f, 1.0f);//clear color
LIGHT_MODEL Scene::light_model = BLINN_PHONG;//场景光照模型

//地板
Plane Scene::floor;
bool Scene::show_floor = false;//是否显示地板
bool Scene::floor_use_tex = false;//地板是否使用纹理
bool Scene::phong_lighting_model = true;//是否使用phone光照模型


//点云
bool Scene::show_all_point_cloud = true;
POINT_TYPE Scene::point_type = POINT;//点云绘制类型
float Scene::point_cloud_point_size = 1.0f;
vec4 Scene::point_cloud_point_color(0.06f, 0.729f, 0.941f, 1.0f);

//mesh
bool Scene::show_all_polygon_mesh = true;
POLYGON_MESH_TYPE Scene::polygon_mesh_type = LINE_AND_FILL;//polygon mesh的类型
float Scene::polygon_mesh_point_size = 5.0f;
vec4 Scene::polygon_mesh_point_line_color = vec4(0.0, 0.0, 0.0, 1.0f);//场景所有mesh 点和线的颜色
vec4 Scene::polygon_mesh_face_color = vec4(0.6, 0.6, 0.6, 1.0f);//场景所有mesh的颜色

//注意static变量要先初始化 否则链接失败
// map<string, Light> Scene::lightCollection;//光源
map<string, Light> Scene::point_light_map;//点光源
map<string, PointCloud> Scene::point_cloud_map;//点云
map<string, Sphere> Scene::sphere_map;//球状点云对应的球
map<string, PolygonMesh> Scene::polygon_mesh_map;//mesh
map<string, Model> Scene::model_map;//Mesh网格


Scene::Scene()
{}

// void Scence::init()
// {}

//添加光源
// void Scene::addLight(string light_name, Light &light)
// {
//     lightCollection[light_name] = light;
//     cout << "Add light successfully." << endl;
// }

//增加点光源
void Scene::add_point_light(string point_light_name, coolender::Light &point_light){
    point_light_map[point_light_name] = point_light;
    cout << "Add point light successfully." << endl;
}

//添加点云
void Scene::add_point_cloud(string point_cloud_name, PointCloud &point_cloud){
    point_cloud_map[point_cloud_name] = point_cloud;
    cout << "Add point cloud successfully." << endl;
}

//添加球面
void Scene::add_sphere(string sphere_name, Sphere& sphere){
    sphere_map[sphere_name] = sphere;
    cout << "Add sphere successfully." << endl;
}

//添加mesh
void Scene::add_polygon_mesh(string polygon_mesh_name, PolygonMesh& polygon_mesh){
    polygon_mesh_map[polygon_mesh_name] = polygon_mesh;
    cout << "Add polygon mesh successfully." << endl;
}

//添加Model
void Scene::add_model(string model_name, Model &model){
    model_map[model_name] = model;
    cout << "Add model successfully." << endl;
}



//删除光源
// void Scene::deleteLight(string light_name)
// {
//     lightCollection.erase(light_name);
//     cout << "Delete light successfully." << endl;
// }

//删除点光源
void Scene::delete_point_light(string point_light_name){
    point_light_map.erase(point_light_name);
    cout << "Delete point light successfully." << endl;
}

//删除点云
void Scene::delete_point_cloud(string point_cloud_name){   
    //先删VBO VAO
    glDeleteBuffers(1, &point_cloud_map[point_cloud_name].VBO);
    glDeleteBuffers(1, &point_cloud_map[point_cloud_name].point_model_matrices_buffer);
    glDeleteVertexArrays(1, &point_cloud_map[point_cloud_name].VAO);
    //删除对应的球面
    delete_sphere(point_cloud_name);
    //再删除场景中的点云
    point_cloud_map.erase(point_cloud_name);
    cout << "Delete point cloud successfully." << endl;
}

//删除球面
void Scene::delete_sphere(string sphere_name){
    //先删VBO EBO VAO
    glDeleteBuffers(1, &sphere_map[sphere_name].VBO);
    glDeleteBuffers(1, &sphere_map[sphere_name].EBO);
    glDeleteVertexArrays(1, &sphere_map[sphere_name].VAO);
    sphere_map.erase(sphere_name);
    cout << "Delete sphere successfully." << endl;
}

//删除mesh
void Scene::delete_polygon_mesh(string polygon_mesh_name)
{
    //先删VBO EBO VAO
    glDeleteBuffers(1, &polygon_mesh_map[polygon_mesh_name].VBO);
    glDeleteBuffers(1, &polygon_mesh_map[polygon_mesh_name].EBO);
    glDeleteVertexArrays(1, &polygon_mesh_map[polygon_mesh_name].VAO);
    polygon_mesh_map.erase(polygon_mesh_name);
    cout << "Delete polygon mesh successfully." << endl;
}

//删除Model
void Scene::delete_model(string model_name)
{
    model_map.erase(model_name);
    cout << "Delete model successfully." << endl;
}


