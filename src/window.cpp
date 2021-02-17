#include <window.h>
using namespace std;
using namespace coolender;

Camera camera;
//timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;


float lastX = 800 / 2.0f;
float lastY = 600 / 2.0f;
bool firstMouse = true;

//默认构造函数
Window::Window():winWidth(800), winHeight(600)
{}

Window::Window(
    unsigned int winWidth, 
    unsigned int winHeight):winWidth(winWidth), winHeight(winHeight)
{}


void Window::initAndRun()
{
    //======================glfw glad opengl 初始化======================
    glfwInit(); //初始化GLFW
    
    //通过glfwWindowHint()函数来设置参数，前面是参数名称，后面是值
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //设置主版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //设置次版本
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //设置使用核心模式
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //mac用户需要设置，初始化才能有效
    #endif
    //创建一个窗口对象
    GLFWwindow* window = glfwCreateWindow(winWidth, winHeight, "Coolender version 1.0", NULL, NULL);
    //参数依次是长，宽，名称，后两个参数忽略
    if (window == NULL)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return ;
    }
    
    //将窗口的上下文设置成主线程的上下文
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync 每帧的交换间隔，防止屏幕撕裂
    //注册回调函数，告诉GLFW窗口大小调整时，调用这个回调函数
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);


    //新增监听鼠标和鼠标滚轮事件
    glfwSetCursorPosCallback(window,mouseCallback);
    glfwSetScrollCallback(window,scrollCallback);
    //告诉GLFW选中窗口不显示鼠标
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    //GLAD是用来管理OpenGL的函数指针
    //初始化GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    //glfwGetProcAddress 根据编译的系统给出了正确的函数
    {
        cout << "Failed to initialize GLAD" << endl;
        return;
    }
    //openGL全局配置
    glEnable(GL_DEPTH_TEST); //开启深度测试
    glEnable(GL_MULTISAMPLE); // 开启MSAA通常都是默认开启的
    //======================glfw glad opengl 初始化结束======================



    //CoolenderUI初始化
    CoolenderUI coolenderIU;
    coolenderIU.init(window);

    // // Setup Dear ImGui context
    // IMGUI_CHECKVERSION();
    // ImGui::CreateContext();
    // ImGuiIO& io = ImGui::GetIO(); (void)io;
    // //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    // //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // // Setup Dear ImGui style
    // //ImGui::StyleColorsDark();
    // //ImGui::StyleColorsClassic();
    // ImGui::StyleColorsLight();

    // // Setup Platform/Renderer backends
    // ImGui_ImplGlfw_InitForOpenGL(window, true);
    // ImGui_ImplOpenGL3_Init("#version 330");









    //shader
    Shader test("shader/test.vs.glsl", "shader/test.fs.glsl");
    Plane floor;
    floor.init();
    test.use();
    test.setInt("floorTexture", 0);
    // lighting info
    glm::vec3 lightPos(0.0f, 0.0f, 0.0f);

    bool blinn = true;
    //渲染循环
    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        //input
        processInput(window);

        // render
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        test.use();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)winWidth / (float)winHeight, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        test.setMat4("projection", projection);
        test.setMat4("view", view);
        // set light uniforms
        test.setVec3("viewPos", camera.Position);
        test.setVec3("lightPos", lightPos);
        test.setInt("blinn", blinn);
        // floor
        glBindVertexArray(floor.VAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, floor.texture);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        //绘制UI 注意绘制UI要放在最后否则UI会被遮盖
        coolenderIU.render(blinn);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    //glfw cleanup
    glfwDestroyWindow(window);
    glfwTerminate();
    return;
}

//回调函数声明，更改窗口大小的时候，更改视口大小
void coolender::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// 声明输入函数，判断是否按下键盘
void coolender::processInput(GLFWwindow *window)
{
    //退出
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    //向前
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(FORWARD, 10 * deltaTime);
    }
    //向后
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(BACKWARD, 10 * deltaTime);
    }
    //向左
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(LEFT, 10 * deltaTime);
    }
    //向右
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(RIGHT, 10 * deltaTime);
    }
    //向上
    if (glfwGetKey(window, GLFW_KEY_SPACE))
    {
        camera.ProcessKeyboard(UPWARD, 10 * deltaTime);
    } 
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void coolender::scrollCallback(GLFWwindow *window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}
// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void coolender::mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
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
