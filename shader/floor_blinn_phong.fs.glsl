#version 330 core
out vec4 FragColor;

// 注意这里要重新声明一次VsOut
in VsOut
{
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;// 顶点在光源空间中的坐标位置（类比相机坐标系，只是视角是从光源看出来）
} fsIn;

//纹理
uniform sampler2D floorTexture;
uniform sampler2D shadowMap;        // 阴影贴图

//视角位置
uniform vec3 viewPos;

//平行光源信息
uniform vec3 lightColor;
uniform vec3 lightPos;//光源位置
uniform vec3 lightLookAt;//光源聚焦位置

uniform float ambientIntensity;

//地板信息
uniform vec4 floorColor;//不使用纹理时的颜色信息
uniform bool floorUseTex;//地板是否使用纹理

// 计算是否在阴影中
float ShadowCalculation(vec4 fragPosLightSpace){
    // perform perspective divide 计算正交投影之后的坐标(计算平行光照是用的正交投影，而不是透视投影)
    // （注意投影矩阵只会显示视锥中的物体，同时会把坐标转化为标准设备坐标[-1,1]，将不在该范围的点裁剪掉）
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;//这里要手动除以w，因为只会在vs赋值给gl_Position后自动除以w
    // transform to [0,1] range 将坐标的范围转化到[0,1]
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
    float bias = 0.0005; // 加一个bias防止摩尔纹

    // 或者通过视角与fragment的法线计算bias
    // vec3 lightDir = normalize(lightPos - fsIn.FragPos);
    // vec3 normal = normalize(fsIn.Normal);
    // float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005); 
    float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
    return shadow;
}


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
    vec3 lightDir = normalize(lightPos - lightLookAt);
    vec3 normal = normalize(fsIn.Normal);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color * lightColor;

    // specular 镜面光
    vec3 viewDir = normalize(viewPos - fsIn.FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
    vec3 specular = spec * color * lightColor;
    
    // calculate shadow
    float shadow = ShadowCalculation(fsIn.FragPosLightSpace); // 判断是否在阴影中，如果是返回1.0否则返回0.0

    //color = ambient + diffuse + specular;

    //HDR
    // color = color / (vec3(1.0f) + color);
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular));
    FragColor = vec4(lighting, 1.0);
}