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
#include "Mesh.h"

struct AABB {
    glm::vec3 position;
    glm::vec3 size;
};

class aModel
{
public:

    // position should be the top most, back most, left most point
    // sizeX = right_most - left_most
    // sizeY = top_most - bottom_most
    // sizeZ = front_most - back_most
    float right_most_point = 0.0f;
    float left_most_point = 0.0f;
    float top_most_point = 0.0f;
    float bottom_most_point = 0.0f;
    float front_most_point = 0.0f;
    float back_most_point = 0.0f;

    
    std::vector<aTexture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    std::vector<aMesh> meshes;
    std::string directory;

    bool gammaCorrection;

    aModel(std::string const& path, bool gamma);
    void Draw(Shader& shader);
    AABB calculateBoundingBox();
    bool CheckCollision(AABB &one, AABB &two); // AABB - AABB collision
    Mesh generateBoundingBoxMesh();

    

private:
    // model data
    void loadModel(std::string const& path);
    void processNode(aiNode* node, const aiScene* scene);
    aMesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<aTexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
        std::string typeName);

};
#endif