#version 330 core
out vec4 frag_color;

// 注意这里要重新声明一次VsOut
in VsOut{
    vec3 frag_pos;
    vec3 normal;
    vec2 tex_coords;
    vec4 frag_pos_light_space;// 顶点在光源空间中的坐标位置（类比相机坐标系，只是视角是从光源看出来）
} fs_in;

//纹理
uniform sampler2D floor_texture;
uniform sampler2D shadow_map;        // 阴影贴图

//视角位置
uniform vec3 view_pos;

//平行光源信息
uniform vec3 light_color;
uniform vec3 light_pos;//光源位置
uniform vec3 light_look_at;//光源聚焦位置

uniform float ambient_intensity;

//地板信息
uniform vec4 floor_color;//不使用纹理时的颜色信息
uniform bool floor_use_tex;//地板是否使用纹理
uniform vec4 clear_color;

// 计算是否在阴影中
float shadow_calculation(vec4 frag_pos_light_space){
    // perform perspective divide 计算正交投影之后的坐标(计算平行光照是用的正交投影，而不是透视投影)
    // 在vertex shader中经过MVP变换后
    // （注意投影矩阵只会显示视锥中的物体，同时会把坐标转化为标准设备坐标[-1,1]，将不在该范围的点裁剪掉）
    vec3 proj_coords = frag_pos_light_space.xyz / frag_pos_light_space.w;//这里要手动除以w，因为只会在vs赋值给gl_Position后自动除以w
    // transform to [0,1] range 将坐标的范围转化到[0,1]
    proj_coords = proj_coords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closest_depth = texture(shadow_map, proj_coords.xy).r;
    // get depth of current fragment from light's perspective
    float current_depth = proj_coords.z;
    // check whether current frag pos is in shadow
    float bias = 0.001; // 加一个bias防止摩尔纹

    // 或者通过视角与fragment的法线计算bias
    // vec3 light_dir = normalize(light_pos - fs_in.frag_pos);
    // vec3 normal = normalize(fs_in.normal);
    // float bias = max(0.05 * (1.0 - dot(normal, light_dir)), 0.005); 
    // float shadow = current_depth - bias > closest_depth  ? 1.0 : 0.0;

    // PCF
    float shadow = 0.0;
    vec2 texel_size = 1.0 / textureSize(shadow_map, 0); //textureSize()返回shadow map第0级的分辨率 之所以除1，是因为下面的projCoords.xy已经是标准坐标了
    for(int x = -1; x <= 1; ++x){// x = -1,0,1
        for(int y = -1; y <= 1; ++y){// y = -1,0,1 一共采样9次
            float pcf_depth = texture(shadow_map, proj_coords.xy + vec2(x, y) * texel_size).r; 
            shadow += current_depth - bias > pcf_depth  ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0; //一共采样9次，所以除以9

    // keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    // 视锥外的物体，都视作不在阴影中
    if(proj_coords.z > 1.0) shadow = 0.0;
        
    return shadow;
}

void blinn_phong(float intensity){
    //地板颜色
    vec3 color;
    if(floor_use_tex){
        color = texture(floor_texture, fs_in.tex_coords).rgb;
    }else{
        color = vec3(floor_color);
    }
    
    // ambient 环境光
    vec3 ambient = ambient_intensity * color * light_color;

    // diffuse 漫反射
    vec3 light_dir = normalize(light_pos - light_look_at);
    vec3 normal = normalize(fs_in.normal);
    float diff = max(dot(light_dir, normal), 0.0);
    vec3 diffuse = diff * color * light_color;

    // specular 镜面光
    vec3 view_dir = normalize(view_pos - fs_in.frag_pos);
    vec3 halfway_dir = normalize(light_dir + view_dir);
    float spec = pow(max(dot(normal, halfway_dir), 0.0), 32.0);
    vec3 specular = spec * color * light_color;
    
    // calculate shadow
    float shadow = shadow_calculation(fs_in.frag_pos_light_space); // 判断是否在阴影中，如果是返回1.0否则返回0.0

    //color = ambient + diffuse + specular;

    //HDR
    // color = color / (vec3(1.0f) + color);
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular));
    frag_color = vec4(lighting, 1.0) * intensity;
}

void main(){
    float dis_frag_pos_to_cen = distance(fs_in.frag_pos, vec3(0.0f, -1.0f, 0.0f));//场景中心的距离
    if(dis_frag_pos_to_cen > 10){//地面绘制成圆形
        frag_color = clear_color;
    }else{
        blinn_phong(1);
    }
}