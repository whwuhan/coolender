#include <coolender_ui.h>
using namespace coolender;
using namespace std;

//static 变量初始化
bool CoolenderUI::showUsage = true;
bool CoolenderUI::showRightSideBar = true;
bool CoolenderUI::showFileChooseDialog = false;

CoolenderUI::CoolenderUI():
globalScale(1.0),
fontSize(15.0)
{}

//初始化UI
void CoolenderUI::init(GLFWwindow* window)
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); 
    (void)io;
    this->io = &io;
    //io.FontGlobalScale = globalScale;//设置字体的缩放大小
    io.Fonts->AddFontFromFileTTF("fonts/DroidSans.ttf", fontSize);//设置字体
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
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

        //使用手册
        if(CoolenderUI::showUsage)
        {
            renderUsage();
        }
        //右侧Sidebar
        if(CoolenderUI::showRightSideBar)
        {
            renderRightSideBar();
        }
        
        //初始显示部分结束



        //界面隐藏部分
        //显示文件选择框
        if(CoolenderUI::showFileChooseDialog)
        {
            renderFileChooseDialog();
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
            if (ImGui::MenuItem("Usage", NULL, CoolenderUI::showUsage))
            {
                CoolenderUI::showUsage = true;
            }

            //右侧Sidebar
            if (ImGui::MenuItem("Show Right Sidebar", NULL, CoolenderUI::showRightSideBar))
            {
                CoolenderUI::showRightSideBar = true;
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
    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 30, main_viewport->WorkPos.y + 50), ImGuiCond_FirstUseEver);
    //ImGui::SetNextWindowSize(ImVec2(400, 200), ImGuiCond_FirstUseEver);
    
    //窗口内容
    ImGui::Begin("Usage", &CoolenderUI::showUsage, ImGuiWindowFlags_AlwaysAutoResize);
    {
        ImGui::Text("Please press Q to change operate mode!");
        ImGui::Separator();
        ImGui::Text("In cursor operate mode:");
        ImGui::Text("You can use cursor to select what you want.");
        ImGui::Separator();
        ImGui::Text("In movement operate mode:");
        ImGui::Text("Press WASD and SPACE key to move your view position.");
        ImGui::Text("Move your mouse to change view angle.");
        ImGui::Text("Scroll the mouse wheel to change the field of view.");
    }

    ImGui::End();
}

//渲染右侧Sidebar
void CoolenderUI::renderRightSideBar()
{
    ImGui::Begin("Coolender", &CoolenderUI::showRightSideBar);
    ImGui::Text("PROGRAMMER GUIDE:");
    ImGui::End();
}

//渲染文件选择框
void CoolenderUI::renderFileChooseDialog()
{
    ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDialog", "Choose File", " ,.cpp,.h,.hpp", "");
    // display
    if (ImGuiFileDialog::Instance()->Display("ChooseFileDialog")) 
    {
        // action if OK
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
            string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
            // action
            cout << "You choose file:" << filePathName << endl;
            cout << "Your choosed file’s path is " << filePath << endl;
            ImGuiFileDialog::Instance()->Close();
            CoolenderUI::showFileChooseDialog = false;
        }
        // close
        ImGuiFileDialog::Instance()->Close();
        CoolenderUI::showFileChooseDialog = false;
    }        
}