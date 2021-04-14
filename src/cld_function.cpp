#include <cld_function.h>
using namespace std;
using namespace coolender;
string Function::screenshot_out_path("./screenshot");//截图存放路径

//当前画面截图
void Function::screenshot(string file_name){
    //y轴翻转
    stbi_flip_vertically_on_write(true);
    int width, height;
    glfwGetFramebufferSize(Window::glfw_window, &width, &height);
    //分配截图数据空间
    GLchar data[width * height * 3];
    //获取当前帧的数据
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
    string finalPath = Function::screenshot_out_path + "/" + file_name;
    stbi_write_png(finalPath.c_str(), width, height, 3, data, 0);
    //stbi_image_free(data);//释放资源
    cout << "Screenshot successfully! Save path:"<< finalPath << endl;
    Window::screenshot = false;//设置当前帧不再截图
}

//获取当前时间
string Function::get_cur_time(){
    time_t now = time(0);			//获取当前时间 1970到现在的秒数
	tm *loc_time = localtime(&now);	//转化成当地时间

    //格式化时间字符串
    string cur_mon = to_string(1 + loc_time->tm_mon);//月份
    string cur_day = to_string(loc_time->tm_mday);//日
    string cur_hour = to_string(loc_time->tm_hour);//时
    string cur_min = to_string(loc_time->tm_min);//分
    string cur_sec = to_string(loc_time->tm_sec);//秒
    if(1 + loc_time->tm_mon < 10) cur_mon = "0" + cur_mon;
    if(loc_time->tm_mday < 10) cur_day = "0" + cur_day;
    if(loc_time->tm_hour < 10) cur_hour = "0" + cur_hour;
    if(loc_time->tm_min < 10) cur_min = "0" + cur_min;
    // if(loc_time->tm_sec < 10) cur_sec = "0" + cur_sec;


    return to_string(1900 + loc_time->tm_year) + cur_mon + cur_day + "_" +cur_hour + cur_min;
}