#version 330 core
/**
Blinn-phong光照模型
*/
out vec4 FragColor;

// 注意这里要重新声明一次VS_OUT
in VsOut{
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} fsIn;//fragment shader input

uniform vec3 lightPos;//灯光位置
uniform vec3 viewPos;//视角位置
uniform vec4 pointCloudColor;//点云颜色 

void main()
{   
    vec3 color = pointCloudColor.rgb;
    // ambient 环境光
    vec3 ambient = 0.05 * color;
    // diffuse 漫反射
    vec3 lightDir = normalize(lightPos - fsIn.FragPos);
    vec3 normal = normalize(fsIn.Normal);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;
    // specular 镜面光
    vec3 viewDir = normalize(viewPos - fsIn.FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
    vec3 specular = vec3(0.3) * spec;// assuming bright white light color
    color = vec3(ambient + diffuse + specular);
    // HDR tonemapping
    color = color / (color + vec3(1.0));
    // gamma correct
    color = pow(color, vec3(1.0/2.2)); 
    FragColor = vec4(color, 1.0);
}