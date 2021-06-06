#include <cld_window.h>
using namespace std;
using namespace coolender;
using namespace glm;
//static变量初始化
GLFWwindow *Window::glfw_window = nullptr;          //glfw window
//窗口大小
unsigned int Window::width = 1600;
unsigned int Window::height = 900;
//相机相关
Camera Window::camera;                                  //相机
float Window::camera_speed_scale = 1.0f;                //相机移速比例
//渲染相关
bool Window::use_MSAA = true;
int Window::MSAA_level = 8;                          //MSAA采样数量
//镜头操作模式
OPERATE_MODE Window::operate_mode = WOW;
//timing
float Window::delta_time = 0.0f;
float Window::last_frame = 0.0f;
//防止模式切换镜头闪烁
bool Window::first_change_to_FPS_mode = true;//第一次切换到FPS操作模式
bool Window::first_change_to_WOW_mode = true;//第一次切换到WOW操作模式
bool Window::change_operate_mode_key_pressed = false;  //更换操作模式按键是否被按下
bool Window::mouse_button_right_first_pressed = true;  //鼠标右键是否第一次被按下
bool Window::mouse_button_right_first_rlease = true;   //鼠标右键是否是第一次被松开
double Window::cursor_pos_x = Window::width / 2.0f;  //鼠标位置X
double Window::cursor_pos_y = Window::height / 2.0f; //鼠标位置Y
//功能
bool Window::screenshot = false;

