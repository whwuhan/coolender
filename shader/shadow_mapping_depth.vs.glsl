#version 330 core
layout (location = 0) in vec3 aPos;
//值得注意的是，这里实际上是占用了location,3，4，5，6因为他是4*4的矩阵，有4个vec4变量
layout (location = 3) in mat4 ainstanceMatrix;//渲染点云用的实例化矩阵

uniform mat4 lightSpaceMatrix;
uniform mat4 model;

//是否渲染的是点云
uniform bool renderPointCloud;

void main()
{
    if(renderPointCloud)
    {
        // 将所有坐标转化到 light space
        gl_Position = lightSpaceMatrix * model * ainstanceMatrix * vec4(aPos, 1.0);
    }
    else
    {
        // 将所有坐标转化到 light space
        gl_Position = lightSpaceMatrix * model * vec4(aPos, 1.0);
    }
}