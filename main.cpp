/**
 * 初始化窗口
*/
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <window.h>

int main()
{
    Coolender::Window coolender;
    coolender.initAndRun();
}