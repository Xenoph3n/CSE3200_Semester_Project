#ifndef A_MODEL_H
#define A_MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include<stb/stb_image.h>


#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include "Shader.h"
#include "aMesh.h"
#include "Mesh.h"
#include "Collision.h"
#include "Bone.h"
// #include "Helpers.h"

struct BoneInfo
{
    int id;
    glm::mat4 offset;
};

class aModel
{
public:

    std::map<std::string, BoneInfo> m_BoneInfoMap;
    int m_BoneCounter = 0;

    Collision collision;
    bool apply_gravity = true; 
    bool full_path = true;   
    float gravity = 9.8f;
    
    std::vector<aTexture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    std::vector<aMesh> meshes;
    std::string directory;

    bool gammaCorrection;
    aModel();
    aModel(std::string const& path, bool gamma);
    void Draw(Shader& shader);
    glm::vec3 ApplyGravity();
    std::map<std::string, BoneInfo>& GetBoneInfoMap();
    int& GetBoneCount();  
    void SetVertexBoneDataToDefault(aVertex& vertex);
    void SetVertexBoneData(aVertex& vertex, int boneID, float weight);
    void ExtractBoneWeightForVertices(std::vector<aVertex>& vertices, aiMesh *mesh, const aiScene *scene);
private:
    void loadModel(std::string const& path);
    void processNode(aiNode* node, const aiScene* scene);
    aMesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<aTexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
        std::string typeName);
    unsigned int TextureFromFile2(const char* path, const std::string& directory, bool gamma = false);

     
};
#endif