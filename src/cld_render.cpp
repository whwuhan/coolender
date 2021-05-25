#include <cld_render.h>
using namespace coolender;
using namespace wh::basic;
using namespace std;
using namespace glm;
//准备渲染点状点云
void Render::render_point_cloud_type_point_init(PointCloud &point_cloud)
{
    //获取C++原生数据
    float point_Cloud_data[point_cloud.size * POINT3D_SIZE];
    for(int i = 0; i < point_cloud.points.rows(); i++)
    {
        for(int j = 0; j < 3;j++)
        {
            point_Cloud_data[i * 3 + j] = point_cloud.points.row(i)[j];
        }
    }
    glGenVertexArrays(1, &point_cloud.VAO);
    glBindVertexArray(point_cloud.VAO);
    glGenBuffers(1, &point_cloud.VBO);
    glBindBuffer(GL_ARRAY_BUFFER, point_cloud.VBO);
    //传递数据
    glBufferData(GL_ARRAY_BUFFER, sizeof(point_Cloud_data), &point_Cloud_data[0], GL_STATIC_DRAW);
    //设置VAO
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindVertexArray(0);
}

//渲染点状点云
void Render::render_point_cloud_type_point(PointCloud &point_cloud)
{
    glBindVertexArray(point_cloud.VAO);
    glDrawArrays(GL_POINTS, 0, point_cloud.size);
    glBindVertexArray(0);
}

//准备渲染球状点云
void Render:: render_point_cloud_type_sphere_init(PointCloud &point_cloud, Sphere &sphere)
{
    glBindVertexArray(sphere.VAO);
    unsigned int point_amount = point_cloud.size;//点云点的数量
    mat4 point_model_matrices[point_amount];//每个球状点云的model矩阵
    for(int i = 0; i < point_amount; i++)
    {
        mat4 point_model(1.0f);
        point_model = translate
        (
            point_model, 
            vec3(point_cloud.points.row(i)[0], point_cloud.points.row(i)[1], point_cloud.points.row(i)[2])
        );//平移
        point_model = 
        scale
        (
            point_model, 
            vec3(point_cloud.point_size * 0.05, point_cloud.point_size * 0.05, point_cloud.point_size * 0.05)
        );//缩放
        //不需要旋转
        point_model_matrices[i] = point_model;
    } 

    // configure instanced array 注意开始配置instanced array(实际就是把这些model矩阵先放到缓存里面)
    if(0 == point_cloud.point_model_matrices_buffer)
    {
        glGenBuffers(1,&point_cloud.point_model_matrices_buffer);
    }
    // cout << point_cloud.point_model_matrices_buffer << endl;
    glBindBuffer(GL_ARRAY_BUFFER, point_cloud.point_model_matrices_buffer);
    glBufferData(GL_ARRAY_BUFFER, point_amount * sizeof(mat4), &point_model_matrices[0], GL_STATIC_DRAW);
    

    // set transformation matrices as an instance vertex attribute (with divisor 1)
    // note: we're cheating a little by taking the, now publicly declared, VAO of the model's mesh(es) and adding new vertexAttribPointers
    // normally you'd want to do this in a more organized fashion, but for learning purposes this will do.

    // set attribute pointers for matrix (4 times vec4) 就是这里把不同的model矩阵传递给了shader 因为此时绑定的VBO是model矩阵数组
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

    glVertexAttribDivisor(3, 1);//参数1：设置vertex attribute的index 参数2：设置每几个instance更新一次数据
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);
    glBindVertexArray(0);
}

//渲染球状点云
void Render::render_point_cloud_type_sphere(PointCloud &point_cloud, Sphere &sphere)
{
    glBindVertexArray(sphere.VAO);
    //注意绘制类型是GL_TRIANGLE_STRIP 不是GL_TRIANGLES
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//设置绘制成线框模式
    glDrawElementsInstanced(GL_TRIANGLE_STRIP, sphere.index_count, GL_UNSIGNED_INT, 0, point_cloud.size);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//设置成默认模式
    glBindVertexArray(0);
}

