#include <cld_render.h>
using namespace coolender;
using namespace wh::basic;
using namespace std;
using namespace glm;
Render::Render()
{}
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
void Render::renderPointCloudTypePoint(PointCloud &pointCloud)
{   
    glBindVertexArray(pointCloud.pointTypeVAO);
    glDrawArrays(GL_POINTS, 0, pointCloud.size);
    glBindVertexArray(0);
}

//准备渲染球状点云
void Render::renderPointCloudTypeSphereInit(PointCloud &pointCloud)
{
    Sphere::createSphere();//画一个球


    // unsigned int pointAmount = pointCloud.size;//点云点的数量
    // mat4 modelMatrices[pointAmount];//每个球状点云的model矩阵
    // for(int i = 0; i < pointAmount; i++)
    // {
    //     mat4 model(1.0f);
    //     model = scale(model, vec3(pointCloud.pointSize));//缩放
    //     model = translate
    //     (
    //         model, 
    //         vec3(pointCloud.points.row(i)[0], pointCloud.points.row(i)[1], pointCloud.points.row(i)[2])
    //     );//平移
    //     //不需要旋转
    //     modelMatrices[i] = model;
        
    // }
    // // configure instanced array 注意开始配置instanced array(实际就是把这些model矩阵先放到缓存里面)
    // unsigned int modelMatricesBuffer;
    // glGenBuffers(1,&modelMatricesBuffer);
    // glBindBuffer(GL_ARRAY_BUFFER, modelMatricesBuffer);
    // glBufferData(GL_ARRAY_BUFFER, pointAmount * sizeof(mat4), &modelMatrices[0], GL_STATIC_DRAW);

    // //生成球面
    // unsigned int sphereVAO = Sphere::createSphere();
    // // cout << sphereVAO << endl;

    // // set transformation matrices as an instance vertex attribute (with divisor 1)
    // // note: we're cheating a little by taking the, now publicly declared, VAO of the model's mesh(es) and adding new vertexAttribPointers
    // // normally you'd want to do this in a more organized fashion, but for learning purposes this will do.
    // for (unsigned int i = 0; i < pointAmount; i++)
    // {
    //     glBindVertexArray(pointCloud.sphereTypeVAO);
    //     // set attribute pointers for matrix (4 times vec4) 就是这里把不同的model矩阵传递给了shader 因为此时绑定的VBO是model矩阵数组
    //     glEnableVertexAttribArray(3);
    //     glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
    //     glEnableVertexAttribArray(4);
    //     glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
    //     glEnableVertexAttribArray(5);
    //     glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
    //     glEnableVertexAttribArray(6);
    //     glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

    //     glVertexAttribDivisor(3, 1);//参数1：设置vertex attribute的index 参数2：设置每几个instance更新一次数据
    //     glVertexAttribDivisor(4, 1);
    //     glVertexAttribDivisor(5, 1);
    //     glVertexAttribDivisor(6, 1);

    //     glBindVertexArray(0);
    // }
}

//渲染球状点云
void Render::renderPointCloudTypeSphere(PointCloud &pointCloud)
{   
    // glBindVertexArray(pointCloud.sphereTypeVAO);
    // glDrawElementsInstanced(GL_TRIANGLES, Sphere::indexCount, GL_UNSIGNED_INT, 0, pointCloud.size);
    glBindVertexArray(Sphere::VAO);
    glDrawElements(GL_TRIANGLE_STRIP, Sphere::indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
