#version 330 core
/**
mesh的点
*/
out vec4 FragColor;

uniform vec4 polygonMeshColor;
void main()
{
    // FragColor = polygonMeshColor;
    FragColor = vec4(0.0, 0.0, 0.0, 1.0f);
}