#version 330 core
layout(location = 0) in vec3 aPos;//位置
layout(location = 1) in vec2 aTexCoords;//uv坐标
layout(location = 2) in vec3 aNormal;//法线


// declare an interface block; see 'Advanced GLSL' for what these are.
out VsOut{
    vec3 FragPos;
    vec2 TexCoords;
    vec3 Normal;
} vsOut;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main(){
    vsOut.FragPos = aPos;
    vsOut.Normal = aNormal;
    vsOut.TexCoords = aTexCoords;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}