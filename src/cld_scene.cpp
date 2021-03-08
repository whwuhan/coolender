#include <cld_scene.h>
using namespace std;
using namespace coolender;
using namespace wh::basic;
using namespace glm;
vec4 Scene::clearColor(1.0f, 1.0f, 1.0f, 1.0f);//clear color
float Scene::ambientIntensity = 0.35;//场景的环境光
Plane Scene::floor;
bool Scene::showFloor = false;//是否显示地板
bool Scene::floorUseTex = false;//地板是否使用纹理
bool Scene::phongLightingModel = true;//是否使用phone光照模型
POINT_TYPE Scene::pointType = POINT;//点云绘制类型
LIGHT_MODEL Scene::lightModel = BLINN_PHONG;//场景光照模型
Light Scene::parallelLight(vec3(0.0f, 0.0f, 0.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f), vec3(0.0f, 1.0f, 1.0f));//场景平行光
float Scene::pointCloudPointSize = 1.0f;
vec4 Scene::pointCloudPointColor(0.06f, 0.729f, 0.941f, 1.0f);
bool Scene::showAllPointCloud = true;
//注意static变量要先初始化 否则链接失败
// map<string, Light> Scene::lightCollection;//光源
map<string, PointCloud> Scene::pointCloudCollection;//点云
map<string, PolygonMesh> Scene::polygonMeshCollection;//Mesh网格
map<string, Sphere> Scene::sphereCollection;//球状点云对应的球
map<string, Light> Scene::pointLightCollection;//点光源

Scene::Scene()
{}

// void Scence::init()
// {}

//添加光源
// void Scene::addLight(string lightName, Light &light)
// {
//     lightCollection[lightName] = light;
//     cout << "Add light successfully." << endl;
// }

//增加点光源
void Scene::addPointLight(std::string pointLightName, coolender::Light &pointLight)
{
    pointLightCollection[pointLightName] = pointLight;
    cout << "Add point light successfully." << endl;
}

//添加点云
void Scene::addPointCloud(string pointCloudName, PointCloud &pointCloud)
{
    pointCloudCollection[pointCloudName] = pointCloud;
    cout << "Add point cloud successfully." << endl;
}

//添加Mesh
void Scene::addPolygonMesh(string polygonMeshName, PolygonMesh &polygonMesh)
{
    polygonMeshCollection[polygonMeshName] = polygonMesh;
    cout << "Add polygonmesh successfully." << endl;
}

//添加球面
void Scene::addSphere(string sphereName, Sphere& sphere)
{
    sphereCollection[sphereName] = sphere;
    cout << "Add sphere successfully." << endl;
}

//删除光源
// void Scene::deleteLight(string lightName)
// {
//     lightCollection.erase(lightName);
//     cout << "Delete light successfully." << endl;
// }

//删除点光源
void Scene::deletePointLight(std::string pointLightName)
{
    polygonMeshCollection.erase(pointLightName);
    cout << "Delete point light successfully." << endl;
}

//删除点云
void Scene::deletePointCloud(string pointCloudName)
{   
    //先删VBO VAO
    glDeleteBuffers(1, &pointCloudCollection[pointCloudName].VBO);
    glDeleteBuffers(1, &pointCloudCollection[pointCloudName].pointModelMatricesBuffer);
    glDeleteVertexArrays(1, &pointCloudCollection[pointCloudName].VAO);
    //删除对应的球面
    deleteSphere(pointCloudName);
    //再删除场景中的点云
    pointCloudCollection.erase(pointCloudName);
    cout << "Delete point cloud successfully." << endl;
}

//删除Mesh
void Scene::deletePolygonMesh(string polygonMeshName)
{
    polygonMeshCollection.erase(polygonMeshName);
    cout << "Delete polygonmesh successfully." << endl;
}

//删除球面
void Scene::deleteSphere(string sphereName)
{
    //先删VBO EBO VAO
    glDeleteBuffers(1, &sphereCollection[sphereName].VBO);
    glDeleteBuffers(1, &sphereCollection[sphereName].EBO);
    glDeleteVertexArrays(1, &sphereCollection[sphereName].VAO);
    sphereCollection.erase(sphereName);
    cout << "Delete sphere successfully." << endl;
}
