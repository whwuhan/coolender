#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <cld_camera.h>
#include <cld_coolender.h>
#include <cld_coolender_ui.h>
#include <cld_shader.h>
#include <cld_texture_loader.h>
#include <cld_plane.h>
#include <cld_render.h>
#include <cld_function.h>
#include <cld_model.h>
#include <cld_shadow_mapping.h>
#include <stb_image.h>
#include <stb_image_write.h>

namespace coolender
{
    class Window
    {
    public :
        // Window();//默认构造函数
        static GLFWwindow *glfwWindow;//glfw window
        static bool cursorDisable;//是否进入光标不可显示模式
        static bool changeOperateModeKeyPressed;//更换操作模式按键是否被按下
        static bool mouseButtonRightFirstRlease;//鼠标右键是否第一次松开
        static bool mouseButtonRightFirstPressed;//鼠标右键是否第一次按下
        static double cursorPosX;//鼠标位置X
        static double cursorPosY;//鼠标位置Y
        static unsigned int width;//window 宽
        static unsigned int height;//window 高
        static Camera camera;//相机
        static float cameraSpeedScale;//相机移速比例
        static bool useMSAA;//是否使用MSAA抗锯齿
        static int MSAALevel;//抗锯齿级别
        //功能
        static bool screenShot;
        //timing
        static float deltaTime;
        static float lastFrame;
        //防止模式切换镜头闪烁
        // static float lastX;
        // static float lastY;
        static bool firstMouse;//第一次聚焦于窗口

        static void initAndRun();//初始化glfw glad并运行窗口(包含渲染循环)
    };
    //回调函数声明，更改窗口大小的时候，更改视口大小
    void framebufferSizeCallback(GLFWwindow* glfwWindow, int width, int height);
    //键盘操作
    void processInput(GLFWwindow *glfwWindow);
    void changeOperateMode(GLFWwindow *glfwWindow);//修改操作模式
    //鼠标滚轮操作
    void scrollCallback(GLFWwindow *glfwWindow, double xoffset, double yoffset);
    //鼠标点击回调函数
    void mouseButtonCallBack(GLFWwindow* glfwWindow, int button, int action, int mods);
    //鼠标移动
    void moveModeMouseCallback(GLFWwindow* glfwWindow, double xpos, double ypos);//移动模式下的鼠标移动回调函数 类似FPS游戏
    void cursorModeMouseCallback(GLFWwindow* glfwWindow, double xpos, double ypos);//鼠标模式下的鼠标移动回调函数 类似WOW
    //获取鼠标位置
    void getCursorPos(GLFWwindow* glfwWindow, double xpos, double ypos);
}


