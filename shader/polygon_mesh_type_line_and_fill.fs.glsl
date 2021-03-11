#version 330 core
/**
mesh的点
*/
out vec4 FragColor;

uniform vec4 pointAndLineColor;
uniform vec4 faceColor;
uniform bool renderLineAndPoint;
void main()
{
    // FragColor = polygonMeshColor;
    if(renderLineAndPoint)
    {
        FragColor = pointAndLineColor;
    }
    else
    {
        FragColor = faceColor;
    }
}