//渲染polygon mesh准备
void Render::render_polygon_mesh_init(PolygonMesh &mesh)
{
    //获取C++原生数据
    float polygon_mesh_data[mesh.vertices.rows() * 6];//分配空间 每个顶点和法线一一对应，pos:3 normals:3 不考虑UV坐标
    //判断是不是正确的polygon mesh
    if(mesh.normals.rows() == 0)
    {
        //没有法线
        cerr << "Warning! There are no normals!" << endl;
        for(int i = 0; i < mesh.vertices.rows(); i++)
        {
            for(int j = 0; j < 3; j++)
            {
                polygon_mesh_data[i * 3 + j] = mesh.vertices(i, j);
            }
        }
    }
    else
    {
        //有法线
        for(int i = 0; i < mesh.vertices.rows(); i++)
        {
            for(int j = 0; j < 6; j++)
            {
                if(j < 3)
                {
                    polygon_mesh_data[i * 6 + j] = mesh.vertices(i, j);
                }
                else
                {
                    polygon_mesh_data[i * 6 + j] = mesh.normals(i, j - 3);
                    // cout << mesh.normals.row(i)[j - 3] << endl;
                }
            }
        }
    }
    
    //面片索引
    unsigned int polygonMeshElement[mesh.vertices_indices.rows() * 3];//EBO数据 一个面片要绘制3个点，所以要3个坐标的索引
    if(mesh.vertices_indices.rows() == 0)
    {
        //没有面片索引
        cerr << "Warning! It's not a polygon mesh model!" << endl;
        return;
    }
    else
    {
        for(int i = 0; i < mesh.vertices_indices.rows(); i++)
        {
            for(int j = 0; j < 3; j++)
            {
                polygonMeshElement[i * 3 + j] = mesh.vertices_indices(i,j) - 1;
            }
        }
    }
    //VAO VBO
    glGenVertexArrays(1, &mesh.VAO);
    glBindVertexArray(mesh.VAO);
    glGenBuffers(1, &mesh.VBO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(polygon_mesh_data), &polygon_mesh_data[0], GL_STATIC_DRAW);
    //EBO
    glGenBuffers(1, &mesh.EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(polygonMeshElement), &polygonMeshElement[0], GL_STATIC_DRAW);
    //设置VAO
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glBindVertexArray(0);
}

//渲染线框模式的mesh
void Render::render_polygon_mesh_type_line(PolygonMesh &mesh)
{
    glBindVertexArray(mesh.VAO);
    // glDrawElements(GL_TRIANGLES, mesh.vertices_indices.rows() * 3, GL_UNSIGNED_INT, 0);
    //绘制点
    glDrawElements(GL_POINTS, mesh.vertices_indices.rows() * 3, GL_UNSIGNED_INT, 0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//设置绘制成线框模式
    glDrawElements(GL_TRIANGLES, mesh.vertices_indices.rows() * 3, GL_UNSIGNED_INT, 0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//设置成默认模式
    glBindVertexArray(0);
}

//填充模式
void Render::render_polygon_mesh_type_fill(PolygonMesh &mesh)
{
    glBindVertexArray(mesh.VAO);
    glDrawElements(GL_TRIANGLES, mesh.vertices_indices.rows() * 3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

//线框加填充模式
void Render::render_polygon_mesh_type_line_fill(PolygonMesh &mesh, Shader &shader)
{
    glBindVertexArray(mesh.VAO);
    shader.setBool("render_line_point", true);
    glDrawElements(GL_POINTS, mesh.vertices_indices.rows() * 3, GL_UNSIGNED_INT, 0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//设置绘制成线框模式
    glDrawElements(GL_TRIANGLES, mesh.vertices_indices.rows() * 3, GL_UNSIGNED_INT, 0);
    shader.setBool("render_line_point", false);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//设置成默认模式
    glDrawElements(GL_TRIANGLES, mesh.vertices_indices.rows() * 3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

//光照模式
void Render::render_polygon_mesh_type_light(wh::basic::PolygonMesh &mesh)
{
    glBindVertexArray(mesh.VAO);
    glDrawElements(GL_TRIANGLES, mesh.vertices_indices.rows() * 3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}