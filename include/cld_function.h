#pragma once
/**
 *封装功能函数 
*/
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cld_window.h>
#include <stb_image_write.h>
#include <glad/glad.h>
#include <string>
#include <ctime>
namespace coolender
{
    class Function
    {
    public:
        static std::string screenShotOutPath;//截图保存文件夹位置





        /**
         * 截图
         * 参数：
         * fileName：截图文件名称 最终路径为 Function::screenShotOutPath + fileName
         * data：保存数据
         * width：图像宽度
         * height：图像高度
        */
        static void screenShot(std::string fileName);

        //获取当前时间
        static std::string getCurTime();
    };
}