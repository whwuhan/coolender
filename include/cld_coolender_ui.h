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
        static  GLFWwindow* glfw_window;//glfw window
        static void init(GLFWwindow* glfw_window);//初始化，在渲染循环外
        static void render_demo_ui();//渲染imgui demo
        static void render();//渲染所有的UI
        static void destroy();//清空数据
        
    private:
        static float font_size;//字体大小
        static float global_scale;//整体的字体缩放
        static float window_rounding;//窗口的圆角
        static float frame_rounding;//内部图标的圆角

        static bool show_point_cloud_obj_file_choose_dialog;//obj点云文件选择框
        static bool show_polygon_mesh_obj_file_choose_dialog;
        static bool show_model_obj_file_choose_dialog;//obj model模型文件选择框
        static bool show_screenshot_save_dir_choose_dialog;//截图保存路径选择选择框
        static bool show_usage;//显示操作手册
        static bool show_right_sidebar;//显示右边Sidebar
        static bool show_message_box;//信息窗口
        static int style;//UI风格
        
        static float usage_pos_x;//usage位置的X坐标
        static float usage_pos_y;//usage位置的Y坐标
        static float right_sidebar_pos_x;//右侧边栏位置的X坐标
        static float right_sidebar_pos_y;//右侧边栏位置的Y坐标
        static float right_sidebar_width;//右侧边栏位置的X坐标
        static float right_sidebar_height;//右侧边栏位置的Y坐标
        static float message_box_pos_x;//message box位置X坐标
        static float message_box_pos_y;//message box位置Y坐标

        //一级UI
        static void render_menu();//顶部菜单栏
        static void render_usage();//使用手册
        static void render_right_sidebar();//右边的Side Bar
        static void render_message_box();//信息框

        //隐藏UI
        static void render_point_cloud_obj_file_choose_dialog();//渲染point cloud文件选择对话框
        static void render_polygon_mesh_obj_file_choose_dialog();//polygon mesh文件选择框
        static void render_model_obj_file_choose_dialog();//渲染文件选择对话框
        static void render_screenshot_save_dir_choose_dialog();//选择渲染截图保存文件夹对话框

        //其他UI
        static void warning_marker(const char* desc);//警告标志
    };// end CoolenderUI
}// end namespace coolender