void Window::init_and_run()
{
    //======================glfw glad opengl 初始化======================
    glfwInit(); //初始化GLFW

    //通过glfwWindowHint()函数来设置参数，前面是参数名称，后面是值
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                 //设置主版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);                 //设置次版本
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //设置使用核心模式
    glfwWindowHint(GLFW_SAMPLES, Window::MSAA_level);               //MSAA采样数
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //mac用户需要设置，初始化才能有效
#endif
    //创建一个窗口对象
    string windowTitle = "Coolender Version " + Coolender::version;
    //参数依次是长，宽，名称，后两个参数忽略
    Window::glfw_window = glfwCreateWindow(Window::width, Window::height, windowTitle.c_str(), NULL, NULL);
    
    if (Window::glfw_window == nullptr)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return;
    }
    //将窗口的上下文设置成主线程的上下文
    glfwMakeContextCurrent(Window::glfw_window);
    glfwSwapInterval(1); // Enable vsync 每帧的交换间隔，防止屏幕撕裂
    //注册回调函数，告诉GLFW窗口大小调整时，调用这个回调函数
    glfwSetFramebufferSizeCallback(Window::glfw_window, framebuffer_size_callback);
    //鼠标滚轮监听
    glfwSetScrollCallback(Window::glfw_window, scroll_callback);
    //鼠标点击回调函数
    glfwSetMouseButtonCallback(glfw_window, mouse_button_callback);
    //鼠标移动回调函数 默认模式是WOW风格
    glfwSetCursorPosCallback(glfw_window, nullptr);
    //告诉GLFW选中窗口不显示鼠标
    //glfwSetInputMode(Window::glfw_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //GLAD是用来管理OpenGL的函数指针
    //初始化GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        //glfwGetProcAddress 根据编译的系统给出了正确的函数
        cout << "Failed to initialize GLAD" << endl;
        return;
    }
    //openGL全局配置
    glEnable(GL_DEPTH_TEST);         //开启深度测试
    glEnable(GL_MULTISAMPLE);        // 开启MSAA通常都是默认开启的
    glEnable(GL_PROGRAM_POINT_SIZE); //开启改变点的大小（暂时无用）

    //glPoint_size(25);
    //======================glfw glad opengl 初始化结束======================

    //CoolenderUI初始化
    CoolenderUI::init(Window::glfw_window);

    //shader
    //地板
    Plane floor;
    floor.init();
    Scene::floor = floor;
    Shader floor_shader("shader/floor.vs.glsl", "shader/floor.fs.glsl");
    floor_shader.use();
    floor_shader.setInt("floor_texture", 0);
    floor_shader.setInt("shadow_map", 1);
    
    
    //point cloud shader
    Shader point_cloud_type_point_shader("shader/point_cloud_type_point.vs.glsl", "shader/point_cloud_type_point.fs.glsl");//点状点云shader
    Shader point_cloud_type_shpere_shader("shader/point_cloud_type_sphere.vs.glsl", "shader/point_cloud_type_sphere.fs.glsl");//绘制球状点云
    
    //polygon mesh shader
    Shader polygon_mesh_type_line_shader("shader/polygon_mesh.vs.glsl", "shader/polygon_mesh_type_line.fs.glsl");
    Shader polygon_mesh_type_fill_shader("shader/polygon_mesh.vs.glsl", "shader/polygon_mesh_type_fill.fs.glsl");
    Shader polygon_mesh_type_line_fill_shader("shader/polygon_mesh.vs.glsl", "shader/polygon_mesh_type_line_fill.fs.glsl");
    Shader polygon_mesh_type_light_shader("shader/polygon_mesh.vs.glsl", "shader/polygon_mesh_type_light.fs.glsl");
    
    //shadow mapping depth map shader
    Shader depth_map_shader("shader/shadow_mapping_depth.vs.glsl", "shader/shadow_mapping_depth.fs.glsl");
    ShadowMapping::init();

    //渲染循环
    // Main loop
    while (!glfwWindowShouldClose(Window::glfw_window))
    {
        
        // per-frame time logic
        float current_frame = glfwGetTime();
        Window::delta_time = current_frame - Window::last_frame;
        Window::last_frame = current_frame;
        //初始设置

        //键盘鼠标事件监听
        process_input(Window::glfw_window);

        //开始渲染场景
        //背景颜色
        glClearColor
        (
            Scene::clear_color.x,
            Scene::clear_color.y,
            Scene::clear_color.z,
            Scene::clear_color.w
        );
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //渲染shawdow mapping depth map(只有显示地板的时候渲染shadow mapping)
        if(Scene::show_floor) ShadowMapping::render_depth_map(depth_map_shader);
        
        //获取投影矩阵和相机矩阵
        mat4 projection = perspective(radians(camera.Zoom), (float)Window::width / (float)Window::height, 0.1f, 100.0f);
        mat4 view = camera.GetViewMatrix();

        //渲染地板
        if (Scene::show_floor)
        {
            floor_shader.use();
            // vs uniform
            //暂时不需要model矩阵
            floor_shader.setMat4("projection", projection);
            floor_shader.setMat4("view", view);
            mat4 light_projection;
            mat4 light_view;
            mat4 light_space_matrix;
            // 正交投影矩阵  参数 左 右 下 上 远 近平面
            light_projection = ortho(-5.0f, 5.0f, -5.0f, 5.0f, ShadowMapping::near_plane, ShadowMapping::far_plane);
            // 从光照位置生成的观察矩阵
            light_view = lookAt(Scene::parallel_light.position, vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f,1.0f,0.0));
            light_space_matrix = light_projection * light_view; //可以将世界坐标系中的点转换到光照空间中
            floor_shader.setMat4("light_space_matrix", light_space_matrix);
            // fs uniform
            // set light uniforms
            floor_shader.setVec3("view_pos", camera.Position);
            floor_shader.setVec3("light_color", vec3(Scene::parallel_light.color));
            floor_shader.setVec3("light_pos", Scene::parallel_light.position);//光源位置
            floor_shader.setVec3("light_look_at", Scene::parallel_light.look_at);
            floor_shader.setFloat("ambient_intensity", Scene::ambient_intensity); //环境光强度
            floor_shader.setBool("floor_use_tex", Scene::floor_use_tex);
            floor_shader.setVec4("floor_color", Scene::floor.color);
            floor_shader.setVec4("clear_color", Scene::clear_color);
            // floor
            glBindVertexArray(floor.VAO);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, floor.texture);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, ShadowMapping::depth_map);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

        //==========================场景渲染==========================
        //渲染点云
        glEnable(GL_CULL_FACE); //开启面剔除，默认剔除背面
        //glCullFace(GL_FRONT);//设置剔除正面
        glFrontFace(GL_CW); //设置顺时针的面为正面
        switch (Scene::point_type)
        {
            //绘制成点
            case POINT:
                for (auto it = Scene::point_cloud_map.begin(); it != Scene::point_cloud_map.end(); it++)
                {
                    //判断是否显示点云模型
                    if (it->second.show)
                    {
                        point_cloud_type_point_shader.use();
                        //vs uniform                   
                        point_cloud_type_point_shader.setMat4("projection", projection);
                        point_cloud_type_point_shader.setMat4("view", view);
                        point_cloud_type_point_shader.setMat4("model", it->second.model);
                        //fs uniform
                        point_cloud_type_point_shader.setFloat("point_size", it->second.point_size);
                        point_cloud_type_point_shader.setVec4("point_cloud_color", it->second.color);
                        //渲染点云
                        Render::render_point_cloud_type_point(it->second);
                    }
                }
                break;
        //将点绘制成球
        case SPHERE:
            for (auto it = Scene::point_cloud_map.begin(); it != Scene::point_cloud_map.end(); it++)
            {
                //判断是否显示球状点云
                if (it->second.show)
                {
                    point_cloud_type_shpere_shader.use();
                    // vs uniform
                    point_cloud_type_shpere_shader.setMat4("projection", projection);
                    point_cloud_type_shpere_shader.setMat4("view", view);
                    point_cloud_type_shpere_shader.setMat4("model", it->second.model);
                    // fs uniform
                    // set light uniforms
                    point_cloud_type_shpere_shader.setVec3("point_cloud_color", vec3(it->second.color));
                    point_cloud_type_shpere_shader.setVec3("view_pos", camera.Position);
                    point_cloud_type_shpere_shader.setVec3("light_color", vec3(Scene::parallel_light.color));//平行光颜色
                    point_cloud_type_shpere_shader.setFloat("ambient_intensity", Scene::ambient_intensity);//平行光环境光强度
                    point_cloud_type_shpere_shader.setVec3("light_pos", Scene::parallel_light.position);//光源位置
                    point_cloud_type_shpere_shader.setVec3("light_look_at", Scene::parallel_light.look_at);//光源位置
                    //判断是否改变了球状点云的半径
                    if (it->second.change_point_size)
                    {
                        Scene::sphere_map[it->first].set_radius_segments_by_point_size(it->second.point_size);
                        Render::render_point_cloud_type_sphere_init(it->second, Scene::sphere_map[it->first]); //重新初始化（因为球的大小变了，要更新VAO）
                    }
                    //渲染球状点云
                    Render::render_point_cloud_type_sphere(it->second, Scene::sphere_map[it->first]);
                }
            }
            break;
        // 绘制成错误类型
        default:
            cerr << "Render Point Cloud Type Wrong!" << endl;
            exit(0);
        } 
        glDisable(GL_CULL_FACE); //关闭面剔除

        //渲染polygon mesh
        for(auto it = Scene::polygon_mesh_map.begin(); it != Scene::polygon_mesh_map.end(); it++){
            if(it->second.show)
            {
                switch(Scene::polygon_mesh_type)
                {
                case LINE:
                    polygon_mesh_type_line_shader.use();
                    polygon_mesh_type_line_shader.setMat4("projection", projection);
                    polygon_mesh_type_line_shader.setMat4("view", view);
                    polygon_mesh_type_line_shader.setMat4("model" , it->second.model);
                    polygon_mesh_type_line_shader.setFloat("point_size", it->second.point_size);
                    polygon_mesh_type_line_shader.setVec4("point_line_color", it->second.point_line_color);
                    Render::render_polygon_mesh_type_line(it->second);
                    break;
                case FILL:
                    polygon_mesh_type_fill_shader.use();
                    polygon_mesh_type_fill_shader.setMat4("projection", projection);
                    polygon_mesh_type_fill_shader.setMat4("view", view);
                    polygon_mesh_type_fill_shader.setMat4("model" , it->second.model);
                    polygon_mesh_type_fill_shader.setFloat("point_size", it->second.point_size);
                    polygon_mesh_type_fill_shader.setVec4("face_color", it->second.face_color);
                    Render::render_polygon_mesh_type_fill(it->second);
                    break;
                case LINE_AND_FILL:
                    polygon_mesh_type_line_fill_shader.use();
                    polygon_mesh_type_line_fill_shader.setMat4("projection", projection);
                    polygon_mesh_type_line_fill_shader.setMat4("view", view);
                    polygon_mesh_type_line_fill_shader.setMat4("model" , it->second.model);
                    polygon_mesh_type_line_fill_shader.setFloat("point_size", it->second.point_size);
                    polygon_mesh_type_line_fill_shader.setVec4("point_line_color", it->second.point_line_color);
                    polygon_mesh_type_line_fill_shader.setVec4("face_color", it->second.face_color);
                    Render::render_polygon_mesh_type_line_fill(it->second, polygon_mesh_type_line_fill_shader);
                    break;
                case LIGHT:
                    polygon_mesh_type_light_shader.use();
                    polygon_mesh_type_light_shader.setMat4("projection", projection);
                    polygon_mesh_type_light_shader.setMat4("view", view);
                    polygon_mesh_type_light_shader.setMat4("model" , it->second.model);
                    polygon_mesh_type_light_shader.setVec3("point_size", vec3(it->second.point_size));
                    polygon_mesh_type_light_shader.setVec3("face_color", vec3(it->second.face_color));
                    polygon_mesh_type_light_shader.setVec3("view_pos", camera.Position);
                    polygon_mesh_type_light_shader.setVec3("light_color", vec3(Scene::parallel_light.color));//平行光颜色
                    polygon_mesh_type_light_shader.setVec3("light_pos", Scene::parallel_light.position);//光源位置
                    polygon_mesh_type_light_shader.setVec3("light_look_at", Scene::parallel_light.look_at);//光源位置
                    polygon_mesh_type_light_shader.setFloat("ambient_intensity", Scene::ambient_intensity);//平行光环境光强度
                    Render::render_polygon_mesh_type_light(it->second);
                    break;
                default:
                    cerr << "Wrong polygon mesh render type!" << endl;
                    exit(0);
                }   
            }
        }//polygon mesh绘制结束
        





        //==========================场景渲染结束==========================

        //场景截图
        if(Window::screenshot)
        {
            string cur_time = Function::get_cur_time();
            Function::screenshot("cld_screenshot_" + cur_time + "_" + to_string(glfwGetTime()) +".png");
        }
        
        //根据场景渲染UI
        //绘制UI 注意绘制UI要放在最后否则UI会被遮盖
        //CoolenderUI.render_demo_ui();
        CoolenderUI::render();
        
        //交换buffer
        glfwSwapBuffers(Window::glfw_window);
        glfwPollEvents();
    }

    //UI cleanup
    CoolenderUI::destroy();

    //glfw cleanup
    glfwDestroyWindow(Window::glfw_window);
    glfwTerminate();

    return;
}

