#include <cld_sphere.h>
using namespace std;
using namespace coolender;
using namespace glm;

unsigned int Sphere::VAO = 0;
unsigned int Sphere::VBO = 0;
unsigned int Sphere::indexCount = 0;//坐标的数量

//产生球的mesh,返回VAO
unsigned int Sphere::createSphere()
{
    if(0 == VAO)
    {
        glGenVertexArrays(1, &VAO);

        unsigned int VBO;
        unsigned int EBO;

        vector<vec3> positions; // 球面上的点
        vector<vec2> uv;        //球面上的uv坐标
        vector<vec3> normals;   //球面上的点法线
        vector<unsigned int> indices;

    }
}