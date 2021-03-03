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
uniform float intensity;
uniform vec3 lightColor;


void main()
{
    vec3 color = texture(floorTexture,fsIn.TexCoords).rgb;

    // ambient 环境光
    vec3 ambient = intensity * color;

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
    // HDR tonemapping
    // color = color / (color + vec3(1.0));
    // gamma correct
    // color = pow(color, vec3(1.0/2.2)); 

    FragColor = vec4(color, 1.0);
    // FragColor = vec4(1.0f, 0.0f, 0.0f, 0.0f);
}