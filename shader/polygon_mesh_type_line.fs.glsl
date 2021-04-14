#version 330 core
/**
 polygon mesh 线框类型
*/
out vec4 frag_color;

uniform vec4 point_line_color;
void main(){
    frag_color = point_line_color;
}