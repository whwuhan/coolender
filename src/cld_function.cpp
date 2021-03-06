#include <cld_function.h>
using namespace std;
using namespace coolender;
string Function::screenShotOutPath("screenshot");//截图存放路径

//当前画面截图
void Function::screenShot(string fileName)
{
    //y轴翻转
    stbi_flip_vertically_on_write(true);
    //分配截图数据空间
    GLchar data[Window::width * Window::height * 3];
    //获取当前帧的数据
    glReadPixels(0, 0, Window::width, Window::height, GL_RGB, GL_UNSIGNED_BYTE, data);
    string finalPath = Function::screenShotOutPath + "/" + fileName;
    stbi_write_png(finalPath.c_str(), Window::width, Window::height, 3, data, 0);
    //stbi_image_free(data);//释放资源
    Window::screenShot = false;//设置点前帧不再截图
}

//获取当前时间
string Function::getCurTime()
{
    time_t now = time(0);			//获取当前时间 1970到现在的秒数
	tm *loc_time = localtime(&now);	//转化成当地时间

    //格式化时间字符串
    string curMonth = to_string(1 + loc_time->tm_mon);//月份
    string curDay = to_string(loc_time->tm_mday);//日
    string curHour = to_string(loc_time->tm_hour);//时
    string curMin = to_string(loc_time->tm_min);//分
    string curSec = to_string(loc_time->tm_sec);
    if(1 + loc_time->tm_mon < 10)
    {
        curMonth = "0" + curMonth;
    }
    if(loc_time->tm_mday < 10)
    {
        curDay = "0" + curDay;
    }
    if(loc_time->tm_hour < 10)
    {
        curHour = "0" + curHour;
    }
    if(loc_time->tm_min < 10)
    {
        curMin = "0" + curMin;
    }
    if(loc_time->tm_hour < 10)
    {
        curSec = "0" + curSec;
    }

    return to_string(1900 + loc_time->tm_year) + curMonth + curDay + "_" +curHour + curMin + curSec;
}