//回调函数声明，更改窗口大小的时候，更改视口大小
void coolender::framebuffer_size_callback(GLFWwindow *glfw_window, int width, int height)
{
    Window::width = width;
    Window::height = height;
    glViewport(0, 0, width, height);
}

// 声明输入函数，判断是否按下键盘
void coolender::process_input(GLFWwindow *glfw_window)
{
    //退出
    if (glfwGetKey(glfw_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(glfw_window, true);

    //按Q切换操作模式
    if 
    (
        glfwGetKey(glfw_window, GLFW_KEY_Q) == GLFW_PRESS && 
        !Window::change_operate_mode_key_pressed && 
        glfwGetMouseButton(glfw_window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE
    )
    {
        Window::change_operate_mode_key_pressed = true;
        change_operate_mode(Window::glfw_window);
    }
    if (glfwGetKey(glfw_window, GLFW_KEY_Q) == GLFW_RELEASE)
    {
        Window::change_operate_mode_key_pressed = false;
    }

    //截图快捷键
    if 
    (
        glfwGetKey(glfw_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS && 
        glfwGetKey(glfw_window, GLFW_KEY_P) == GLFW_PRESS
    )
    {
        Window::screenshot = true;
    }
        

    //键盘监听
    //相机移动
    //向前
    if (glfwGetKey(glfw_window, GLFW_KEY_W) == GLFW_PRESS)
    {
        Window::camera.ProcessKeyboard(FORWARD, Window::delta_time * Window::camera_speed_scale);
    }
    //向后
    if (glfwGetKey(glfw_window, GLFW_KEY_S) == GLFW_PRESS)
    {
        Window::camera.ProcessKeyboard(BACKWARD, Window::delta_time * Window::camera_speed_scale);
    }
    //向左
    if (glfwGetKey(glfw_window, GLFW_KEY_A) == GLFW_PRESS)
    {
        Window::camera.ProcessKeyboard(LEFT, Window::delta_time * Window::camera_speed_scale);
    }
    //向右
    if (glfwGetKey(glfw_window, GLFW_KEY_D) == GLFW_PRESS)
    {
        Window::camera.ProcessKeyboard(RIGHT, Window::delta_time * Window::camera_speed_scale);
    }
    //向上
    if (glfwGetKey(glfw_window, GLFW_KEY_SPACE))
    {
        Window::camera.ProcessKeyboard(UPWARD, Window::delta_time * Window::camera_speed_scale);
    }
}

//修改操作模式
void coolender::change_operate_mode(GLFWwindow *glfw_window)
{
    switch(Window::operate_mode)
    {
    //注意设置的顺序
    case WOW:
        //切换为FPS风格
        Window::first_change_to_FPS_mode = true;
        Window::operate_mode = FPS;
        glfwSetMouseButtonCallback(glfw_window, nullptr);                //禁用鼠标按键监听
        glfwSetInputMode(glfw_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//隐藏鼠标
        glfwSetCursorPosCallback(glfw_window, FPS_mode_mouse_callback);     //设置鼠标的移动模式为FPS mode
        break;
    case FPS:
        //切换为WOW风格
        Window::first_change_to_WOW_mode = true;
        Window::operate_mode = WOW;
        glfwSetMouseButtonCallback(glfw_window, mouse_button_callback);    //启动鼠标按键监听
        glfwSetInputMode(glfw_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);  //显示鼠标
        glfwSetCursorPosCallback(glfw_window, WOW_mode_mouse_callback);     //设置鼠标的移动模式为WOW mode
        break;
    default:
        cerr << "Wrong operate mode!" << endl;
        exit(0);
    }
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void coolender::scroll_callback(GLFWwindow *winglfwWindowdow, double xoffset, double yoffset)
{
    Window::camera.ProcessMouseScroll(yoffset);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
//移动模式下的鼠标移动回调函数 类似FPS游戏
void coolender::FPS_mode_mouse_callback(GLFWwindow *glfw_window, double xpos, double ypos)
{   
    //防止镜头抖动
    if (Window::first_change_to_FPS_mode)
    {
        Window::cursor_pos_x = xpos;
        Window::cursor_pos_y = ypos;
        Window::first_change_to_FPS_mode = false;
    }

    float xoffset = xpos - Window::cursor_pos_x;
    float yoffset = Window::cursor_pos_y - ypos; // reversed since y-coordinates go from bottom to top

    Window::cursor_pos_x = xpos;
    Window::cursor_pos_y = ypos;

    Window::camera.ProcessMouseMovement(xoffset, yoffset);
}

//鼠标点击回调函数
void coolender::mouse_button_callback(GLFWwindow* glfw_window, int button, int action, int mods)
{
    //===============WOW操作风格下的鼠标按键监听===============
    //监听鼠标右键按下
    if (action == GLFW_PRESS && Window::operate_mode == WOW)
    {
        switch(button)
        {
        case GLFW_MOUSE_BUTTON_RIGHT:
            if(Window::mouse_button_right_first_pressed){
                glfwSetCursorPosCallback(glfw_window, nullptr);                  //先禁用鼠标移动监听
                Window::mouse_button_right_first_pressed = false;
                Window::mouse_button_right_first_rlease = true;
                Window::first_change_to_WOW_mode = true;
                glfwSetInputMode(glfw_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//隐藏鼠标
                glfwSetCursorPosCallback(glfw_window, WOW_mode_mouse_callback);     //设置为WOW操作模式
            }
            break;
        }
    }
    //监听鼠标右键释放
    if(action == GLFW_RELEASE && Window::operate_mode == WOW)
    {
        switch(button)
        {
        case GLFW_MOUSE_BUTTON_RIGHT:
            if(Window::mouse_button_right_first_rlease)
            {
                glfwSetCursorPosCallback(glfw_window, nullptr);                  //先禁用鼠标移动监听
                Window::mouse_button_right_first_pressed = true;
                Window::mouse_button_right_first_rlease = false;
                glfwSetInputMode(glfw_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);//显示鼠标
                // Window::first_change_to_WOW_mode = true;
            }
            // Window::mouse_button_right_first_rlease = true;
            break;
        }
    }//WOW操作模式下的鼠标监听结束
}

//鼠标模式下的鼠标移动回调函数 类似WOW
void coolender::WOW_mode_mouse_callback(GLFWwindow* glfw_window, double xpos, double ypos)
{
    if (glfwGetMouseButton(glfw_window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    { 
        //防止镜头抖动
        if (Window::first_change_to_WOW_mode)
        {
            Window::cursor_pos_x = xpos;
            Window::cursor_pos_y = ypos;
            Window::first_change_to_WOW_mode = false;
        }
        float xoffset = xpos - Window::cursor_pos_x;
        float yoffset = Window::cursor_pos_y - ypos; // reversed since y-coordinates go from bottom to top

        Window::cursor_pos_x = xpos;
        Window::cursor_pos_y = ypos;

        Window::camera.ProcessMouseMovement(xoffset, yoffset); 
    }
}

//获取当前指针的位置
void coolender::get_cursor_pos(GLFWwindow *glfw_window, double xpos, double ypos)
{
    Window::cursor_pos_x = xpos;
    Window::cursor_pos_y = ypos;
}

