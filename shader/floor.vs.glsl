#version 330 core
layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_texCoords;

// declare an interface block; see 'Advanced GLSL' for what these are.
out VsOut
{
    vec3 frag_pos;// 将顶点在世界坐标系中的位置传递给片段着色器
    vec3 normal;// 顶点的法线（注意是经过model矩阵移动过后的顶点法线）
    vec2 tex_coords;// 顶点的纹理坐标
    vec4 frag_pos_light_space;// 顶点在光源空间中的坐标位置（类比相机坐标系，只是视角是从光源看出来）
} vs_out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 light_space_matrix;//世界坐标转换到light space

void main()
{
    vs_out.frag_pos = a_pos;
    vs_out.normal = a_normal;
    vs_out.tex_coords = a_texCoords;
    vs_out.frag_pos_light_space = light_space_matrix * vec4(vs_out.frag_pos, 1.0); // 光源坐标系中的坐标
    gl_Position = projection * view * vec4(a_pos, 1.0);
}