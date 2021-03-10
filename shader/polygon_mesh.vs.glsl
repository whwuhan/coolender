#version 330 core
/**
绘制Polygon Mesh
*/
layout(location = 0) in vec3 aPos;//mesh坐标
layout(location = 1) in vec3 aNormal;//法线

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform float pointSize;//mesh点的大小

void main()
{
    gl_Position = projection * view *  model * vec4(aPos, 1.0);
    gl_PointSize = 5;
}