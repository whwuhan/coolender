#version 330 core
/**
 polygon mesh 线框类型
*/
out vec4 FragColor;

uniform vec4 pointAndLineColor;
void main()
{
    // FragColor = polygonMeshColor;
    FragColor = pointAndLineColor;
}