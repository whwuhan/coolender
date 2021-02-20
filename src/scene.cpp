#include <scene.h>
using namespace std;
using namespace coolender;
using namespace wh::basic;
//注意static变量要先初始化 链接失败
map<string, Light> Scene::lightCollection;//光源
map<string, PointCloud> Scene::pointCloudCollection;//点云
map<string, PolygonMesh> Scene::polygonMeshCollection;//Mesh网格

Scene::Scene()
{}

// void Scence::init()
// {}

//添加光源
void Scene::addLight(string lightName, Light &light)
{
    lightCollection[lightName] = light;
    cout << "Add light successfully." << endl;
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

//删除光源
void Scene::deleteLight(string lightName)
{
    lightCollection.erase(lightName);
    cout << "Delete light successfully." << endl;
}

//删除点云
void Scene::deletePointCloud(string pointCloudName)
{
    pointCloudCollection.erase(pointCloudName);
    cout << "Delete point cloud successfully." << endl;
}

//删除Mesh
void Scene::deletePolygonMesh(string polygonMeshName)
{
    polygonMeshCollection.erase(polygonMeshName);
    cout << "Delete polygonmesh successfully." << endl;
}