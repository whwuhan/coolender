
#include <cld_plane.h>
using namespace std;
using namespace coolender;
using namespace glm;
Plane::Plane():color(1.0f, 1.0f, 1.0f, 1.0f), texture_path("img/concrete_seamless.jpg")
{}

Plane::Plane(vec4 color, string texture_path):color(color), texture_path(texture_path)
{}

void Plane::init()
{
    // set up vertex data (and buffer(s)) and configure vertex attributes
    float planeVertices[] = 
    {
        // positions            // normals         // texcoords
         10.0f, -1.0f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
        -10.0f, -1.0f,  10.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
        -10.0f, -1.0f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
         10.0f, -1.0f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
        -10.0f, -1.0f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
         10.0f, -1.0f, -10.0f,  0.0f, 1.0f, 0.0f,  10.0f, 10.0f
    };

    // plane VAO VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glBindVertexArray(0);
    texture = TextureLoader::loadTexture2D(texture_path.c_str());
    return ;
}
