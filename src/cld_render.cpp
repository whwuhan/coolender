#include <cld_render.h>
using namespace coolender;
using namespace wh::basic;
using namespace std;
using namespace glm;
//准备渲染点状点云
void Render::renderPointCloudTypePointInit(PointCloud &pointCloud)
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
    glGenVertexArrays(1, &pointCloud.VAO);
    glGenBuffers(1, &pointCloud.VBO);
    glBindVertexArray(pointCloud.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, pointCloud.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pointCloudData), pointCloudData, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindVertexArray(0);
}

//渲染点状点云
void Render::renderPointCloudTypePoint(PointCloud &pointCloud)
{   
    glBindVertexArray(pointCloud.VAO);
    glDrawArrays(GL_POINTS, 0, pointCloud.size);
    glBindVertexArray(0);
}

//准备渲染球状点云
void Render:: renderPointCloudTypeSphereInit(PointCloud &pointCloud, Sphere &sphere)
{
    glBindVertexArray(sphere.VAO);
    unsigned int pointAmount = pointCloud.size;//点云点的数量
    mat4 pointModelMatrices[pointAmount];//每个球状点云的model矩阵
    for(int i = 0; i < pointAmount; i++)
    {
        mat4 pointModel(1.0f);
       
        pointModel = translate
        (
            pointModel, 
            vec3(pointCloud.points.row(i)[0], pointCloud.points.row(i)[1], pointCloud.points.row(i)[2])
        );//平移
        pointModel = scale(pointModel, vec3(pointCloud.pointSize * 0.05, pointCloud.pointSize * 0.05, pointCloud.pointSize * 0.05));//QIU D缩放
        //不需要旋转
        pointModelMatrices[i] = pointModel;
    } 

    // configure instanced array 注意开始配置instanced array(实际就是把这些model矩阵先放到缓存里面)
    if(0 == pointCloud.pointModelMatricesBuffer)
    {
        glGenBuffers(1,&pointCloud.pointModelMatricesBuffer);
    }
    // cout << pointCloud.pointModelMatricesBuffer << endl;
    glBindBuffer(GL_ARRAY_BUFFER, pointCloud.pointModelMatricesBuffer);
    glBufferData(GL_ARRAY_BUFFER, pointAmount * sizeof(mat4), &pointModelMatrices[0], GL_STATIC_DRAW);
    

    // set transformation matrices as an instance vertex attribute (with divisor 1)
    // note: we're cheating a little by taking the, now publicly declared, VAO of the model's mesh(es) and adding new vertexAttribPointers
    // normally you'd want to do this in a more organized fashion, but for learning purposes this will do.

    // set attribute pointers for matrix (4 times vec4) 就是这里把不同的model矩阵传递给了shader 因为此时绑定的VBO是model矩阵数组
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

    glVertexAttribDivisor(3, 1);//参数1：设置vertex attribute的index 参数2：设置每几个instance更新一次数据
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);
    glBindVertexArray(0);
}

//渲染球状点云
void Render::renderPointCloudTypeSphere(PointCloud &pointCloud, Sphere &sphere)
{   
    glBindVertexArray(sphere.VAO);
    //注意绘制类型是GL_TRIANGLE_STRIP 不是GL_TRIANGLES
    glDrawElementsInstanced(GL_TRIANGLE_STRIP, sphere.indexCount, GL_UNSIGNED_INT, 0, pointCloud.size);
    glBindVertexArray(0);
}

// //渲染mesh准备
// void Render::renderPolygonMeshInit(PolygonMesh &mesh)
// {

// }

// //渲染mesh
// void Render::renderPolygonMesh(PolygonMesh &mesh)
// {

// }