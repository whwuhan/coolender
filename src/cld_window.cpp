#include <cld_window.h>
using namespace std;
using namespace coolender;
using namespace glm;
//static变量初始化
GLFWwindow *Window::glfwWindow = nullptr;          //glfw window
//窗口大小
unsigned int Window::width = 1600;
unsigned int Window::height = 900;
//相机相关
Camera Window::camera;                             //相机
float Window::cameraSpeedScale = 1.0f;             //相机移速比例
//渲染相关
bool Window::useMSAA = true;
int Window::MSAALevel = 8;                          //MSAA采样数量
//镜头操作模式
OPERATE_MODE Window::operateMode = WOW;
//timing
float Window::deltaTime = 0.0f;
float Window::lastFrame = 0.0f;
//防止模式切换镜头闪烁
bool Window::firstChangeToFPSMode = true;//第一次切换到FPS操作模式
bool Window::firstChangeToWOWMode = true;//第一次切换到WOW操作模式
bool Window::changeOperateModeKeyPressed = false;  //更换操作模式按键是否被按下
bool Window::mouseButtonRightFirstPressed = true;  //鼠标右键是否第一次被按下
bool Window::mouseButtonRightFirstRlease = true;   //鼠标右键是否是第一次被松开
double Window::cursorPosX = Window::width / 2.0f;  //鼠标位置X
double Window::cursorPosY = Window::height / 2.0f; //鼠标位置Y
//功能
bool Window::screenShot = false;

