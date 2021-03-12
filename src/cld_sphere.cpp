#include <cld_sphere.h>
using namespace std;
using namespace coolender;
using namespace glm;

// unsigned int Sphere::VAO = 0;
// unsigned int Sphere::VBO = 0;
// unsigned int Sphere::EBO = 0;//Element Buffer Object
// double Sphere::radius = 0.005;//半径
// unsigned int Sphere::indexCount = 0;//坐标的数量
// unsigned int Sphere::xSegments = 4;//x轴上的分割数量
// unsigned int Sphere::ySegments = 4;//y轴上的分割数量

Sphere::Sphere():
VAO(0),
VBO(0),
EBO(0),
radius(0.05),
indexCount(0),
xSegments(10),
ySegments(10)
{}

//产生球的mesh,返回VAO
void Sphere::createSphere()
{
    if(0 == VAO)
    {
        glGenVertexArrays(1, &VAO);

        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        vector<vec3> positions; // 球面上的点
        vector<vec2> uv;        //球面上的uv坐标
        vector<vec3> normals;   //球面上的点法线
        vector<unsigned int> indices;

        //生成球的坐标信息
        float PI = 3.14159265359;
        for (unsigned int y = 0; y <= ySegments; ++y)
        {
            for (unsigned int x = 0; x <= xSegments; ++x)
            {
                // 绘制球面上的点
                float xSegment = (float)x / (float)xSegments;
                float ySegment = (float)y / (float)ySegments;
                float xPos = cos(xSegment * 2.0f * PI) * sin(ySegment * PI) * radius;
                float yPos = cos(ySegment * PI) * radius;
                float zPos = sin(xSegment * 2.0f * PI) * sin(ySegment * PI) * radius;

                positions.push_back(vec3(xPos, yPos, zPos));
                uv.push_back(vec2(xSegment, ySegment));
                normals.push_back(vec3(xPos, yPos, zPos));
            }
        }

        //生成EBO
        // 将三个点绘制成一个面
        bool oddRow = false; //是否是奇数行
        for (unsigned int y = 0; y < ySegments; ++y)
        {
            if (!oddRow) // even rows: y == 0, y == 2; and so on
            {
                for (unsigned int x = 0; x <= xSegments; ++x)
                {
                    indices.push_back(y * (xSegments + 1) + x);
                    indices.push_back((y + 1) * (xSegments + 1) + x);
                }
            }
            else
            {
                for (int x = xSegments; x >= 0; --x) // 注意这里是int类型而不是unsigned int 如果是unsigned int会陷入死循环，因为无符号数不会小于0
                {
                    indices.push_back((y + 1) * (xSegments + 1) + x);
                    indices.push_back(y * (xSegments + 1) + x);
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
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
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
    // glBindVertexArray(VAO);
    // glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    return ;
}

//根据pointSize设置球的半径和分割数量
void Sphere::setRadiusAndSegmentsByPointSize(float pointSize)
{
    //先删VBO EBO VAO
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
    //重置VBO VAO EBO
    VBO = 0;
    EBO = 0;
    VAO = 0;
    //设置球的参数
    radius = pointSize * 0.05;
    xSegments = 10+ pointSize;
    ySegments = 10 + pointSize;
    //打印球的细分程度
    // cout << "xSegments : " << xSegments << endl;
    // cout << "ySegments : " << ySegments << endl;
    createSphere();
}