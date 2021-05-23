#version 330 core
/**
绘制Polygon Mesh
*/
layout(location = 0) in vec3 a_pos;//mesh坐标
layout(location = 1) in vec3 a_normal;//法线

out VsOut
{
    vec3 frag_pos;// 将顶点在世界坐标系中的位置传递给片段着色器
    vec3 normal;// 顶点的法线（注意是经过model矩阵移动过后的顶点法线）
} vs_out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform float point_size;//mesh点的大小

void main()
{
    vs_out.frag_pos = a_pos;
    vs_out.normal = vec3(model * vec4(a_normal, 1.0f));
    gl_Position = projection * view *  model * vec4(a_pos, 1.0);
    gl_PointSize = point_size;
}
