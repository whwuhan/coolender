#version 330 core
layout (location = 0) in vec3 aPos;
//值得注意的是，这里实际上是占用了location,3，4，5，6因为他是4*4的矩阵，有4个vec4变量
layout (location = 3) in mat4 ainstanceMatrix;//点的model矩阵
uniform mat4 lightSpaceMatrix;
uniform mat4 model;

void main()
{
    // 将所有坐标转化到 light space
    gl_Position = lightSpaceMatrix * model * ainstanceMatrix * vec4(aPos, 1.0);
}