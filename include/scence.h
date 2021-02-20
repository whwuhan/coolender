#pragma once
#include <map>
#include <whlib.h>
namespace coolender
{
    class Scence
    {
    public:
        Scence();
        // void init();
        //场景中的物体
        static std::map<std::string, >
        static std::map<std::string, wh::basic::PointCloud> pointCloudCollection;
        static std::map<std::string, wh::basic::PolygonMesh> polygonMeshCollection;


        //给场景中添加物体
        static void addPointCloud(std::string pointCloudName, wh::basic::PointCloud &pointCloud);
        static void addPolygonMesh(std::string polygonMeshName, wh::basic::PolygonMesh &polygonMesh);

        //删除场景中的物体

    };
}