#pragma once 
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <ImGuiFileDialog.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
namespace coolender
{
    class CoolenderUI
    {
    public:
        CoolenderUI();
        CoolenderUI(GLFWwindow* window);//带glfw window的构造函数
        GLFWwindow* window;//glfw window
        void init();//初始化，在渲染循环外
        void renderDemoUI();//根据scence，渲染UI
        void render();//渲染所有的UI
        void terminate();//清空数据

        static bool showFileChooseDialog;//文件选择对话框
        static bool showUsage;//显示操作手册
        static bool showRightSideBar;//显示右边Sidebar
        

    private:
        
        static float usagePosX;//usage位置的X坐标
        static float usagePosY;//usage位置的Y坐标

        static float rightSidebarPosX;//右侧边栏位置的X坐标
        static float rightSidebarPosY;//右侧边栏位置的Y坐标
        
        float fontSize;//字体大小
        float globalScale;//整体的字体缩放
        float windowRounding;//窗口的圆角
        float frameRounding;//内部图标的圆角

        
        //一级UI
        void renderMenu();//顶部菜单栏
        void renderUsage();//使用手册
        void renderRightSideBar();//右边的Side Bar
        

        //二级UI




        //隐藏UI
        void renderFileChooseDialog();//渲染文件选择对话框
        
    };
}