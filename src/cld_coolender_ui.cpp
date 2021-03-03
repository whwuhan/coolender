#include <cld_coolender_ui.h>
using namespace coolender;
using namespace std;
using namespace wh::basic;
using namespace wh::utils::io;
//static 变量初始化
GLFWwindow* CoolenderUI::glfwWindow = nullptr;
//整体设置
float CoolenderUI::fontSize = 15.0;//字体大小
float CoolenderUI::globalScale = 1.0;//整体的字体缩放
float CoolenderUI::windowRounding = 6.0;//窗口的圆角
float CoolenderUI::frameRounding = 3.0;//内部图标的圆角

bool CoolenderUI::showRightSideBar = true;
bool CoolenderUI::showUsage = true;
bool CoolenderUI::showMessageBox = true;
bool CoolenderUI::showFileChooseDialog = false;
int CoolenderUI::style = 0;

float CoolenderUI::usagePosX = 3;//usage位置的X坐标
float CoolenderUI::usagePosY = 22;//usage位置的Y坐标
float CoolenderUI::rightSidebarPosX = 3;//右侧边栏位置的X坐标(距离右侧的距离) 
float CoolenderUI::rightSidebarPosY = 22;//右侧边栏位置的Y坐标
float CoolenderUI::rightSidebarWidth = 500;//右侧边栏宽
float CoolenderUI::rightSidebarHeight = 650;//右侧边栏高
float CoolenderUI::messageBoxPosX = 3;//message box距离左边距离
float CoolenderUI::messageBoxPosY = 300;//message box距离usage的纵向距离
// float CoolenderUI::messageBoxWidth = 200;//宽
// float CoolenderUI::messageBoxHeight = 200;//高

// int CoolenderUI::globalSettingOpenAction = 1;//初始是否打开global setting界面
// int CoolenderUI::sceneSettingOpenAction = 1;//初始是否打开scene setting界面

// CoolenderUI::CoolenderUI():
// window(nullptr),
// globalScale(1.0),
// fontSize(15.0),
// windowRounding(6.0),
// frameRounding(3.0)
// {}

// CoolenderUI::CoolenderUI(GLFWwindow* window):
// window(window),
// globalScale(1.0),
// fontSize(15.0),
// windowRounding(6.0),
// frameRounding(3.0)
// {}


//初始化UI
void CoolenderUI::init(GLFWwindow* glfwWindow)
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    //io
    ImGuiIO& io = ImGui::GetIO(); 
    (void)io;
    io.FontGlobalScale = globalScale;//设置字体的缩放大小
    io.Fonts->AddFontFromFileTTF("fonts/DroidSans.ttf", fontSize);//设置字体
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls


    // Setup Dear ImGui style
    ImGuiStyle& style = ImGui::GetStyle();
    style.FrameRounding = frameRounding; //设置frame的圆角
    style.WindowRounding = windowRounding;//设置window的圆角
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

//渲染DemoUI
void CoolenderUI::renderDemoUI()
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
        renderMenu();//顶部菜单栏


        // We specify a default position/size in case there's no data in the .ini file.
        // We only do it to make the demo applications a little more welcoming, but typically this isn't required.
        // const ImGuiViewport* mainViewport = ImGui::GetMainViewport();
        // ImGui::SetNextWindowPos(ImVec2(mainViewport->WorkPos.x + 650, mainViewport->WorkPos.y + 20), ImGuiCond_FirstUseEver);
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
        //使用手册
        if(CoolenderUI::showUsage)
        {
            CoolenderUI::renderUsage();
        }
        //右侧Sidebar
        if(CoolenderUI::showRightSideBar)
        {
            CoolenderUI::renderRightSideBar();
        }
        //messagebox
        if(CoolenderUI::showMessageBox)
        {
            CoolenderUI::renderMessageBox();
        }
        //初始显示部分结束



        //界面隐藏部分
        //显示文件选择框
        if(CoolenderUI::showFileChooseDialog)
        {
            CoolenderUI::renderFileChooseDialog();
        }
        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

