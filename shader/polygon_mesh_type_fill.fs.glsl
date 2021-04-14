#version 330 core
/**
 polygon mesh 填充类型
*/
out vec4 frag_color;

uniform vec4 face_color;//面片颜色

void main(){
    frag_color = face_color;
}