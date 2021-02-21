#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <camera.h>
#include <coolender.h>
#include <coolender_ui.h>
#include <shader.h>
#include <texture_loader.h>
#include <plane.h>
#include <render.h>
#include <stb_image.h>
namespace coolender
{
    class Window
    {
    public :
        Window();//默认构造函数
        void initAndRun();//初始化glfw glad并运行窗口(包含渲染循环)
        static bool cursorDisable;//是否进入光标不可显示模式
        static bool changeOperateModeKeyPressed;//更换操作模式按键是否被按下
        static double cursorPosX;//鼠标位置X
        static double cursorPosY;//鼠标位置Y


        static unsigned int winWidth;//window 宽
        static unsigned int winHeight;//window 高
        static Camera camera;//相机
        static float cameraSpeedScale;//相机移速比例
        static bool useMSAA;//是否使用MSAA抗锯齿
        static int MSAALevel;//抗锯齿级别
        
        //timing
        static float deltaTime;
        static float lastFrame;
        //防止模式切换镜头闪烁
        // static float lastX;
        // static float lastY;
        static bool firstMouse;//第一次聚焦于窗口

    private:
        GLFWwindow *window;
    };
    //回调函数声明，更改窗口大小的时候，更改视口大小
    void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    //键盘操作
    void processInput(GLFWwindow *window, Window *coolenderWindow);
    void changeOperateMode(GLFWwindow *window, Window *coolenderWindow);//修改操作模式
    //鼠标滚轮操作
    void scrollCallback(GLFWwindow *window, double xoffset, double yoffset);
    //鼠标移动
    void mouseCallback(GLFWwindow* window, double xpos, double ypos);
    //获取鼠标位置
    void getCursorPos(GLFWwindow* window, double xpos, double ypos);
}


