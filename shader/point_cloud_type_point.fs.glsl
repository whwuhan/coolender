#version 330 core
/**
绘制点状的点云
*/
out vec4 FragColor;

uniform vec4 pointCloudColor;
void main()
{
    FragColor = pointCloudColor;
}