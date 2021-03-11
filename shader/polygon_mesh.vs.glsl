#version 330 core
/**
绘制Polygon Mesh
*/
layout(location = 0) in vec3 aPos;//mesh坐标
layout(location = 1) in vec3 aNormal;//法线

out VsOut
{
    vec3 FragPos;// 将顶点在世界坐标系中的位置传递给片段着色器
    vec3 Normal;// 顶点的法线（注意是经过model矩阵移动过后的顶点法线）
} vsOut;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform float pointSize;//mesh点的大小

void main()
{
    vsOut.FragPos = aPos;
    vsOut.Normal = vec3(model * vec4(aNormal, 1.0f));
    gl_Position = projection * view *  model * vec4(aPos, 1.0);
    gl_PointSize = pointSize;
}
