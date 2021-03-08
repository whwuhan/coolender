#version 330 core
out vec4 FragColor;

// 注意这里要重新声明一次VsOut
in VsOut
{
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} fsIn;

uniform sampler2D floorTexture;

uniform vec3 viewPos;

//平行光源信息
uniform vec3 lightColor;
uniform float ambientIntensity;
uniform vec3 parallelLightDir;//平行光源的方向

//地板信息
uniform vec4 floorColor;
uniform bool floorUseTex;//地板是否使用纹理

void main()
{
    //地板颜色
    vec3 color;
    if(floorUseTex)
    {
        color = texture(floorTexture,fsIn.TexCoords).rgb;
    }
    else
    {
        color = vec3(floorColor);
    }
    

    // ambient 环境光
    vec3 ambient = ambientIntensity * color * lightColor;

    // diffuse 漫反射
    vec3 lightDir = normalize(parallelLightDir);
    vec3 normal = normalize(fsIn.Normal);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color * lightColor;

    // specular 镜面光
    vec3 viewDir = normalize(viewPos - fsIn.FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
    vec3 specular = lightColor * spec;
    
    color = ambient + diffuse + specular;

    //HDR
    // color = color / (vec3(1.0f) + color);
    FragColor = vec4(color, 1.0);
}