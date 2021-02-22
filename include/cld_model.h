#pragma once
#include <glad/glad.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <cld_shader.h>
#include <cld_mesh.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

namespace coolender
{
    class Model 
    {
    public:
        //模型数据
        std::vector<coolender::Texture> textures_loaded;    //保存当前加载的纹理，保证纹理不需要重复加载
        std::vector<coolender::Mesh>    meshes;             //mesh
        std::string directory;                   //模型加载路径
        bool gammaCorrection;                    //

        //构造函数加载模型
        Model(std::string const &path, bool gamma = false);

        //遍历所有网格，并且绘制他们
        void Draw(coolender::Shader &shader);
        
    private:
        //使用assimp加载模型
        void loadModel(std::string const &path);

        // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
        //递归处理assimp的节点
        void processNode(aiNode *node, const aiScene *scene);
        
        //处理mesh
        coolender::Mesh processMesh(aiMesh *mesh, const aiScene *scene);

        // checks all material textures of a given type and loads the textures if they're not loaded yet.
        // the required info is returned as a Texture struct.
        std::vector<coolender::Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
    };

    //加载纹理
    unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);
}
