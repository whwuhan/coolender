#include <cld_coolender_ui.h>
using namespace coolender;
using namespace std;
using namespace wh::basic;
using namespace wh::utils::io;
//static 变量初始化
GLFWwindow* CoolenderUI::glfw_window = nullptr;
//整体设置
float CoolenderUI::font_size = 15.0;//字体大小
float CoolenderUI::global_scale = 1.0;//整体的字体缩放
float CoolenderUI::window_rounding = 6.0;//窗口的圆角
float CoolenderUI::frame_rounding = 3.0;//内部图标的圆角

bool CoolenderUI::show_right_sidebar = true;
bool CoolenderUI::show_usage = true;
bool CoolenderUI::show_message_box = true;
bool CoolenderUI::show_point_cloud_obj_file_choose_dialog = false;
bool CoolenderUI::show_polygon_mesh_obj_file_choose_dialog = false;
bool CoolenderUI::show_model_obj_file_choose_dialog = false;
bool CoolenderUI::show_screenshot_save_dir_choose_dialog = false;
int CoolenderUI::style = 0;//UI风格

float CoolenderUI::usage_pos_x = 3;//usage位置的X坐标
float CoolenderUI::usage_pos_y = 22;//usage位置的Y坐标
float CoolenderUI::right_sidebar_pos_x = 3;//右侧边栏位置的X坐标(距离右侧的距离) 
float CoolenderUI::right_sidebar_pos_y = 22;//右侧边栏位置的Y坐标
float CoolenderUI::right_sidebar_width = 500;//右侧边栏宽
float CoolenderUI::right_sidebar_height = 650;//右侧边栏高
float CoolenderUI::message_box_pos_x = 3;//message box距离左边距离
float CoolenderUI::message_box_pos_y = 300;//message box距离usage的纵向距离

