#version 330 core
/**
mesh的点
*/
out vec4 FragColor;

in VsOut
{
    vec3 FragPos;
    vec3 Normal;
} fsIn;

//面片颜色
uniform vec3 faceColor;

//视角位置
uniform vec3 viewPos;   

//平行光源信息
uniform vec3 lightColor;
uniform vec3 lightPos;//光源位置
uniform vec3 lightLookAt;//光源聚焦位置

//环境光强度
uniform float ambientIntensity;

void main()
{
    vec3 color = faceColor;

     // ambient 环境光
    vec3 ambient = ambientIntensity * color * lightColor;

    // diffuse 漫反射
    vec3 lightDir = normalize(lightPos - lightLookAt);
    vec3 normal = normalize(fsIn.Normal);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color * lightColor;

    // specular 镜面光
    vec3 viewDir = normalize(viewPos - fsIn.FragPos);    
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
    vec3 specular = spec * lightColor;
    
    color = ambient + diffuse + specular;

    //HDR
    // color = color / (vec3(1.0f) + color);

    FragColor = vec4(color, 1.0);
}