#pragma once 
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <ImGuiFileDialog.h>
#include <iostream>
namespace coolender
{
    class CoolenderUI
    {
    public:
        CoolenderUI();
        void init(GLFWwindow* window);//初始化，在渲染循环外
        void renderDemoUI();//根据scence，渲染UI
        void render();//渲染所有的UI
        void terminate();//清空数据

        static bool showFileChooseDialog;//文件选择对话框
        static bool showUsage;//显示操作手册
        static bool showRightSideBar;//显示右边Sidebar
        

    private:
        ImGuiIO* io;//ImGui io
        float fontSize;//字体大小
        float globalScale;//整体的字体缩放
        //一级UI
        void renderMenu();//顶部菜单栏
        void renderUsage();//使用手册
        void renderRightSideBar();//右边的Side Bar
        


        //二级UI




        //隐藏UI
        void renderFileChooseDialog();//渲染文件选择对话框
        
    };
}