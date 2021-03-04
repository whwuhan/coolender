#version 330 core
/**
绘制球状的点云
*/
out vec4 FragColor;
in VsOut
{
    vec3 FragPos;
    vec2 TexCoords;
    vec3 Normal;
} fsIn;

//点云颜色
uniform vec3 pointCloudColor;

//视角位置
uniform vec3 viewPos;   

//平行光源信息
uniform vec3 lightColor;
uniform float ambientIntensity;
uniform vec3 parallelLightDir2;//平行光源的方向

void main()
{
    vec3 color = pointCloudColor;

    // ambient 环境光
    vec3 ambient = ambientIntensity * color;

    // diffuse 漫反射
    vec3 lightDir = normalize(parallelLightDir2);
    vec3 normal = normalize(fsIn.Normal);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;

    // specular 镜面光
    vec3 viewDir = normalize(viewPos - fsIn.FragPos);    
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
    vec3 specular = lightColor * spec;
    
    color = ambient + diffuse + specular;

    FragColor = vec4(color, 1.0f);
}