#ifndef A_MODEL_H
#define A_MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include "Shader.h"
#include "aMesh.h"

class aModel
{
public:

    std::vector<aTexture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    std::vector<aMesh> meshes;
    std::string directory;
    bool gammaCorrection;

    std::vector<aVertex> vertices;    
    std::vector<unsigned int> indices;
    std::vector<aTexture> textures;
    
    aModel(std::string const& path, bool gamma);
    void Draw(Shader& shader);

private:
    // model data
    void loadModel(std::string const& path);
    void processNode(aiNode* node, const aiScene* scene);
    aMesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<aTexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
        std::string typeName);
};
#endif