void Window::initAndRun()
{
    //======================glfw glad opengl 初始化======================
    glfwInit(); //初始化GLFW

    //通过glfwWindowHint()函数来设置参数，前面是参数名称，后面是值
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                 //设置主版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);                 //设置次版本
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //设置使用核心模式
    glfwWindowHint(GLFW_SAMPLES, Window::MSAALevel);               //MSAA采样数
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //mac用户需要设置，初始化才能有效
#endif
    //创建一个窗口对象
    string windowTitle = "Coolender Version " + Coolender::version;
    Window::glfwWindow = glfwCreateWindow(Window::width, Window::height, windowTitle.c_str(), NULL, NULL);

    //参数依次是长，宽，名称，后两个参数忽略
    if (Window::glfwWindow == nullptr)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return;
    }
    //将窗口的上下文设置成主线程的上下文
    glfwMakeContextCurrent(Window::glfwWindow);
    glfwSwapInterval(1); // Enable vsync 每帧的交换间隔，防止屏幕撕裂
    //注册回调函数，告诉GLFW窗口大小调整时，调用这个回调函数
    glfwSetFramebufferSizeCallback(Window::glfwWindow, framebufferSizeCallback);
    //鼠标滚轮监听
    glfwSetScrollCallback(Window::glfwWindow, scrollCallback);
    //鼠标点击回调函数
    glfwSetMouseButtonCallback(glfwWindow, mouseButtonCallBack);
    //鼠标移动回调函数 默认模式是WOW风格
    glfwSetCursorPosCallback(glfwWindow, nullptr);
    //告诉GLFW选中窗口不显示鼠标
    //glfwSetInputMode(Window::glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //GLAD是用来管理OpenGL的函数指针
    //初始化GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    //glfwGetProcAddress 根据编译的系统给出了正确的函数
    {
        cout << "Failed to initialize GLAD" << endl;
        return;
    }
    //openGL全局配置
    glEnable(GL_DEPTH_TEST);         //开启深度测试
    glEnable(GL_MULTISAMPLE);        // 开启MSAA通常都是默认开启的
    glEnable(GL_PROGRAM_POINT_SIZE); //开启改变点的大小（暂时无用）

    //glPointSize(25);
    //======================glfw glad opengl 初始化结束======================

    //CoolenderUI初始化
    CoolenderUI::init(Window::glfwWindow);

    //shader
    //地板
    Shader floorShader("shader/floor.vs.glsl", "shader/floor.fs.glsl");
    Plane floor;
    floor.init();
    floorShader.use();
    floorShader.setInt("floorTexture", 0);
    floorShader.setInt("shadowMap", 1);
    Scene::floor = floor;
    
    //point cloud shader
    Shader pointCloudTypePointShader("shader/point_cloud_type_point.vs.glsl", "shader/point_cloud_type_point.fs.glsl");//点状点云shader
    Shader pointCloudTypeShpereShader("shader/point_cloud_type_sphere.vs.glsl", "shader/point_cloud_type_sphere.fs.glsl");//绘制球状点云
    
    //polygon mesh shader
    Shader polygonMeshTypeLineShader("shader/polygon_mesh.vs.glsl", "shader/polygon_mesh_type_line.fs.glsl");
    Shader polygonMeshTypeFillShader("shader/polygon_mesh.vs.glsl", "shader/polygon_mesh_type_fill.fs.glsl");
    Shader polygonMeshTypeLineAndFillShader("shader/polygon_mesh.vs.glsl", "shader/polygon_mesh_type_line_and_fill.fs.glsl");
    Shader polygonMeshTypeLightShader("shader/polygon_mesh.vs.glsl", "shader/polygon_mesh_type_light.fs.glsl");
    
    //shadow mapping depth map shader
    Shader simpleDepthShader("shader/shadow_mapping_point_cloud_depth.vs.glsl", "shader/shadow_mapping_depth.fs.glsl");
    ShadowMapping shadowMapping;
    shadowMapping.init();

    //渲染循环
    // Main loop
    while (!glfwWindowShouldClose(Window::glfwWindow))
    {
        
        // per-frame time logic
        float currentFrame = glfwGetTime();
        Window::deltaTime = currentFrame - Window::lastFrame;
        Window::lastFrame = currentFrame;
        //初始设置

        //键盘鼠标事件监听
        processInput(Window::glfwWindow);

        //开始渲染场景
        //背景颜色
        glClearColor(
            Scene::clearColor.x,
            Scene::clearColor.y,
            Scene::clearColor.z,
            Scene::clearColor.w
        );
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //渲染shawdow mapping depth map
        shadowMapping.renderDepthMap(simpleDepthShader);
        
        //获取投影矩阵和相机矩阵
        mat4 projection = perspective(radians(camera.Zoom), (float)width / (float)height, 0.1f, 100.0f);
        mat4 view = camera.GetViewMatrix();

        //渲染地板
        if (Scene::showFloor)
        {
            floorShader.use();
            // vs uniform
            //暂时不需要model矩阵
            floorShader.setMat4("projection", projection);
            floorShader.setMat4("view", view);
            mat4 lightProjection, lightView;
            mat4 lightSpaceMatrix;
            // 正交投影矩阵  参数 左 右 下 上 远 近平面
            lightProjection = ortho(-5.0f, 5.0f, -5.0f, 5.0f, shadowMapping.nearPlane, shadowMapping.farPlane);
            // 从光照位置生成的观察矩阵
            lightView = lookAt(Scene::parallelLight.position, vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f,1.0f,0.0));
            lightSpaceMatrix = lightProjection * lightView; //可以将世界坐标系中的点转换到光照空间中
            floorShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);
            // fs uniform
            // set light uniforms
            floorShader.setVec3("viewPos", camera.Position);
            floorShader.setVec3("lightColor", vec3(Scene::parallelLight.color));
            floorShader.setVec3("lightPos", Scene::parallelLight.position);//光源位置
            floorShader.setVec3("lightLookAt", Scene::parallelLight.lookAt);

            floorShader.setFloat("ambientIntensity", Scene::ambientIntensity); //环境光强度
            
            floorShader.setBool("floorUseTex", Scene::floorUseTex);
            floorShader.setVec4("floorColor", Scene::floor.color);
            floorShader.setVec4("clearColor", Scene::clearColor);
            // floor
            glBindVertexArray(floor.VAO);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, floor.texture);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, shadowMapping.depthMap);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

        //==========================场景渲染==========================
        //渲染点云
        glEnable(GL_CULL_FACE); //开启面剔除，默认剔除背面
        //glCullFace(GL_FRONT);//设置剔除正面
        glFrontFace(GL_CW); //设置顺时针的面为正面
        switch (Scene::pointType)
        {
        //绘制成点
        case POINT:
            for (auto it = Scene::pointCloudCollection.begin(); it != Scene::pointCloudCollection.end(); it++)
            {
                //判断是否显示点云模型
                if (it->second.show)
                {
                    pointCloudTypePointShader.use();
                    //vs uniform                   
                    pointCloudTypePointShader.setMat4("projection", projection);
                    pointCloudTypePointShader.setMat4("view", view);
                    pointCloudTypePointShader.setMat4("model", it->second.model);
                    //fs uniform
                    pointCloudTypePointShader.setFloat("pointSize", it->second.pointSize);
                    pointCloudTypePointShader.setVec4("pointCloudColor", it->second.color);
                    //渲染点云
                    Render::renderPointCloudTypePoint(it->second);
                }
            }
            break;
        //将点绘制成球
        case SPHERE:
            for (auto it = Scene::pointCloudCollection.begin(); it != Scene::pointCloudCollection.end(); it++)
            {
                //判断是否显示球状点云
                if (it->second.show)
                {
                    pointCloudTypeShpereShader.use();
                    // vs uniform
                    pointCloudTypeShpereShader.setMat4("projection", projection);
                    pointCloudTypeShpereShader.setMat4("view", view);
                    pointCloudTypeShpereShader.setMat4("model", it->second.model);
                    // fs uniform
                    // set light uniforms
                    pointCloudTypeShpereShader.setVec3("pointCloudColor", vec3(it->second.color));
                    pointCloudTypeShpereShader.setVec3("viewPos", camera.Position);
                    pointCloudTypeShpereShader.setVec3("lightColor", vec3(Scene::parallelLight.color));//平行光颜色
                    pointCloudTypeShpereShader.setFloat("ambientIntensity", Scene::ambientIntensity);//平行光环境光强度
                    pointCloudTypeShpereShader.setVec3("lightPos", Scene::parallelLight.position);//光源位置
                    pointCloudTypeShpereShader.setVec3("lightLookAt", Scene::parallelLight.lookAt);//光源位置

                    // cout << glGetUniformLocation(pointCloudTypeShpereShader.ID, "parallelLightDir2") << endl;
                    //判断是否改变了球状点云的半径
                    if (it->second.changePointSize)
                    {
                        Scene::sphereCollection[it->first].setRadiusAndSegmentsByPointSize(it->second.pointSize);
                        Render::renderPointCloudTypeSphereInit(it->second, Scene::sphereCollection[it->first]); //重新初始化（因为球的大小变了，要更新VAO）
                    }
                    //渲染球状点云
                    Render::renderPointCloudTypeSphere(it->second, Scene::sphereCollection[it->first]);
                }
            }
            break;
        // 绘制成错误类型
        default:
            cerr << "Render Point Cloud Type Wrong!" << endl;
            exit(0);
        } 
        glDisable(GL_CULL_FACE); //关闭面剔除

        //渲染polygon mesh
        for(auto it = Scene::polygonMeshCollection.begin(); it != Scene::polygonMeshCollection.end(); it++)
        {
            if(it->second.show)
            {
                switch(Scene::polygonMeshType)
                {
                case LINE:
                    polygonMeshTypeLineShader.use();
                    polygonMeshTypeLineShader.setMat4("projection", projection);
                    polygonMeshTypeLineShader.setMat4("view", view);
                    polygonMeshTypeLineShader.setMat4("model" , it->second.model);
                    polygonMeshTypeLineShader.setFloat("pointSize", it->second.pointSize);
                    polygonMeshTypeLineShader.setVec4("pointAndLineColor", it->second.pointAndLineColor);
                    Render::renderPolygonMeshTypeLine(it->second);
                    break;
                case FILL:
                    polygonMeshTypeFillShader.use();
                    polygonMeshTypeFillShader.setMat4("projection", projection);
                    polygonMeshTypeFillShader.setMat4("view", view);
                    polygonMeshTypeFillShader.setMat4("model" , it->second.model);
                    polygonMeshTypeFillShader.setFloat("pointSize", it->second.pointSize);
                    polygonMeshTypeFillShader.setVec4("faceColor", it->second.faceColor);
                    Render::renderPolygonMeshTypeFILL(it->second);
                    break;
                case LINE_AND_FILL:
                    polygonMeshTypeLineAndFillShader.use();
                    polygonMeshTypeLineAndFillShader.setMat4("projection", projection);
                    polygonMeshTypeLineAndFillShader.setMat4("view", view);
                    polygonMeshTypeLineAndFillShader.setMat4("model" , it->second.model);
                    polygonMeshTypeLineAndFillShader.setFloat("pointSize", it->second.pointSize);
                    polygonMeshTypeLineAndFillShader.setVec4("pointAndLineColor", it->second.pointAndLineColor);
                    polygonMeshTypeLineAndFillShader.setVec4("faceColor", it->second.faceColor);
                    Render::renderPolygonMeshTypeLineAndFill(it->second, polygonMeshTypeLineAndFillShader);
                    break;
                case LIGHT:
                    polygonMeshTypeLightShader.use();
                    polygonMeshTypeLightShader.setMat4("projection", projection);
                    polygonMeshTypeLightShader.setMat4("view", view);
                    polygonMeshTypeLightShader.setMat4("model" , it->second.model);
                    polygonMeshTypeLightShader.setVec3("pointSize", vec3(it->second.pointSize));
                    polygonMeshTypeLightShader.setVec3("faceColor", vec3(it->second.faceColor));
                    polygonMeshTypeLightShader.setVec3("viewPos", camera.Position);
                    polygonMeshTypeLightShader.setVec3("lightColor", vec3(Scene::parallelLight.color));//平行光颜色
                    polygonMeshTypeLightShader.setVec3("lightPos", Scene::parallelLight.position);//光源位置
                    polygonMeshTypeLightShader.setVec3("lightLookAt", Scene::parallelLight.lookAt);//光源位置
                    polygonMeshTypeLightShader.setFloat("ambientIntensity", Scene::ambientIntensity);//平行光环境光强度
                    Render::renderPolygonMeshTypeLight(it->second);
                    break;
                default:
                    cerr << "Wrong polygon mesh render type!" << endl;
                    exit(0);
                }   
            }
        }//polygon mesh绘制结束
        





        //==========================场景渲染结束==========================

        //场景截图
        if(Window::screenShot)
        {
            string curTime = Function::getCurTime();
            Function::screenShot("cld_screenshot_" + curTime + "_" + to_string(glfwGetTime()) +".png");
        }
        
        //根据场景渲染UI
        //绘制UI 注意绘制UI要放在最后否则UI会被遮盖
        //CoolenderUI.renderDemoUI();
        CoolenderUI::render();
        
        //交换buffer
        glfwSwapBuffers(Window::glfwWindow);
        glfwPollEvents();
    }

    //UI cleanup
    CoolenderUI::destroy();

    //glfw cleanup
    glfwDestroyWindow(Window::glfwWindow);
    glfwTerminate();

    return;
}

