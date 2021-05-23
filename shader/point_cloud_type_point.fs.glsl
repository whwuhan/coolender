#version 330 core
/**
绘制点状的点云
*/
out vec4 frag_color;

uniform vec4 point_cloud_color;

void main()
{
    frag_color = point_cloud_color;
}