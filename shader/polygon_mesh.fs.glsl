#version 330 core
/**
mesh的点
*/
out vec4 FragColor;

uniform int polygonModel;//polygon mesh的绘制模式 线框模式和填充模式，或者点模式
// uniform vec4 pointCloudColor;
void main()
{
    if(polygonModel == 0) FragColor = vec4(0.6f, 0.6f ,0.6f, 1.0f);
    if(polygonModel == 1) FragColor = vec4(0.0f, 0.0f ,0.0f, 1.0f);
    
}