#include <cld_sphere.h>
using namespace std;
using namespace coolender;
using namespace glm;

unsigned int Sphere::VAO = 0;
unsigned int Sphere::VBO = 0;
unsigned int Sphere::EBO = 0;//Element Buffer Object
unsigned int Sphere::indexCount = 0;//坐标的数量
unsigned int Sphere::xSegments = 64;//x轴上的分割数量
unsigned int Sphere::ySegments = 64;//y轴上的分割数量

//产生球的mesh,返回VAO
unsigned int Sphere::createSphere()
{
    if(0 == VAO || xSegments!= 64 || ySegments != 64)
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
        for(unsigned int y = 0; y <= ySegments; y++)
        {
            for(unsigned int x = 0; x <= xSegments; x++)
            {
                // 绘制球面上的点 (球坐标系)
                float xSeg = float(x) / float(xSegments);
                float ySeg = float(y) / float(ySegments);
                float xPos = cos(xSeg * 2.0f * PI) * sin(ySeg * PI);
                float yPos = cos(ySeg * PI);
                float zPos = sin(xSeg * 2.0f * PI) * sin(ySeg * PI);

                positions.push_back(vec3(xPos, yPos, zPos));
                uv.push_back(vec2(xSeg, ySeg));
                normals.push_back(vec3(xPos, yPos, zPos));
            }
        }

        //生成EBO
        // 将三个点绘制成一个面
        bool oddRow = false; //是否是奇数行
        for(unsigned int y = 0; y < ySegments; y++)
        {
            if (!oddRow) // even rows: y == 0, y == 2; and so on
            {
                for(unsigned int x = 0; x <= xSegments; x++)
                {
                    indices.push_back(y * (xSegments + 1) + x);
                    indices.push_back((y + 1) * (xSegments + 1) + x);
                }
            }
            else
            {
                for(int x = xSegments; x >= 0; x--)
                {
                    indices.push_back((y + 1) * (xSegments + 1) + x);
                    indices.push_back(y * (xSegments + 1) + x);
                }
            }
            oddRow = !oddRow;
        }
        indexCount = indices.size();

        // 将点的坐标 法线 uv坐标放到一起（放入data内）
        std::vector<float> data;
        for (unsigned int i = 0; i < positions.size(); i++)
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
    return VAO;//返回VAO
}