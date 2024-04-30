#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>   
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

#include "Shader.h"

#define MAX_BONE_INFLUENCE 4

struct aVertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
    int m_BoneIDs[MAX_BONE_INFLUENCE];
    float m_Weights[MAX_BONE_INFLUENCE];
};

struct aTexture
{
    unsigned int id;
    std::string type;
    std::string path;
};

class aMesh {
public:

    std::vector<aVertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<aTexture>      textures;
    unsigned int VAO;
    aMesh(std::vector<aVertex> vertices, std::vector<unsigned int> indices, std::vector<aTexture> textures);
    void Draw(Shader& shader);
    void SetupMesh();
};

#endif