#version 330 core
layout(location = 0) in vec3 a_pos;//位置
layout(location = 1) in vec2 a_tex_coords;//uv坐标
layout(location = 2) in vec3 a_normal;//法线
//值得注意的是，这里实际上是占用了location,3，4，5，6因为他是4*4的矩阵，有4个vec4变量
layout (location = 3) in mat4 a_instance_matrix;//点的model矩阵

// declare an interface block; see 'Advanced GLSL' for what these are.
out VsOut{
    vec3 frag_pos;
    vec2 tex_coords;
    vec3 normal;
} vs_out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;//点云的model矩阵

void main()
{
    vs_out.frag_pos = vec3(model * vec4(a_pos, 1.0));
    vs_out.tex_coords = a_tex_coords;
    vs_out.normal = vec3(model * vec4(a_normal, 1.0));
    gl_Position = projection * view * model * a_instance_matrix * vec4(a_pos, 1.0f); 
}