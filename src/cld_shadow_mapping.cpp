#include <cld_shadow_mapping.h>
using namespace std;
using namespace coolender;
using namespace glm;

ShadowMapping::ShadowMapping():
shadowMappingScale(1),
width(Window::width * shadowMappingScale),
height(Window::height * shadowMappingScale),
nearPlane(0.1f),
farPlane(100.0f),
depthMapFBO(0),
depthMap(0)
{}

ShadowMapping::ShadowMapping(unsigned int width, unsigned int height, float nearPlane, float farPlane):
width(width),
height(height),
nearPlane(nearPlane),
farPlane(farPlane),
depthMapFBO(0),
depthMap(0)
{}

void ShadowMapping::init()
{
    // 创建 depth map framebuffer object
    glGenFramebuffers(1, &depthMapFBO);
    // create depth texture 将深度信息放在纹理上
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    //设置当前绑定纹理的信息 注意纹理的类型，参数 纹理的类型， level, 纹理内部存储数据的格式， 宽，高 
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //防止视锥外的部分被视作阴影 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    // attach depth texture as FBO's depth buffer 将纹理绑定在帧缓冲上
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);//表示只需要深度信息
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

//渲染整个场景的depth map
void ShadowMapping::renderDepthMap(Shader &simpleDepthShader)
{
    mat4 lightProjection, lightView;
    mat4 lightSpaceMatrix;
    // 正交投影矩阵  参数 左 右 下 上 远 近平面
    lightProjection = ortho(-5.0f, 5.0f, -5.0f, 5.0f, nearPlane, farPlane);
    // 从光照位置生成的观察矩阵
    lightView = lookAt(Scene::parallelLight.position, Scene::parallelLight.lookAt, glm::vec3(0.0f,1.0f,0.0));
    lightSpaceMatrix = lightProjection * lightView; //可以将世界坐标系中的点转换到光照空间中

    // 开始渲染从光照位置的depth map
    // 设置视口参数 参数 x y 宽 高
    glViewport(0, 0, width, height);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);

    //渲染地板depth map
    renderFloorDepthMap(simpleDepthShader, lightSpaceMatrix);
    //渲染球状点云shadow mapping的depth map
    renderPointCloudTypeSphereDepthMap(simpleDepthShader, lightSpaceMatrix);
    //渲染polygon mesh的depth map
    //renderPolygonMeshDepthMap(simpleDepthShader, lightSpaceMatrix);

    // 解绑帧缓冲
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    // reset viewport
    int width, height;
    glfwGetFramebufferSize(Window::glfwWindow, &width, &height);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//渲染地板的depth map
void ShadowMapping::renderFloorDepthMap(coolender::Shader &simpleDepthShader, glm::mat4& lightSpaceMatrix)
{
    simpleDepthShader.use();
    simpleDepthShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);
    simpleDepthShader.setMat4("model", mat4(1.0f));
    glBindVertexArray(Scene::floor.VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

//渲染点云的depth map
void ShadowMapping::renderPointCloudTypeSphereDepthMap(Shader &simpleDepthShader, mat4& lightSpaceMatrix)
{
    glEnable(GL_CULL_FACE); //开启面剔除，默认剔除背面
    //glCullFace(GL_FRONT);//设置剔除正面
    glFrontFace(GL_CW); //设置顺时针的面为正面
    for (auto it = Scene::pointCloudCollection.begin(); it != Scene::pointCloudCollection.end(); it++)
    {
        //判断是否显示球状点云
        if (it->second.show)
        {
            simpleDepthShader.use();
            // vs uniform
            simpleDepthShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);
            simpleDepthShader.setMat4("model", it->second.model);

            //判断是否改变了球状点云的半径
            if (it->second.changePointSize)
            {
                Scene::sphereCollection[it->first].setRadiusAndSegmentsByPointSize(it->second.pointSize);
                Render::renderPointCloudTypeSphereInit(it->second, Scene::sphereCollection[it->first]); //重新初始化（因为球的大小变了，要更新VAO）
            }
            //渲染球状点云
            Render::renderPointCloudTypeSphere(it->second, Scene::sphereCollection[it->first]);
        }
    }
    glDisable(GL_CULL_FACE); //关闭面剔除
}

//渲染polygon mesh的depth map
void ShadowMapping::renderPolygonMeshDepthMap(Shader &simpleDepthShader, mat4& lightSpaceMatrix)
{
    //渲染polygon mesh
    for(auto it = Scene::polygonMeshCollection.begin(); it != Scene::polygonMeshCollection.end(); it++)
    {
        if(it->second.show)
        {
            simpleDepthShader.use();
            // vs uniform
            simpleDepthShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);
            simpleDepthShader.setMat4("model", it->second.model);
            Render::renderPolygonMeshTypeLine(it->second);
        }
    }
}
