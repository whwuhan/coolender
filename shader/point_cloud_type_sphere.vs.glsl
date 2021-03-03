#version 330 core
layout(location = 0) in vec3 aPos;//位置
layout(location = 1) in vec2 aTexCoords;//uv坐标
layout(location = 2) in vec3 aNormal;//法线
//值得注意的是，这里实际上是占用了location,3，4，5，6因为他是4*4的矩阵，有4个vec4变量
layout (location = 3) in mat4 ainstanceMatrix;

// declare an interface block; see 'Advanced GLSL' for what these are.
// out VsOut
// {
//     vec3 FragPos;
//     vec2 TexCoords;
//     vec3 Normal;
// } vsOut;

// uniform mat4 pointModel;//点的model矩阵
// uniform mat4 model;//点云的model矩阵
uniform mat4 view;
uniform mat4 projection;

// uniform float pointSize;


void main()
{
    // vsOut.FragPos = aPos;
    // vsOut.Normal = aNormal;
    // vsOut.TexCoords = aTexCoords;
    gl_Position = projection * view * ainstanceMatrix * vec4(aPos, 1.0f); 
    // gl_Position = projection * view * pointModel * vec4(aPos, 1.0f); 
}