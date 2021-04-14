#version 330 core
/**
绘制球状的点云
*/
out vec4 frag_color;
in VsOut{
    vec3 frag_pos;
    vec2 tex_coords;
    vec3 normal;
} fs_in;

//点云颜色
uniform vec3 point_cloud_color;

//视角位置
uniform vec3 view_pos;

//平行光源信息
uniform vec3 light_color;
uniform vec3 light_pos;//光源位置
uniform vec3 light_look_at;//光源聚焦位置

//环境光强度
uniform float ambient_intensity;
void main(){
    vec3 color = point_cloud_color;

    // ambient 环境光
    vec3 ambient = ambient_intensity * color * light_color;
    // vec3 ambient = ambient_intensity * color;   

    // diffuse 漫反射
    vec3 light_dir = normalize(light_pos - light_look_at);
    // vec3 light_dir = normalize(light_pos);
    vec3 normal = normalize(fs_in.normal);
    float diff = max(dot(light_dir, normal), 0.0);
    vec3 diffuse = diff * color * light_color;
    // vec3 diffuse = diff * color;

    // specular 镜面光
    vec3 view_dir = normalize(view_pos - fs_in.frag_pos);    
    vec3 halfway_dir = normalize(light_dir + view_dir);
    float spec = pow(max(dot(normal, halfway_dir), 0.0), 32.0);
    vec3 specular = spec * light_color;
    
    color = ambient + diffuse + specular;

    //HDR
    // color = color / (vec3(1.0f) + color);

    frag_color = vec4(color, 1.0);
}
