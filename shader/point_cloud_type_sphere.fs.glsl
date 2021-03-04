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

uniform vec3 viewPos;
//光照信息
uniform vec3 lightColor;
uniform float ambientIntensity;//环境光强度
//点云颜色
uniform vec4 pointCloudColor;

void main()
{
    vec3 color = vec3(pointCloudColor);
    // ambient 环境光
    vec3 ambient = ambientIntensity * color;
    
    // diffuse 漫反射
    vec3 lightDir = normalize(vec3(1.0f, 1.0f, 0.0f));
    vec3 normal = normalize(fsIn.Normal);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;

    // specular 镜面光
    vec3 viewDir = normalize(viewPos - fsIn.FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
    vec3 specular = lightColor * spec;// assuming bright white light color
    
    color = ambient + diffuse + specular;
    // // HDR tonemapping
    // // color = color / (color + vec3(1.0));
    // // gamma correct
    // // color = pow(color, vec3(1.0/2.2)); 

    FragColor = vec4(color, 1.0f);
    // FragColor = vec4(1.0f, 0.0f, 0.0f, 0.0f);
}