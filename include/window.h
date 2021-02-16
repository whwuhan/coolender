#pragma once
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
namespace Coolender
{
    class Window
    {
    public :
        Window();//默认构造函数
        Window(unsigned int winWidth, unsigned int winHeight);//设置宽高
        
        void initAndRun();//初始化glfw glad并运行窗口(包含渲染循环)
    private:
        unsigned int winWidth;//window 宽
        unsigned int winHeight;//window 高
    };

    //回调函数声明，更改窗口大小的时候，更改视口大小
    void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    // 声明输入函数，判断是否按下键盘
    void processInput(GLFWwindow *window);
}


