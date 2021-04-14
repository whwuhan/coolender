#version 330 core
/**
mesh的点
*/
out vec4 frag_color;

uniform vec4 point_line_color;
uniform vec4 face_color;
uniform bool render_line_point;
void main(){
    if(render_line_point){
        frag_color = point_line_color;
    }else{
        frag_color = face_color;
    }
}