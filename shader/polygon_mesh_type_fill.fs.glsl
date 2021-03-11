#version 330 core
/**
 polygon mesh 填充类型
*/
out vec4 FragColor;

uniform vec4 faceColor;
void main()
{
    FragColor = faceColor;
}