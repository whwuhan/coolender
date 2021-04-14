#include <cld_shadow_mapping.h>
using namespace std;
using namespace coolender;
using namespace glm;

// ShadowMapping::ShadowMapping():
// shadow_mapping_scale(3),
// width(Window::width * shadow_mapping_scale),
// height(Window::height * shadow_mapping_scale),
// near_plane(0.1f),
// far_plane(100.0f),
// depth_map_FBO(0),
// depth_map(0)
// {}

// ShadowMapping::ShadowMapping(unsigned int width, unsigned int height, float near_plane, float far_plane):
// width(width),
// height(height),
// near_plane(near_plane),
// far_plane(far_plane),
// depth_map_FBO(0),
// depth_map(0)
// {}

//FrameBuffer Object的分辨率
float ShadowMapping::shadow_mapping_scale = 1.0;//shadow mapping分辨率缩放
unsigned int ShadowMapping::width = Window::width;
unsigned int ShadowMapping::height = Window::height;


unsigned int ShadowMapping::depth_map_FBO = 0;// 创建 depth map framebuffer object
unsigned int ShadowMapping::depth_map = 0;// create depth texture 将深度信息放在纹理上
float ShadowMapping::near_plane = 0.1f;//在光源位置渲染时，投影矩阵近平面
float ShadowMapping::far_plane = 100.0f;//远平面

void ShadowMapping::init(){
    // 创建 depth map framebuffer object
    glGenFramebuffers(1, &ShadowMapping::depth_map_FBO);
    // create depth texture 将深度信息放在纹理上
    glGenTextures(1, &ShadowMapping::depth_map);
    glBindTexture(GL_TEXTURE_2D, ShadowMapping::depth_map);
    //设置当前绑定纹理的信息 注意纹理的类型，参数 纹理的类型， level, 纹理内部存储数据的格式， 宽，高 
    glTexImage2D(
        GL_TEXTURE_2D, 
        0, GL_DEPTH_COMPONENT, 
        ShadowMapping::width * ShadowMapping::shadow_mapping_scale, 
        ShadowMapping::height * ShadowMapping::shadow_mapping_scale, 
        0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL
    );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //防止视锥外的部分被视作阴影 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float border_color[] = { 1.0, 1.0, 1.0, 1.0 };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border_color);
    // attach depth texture as FBO's depth buffer 将纹理绑定在帧缓冲上
    glBindFramebuffer(GL_FRAMEBUFFER, ShadowMapping::depth_map_FBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, ShadowMapping::depth_map, 0);
    glDrawBuffer(GL_NONE);//表示只需要深度信息
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

//渲染整个场景的depth map
void ShadowMapping::render_depth_map(Shader &depth_map_shader){
    mat4 light_projection, light_view;
    mat4 light_space_matrix;
    // 正交投影矩阵  参数 左 右 下 上 远 近平面
    light_projection = ortho(-5.0f, 5.0f, -5.0f, 5.0f, near_plane, far_plane);
    // 从光照位置生成的观察矩阵
    light_view = lookAt(Scene::parallel_light.position, Scene::parallel_light.look_at, glm::vec3(0.0f,1.0f,0.0));
    light_space_matrix = light_projection * light_view; //可以将世界坐标系中的点转换到光照空间中

    // 开始渲染从光照位置的depth map
    // 设置视口参数 参数 x y 宽 高
    glViewport(0, 0, ShadowMapping::width * ShadowMapping::shadow_mapping_scale, ShadowMapping::height * ShadowMapping::shadow_mapping_scale);
    glBindFramebuffer(GL_FRAMEBUFFER, ShadowMapping::depth_map_FBO);
    glClear(GL_DEPTH_BUFFER_BIT);
    
    //剔除正面防止peter panning
    glEnable(GL_CULL_FACE); //开启面剔除
    glFrontFace(GL_CW); //设置顺时针的面为正面
    glCullFace(GL_FRONT);//剔除前面的面
    //开始渲染
    //render_floor_depth_map(depth_map_shader, light_space_matrix);//渲染地板depth map 做了面剔除后不会再渲染地板了
    render_point_cloud_type_sphere_depth_map(depth_map_shader, light_space_matrix);//渲染球状点云shadow mapping的depth map
    render_polygon_mesh_depth_map(depth_map_shader, light_space_matrix);//渲染polygon mesh的depth map
    glCullFace(GL_BACK); // 不要忘记设回原先的culling face
    glDisable(GL_CULL_FACE); //关闭面剔除

    // 解绑帧缓冲
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    // reset viewport
    int width, height;
    glfwGetFramebufferSize(Window::glfw_window, &width, &height);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//渲染地板的depth map
void ShadowMapping::render_floor_depth_map(coolender::Shader &depth_map_shader, glm::mat4& light_space_matrix){
    depth_map_shader.use();
    depth_map_shader.setMat4("light_space_matrix", light_space_matrix);
    depth_map_shader.setMat4("model", mat4(1.0f));
    depth_map_shader.setBool("render_point_cloud", false);
    glBindVertexArray(Scene::floor.VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

//渲染点云的depth map
void ShadowMapping::render_point_cloud_type_sphere_depth_map(Shader &depth_map_shader, mat4& light_space_matrix){
    for (auto it = Scene::point_cloud_map.begin(); it != Scene::point_cloud_map.end(); it++){
        //判断是否显示球状点云
        if (it->second.show){
            depth_map_shader.use();
            // vs uniform
            depth_map_shader.setMat4("light_space_matrix", light_space_matrix);
            depth_map_shader.setMat4("model", it->second.model);
            depth_map_shader.setBool("render_point_cloud", true);
            //判断是否改变了球状点云的半径
            if (it->second.change_point_size){
                Scene::sphere_map[it->first].set_radius_segments_by_point_size(it->second.point_size);
                Render::render_point_cloud_type_sphere_init(it->second, Scene::sphere_map[it->first]); //重新初始化（因为球的大小变了，要更新VAO）
            }
            //渲染球状点云
            Render::render_point_cloud_type_sphere(it->second, Scene::sphere_map[it->first]);
        }
    }
}

//渲染polygon mesh的depth map
void ShadowMapping::render_polygon_mesh_depth_map(Shader &depth_map_shader, mat4& light_space_matrix){
    //渲染polygon mesh
    for(auto it = Scene::polygon_mesh_map.begin(); it != Scene::polygon_mesh_map.end(); it++){
        if(it->second.show){
            depth_map_shader.use();
            // vs uniform
            depth_map_shader.setMat4("light_space_matrix", light_space_matrix);
            depth_map_shader.setMat4("model", it->second.model);
            depth_map_shader.setBool("render_point_cloud", false);
            Render::render_polygon_mesh_type_fill(it->second);
        }
    }
}
