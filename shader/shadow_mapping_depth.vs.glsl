#version 330 core
layout (location = 0) in vec3 a_pos;
//值得注意的是，这里实际上是占用了location,3，4，5，6因为他是4*4的矩阵，有4个vec4变量
layout (location = 3) in mat4 a_instance_matrix;//渲染点云用的实例化矩阵

uniform mat4 light_space_matrix;
uniform mat4 model;

//是否渲染的是点云
uniform bool render_point_cloud;

void main(){
    if(render_point_cloud){
        // 将所有坐标转化到 light space
        gl_Position = light_space_matrix * model * a_instance_matrix * vec4(a_pos, 1.0);
    }else{
        // 将所有坐标转化到 light space
        gl_Position = light_space_matrix * model * vec4(a_pos, 1.0);
    }
}