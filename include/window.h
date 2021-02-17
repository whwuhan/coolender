#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <camera.h>
#include <coolender_ui.h>
#include <shader.h>
#include <texture_loader.h>
#include <plane.h>
#include <stb_image.h>
namespace coolender
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
    //键盘操作
    void processInput(GLFWwindow *window);
    //鼠标滚轮操作
    void scrollCallback(GLFWwindow *window, double xoffset, double yoffset);
    //鼠标移动
    void mouseCallback(GLFWwindow* window, double xpos, double ypos);
}