//渲染顶部菜单栏
void CoolenderUI::renderMenu()
{
    //顶部菜单栏
    if (ImGui::BeginMainMenuBar())
    {   
        //File
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("open", "CTRL+O"))
            {
                CoolenderUI::showFileChooseDialog = true;
            }
            ImGui::EndMenu();
        }
        
        //Edit
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", "CTRL+Z"))
            {
                
            }
            if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "CTRL+X")) {}
            if (ImGui::MenuItem("Copy", "CTRL+C")) {}
            if (ImGui::MenuItem("Paste", "CTRL+V")) {}
            ImGui::EndMenu();
        }

        //Window 控制显示哪些窗口
        if (ImGui::BeginMenu("Window"))
        {
            //使用手册
            if (ImGui::MenuItem("Show Usage", NULL, CoolenderUI::showUsage))
            {
                CoolenderUI::showUsage = !CoolenderUI::showUsage;
            }

            //message box
            if (ImGui::MenuItem("Show Message Box", NULL, CoolenderUI::showMessageBox))
            {
                CoolenderUI::showMessageBox = !CoolenderUI::showMessageBox;
            }

            //右侧Sidebar
            if (ImGui::MenuItem("Show Right Sidebar", NULL, CoolenderUI::showRightSideBar))
            {
                CoolenderUI::showRightSideBar = !CoolenderUI::showRightSideBar;
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

//渲染使用手册窗口
void CoolenderUI::renderUsage()
{   
    //设置大小和位置
    const ImGuiViewport* mainViewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos
    (
        ImVec2(mainViewport->WorkPos.x + CoolenderUI::usagePosX, mainViewport->WorkPos.y + CoolenderUI::usagePosY), 
        ImGuiCond_FirstUseEver
    );
    //ImGui::SetNextWindowSize(ImVec2(400, 200), ImGuiCond_FirstUseEver);
    
    //窗口内容
    ImGui::Begin("Usage", &CoolenderUI::showUsage, ImGuiWindowFlags_AlwaysAutoResize);
    {
        ImGui::Text("How to switch mode:");
        ImGui::BulletText("Please press Q to change operate mode!");
        ImGui::Separator();
        ImGui::Text("In cursor operate mode:");
        ImGui::BulletText("You can use cursor to select what you want.");
        ImGui::Separator();
        ImGui::Text("In movement operate mode:");
        ImGui::BulletText("Press WASD and SPACE key to move your view position.");
        ImGui::BulletText("Move your mouse to change view angle.");
        ImGui::BulletText("Scroll the mouse wheel to change the field of view.");
    }
    ImGui::End();
}

//渲染右侧Sidebar
void CoolenderUI::renderRightSideBar()
{
    //获取glfw window宽高
    int winWidth, winHeight;
    glfwGetFramebufferSize(Window::glfwWindow, &winWidth, &winHeight);
    const ImGuiViewport* mainViewport = ImGui::GetMainViewport();
    //设置位置
    ImGui::SetNextWindowPos
    (
        ImVec2
        (   // 注意FramebufferSize是窗口实际长度的2倍
            mainViewport->WorkPos.x + winWidth / 2.0 - CoolenderUI::rightSidebarWidth - CoolenderUI::rightSidebarPosX, 
            mainViewport->WorkPos.y + CoolenderUI::rightSidebarPosY
        ), 
        ImGuiCond_FirstUseEver
    );
    //设置大小
    ImGui::SetNextWindowSize
    (
        ImVec2(CoolenderUI::rightSidebarWidth, CoolenderUI::rightSidebarHeight), 
        ImGuiCond_FirstUseEver
    );
    //右侧Sidebar开始
    ImGui::Begin("Coolender", &CoolenderUI::showRightSideBar, ImGuiWindowFlags_None);
    {
        //全局设置
        ImGui::SetNextItemOpen(true, ImGuiCond_Once);//设置下一个窗口打开（只设置一次）
        if(ImGui::CollapsingHeader("Global Setting"))
        {   
            //UI风格设置
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
            //相机速度
            ImGui::SliderFloat("Camera speed", &Window::cameraSpeedScale, 0.0f, 5.0f, "Speed scale = %.3f");
            ImGui::Separator();

            //点云绘制类型
            int pointType = Scene::pointType;//enum强制转换为int
            ImGui::Text("Point cloud point type:");
            ImGui::RadioButton("Point", &pointType, 0); ImGui::SameLine();
            ImGui::RadioButton("Sphere", &pointType, 1);
            Scene::pointType = POINT_TYPE(pointType);//int强制转化为enum
            ImGui::Separator();
            //MSAA
            // ImGui::Checkbox("MSAA", &Window::useMSAA);
            // if(Window::useMSAA)
            // {
            //     ImGui::RadioButton("MSAA x0", &Window::MSAALevel, 0); ImGui::SameLine();
            //     ImGui::RadioButton("MSAA x8", &Window::MSAALevel, 8); ImGui::SameLine();
            //     ImGui::RadioButton("MSAA x16", &Window::MSAALevel, 16); ImGui::SameLine();
            //     ImGui::RadioButton("MSAA x32", &Window::MSAALevel, 32);
            // }

        }

        //场景设置
        ImGui::SetNextItemOpen(true, ImGuiCond_Once);//设置下一个窗口打开（只设置一次）
        if(ImGui::CollapsingHeader("Scene Setting"))
        {   
            //背景颜色调整框
            float clearColor[4] = 
            {
                Scene::clearColor.x,
                Scene::clearColor.y,
                Scene::clearColor.z,
                Scene::clearColor.w
            };
            ImGui::ColorEdit3("Background color", clearColor);
            Scene::clearColor.x = clearColor[0];
            Scene::clearColor.y = clearColor[1];
            Scene::clearColor.z = clearColor[2];
            Scene::clearColor.w = 1.0f;
            

            //地板设置
            ImGui::TableNextColumn();
            ImGui::Checkbox("Show floor", &Scene::showFloor);
            ImGui::Separator();

            //根据场景中数据渲染UI
            ImGui::SetNextItemOpen(true, ImGuiCond_Once);//设置下一个窗口打开（只设置一次）
            if (ImGui::TreeNode("Point Cloud:"))
            {
                //每一个点云
                for(auto it = Scene::pointCloudCollection.begin(); it != Scene::pointCloudCollection.end(); it++)
                {   
                    ImGui::SetNextItemOpen(true, ImGuiCond_Once);//设置下一个窗口打开（只设置一次）
                    if (ImGui::TreeNode(it->first.c_str()))
                    {
                        //checkbox
                        ImGui::Checkbox("Show point cloud", &it->second.show);
                        
                        //pointSize
                        ImGui::DragFloat("Point size", &it->second.pointSize, 0.005f, 0.0f, 50.0f, "Point size: s%.3f");
                        //ImGui::SliderFloat("Point size", &it->second.pointSize, 0.0f, 10.f, "Point size = %.3f");
                        
                        //color
                        float pointColor[4] = 
                        {
                            it->second.color.x,
                            it->second.color.y,
                            it->second.color.z,
                            it->second.color.w,
                        };
                        ImGui::ColorEdit4("Point color", pointColor);
                        it->second.color.x = pointColor[0];
                        it->second.color.y = pointColor[1];
                        it->second.color.z = pointColor[2];
                        it->second.color.w = pointColor[3];
                        
                        //注意glm::mat4是按照列优选的顺序来的

                        //缩放
                        ImGui::SliderFloat("Scale", &it->second.scale, 0.0f, 10.0f, "Scale = %.3f");
                        it->second.model =
                            glm::scale(glm::mat4(1.0f), glm::vec3(it->second.scale));

                        //平移 
                        ImGui::SetNextItemWidth(80);
                        ImGui::DragFloat("transX", &it->second.transX, 0.01f);
                        ImGui::SameLine();
                        ImGui::SetNextItemWidth(80);
                        ImGui::DragFloat("transY", &it->second.transY, 0.01f);
                        ImGui::SameLine();
                        ImGui::SetNextItemWidth(80);
                        ImGui::DragFloat("transZ", &it->second.transZ, 0.01f);
                        it->second.model =
                            glm::translate(
                                it->second.model,
                                glm::vec3(it->second.transX, it->second.transY, it->second.transZ));
                        
                        //旋转
                        ImGui::SetNextItemWidth(80);
                        ImGui::DragFloat("rotateX", &it->second.rotateX, 0.1f);
                        ImGui::SameLine();
                        ImGui::SetNextItemWidth(80);
                        ImGui::DragFloat("rotateY", &it->second.rotateY, 0.1f);
                        ImGui::SameLine();
                        ImGui::SetNextItemWidth(80);
                        ImGui::DragFloat("rotateZ", &it->second.rotateZ, 0.1f);
                        it->second.model =  
                            glm::rotate(
                                it->second.model,
                                glm::radians(it->second.rotateX), 
                                glm::vec3(1.0f, 0.0f, 0.0f));
                        it->second.model= 
                            glm::rotate(
                                it->second.model,
                                glm::radians(it->second.rotateY), 
                                glm::vec3(0.0f, 1.0f, 0.0f));
                        it->second.model= 
                            glm::rotate(
                                it->second.model,
                                glm::radians(it->second.rotateZ), 
                                glm::vec3(0.0f, 0.0f, 1.0f));



                        
                        //delete button 
                        ImVec2 buttonSize(ImGui::GetFontSize() * 6.0f, 0.0f);
                        if(ImGui::Button("Delete", buttonSize))
                        {
                            Scene::deletePointCloud(it->first);
                            //注意这里删除后要break否则会出现内存错误
                            //猜测是因为map删除元素后，迭代器失效！！！！
                            ImGui::TreePop();
                            ImGui::Separator();
                            break;
                        }
                        ImGui::TreePop();
                    }
                }
                ImGui::TreePop();
            }
            ImGui::Separator();
        }
    }
    ImGui::End();
}

//message信息框
void CoolenderUI::renderMessageBox()
{   
    const ImGuiViewport* mainViewport = ImGui::GetMainViewport();
    //获取glfw window宽高
    int winWidth, winHeight;
    glfwGetFramebufferSize(Window::glfwWindow, &winWidth, &winHeight);
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
        (   // 注意FramebufferSize是窗口实际长度的2倍
            mainViewport->WorkPos.x + CoolenderUI::messageBoxPosX, 
            mainViewport->WorkPos.y + CoolenderUI::messageBoxPosY
        ), 
        ImGuiCond_FirstUseEver
    );

    //Message box
    ImGui::Begin("Message Box", &CoolenderUI::showMessageBox, ImGuiWindowFlags_AlwaysAutoResize);
    {   
        //简介
        ImGui::Text("Brief Introduction:");
        ImGui::BulletText("This is a simple scene renderer for \npoint cloud, polygonmesh and model.");
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

//渲染文件选择框
void CoolenderUI::renderFileChooseDialog()
{
    //设置大小和位置
    const ImGuiViewport* mainViewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(ImVec2(mainViewport->WorkPos.x + 30, mainViewport->WorkPos.y + 50), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(400, 600), ImGuiCond_FirstUseEver);
    ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDialog", "Choose File", ".obj", "");
    
    // display
    if (ImGuiFileDialog::Instance()->Display("ChooseFileDialog")) 
    {
        // action if OK 点击OK
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            //获取的路径和文件名称
            string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
            string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
            // action
            cout << "You choose file:" << filePathName << endl;
            cout << "Your choosed file’s path is " << filePath << endl;
            //读取点云数据
            PointCloud pointCloud;
            loadPointCloudObj(filePathName, &pointCloud);
            //将点云添加到场景中
            Scene::addPointCloud(filePathName, pointCloud);
            //传输数据给GPU
            Render::renderPointCloudTypePointInit(Scene::pointCloudCollection[filePathName]);
            Sphere sphere = Render::renderPointCloudTypeSphereInit(Scene::pointCloudCollection[filePathName]);//初始化球状点云，并返回对应的球面
            Scene::addSphere(filePathName, sphere);
            
            // switch(Scene::pointType)
            // {
            //     case POINT:
            //         //并做渲染初始化
            //         Render::renderPointCloudPointInit(Scene::pointCloudCollection[filePathName]);
            //         break;
            //     case SPHERE:
            //         Render::renderPointCloudSphereInit(Scene::pointCloudCollection[filePathName]);
            //         break;
            //     default:
            //         cerr << "Render Point Cloud Type Wrong!" << endl;
            //         exit(0);
            // }
            
            //关闭窗口
            ImGuiFileDialog::Instance()->Close();
            CoolenderUI::showFileChooseDialog = false;
        }
        // close
        ImGuiFileDialog::Instance()->Close();
        CoolenderUI::showFileChooseDialog = false;
    }        
}

//cleanup
void CoolenderUI::destroy()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}