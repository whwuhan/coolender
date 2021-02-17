#pragma once 
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
namespace coolender
{
    class CoolenderUI
    {
    public:
        CoolenderUI();
        void init(GLFWwindow* window);//初始化，在渲染循环外
        void renderDemoUI();//根据scence，渲染UI
        void render();
        void terminate();//清空数据
    };
}