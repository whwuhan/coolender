#include <cld_render.h>
using namespace coolender;
using namespace wh::basic;
using namespace std;
Render::Render()
{}
//准备渲染点状点云
void Render::renderPointCloudPointInit(PointCloud &pointCloud)
{
    //获取C++原生数据
    float pointCloudData[pointCloud.size * POINT3D_SIZE];
    for(int i = 0; i < pointCloud.points.rows(); i++)
    {
        for(int j = 0; j < 3;j++)
        {
            pointCloudData[i * 3 + j] = pointCloud.points.row(i)[j];
        }
    }
    glGenVertexArrays(1, &pointCloud.pointTypeVAO);
    glGenBuffers(1, &pointCloud.pointTypeVBO);
    glBindVertexArray(pointCloud.pointTypeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, pointCloud.pointTypeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pointCloudData), pointCloudData, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindVertexArray(0);
}

//渲染点状点云
void Render::renderPointCloudPoint(PointCloud &pointCloud)
{   
    glBindVertexArray(pointCloud.pointTypeVAO);
    glDrawArrays(GL_POINTS, 0, pointCloud.size);
    glBindVertexArray(0);
}

//准备渲染球状点云
void Render::renderPointCloudSphereInit(PointCloud &pointCloud)
{
    
}

//渲染球状点云
void Render::renderPointCloudSphere(PointCloud &pointCloud)
{   
    glBindVertexArray(pointCloud.sphereTypeVAO);
    glDrawArrays(GL_POINTS, 0, pointCloud.size);
    glBindVertexArray(0);
}
