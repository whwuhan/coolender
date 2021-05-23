#version 330 core
/**
绘制点状的点云
*/
layout(location = 0) in vec3 a_pos;//点云点的坐标

//MVP
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform float point_size;//点的大小

void main()
{
    gl_Position = projection * view *  model * vec4(a_pos, 1.0);
    gl_PointSize = point_size;
}