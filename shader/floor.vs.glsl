#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

// declare an interface block; see 'Advanced GLSL' for what these are.
out VsOut
{
    vec3 FragPos;// 将顶点在世界坐标系中的位置传递给片段着色器
    vec3 Normal;// 顶点的法线（注意是经过model矩阵移动过后的顶点法线）
    vec2 TexCoords;// 顶点的纹理坐标
    vec4 FragPosLightSpace;// 顶点在光源空间中的坐标位置（类比相机坐标系，只是视角是从光源看出来）
} vsOut;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 lightSpaceMatrix;//世界坐标转换到light space
void main()
{
    vsOut.FragPos = aPos;
    vsOut.Normal = aNormal;
    vsOut.TexCoords = aTexCoords;
    vsOut.FragPosLightSpace = lightSpaceMatrix * vec4(vsOut.FragPos, 1.0); // 光源坐标系中的坐标
    gl_Position = projection * view * vec4(aPos, 1.0);
}