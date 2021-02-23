#pragma once 
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <ImGuiFileDialog.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <math.h>
#include <cld_window.h>
#include <cld_scene.h>
#include <whlib.h>

namespace coolender
{
    class CoolenderUI
    {
    public:
       
        static  GLFWwindow* glfwWindow;//glfw window

        
        static void init(GLFWwindow* glfwWindow);//初始化，在渲染循环外
        static void renderDemoUI();//渲染imgui demo
        static void render();//渲染所有的UI
        static void destroy();//清空数据
        

    private:
        static float fontSize;//字体大小
        static float globalScale;//整体的字体缩放
        static float windowRounding;//窗口的圆角
        static float frameRounding;//内部图标的圆角

        static bool showFileChooseDialog;//文件选择对话框
        static bool showUsage;//显示操作手册
        static bool showRightSideBar;//显示右边Sidebar
        static bool showMessageBox;//信息窗口
        static int style;//UI风格
        
        static float usagePosX;//usage位置的X坐标
        static float usagePosY;//usage位置的Y坐标
        static float rightSidebarPosX;//右侧边栏位置的X坐标
        static float rightSidebarPosY;//右侧边栏位置的Y坐标
        static float rightSidebarWidth;//右侧边栏位置的X坐标
        static float rightSidebarHeight;//右侧边栏位置的Y坐标
        static float messageBoxPosX;//message box位置X坐标
        static float messageBoxPosY;//message box位置Y坐标
        // static float messageBoxWidth;
        // static float messageBoxHeight;

        // static int globalSettingOpenAction;//初始是否打开global setting界面
        // static int sceneSettingOpenAction;//初始是否打开scene setting界面
        //一级UI
        static void renderMenu();//顶部菜单栏
        static void renderUsage();//使用手册
        static void renderRightSideBar();//右边的Side Bar
        static void renderMessageBox();//信息框

        //隐藏UI
        static void renderFileChooseDialog();//渲染文件选择对话框
    };
}