//回调函数声明，更改窗口大小的时候，更改视口大小
void coolender::framebufferSizeCallback(GLFWwindow *glfwWindow, int width, int height)
{
    glViewport(0, 0, width, height);
}

// 声明输入函数，判断是否按下键盘
void coolender::processInput(GLFWwindow *glfwWindow)
{
    //退出
    if (glfwGetKey(glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(glfwWindow, true);
    }

    //按Q切换操作模式
    if (
        glfwGetKey(glfwWindow, GLFW_KEY_Q) == GLFW_PRESS && 
        !Window::changeOperateModeKeyPressed && 
        glfwGetMouseButton(glfwWindow, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE
    )
    {
        Window::changeOperateModeKeyPressed = true;
        changeOperateMode(Window::glfwWindow);
    }
    if (glfwGetKey(glfwWindow, GLFW_KEY_Q) == GLFW_RELEASE)
    {
        Window::changeOperateModeKeyPressed = false;
    }
    
    //截图快捷键
    if (glfwGetKey(glfwWindow, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS && glfwGetKey(glfwWindow, GLFW_KEY_P) == GLFW_PRESS)
    {
        Window::screenShot = true;
    }

    //键盘监听
    //相机移动
    //向前
    if (glfwGetKey(glfwWindow, GLFW_KEY_W) == GLFW_PRESS)
    {
        Window::camera.ProcessKeyboard(FORWARD, Window::deltaTime * Window::cameraSpeedScale);
    }
    //向后
    if (glfwGetKey(glfwWindow, GLFW_KEY_S) == GLFW_PRESS)
    {
        Window::camera.ProcessKeyboard(BACKWARD, Window::deltaTime * Window::cameraSpeedScale);
    }
    //向左
    if (glfwGetKey(glfwWindow, GLFW_KEY_A) == GLFW_PRESS)
    {
        Window::camera.ProcessKeyboard(LEFT, Window::deltaTime * Window::cameraSpeedScale);
    }
    //向右
    if (glfwGetKey(glfwWindow, GLFW_KEY_D) == GLFW_PRESS)
    {
        Window::camera.ProcessKeyboard(RIGHT, Window::deltaTime * Window::cameraSpeedScale);
    }
    //向上
    if (glfwGetKey(glfwWindow, GLFW_KEY_SPACE))
    {
        Window::camera.ProcessKeyboard(UPWARD, Window::deltaTime * Window::cameraSpeedScale);
    }
}

//修改操作模式
void coolender::changeOperateMode(GLFWwindow *glfwWindow)
{
    // Window::cursorDisable = !Window::cursorDisable;
    switch(Window::operateMode)
    {//注意设置的顺序
    case WOW:
        //切换为FPS风格
        Window::firstChangeToFPSMode = true;
        Window::operateMode = FPS;
        glfwSetMouseButtonCallback(glfwWindow, nullptr);                //禁用鼠标按键监听
        glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//隐藏鼠标
        glfwSetCursorPosCallback(glfwWindow, FPSModeMouseCallback);     //设置鼠标的移动模式为FPS mode
        
        break;
    case FPS:
        //切换为WOW风格
        Window::firstChangeToWOWMode = true;
        Window::operateMode = WOW;
        glfwSetMouseButtonCallback(glfwWindow, mouseButtonCallBack);    //启动鼠标按键监听
        glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);  //显示鼠标
        glfwSetCursorPosCallback(glfwWindow, WOWModeMouseCallback);     //设置鼠标的移动模式为WOW mode
        break;
    default:
        cerr << "Wrong operate mode!" << endl;
        exit(0);
    }
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void coolender::scrollCallback(GLFWwindow *winglfwWindowdow, double xoffset, double yoffset)
{
    Window::camera.ProcessMouseScroll(yoffset);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
//移动模式下的鼠标移动回调函数 类似FPS游戏
void coolender::FPSModeMouseCallback(GLFWwindow *glfwWindow, double xpos, double ypos)
{   
    //防止镜头抖动
    if (Window::firstChangeToFPSMode)
    {
        Window::cursorPosX = xpos;
        Window::cursorPosY = ypos;
        Window::firstChangeToFPSMode = false;
    }

    float xoffset = xpos - Window::cursorPosX;
    float yoffset = Window::cursorPosY - ypos; // reversed since y-coordinates go from bottom to top

    Window::cursorPosX = xpos;
    Window::cursorPosY = ypos;

    Window::camera.ProcessMouseMovement(xoffset, yoffset);
}

//鼠标点击回调函数
void coolender::mouseButtonCallBack(GLFWwindow* glfwWindow, int button, int action, int mods)
{
    //===============WOW操作风格下的鼠标按键监听===============
    //监听鼠标右键按下
    if (action == GLFW_PRESS && Window::operateMode == WOW)
    {
        switch(button)
        {
        case GLFW_MOUSE_BUTTON_RIGHT:
            if(Window::mouseButtonRightFirstPressed)
            {
                glfwSetCursorPosCallback(glfwWindow, nullptr);                  //先禁用鼠标移动监听
                Window::mouseButtonRightFirstPressed = false;
                Window::mouseButtonRightFirstRlease = true;
                Window::firstChangeToWOWMode = true;
                glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//隐藏鼠标
                glfwSetCursorPosCallback(glfwWindow, WOWModeMouseCallback);     //设置为WOW操作模式
            }
            break;
        }
    }
    //监听鼠标右键释放
    if(action == GLFW_RELEASE && Window::operateMode == WOW)
    {
        switch(button)
        {
        case GLFW_MOUSE_BUTTON_RIGHT:
            if(Window::mouseButtonRightFirstRlease)
            {
                glfwSetCursorPosCallback(glfwWindow, nullptr);                  //先禁用鼠标移动监听
                Window::mouseButtonRightFirstPressed = true;
                Window::mouseButtonRightFirstRlease = false;
                glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);//显示鼠标
                // Window::firstChangeToWOWMode = true;
            }
            // Window::mouseButtonRightFirstRlease = true;
            break;
        }
    }//WOW操作模式下的鼠标监听结束
}

//鼠标模式下的鼠标移动回调函数 类似WOW
void coolender::WOWModeMouseCallback(GLFWwindow* glfwWindow, double xpos, double ypos)
{
    if (glfwGetMouseButton(glfwWindow, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    { 
        //防止镜头抖动
        if (Window::firstChangeToWOWMode)
        {
            Window::cursorPosX = xpos;
            Window::cursorPosY = ypos;
            Window::firstChangeToWOWMode = false;
        }
        float xoffset = xpos - Window::cursorPosX;
        float yoffset = Window::cursorPosY - ypos; // reversed since y-coordinates go from bottom to top

        Window::cursorPosX = xpos;
        Window::cursorPosY = ypos;

        Window::camera.ProcessMouseMovement(xoffset, yoffset); 
    }
}

//获取当前指针的位置
void coolender::getCursorPos(GLFWwindow *glfwWindow, double xpos, double ypos)
{
    Window::cursorPosX = xpos;
    Window::cursorPosY = ypos;
}

// 渲染一个球体
unsigned int sphereVAO = 0;
unsigned int indexCount;
void renderSphere()
{
    if (0 == sphereVAO)
    {
        glGenVertexArrays(1, &sphereVAO);

        unsigned int vbo, ebo;
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        vector<glm::vec3> positions; // 球面上的点
        vector<glm::vec2> uv;        //球面上的uv坐标
        vector<glm::vec3> normals;   //球面上的点法线
        vector<unsigned int> indices;

        // 球的精细程度
        const unsigned int X_SEGMENTS = 64;
        const unsigned int Y_SEGMENTS = 64;
        const float PI = 3.14159265359;
        for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
        {
            for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
            {
                // 绘制球面上的点
                float xSegment = (float)x / (float)X_SEGMENTS;
                float ySegment = (float)y / (float)Y_SEGMENTS;
                float xPos = cos(xSegment * 2.0f * PI) * sin(ySegment * PI);
                float yPos = cos(ySegment * PI);
                float zPos = sin(xSegment * 2.0f * PI) * sin(ySegment * PI);

                positions.push_back(glm::vec3(xPos, yPos, zPos));
                uv.push_back(glm::vec2(xSegment, ySegment));
                normals.push_back(glm::vec3(xPos, yPos, zPos));
            }
        }

        // 将三个点绘制成一个面
        bool oddRow = false; //是否是奇数行
        for (unsigned int y = 0; y < Y_SEGMENTS; ++y)
        {
            if (!oddRow) // even rows: y == 0, y == 2; and so on
            {
                for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
                {
                    indices.push_back(y * (X_SEGMENTS + 1) + x);
                    indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
                }
            }
            else
            {
                for (int x = X_SEGMENTS; x >= 0; --x) // 注意这里是int类型而不是unsigned int 如果是unsigned int会陷入死循环，因为无符号数不会小于0
                {
                    indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
                    indices.push_back(y * (X_SEGMENTS + 1) + x);
                }
            }
            oddRow = !oddRow;
        }
        indexCount = indices.size();

        // 将点的坐标 法线 uv坐标放到一起（放入data内）
        vector<float> data;
        for (unsigned int i = 0; i < positions.size(); ++i)
        {
            data.push_back(positions[i].x);
            data.push_back(positions[i].y);
            data.push_back(positions[i].z);
            if (uv.size() > 0)
            {
                data.push_back(uv[i].x);
                data.push_back(uv[i].y);
            }
            if (normals.size() > 0)
            {
                data.push_back(normals[i].x);
                data.push_back(normals[i].y);
                data.push_back(normals[i].z);
            }
        }
        // VAO VBO EBO 传输球的顶点数据
        glBindVertexArray(sphereVAO);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
        float stride = (3 + 2 + 3) * sizeof(float); // 第一个3 position.xyz 第二个2 uv.xy 第三个3 normal.xyz
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void *)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void *)(5 * sizeof(float)));
    }
    //绘制组成球面的三角形
    glBindVertexArray(sphereVAO);
    glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0);
}