//初始化UI
void CoolenderUI::init(GLFWwindow* glfw_window)
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    //io
    ImGuiIO& io = ImGui::GetIO(); 
    (void)io;
    io.FontGlobalScale = global_scale;//设置字体的缩放大小
    // io.Fonts->AddFontFromFileTTF("fonts/Cousine-Regular.ttf", font_size);//设置字体
    // io.Fonts->AddFontFromFileTTF("fonts/DroidSans.ttf", font_size);//设置字体
    // io.Fonts->AddFontFromFileTTF("fonts/Karla-Regular.ttf", font_size);//设置字体
    // io.Fonts->AddFontFromFileTTF("fonts/ProggyClean.ttf", font_size);//设置字体
    //io.Fonts->AddFontFromFileTTF("fonts/ProggyTiny.ttf", font_size);//设置字体
    io.Fonts->AddFontFromFileTTF("fonts/Roboto-Medium.ttf", CoolenderUI::font_size);//设置字体
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls


    // Setup Dear ImGui style
    ImGuiStyle& style = ImGui::GetStyle();
    style.FrameRounding = frame_rounding; //设置frame的圆角
    style.WindowRounding = window_rounding;//设置window的圆角
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(glfw_window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

//渲染DemoUI
void CoolenderUI::render_demo_ui()
{
    bool show = true;
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    
    ImGui::ShowDemoWindow(&show);
    
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

//渲染所有UI
void CoolenderUI::render()
{
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        IM_ASSERT(ImGui::GetCurrentContext() != NULL && "Missing dear imgui context. Refer to examples app!");
        //开始渲染UI
        render_menu();//顶部菜单栏


        // We specify a default position/size in case there's no data in the .ini file.
        // We only do it to make the demo applications a little more welcoming, but typically this isn't required.
        // const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
        // ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 650, main_viewport->WorkPos.y + 20), ImGuiCond_FirstUseEver);
        // ImGui::SetNextWindowSize(ImVec2(100, 68), ImGuiCond_FirstUseEver);
        // ImGuiWindowFlags windowFlags = 0;
        //     // Demonstrate the various window flags. Typically you would just use the default!
        // static bool no_titlebar = false;
        // static bool no_scrollbar = false;
        // static bool no_menu = false;
        // static bool no_move = false;
        // static bool no_resize = true;
        // static bool no_collapse = false;
        // static bool no_close = false;
        // static bool no_nav = false;
        // static bool no_background = false;
        // static bool no_bring_to_front = false;
        // if (no_titlebar)        windowFlags |= ImGuiWindowFlags_NoTitleBar;
        // if (no_scrollbar)       windowFlags |= ImGuiWindowFlags_NoScrollbar;
        // if (!no_menu)           windowFlags |= ImGuiWindowFlags_MenuBar;
        // if (no_move)            windowFlags |= ImGuiWindowFlags_NoMove;
        // if (no_resize)          windowFlags |= ImGuiWindowFlags_NoResize;
        // if (no_collapse)        windowFlags |= ImGuiWindowFlags_NoCollapse;
        // if (no_nav)             windowFlags |= ImGuiWindowFlags_NoNav;
        // if (no_background)      windowFlags |= ImGuiWindowFlags_NoBackground;
        // if (no_bring_to_front)  windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;

        //初始界面显示部分
        if(CoolenderUI::show_usage) CoolenderUI::render_usage();//使用手册
        if(CoolenderUI::show_right_sidebar) CoolenderUI::render_right_sidebar();//右侧Sidebar
        if(CoolenderUI::show_message_box) CoolenderUI::render_message_box();//messagebox
        //初始显示部分结束

        //界面隐藏部分
        
        if(CoolenderUI::show_point_cloud_obj_file_choose_dialog) 
            CoolenderUI::render_point_cloud_obj_file_choose_dialog();//显示obj点云文件选择框
        if(CoolenderUI::show_polygon_mesh_obj_file_choose_dialog) 
            CoolenderUI::render_polygon_mesh_obj_file_choose_dialog();//obj polygon mesh
        if(CoolenderUI::show_model_obj_file_choose_dialog) 
            CoolenderUI::render_model_obj_file_choose_dialog();//obj model
        if(CoolenderUI::show_screenshot_save_dir_choose_dialog)
            CoolenderUI::render_screenshot_save_dir_choose_dialog();//截图存放位置选择对话框
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

//渲染顶部菜单栏
void CoolenderUI::render_menu(){
    //顶部菜单栏
    if (ImGui::BeginMainMenuBar())
    {   
        //File
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Import point clouds .obj", ""))
            {
                CoolenderUI::show_point_cloud_obj_file_choose_dialog = true;
            }
            if (ImGui::MenuItem("Import polygom mesh .obj", ""))
            {
                CoolenderUI::show_polygon_mesh_obj_file_choose_dialog = true;
            }
            if (ImGui::MenuItem("Import model .obj (TODO)", NULL, false, false))
            {
                CoolenderUI::show_model_obj_file_choose_dialog = true;
            }
            ImGui::EndMenu();
        }
        
        //Edit
        // if (ImGui::BeginMenu("Edit"))
        // {
        //     if (ImGui::MenuItem("Undo", "CTRL+Z"))
        //     {
                
        //     }
        //     if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
        //     ImGui::Separator();
        //     if (ImGui::MenuItem("Cut", "CTRL+X")) {}
        //     if (ImGui::MenuItem("Copy", "CTRL+C")) {}
        //     if (ImGui::MenuItem("Paste", "CTRL+V")) {}
        //     ImGui::EndMenu();
        // }

        //Window 控制显示哪些窗口
        if (ImGui::BeginMenu("Window"))
        {
            //使用手册
            if (ImGui::MenuItem("Show Usage", NULL, CoolenderUI::show_usage))
            {
                CoolenderUI::show_usage = !CoolenderUI::show_usage;
            }
            //message box
            if (ImGui::MenuItem("Show Message Box", NULL, CoolenderUI::show_message_box))
            {
                CoolenderUI::show_message_box = !CoolenderUI::show_message_box;
            }
            //右侧Sidebar
            if (ImGui::MenuItem("Show Right Sidebar", NULL, CoolenderUI::show_right_sidebar))
            {
                CoolenderUI::show_right_sidebar = !CoolenderUI::show_right_sidebar;
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

//渲染使用手册窗口
void CoolenderUI::render_usage()
{   
    //设置大小和位置
    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos
    (
        ImVec2
        (
            main_viewport->WorkPos.x + CoolenderUI::usage_pos_x, 
            main_viewport->WorkPos.y + CoolenderUI::usage_pos_y
        ), 
        ImGuiCond_FirstUseEver
    );
    //ImGui::SetNextWindowSize(ImVec2(400, 200), ImGuiCond_FirstUseEver);
    
    //窗口内容
    ImGui::Begin("Usage", &CoolenderUI::show_usage, ImGuiWindowFlags_AlwaysAutoResize);
    {
        ImGui::Text("How to switch mode:");
        ImGui::BulletText("Please press Q to switch operate mode!");
        ImGui::Separator();
        ImGui::Text("In WOW operate mode(default operate mode):");
        ImGui::BulletText("Like World of Warcraft's operate mode.");
        ImGui::BulletText("You can use cursor to select what you want.");
        ImGui::BulletText("Press WASD and SPACE key to move your view position.");
        ImGui::BulletText("Move your mouse with mouse right button pressed to change view angle.");
        ImGui::BulletText("Scroll the mouse wheel to change the field of view.");
        ImGui::Separator();
        ImGui::Text("In FPS operate mode:");
        ImGui::BulletText("Like FPS game's operate mode.");
        ImGui::BulletText("Press WASD and SPACE key to move your view position.");
        ImGui::BulletText("Move your mouse to change view angle.");
        ImGui::BulletText("Scroll the mouse wheel to change the field of view.");
    }
    ImGui::End();
}

//渲染右侧Sidebar
void CoolenderUI::render_right_sidebar()
{
    //获取glfw window宽高
    int win_width, win_height;
    glfwGetFramebufferSize(Window::glfw_window, &win_width, &win_height);
    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    //设置位置
    ImGui::SetNextWindowPos
    (
        ImVec2
        (
            main_viewport->WorkPos.x + win_width - CoolenderUI::right_sidebar_width - CoolenderUI::right_sidebar_pos_x, 
            main_viewport->WorkPos.y + CoolenderUI::right_sidebar_pos_y
        ), 
            ImGuiCond_FirstUseEver
    );
    //设置Sidebar大小
    ImGui::SetNextWindowSize
    (
        ImVec2(CoolenderUI::right_sidebar_width, CoolenderUI::right_sidebar_height), 
        ImGuiCond_FirstUseEver
    );
    //右侧Sidebar开始
    ImGui::Begin("Coolender", &CoolenderUI::show_right_sidebar, ImGuiWindowFlags_None);
    {
        //被选中时禁用滚轮调整视角
        if(ImGui::IsWindowFocused())
        {
            glfwSetScrollCallback(Window::glfw_window, nullptr);
        }
        else
        {
            glfwSetScrollCallback(Window::glfw_window, scroll_callback);
        }

        //整体全局设置
        ImGui::SetNextItemOpen(true, ImGuiCond_Once);//设置下一个窗口打开（只设置一次）
        if(ImGui::CollapsingHeader("Global Settings"))
        {
            //UI风格设置
            ImGui::SetNextItemOpen(true, ImGuiCond_Once);//设置下一个窗口打开（只设置一次）
            if (ImGui::TreeNode("UI theme settings"))
            {
                if (ImGui::Combo("Theme", &CoolenderUI::style, "Dark\0Light\0Classic"))
                {
                    switch (CoolenderUI::style)
                    {
                        case 0: 
                            ImGui::StyleColorsDark(); 
                            break;
                        case 1: 
                            ImGui::StyleColorsLight(); 
                            break;
                        case 2: 
                            ImGui::StyleColorsClassic(); 
                            break;
                    }
                }
                ImGui::TreePop();
            }
            ImGui::Separator();
            
            //相机设置
            ImGui::SetNextItemOpen(true, ImGuiCond_Once);//设置下一个窗口打开（只设置一次）
            if (ImGui::TreeNode("Camera settings and information"))
            {
                //相机位置
                ImGui::Text("Camera information:");
                ImGui::SetNextItemWidth(80);
                ImGui::DragFloat("posX", &Window::camera.Position.x, 0.01f);ImGui::SameLine();
                ImGui::SetNextItemWidth(80);
                ImGui::DragFloat("posY", &Window::camera.Position.y, 0.01f);ImGui::SameLine();
                ImGui::SetNextItemWidth(80);
                ImGui::DragFloat("posZ", &Window::camera.Position.z, 0.01f);
                //相机朝向
                ImGui::SetNextItemWidth(80);
                ImGui::DragFloat("frontX", &Window::camera.Front.x, 0.01f);ImGui::SameLine();
                ImGui::SetNextItemWidth(80);
                ImGui::DragFloat("frontY", &Window::camera.Front.y, 0.01f);ImGui::SameLine();
                ImGui::SetNextItemWidth(80);
                ImGui::DragFloat("frontZ", &Window::camera.Front.z, 0.01f);
                //相机移动速度
                ImGui::SliderFloat("Speed scale", &Window::camera_speed_scale, 0.0f, 5.0f, "Speed scale = %.3f");
                ImGui::TreePop();
            }
            ImGui::Separator();

            //全局光照信息
            ImGui::SetNextItemOpen(true, ImGuiCond_Once);//设置下一个窗口打开（只设置一次）
            if (ImGui::TreeNode("Global illumination settings"))
            {
                //平行光环境光强度
                ImGui::SliderFloat("Ambient light intensity", &Scene::ambient_intensity, 0.0f, 1.0f, "Ambient intensity = %.3f");
                
                //平行光的方向
                ImGui::Text("Parallel light settings:");
                ImGui::SetNextItemWidth(80);
                ImGui::DragFloat("positionX", &Scene::parallel_light.position.x, 0.1f);ImGui::SameLine();
                ImGui::SetNextItemWidth(80);
                ImGui::DragFloat("positionY", &Scene::parallel_light.position.y, 0.1f);ImGui::SameLine();
                ImGui::SetNextItemWidth(80);
                ImGui::DragFloat("positionZ", &Scene::parallel_light.position.z, 0.1f);

                ImGui::SetNextItemWidth(80);
                ImGui::DragFloat("lookAtX", &Scene::parallel_light.look_at.x, 0.1f);ImGui::SameLine();
                ImGui::SetNextItemWidth(80);
                ImGui::DragFloat("lookAtY", &Scene::parallel_light.look_at.y, 0.1f);ImGui::SameLine();
                ImGui::SetNextItemWidth(80);
                ImGui::DragFloat("lookAtZ", &Scene::parallel_light.look_at.z, 0.1f);   

                

                //光线颜色
                float parallelLightColor[4] = 
                {
                    Scene::parallel_light.color.x,
                    Scene::parallel_light.color.y,
                    Scene::parallel_light.color.z,
                    Scene::parallel_light.color.w
                };
                ImGui::ColorEdit3("Parallel light color", parallelLightColor);
                Scene::parallel_light.color.x = parallelLightColor[0];
                Scene::parallel_light.color.y = parallelLightColor[1];
                Scene::parallel_light.color.z = parallelLightColor[2];
                Scene::parallel_light.color.w = 1.0f;
                ImGui::TreePop();
            }
            ImGui::Separator();
            
            //MSAA 暂时无法动态变更
            // ImGui::Checkbox("MSAA", &Window::use_MSAA);
            // int MSAA_level = Window::MSAA_level;
            // if(Window::use_MSAA)
            // {
            //     ImGui::RadioButton("MSAA x0", &Window::MSAA_level, 0); ImGui::SameLine();
            //     ImGui::RadioButton("MSAA x8", &Window::MSAA_level, 8); ImGui::SameLine();
            //     ImGui::RadioButton("MSAA x16", &Window::MSAA_level, 16); ImGui::SameLine();
            //     ImGui::RadioButton("MSAA x32", &Window::MSAA_level, 32);
            // }
            // if(Window::MSAA_level != MSAA_level)
            // {
            //     glfwWindowHint(GLFW_SAMPLES, Window::MSAA_level);               //MSAA采样数
            //     string windowTitle = "Coolender Version " + Coolender::version;
            //     Window::glfw_window = glfwCreateWindow(Window::width, Window::height, windowTitle.c_str(), NULL, NULL);
            //     //参数依次是长，宽，名称，后两个参数忽略
            //     if (Window::glfw_window == nullptr)
            //     {
            //         cout << "Failed to create GLFW window" << endl;
            //         glfwTerminate();
            //         return;
            //     }
            // }
        }
        

        //========================================================================================================
        //功能相关UI
        ImGui::SetNextItemOpen(true, ImGuiCond_Once);//设置下一个窗口打开（只设置一次）
        if(ImGui::CollapsingHeader("Function"))
        {
            ImGui::SetNextItemOpen(true, ImGuiCond_Once);//设置下一个窗口打开（只设置一次）
            if(ImGui::TreeNode("Screenshot"))
            {
                ImGui::Text("Screenshot save path:");ImGui::SameLine();
                //注意ImGui使用的format string 最好这样写，否则会出现warning
                ImGui::Text("%s", (Function::screenshot_out_path).c_str());ImGui::SameLine();
                if(ImGui::Button("Change path"))
                {
                    CoolenderUI::show_screenshot_save_dir_choose_dialog = true;
                }
                if(ImGui::Button("Screenshot"))
                {
                    Window::screenshot = true;
                }
                //判断前一个组件是否Hovered
                if (ImGui::IsItemHovered())
                {
                    ImGui::BeginTooltip();
                    ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
                    ImGui::TextUnformatted("Shorcut: LEFT CTRL + P");
                    ImGui::PopTextWrapPos();
                    ImGui::EndTooltip();
                }
                ImGui::TreePop();
            }
        }ImGui::Separator();//功能相关UI结束


        //========================================================================================================
        //场景设置
        ImGui::SetNextItemOpen(true, ImGuiCond_Once);//设置下一个窗口打开（只设置一次）
        if(ImGui::CollapsingHeader("Scene Settings"))
        {
            //全局场景设置
            ImGui::SetNextItemOpen(true, ImGuiCond_Once);//设置下一个窗口打开（只设置一次）
            if(ImGui::TreeNode("Global scene settings"))
            {   
                //背景颜色调整框
                float clear_color[4] = 
                {
                    Scene::clear_color.x,
                    Scene::clear_color.y,
                    Scene::clear_color.z,
                    Scene::clear_color.w
                };
                ImGui::ColorEdit3("Background color", clear_color);
                Scene::clear_color.x = clear_color[0];
                Scene::clear_color.y = clear_color[1];
                Scene::clear_color.z = clear_color[2];
                Scene::clear_color.w = 1.0f;
                
                //shadow mapping 分辨率缩放设置
                float shadow_mapping_scale = ShadowMapping::shadow_mapping_scale;
                ImGui::DragFloat("Shadow mapping resolution scale", &ShadowMapping::shadow_mapping_scale, 0.05f, 1.0f, 5.0f, "Shadow mapping resolution scale: %.3f");
                if(abs(ShadowMapping::shadow_mapping_scale - shadow_mapping_scale) > 0.01)
                {
                    ShadowMapping::init();//如果改变了shadow mapping的缩放大小重新初始化
                }
                ImGui::Separator();

                //点云全局设置
                ImGui::SetNextItemOpen(true, ImGuiCond_Once);//设置下一个窗口打开（只设置一次）
                if (ImGui::TreeNode("Point cloud global settings"))
                {
                    //所有点云显示设置
                    for(auto it = Scene::point_cloud_map.begin(); it != Scene::point_cloud_map.end(); it++)
                    {
                        //如果有一个点云不显示，设置Scene::show_all_point_cloud为false
                        if(!it->second.show)
                        {
                            Scene::show_all_point_cloud = false;
                            break;
                        }
                        else
                        {
                            Scene::show_all_point_cloud = true;
                        }
                    }
                    //判断是否显示所有点云
                    bool show_all_point_cloud = Scene::show_all_point_cloud;
                    ImGui::Checkbox("Show all the point clouds", &Scene::show_all_point_cloud);
                    if(show_all_point_cloud != Scene::show_all_point_cloud)
                    {
                        //如果改变了Scene::show_all_point_cloud，将所有点云的show属性设置为Scene::show_all_point_cloud
                        for(auto it = Scene::point_cloud_map.begin(); it != Scene::point_cloud_map.end(); it++)
                        {
                            it->second.show = Scene::show_all_point_cloud;
                        }
                    }

                    //设置点云类型
                    int point_type = Scene::point_type;//enum强制转换为int
                    ImGui::Text("Point cloud render type:");ImGui::SameLine();
                    ImGui::RadioButton("Point", &point_type, 0); ImGui::SameLine();
                    ImGui::RadioButton("Sphere", &point_type, 1);
                    Scene::point_type = POINT_TYPE(point_type);//int强制转化为enum

                    //设置所有点云的point size
                    for(auto it = Scene::point_cloud_map.begin(); it != Scene::point_cloud_map.end(); it++)
                    {
                        // 将所有点云的change_point_size设置为false
                        it->second.change_point_size = false;
                    }
                    float point_cloud_point_size = Scene::point_cloud_point_size;
                    ImGui::DragFloat
                    (
                        "Global point cloud point size", 
                        &Scene::point_cloud_point_size, 
                        0.005f, 0.0f, 2.0f, 
                        "Global point cloud point size: %.3f"
                    );
                    ImGui::SameLine();
                    warning_marker("WARNING!!! If you set all the point clouds' point size \ntoo big in sphere type with too many point cloud models, \nyour PC will explode!!!");
                    if(abs(Scene::point_cloud_point_size - point_cloud_point_size) > 0.001)
                    {//如果改变的点云球面的大小
                        for(auto it = Scene::point_cloud_map.begin(); it != Scene::point_cloud_map.end(); it++)
                        {
                            it->second.point_size = Scene::point_cloud_point_size;
                            it->second.change_point_size = true;
                        }
                    }

                    //设置所有点云的颜色
                    float point_cloud_color_r = Scene::point_cloud_point_color.x;
                    float point_cloud_color_g = Scene::point_cloud_point_color.y;
                    float point_cloud_color_b = Scene::point_cloud_point_color.z;
                    float point_cloud_point_color[3] = 
                    {
                        Scene::point_cloud_point_color.x,
                        Scene::point_cloud_point_color.y,
                        Scene::point_cloud_point_color.z
                    };
                    ImGui::ColorEdit3("Global point cloud point color", point_cloud_point_color);
                    Scene::point_cloud_point_color.x = point_cloud_point_color[0];
                    Scene::point_cloud_point_color.y = point_cloud_point_color[1];
                    Scene::point_cloud_point_color.z = point_cloud_point_color[2];
                    //判断是否更改了全局点云颜色
                    if
                    (
                        abs(Scene::point_cloud_point_color.x - point_cloud_color_r) >  0.001 ||
                        abs(Scene::point_cloud_point_color.y - point_cloud_color_g) >  0.001 ||
                        abs(Scene::point_cloud_point_color.z - point_cloud_color_b) >  0.001 
                    )
                    {
                        for(auto it = Scene::point_cloud_map.begin(); it != Scene::point_cloud_map.end(); it++)
                        {
                            //color
                            it->second.color.x = point_cloud_point_color[0];
                            it->second.color.y = point_cloud_point_color[1];
                            it->second.color.z = point_cloud_point_color[2];
                            // it->second.color.w = 1.0;
                        }
                    }
                    ImGui::TreePop();
                }
                //point cloud 全局设置结束

                //Polygon mesh全局设置
                ImGui::SetNextItemOpen(true, ImGuiCond_Once);//设置下一个窗口打开（只设置一次）
                if (ImGui::TreeNode("Polygon mesh global settings"))
                {
                    //所有polygon mesh显示设置
                    for(auto it = Scene::polygon_mesh_map.begin(); it != Scene::polygon_mesh_map.end(); it++)
                    {
                        //如果有一个polygon mesh不显示，设置Scene::show_all_polygon_mesh为false
                        if(!it->second.show)
                        {
                            Scene::show_all_polygon_mesh = false;
                            break;
                        }
                        else
                        {
                             Scene::show_all_polygon_mesh = true;
                        }
                    }
                    //判断是否显示所有mesh
                    bool show_all_polygon_mesh = Scene::show_all_polygon_mesh;
                    ImGui::Checkbox("Show all the polygon mesh", &Scene::show_all_polygon_mesh);
                    if(show_all_polygon_mesh != Scene::show_all_polygon_mesh)
                    {
                        //如果改变了Scene::show_all_polygon_mesh，将所有点云的show属性设置为Scene::show_all_polygon_mesh
                        for(auto it = Scene::polygon_mesh_map.begin(); it != Scene::polygon_mesh_map.end(); it++)
                        {
                            it->second.show = Scene::show_all_polygon_mesh;
                        }
                    }

                    //设置mesh类型
                    int polygon_mesh_type = Scene::polygon_mesh_type;//enum强制转换为int
                    ImGui::Text("Polygon mesh render type:");ImGui::SameLine();
                    ImGui::RadioButton("Line", &polygon_mesh_type, 0); ImGui::SameLine();
                    ImGui::RadioButton("Fill", &polygon_mesh_type, 1); ImGui::SameLine();
                    ImGui::RadioButton("Line and fill", &polygon_mesh_type, 2); ImGui::SameLine();
                    ImGui::RadioButton("Light", &polygon_mesh_type, 3);
                    Scene::polygon_mesh_type = POLYGON_MESH_TYPE(polygon_mesh_type);//int强制转化为enum

                    float polygon_mesh_point_size = Scene::polygon_mesh_point_size;
                    ImGui::DragFloat("Global polygon mesh point size", &Scene::polygon_mesh_point_size, 0.005f, 0.0f, 50.0f, "Global polygon mesh point size: %.3f");
                    if(abs(Scene::polygon_mesh_point_size - polygon_mesh_point_size) > 0.001)
                    {
                        //如果改变了polygon mesh顶点的大小
                        for(auto it = Scene::polygon_mesh_map.begin(); it != Scene::polygon_mesh_map.end(); it++)
                        {
                            it->second.point_size = Scene::polygon_mesh_point_size;
                        }
                    }

                    //设置所有polygon mesh的颜色
                    //点和线的颜色
                    float polygonMeshPointAndLineColorR = Scene::polygon_mesh_point_line_color.x;
                    float polygonMeshPointAndLineColorG = Scene::polygon_mesh_point_line_color.y;
                    float polygonMeshPointAndLineColorB = Scene::polygon_mesh_point_line_color.z;
                    float polygon_mesh_point_line_color[3] = 
                    {
                        Scene::polygon_mesh_point_line_color.x,
                        Scene::polygon_mesh_point_line_color.y,
                        Scene::polygon_mesh_point_line_color.z
                    };
                    ImGui::ColorEdit3("Global polygon mesh point and line color", polygon_mesh_point_line_color);
                    Scene::polygon_mesh_point_line_color.x = polygon_mesh_point_line_color[0];
                    Scene::polygon_mesh_point_line_color.y = polygon_mesh_point_line_color[1];
                    Scene::polygon_mesh_point_line_color.z = polygon_mesh_point_line_color[2];
                    //判断是否更改了全局点云颜色
                    if
                    (
                        abs(Scene::polygon_mesh_point_line_color.x - polygonMeshPointAndLineColorR) >  0.001 ||
                        abs(Scene::polygon_mesh_point_line_color.y - polygonMeshPointAndLineColorG) >  0.001 ||
                        abs(Scene::polygon_mesh_point_line_color.z - polygonMeshPointAndLineColorB) >  0.001 
                    )
                    {
                        for(auto it = Scene::polygon_mesh_map.begin(); it != Scene::polygon_mesh_map.end(); it++)
                        {
                            //color
                            it->second.point_line_color.x = polygon_mesh_point_line_color[0];
                            it->second.point_line_color.y = polygon_mesh_point_line_color[1];
                            it->second.point_line_color.z = polygon_mesh_point_line_color[2];
                        }
                    }
                    //面的颜色
                    float face_color_r = Scene::polygon_mesh_face_color.x;
                    float face_color_g = Scene::polygon_mesh_face_color.y;
                    float face_color_b = Scene::polygon_mesh_face_color.z;
                    float polygon_mesh_face_color[3] = 
                    {
                        Scene::polygon_mesh_face_color.x,
                        Scene::polygon_mesh_face_color.y,
                        Scene::polygon_mesh_face_color.z
                    };
                    ImGui::ColorEdit3("Global polygon mesh face color", polygon_mesh_face_color);
                    Scene::polygon_mesh_face_color.x = polygon_mesh_face_color[0];
                    Scene::polygon_mesh_face_color.y = polygon_mesh_face_color[1];
                    Scene::polygon_mesh_face_color.z = polygon_mesh_face_color[2];
                    //判断是否更改了全局点云颜色
                    if
                    (
                        abs(Scene::polygon_mesh_face_color.x - face_color_r) >  0.001 ||
                        abs(Scene::polygon_mesh_face_color.y - face_color_g) >  0.001 ||
                        abs(Scene::polygon_mesh_face_color.z - face_color_b) >  0.001 
                    )
                    {
                        for(auto it = Scene::polygon_mesh_map.begin(); it != Scene::polygon_mesh_map.end(); it++)
                        {
                            //color
                            it->second.face_color.x = polygon_mesh_face_color[0];
                            it->second.face_color.y = polygon_mesh_face_color[1];
                            it->second.face_color.z = polygon_mesh_face_color[2];
                            // it->second.color.w = 1.0;
                        }
                    }
                    ImGui::TreePop();
                }
                ImGui::TreePop();
            }
            ImGui::Separator();
            //polygon mesh 全局设置结束


            //地板显示设置
            //ImGui::TableNextColumn();
            ImGui::SetNextItemOpen(true, ImGuiCond_Once);//设置下一个窗口打开（只设置一次）
            if (ImGui::TreeNode("Floor:"))
            {
                ImGui::Checkbox("Show floor", &Scene::show_floor);ImGui::SameLine();
                ImGui::Checkbox("Use texture", &Scene::floor_use_tex);
                if(!Scene::show_floor)
                {
                    Scene::floor_use_tex = false;
                }
                if(Scene::show_floor && !Scene::floor_use_tex)
                {
                    //地板不使用纹理，使用纯色
                    float floor_color[] = 
                    {
                        Scene::floor.color.x,
                        Scene::floor.color.y,
                        Scene::floor.color.z
                    };
                    ImGui::ColorEdit3("Floor color", floor_color);
                    Scene::floor.color.x = floor_color[0];
                    Scene::floor.color.y = floor_color[1];
                    Scene::floor.color.z = floor_color[2];
                }
                ImGui::TreePop();
            }
            ImGui::Separator();
            //地板设置结束

            //======================根据场景中数据渲染UI======================
            //点云数据
            ImGui::SetNextItemOpen(true, ImGuiCond_Once);//设置下一个窗口打开（只设置一次）
            if (ImGui::TreeNode("Point Cloud:"))
            {
                //每一个点云
                for(auto it = Scene::point_cloud_map.begin(); it != Scene::point_cloud_map.end(); it++)
                {   
                    ImGui::SetNextItemOpen(true, ImGuiCond_Once);//设置下一个窗口打开（只设置一次）
                    if (ImGui::TreeNode(it->first.c_str()))
                    {   
                        //checkbox
                        ImGui::Checkbox("Show point cloud", &it->second.show);
                        
                        //设置point_size
                        float point_size = it->second.point_size;//用于判断是否改变了point size
                        ImGui::DragFloat("Point size", &it->second.point_size, 0.005f, 0.0f, 2.0f, "Point size: %.3f");
                        //ImGui::SliderFloat("Point size", &it->second.point_size, 0.0f, 10.f, "Point size = %.3f");
                        //判断是否改变了球面的半径
                        if(abs(it->second.point_size - point_size) > 0.001)
                        {
                            it->second.change_point_size = true;
                        }
                        //color
                        float pointColor[3] = 
                        {
                            it->second.color.x,
                            it->second.color.y,
                            it->second.color.z,
                        };
                        ImGui::ColorEdit3("Point color", pointColor);
                        it->second.color.x = pointColor[0];
                        it->second.color.y = pointColor[1];
                        it->second.color.z = pointColor[2];
                        it->second.color.w = 1.0;
                        
                        //注意glm::mat4是按照列优选的顺序来的
                        //缩放
                        ImGui::SliderFloat("Scale", &it->second.scale, 0.0f, 10.0f, "Scale = %.3f");
                        it->second.model = glm::scale(glm::mat4(1.0f), glm::vec3(it->second.scale));

                        //平移 
                        ImGui::SetNextItemWidth(80);
                        ImGui::DragFloat("trans_x", &it->second.trans_x, 0.01f);ImGui::SameLine();                        
                        ImGui::SetNextItemWidth(80);
                        ImGui::DragFloat("trans_y", &it->second.trans_y, 0.01f);ImGui::SameLine();
                        ImGui::SetNextItemWidth(80);
                        ImGui::DragFloat("trans_z", &it->second.trans_z, 0.01f);
                        it->second.model = 
                        glm::translate
                        (
                            it->second.model,
                            glm::vec3(it->second.trans_x, it->second.trans_y, it->second.trans_z)
                        );
                        
                        //旋转
                        ImGui::SetNextItemWidth(80);
                        ImGui::DragFloat("rotate_x", &it->second.rotate_x, 0.1f);ImGui::SameLine();
                        ImGui::SetNextItemWidth(80);
                        ImGui::DragFloat("rotate_y", &it->second.rotate_y, 0.1f);ImGui::SameLine();
                        ImGui::SetNextItemWidth(80);
                        ImGui::DragFloat("rotate_z", &it->second.rotate_z, 0.1f);
                        it->second.model = 
                        glm::rotate
                        (
                            it->second.model,
                            glm::radians(it->second.rotate_x), 
                            glm::vec3(1.0f, 0.0f, 0.0f)
                        );

                        it->second.model = 
                        glm::rotate
                        (
                            it->second.model,
                            glm::radians(it->second.rotate_y), 
                            glm::vec3(0.0f, 1.0f, 0.0f)
                        );
                        it->second.model = 
                        glm::rotate
                        (
                            it->second.model,
                            glm::radians(it->second.rotate_z), 
                            glm::vec3(0.0f, 0.0f, 1.0f)
                        );

                        //delete button 
                        ImVec2 button_size(ImGui::GetFontSize() * 6.0f, 0.0f);
                        if(ImGui::Button("Delete", button_size))
                        {
                            Scene::delete_point_cloud(it->first);
                            //注意这里删除后要break否则会出现内存错误
                            //猜测是因为map删除元素后，迭代器失效！！！！
                            ImGui::TreePop();
                            break;
                        }
                        ImGui::TreePop();
                    }
                }
                ImGui::TreePop();
            }
            ImGui::Separator();
            //场景点云数据UI绘制结束


            //polygon mesh的相关UI
            ImGui::SetNextItemOpen(true, ImGuiCond_Once);//设置下一个窗口打开（只设置一次）
            if (ImGui::TreeNode("Polygon Mesh:"))
            {
                //每一个polygon mesh的UI
                for(auto it = Scene::polygon_mesh_map.begin(); it != Scene::polygon_mesh_map.end(); it++)
                {
                    ImGui::SetNextItemOpen(true, ImGuiCond_Once);//设置下一个窗口打开（只设置一次）
                    if (ImGui::TreeNode(it->first.c_str()))
                    {   
                        //checkbox
                        ImGui::Checkbox("Show polygon mesh", &it->second.show);
                        
                        //设置point_size
                        ImGui::DragFloat("Point size", &it->second.point_size, 0.005f, 0.0f, 50.0f, "Point size: %.3f");
                        
                        //color
                        float point_line_color[3] = 
                        {
                            it->second.point_line_color.x,
                            it->second.point_line_color.y,
                            it->second.point_line_color.z,
                        };
                        ImGui::ColorEdit3("Point and line color", point_line_color);
                        it->second.point_line_color.x = point_line_color[0];
                        it->second.point_line_color.y = point_line_color[1];
                        it->second.point_line_color.z = point_line_color[2];
                        it->second.point_line_color.w = 1.0;

                        float face_color[3] = 
                        {
                            it->second.face_color.x,
                            it->second.face_color.y,
                            it->second.face_color.z,
                        };
                        ImGui::ColorEdit3("Face color", face_color);
                        it->second.face_color.x = face_color[0];
                        it->second.face_color.y = face_color[1];
                        it->second.face_color.z = face_color[2];
                        
                        //注意glm::mat4是按照列优选的顺序来的
                        //缩放
                        ImGui::SliderFloat("Scale", &it->second.scale, 0.0f, 10.0f, "Scale = %.3f");
                        it->second.model = glm::scale(glm::mat4(1.0f), glm::vec3(it->second.scale));

                        //平移 
                        ImGui::SetNextItemWidth(80);
                        ImGui::DragFloat("trans_x", &it->second.trans_x, 0.01f);ImGui::SameLine();                        
                        ImGui::SetNextItemWidth(80);
                        ImGui::DragFloat("trans_y", &it->second.trans_y, 0.01f);ImGui::SameLine();
                        ImGui::SetNextItemWidth(80);
                        ImGui::DragFloat("trans_z", &it->second.trans_z, 0.01f);
                        it->second.model = 
                        glm::translate
                        (
                            it->second.model,
                            glm::vec3(it->second.trans_x, it->second.trans_y, it->second.trans_z)
                        );
                        
                        //旋转
                        ImGui::SetNextItemWidth(80);
                        ImGui::DragFloat("rotate_x", &it->second.rotate_x, 0.1f);ImGui::SameLine();
                        ImGui::SetNextItemWidth(80);
                        ImGui::DragFloat("rotate_y", &it->second.rotate_y, 0.1f);ImGui::SameLine();
                        ImGui::SetNextItemWidth(80);
                        ImGui::DragFloat("rotate_z", &it->second.rotate_z, 0.1f);
                        it->second.model = 
                        glm::rotate
                        (
                            it->second.model,
                            glm::radians(it->second.rotate_x), 
                            glm::vec3(1.0f, 0.0f, 0.0f)
                        );
                        it->second.model = 
                        glm::rotate
                        (
                            it->second.model,
                            glm::radians(it->second.rotate_y), 
                            glm::vec3(0.0f, 1.0f, 0.0f)
                        );
                        it->second.model = 
                        glm::rotate
                        (
                            it->second.model,
                            glm::radians(it->second.rotate_z), 
                            glm::vec3(0.0f, 0.0f, 1.0f)
                        );

                        //delete button 
                        ImVec2 button_size(ImGui::GetFontSize() * 6.0f, 0.0f);
                        if(ImGui::Button("Delete", button_size))
                        {
                            Scene::delete_polygon_mesh(it->first);
                            //注意这里删除后要break否则会出现内存错误
                            //猜测是因为map删除元素后，迭代器失效！！！！
                            ImGui::TreePop();
                            break;
                        }
                        ImGui::TreePop();
                    }
                }
                ImGui::TreePop();
            }
            ImGui::Separator();
            //场景polygon mesh设置UI结束
            //======================根据场景中数据渲染UI结束======================
        }
    }
    ImGui::End();//sidebar结束
}

//message信息框
void CoolenderUI::render_message_box()
{   
    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    //获取glfw window宽高
    int win_width, win_height;
    glfwGetFramebufferSize(Window::glfw_window, &win_width, &win_height);
    //设置大小
    // ImGui::SetNextWindowSize
    // (
    //     ImVec2(CoolenderUI::messageBoxWidth, CoolenderUI::messageBoxHeight), 
    //     ImGuiCond_FirstUseEver
    // );

    //设置位置
    ImGui::SetNextWindowPos
    (
        ImVec2
        (   
            // 注意FramebufferSize是窗口实际长度的2倍(?????)
            main_viewport->WorkPos.x + CoolenderUI::message_box_pos_x, 
            main_viewport->WorkPos.y + CoolenderUI::message_box_pos_y
        ), 
        ImGuiCond_FirstUseEver
    );

    //Message box
    ImGui::Begin("Message Box", &CoolenderUI::show_message_box, ImGuiWindowFlags_AlwaysAutoResize);
    {   
        //简介
        ImGui::Text("Brief Introduction:");
        ImGui::BulletText("This is a simple scene renderer for \npoint clouds, polygon meshes without any \nPBR texture and models with PBR textures(TODO).");
        ImGui::Separator();
        //显示帧数
        ImGui::Text
        (
            "Application average %.3f ms/frame (%.1f FPS)", 
            1000.0f / ImGui::GetIO().Framerate, 
            ImGui::GetIO().Framerate
        );
    }
    ImGui::End();
}

//渲染点云文件选择框
void CoolenderUI::render_point_cloud_obj_file_choose_dialog()
{
    //设置大小和位置
    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos
    (
        ImVec2(main_viewport->WorkPos.x + 30, main_viewport->WorkPos.y + 50), 
        ImGuiCond_FirstUseEver
    );
    ImGui::SetNextWindowSize(ImVec2(400, 600), ImGuiCond_FirstUseEver);
    ImGuiFileDialog::Instance()->OpenDialog("polygon_mesh_obj_file_choose_dialog", "Choose Obj File", ".obj", ".", 0);
    ImGuiFileDialog::Instance()->SetExtentionInfos(".obj", ImVec4(1,0,1, 0.9));//设置.obj文件的颜色
    // display
    if (ImGuiFileDialog::Instance()->Display("polygon_mesh_obj_file_choose_dialog")) 
    {
        // action if OK 点击OK
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            //获取的路径和文件名称
            auto file_map = ImGuiFileDialog::Instance()->GetSelection();//返回一个map<string, string> key是文件名，value是路径
            for(auto it = file_map.begin(); it != file_map.end(); it++)
            {
                // action
                cout << "You choose point cloud file:" << it->first << endl;
                cout << "Your choosed file’s path is " << it->second << endl;
                //读取点云数据
                PointCloud pointCloud;
                load_point_cloud_obj(it->second, &pointCloud);
                //将点云添加到场景中
                Scene::add_point_cloud(it->second, pointCloud);
                //传输数据给GPU
                Render::render_point_cloud_type_point_init(Scene::point_cloud_map[it->second]);//点状点云
                //球状点云准备
                Sphere sphere;
                sphere.create_sphere(); 
                Render::render_point_cloud_type_sphere_init(Scene::point_cloud_map[it->second], sphere);//初始化球状点云
                Scene::add_sphere(it->second, sphere);//将对应的球体添加到场景中
            }
            //关闭窗口
            ImGuiFileDialog::Instance()->Close();
            CoolenderUI::show_point_cloud_obj_file_choose_dialog = false;
        }
        // close
        ImGuiFileDialog::Instance()->Close();
        CoolenderUI::show_point_cloud_obj_file_choose_dialog = false;
    }        
}

//渲染mesh文件选择框
void CoolenderUI::render_polygon_mesh_obj_file_choose_dialog()
{
    //设置大小和位置
    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 30, main_viewport->WorkPos.y + 50), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(400, 600), ImGuiCond_FirstUseEver);
    ImGuiFileDialog::Instance()->OpenDialog("polygon_mesh_obj_file_choose_dialog", "Choose Obj File", ".obj", ".", 0);
    ImGuiFileDialog::Instance()->SetExtentionInfos(".obj", ImVec4(1,0,1, 0.9));//设置.obj文件的颜色
    // display
    if (ImGuiFileDialog::Instance()->Display("polygon_mesh_obj_file_choose_dialog")) 
    {
        // action if OK 点击OK
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            //获取的路径和文件名称
            auto file_map = ImGuiFileDialog::Instance()->GetSelection();//返回一个map<string, string> key是文件名，value是路径
            for(auto it = file_map.begin(); it != file_map.end(); it++)
            {
                // action
                cout << "You choose polygon mesh file:" << it->first << endl;
                cout << "Your choosed file’s path is " << it->second << endl;
                //读取点云数据
                PolygonMesh mesh;
                load_polygon_mesh_obj(it->second, &mesh);
                //将点云添加到场景中
                Scene::add_polygon_mesh(it->second, mesh);
                //传输数据给GPU
                Render::render_polygon_mesh_init(Scene::polygon_mesh_map[it->second]);//polygon mesh准备
            }
            //关闭窗口
            ImGuiFileDialog::Instance()->Close();
            CoolenderUI::show_polygon_mesh_obj_file_choose_dialog = false;
        }
        // close
        ImGuiFileDialog::Instance()->Close();
        CoolenderUI::show_polygon_mesh_obj_file_choose_dialog = false;
    }        
}

//渲染model文件选择对话框
void CoolenderUI::render_model_obj_file_choose_dialog()
{
    //设置大小和位置
    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos
    (
        ImVec2(main_viewport->WorkPos.x + 30, main_viewport->WorkPos.y + 50), 
        ImGuiCond_FirstUseEver
    );
    ImGui::SetNextWindowSize(ImVec2(400, 600), ImGuiCond_FirstUseEver);
    ImGuiFileDialog::Instance()->OpenDialog("ModelObjFileChooseDialog", "Choose Obj File", ".obj", ".", 0);
    ImGuiFileDialog::Instance()->SetExtentionInfos(".obj", ImVec4(1,0,1, 0.9));//设置.obj文件的颜色
    // display
    if (ImGuiFileDialog::Instance()->Display("ModelObjFileChooseDialog"))
    {
        // action if OK 点击OK
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            //获取的路径和文件名称
            auto file_map = ImGuiFileDialog::Instance()->GetSelection();//返回一个map<string, string> key是文件名，value是路径
            for(auto it = file_map.begin(); it != file_map.end(); it++)
            {
                // action
                cout << "You choose model file:" << it->first << endl;
                cout << "Your choosed file’s path is " << it->second << endl;
                Model model(it->second);
                //将model添加到场景中
                Scene::add_model(it->second, model);
            }
            //关闭窗口
            ImGuiFileDialog::Instance()->Close();
            CoolenderUI::show_model_obj_file_choose_dialog = false;
        }
        // close
        ImGuiFileDialog::Instance()->Close();
        CoolenderUI::show_model_obj_file_choose_dialog = false;
    }       
}

//截图保存路径选择对话框
void CoolenderUI::render_screenshot_save_dir_choose_dialog()
{
    //设置大小和位置
    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos
    (
        ImVec2(main_viewport->WorkPos.x + 30, main_viewport->WorkPos.y + 50), 
        ImGuiCond_FirstUseEver
    );
    ImGui::SetNextWindowSize(ImVec2(400, 600), ImGuiCond_FirstUseEver);
    ImGuiFileDialog::Instance()->OpenDialog("ScreenshotSaveDirChooseDialog", "Choose Directory", nullptr, ".", 0);
    
    // display
    if (ImGuiFileDialog::Instance()->Display("ScreenshotSaveDirChooseDialog"))
    {
        // action if OK 点击OK
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            Function::screenshot_out_path = ImGuiFileDialog::Instance()->GetCurrentPath();
            //关闭窗口
            ImGuiFileDialog::Instance()->Close();
            CoolenderUI::show_screenshot_save_dir_choose_dialog = false;
        }
        // close
        ImGuiFileDialog::Instance()->Close();
        CoolenderUI::show_screenshot_save_dir_choose_dialog = false;
    }        
}

//warning 提示
void CoolenderUI::warning_marker(const char* desc)
{
    ImGui::TextDisabled("(!!!)");
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

//cleanup
void CoolenderUI::destroy()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}