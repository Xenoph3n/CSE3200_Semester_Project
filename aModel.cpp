#include "aModel.h"
#include<stb/stb_image.h>

unsigned int TextureFromFile2(const char* path, const std::string& directory, bool gamma = false);

// constructor, expects a filepath to a 3D model.
aModel::aModel(std::string const& path, bool gamma = false) : gammaCorrection(gamma)
{
    loadModel(path);
}

// draws the model, and thus all its meshes
void aModel::Draw(Shader& shader)
{
   for (unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].Draw(shader);
}

// loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes std::vector.
void aModel::loadModel(std::string const& path)
{
    // read file via ASSIMP
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    // check for errors
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }
    // retrieve the directory path of the filepath
    directory = path.substr(0, path.find_last_of('/'));

    // process ASSIMP's root node recursively
    processNode(scene->mRootNode, scene);
}

// processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
void aModel::processNode(aiNode* node, const aiScene* scene)
{
    // process each mesh located at the current node
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        // the node object only contains indices to index the actual objects in the scene. 
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }

}

aMesh aModel::processMesh(aiMesh* mesh, const aiScene* scene)
{
    // data to fill
    std::vector<aVertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<aTexture> textures;

    
    // process materials
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
    // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
    // Same applies to other texture as the following list summarizes:
    // diffuse: texture_diffuseN
    // specular: texture_specularN
    // normal: texture_normalN

    // walk through each of the mesh's vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        aVertex vertex;
        glm::vec3 vector; // we declare a placeholder std::vector since assimp uses its own std::vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
        // positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;

        if (vector.x > right_most_point) {
            right_most_point = vector.x;
        }

        if (vector.x < left_most_point) {
            left_most_point = vector.x;
        }

        if (vector.y > top_most_point) {
            top_most_point = vector.y;
        }

        if (vector.y < bottom_most_point) {
            bottom_most_point = vector.y;
        }

        if (vector.z > front_most_point) {
            front_most_point = vector.z;
        }

        if (vector.z < back_most_point) {
            back_most_point = vector.z;
        }
        
        if (mesh->HasVertexColors(i)) {
            // std::cout << "Color Point" << mesh->mColors[i]->r;
            // vertex.Color = vector;
            std::cout << "Color Point" << mesh->mColors[i]->r;
        }
        
        // normals
        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
        }
        // texture coordinates
        if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
            // tangent
            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            vertex.Tangent = vector;
            // bitangent
            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            vertex.Bitangent = vector;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);


        aiColor4D color(0.0f, 0.0f, 0.0f, 1.0f);
        material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
        vertex.Color.x = color.r;

        // std::cout << vertex.Color.x;

        vertex.Color.y = color.g;
        vertex.Color.z = color.b;
        vertex.Color.w = color.a;

        vertices.push_back(vertex);

    }
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices std::vector
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }



    // 1. diffuse maps
    std::vector<aTexture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    // 2. specular maps
    std::vector<aTexture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    // 3. normal maps
    std::vector<aTexture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    // 4. height maps
    std::vector<aTexture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    // return a mesh object created from the extracted mesh data
    return aMesh(vertices, indices, textures);
}

// checks all material textures of a given type and loads the textures if they're not loaded yet.
// the required info is returned as a aTexture struct.
std::vector<aTexture> aModel::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
    std::vector<aTexture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
        bool skip = false;
        for (unsigned int j = 0; j < textures_loaded.size(); j++)
        {
            if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(textures_loaded[j]);
                skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                break;
            }
        }
        if (!skip)
        {   // if texture hasn't been loaded already, load it
            aTexture texture;
            texture.id = TextureFromFile2(str.C_Str(), this->directory);
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecessary load duplicate textures.
        }
    }
    return textures;
}

AABB aModel::calculateBoundingBox() {
    glm::vec3 position = glm::vec3(left_most_point , top_most_point , back_most_point );
    float sizeX = right_most_point - left_most_point;
    float sizeY = top_most_point - bottom_most_point;
    float sizeZ = front_most_point - back_most_point;

    glm::vec3 size = glm::vec3(sizeX , sizeY , sizeZ ) ;

    AABB aabb;
    aabb.position = position;
    aabb.size = size;

    modelAABB = aabb;

    return aabb;
}

bool aModel::CheckCollision(AABB &one, AABB &two) // AABB - AABB collision
{
    // collision x-axis?
    bool collisionX = one.position.x + one.size.x >= two.position.x &&
        two.position.x + two.size.x >= one.position.x;
    // collision y-axis?
    bool collisionY = one.position.y - one.size.y <= two.position.y &&
        two.position.y - two.size.y <= one.position.y;

    bool collisionZ = one.position.z + one.size.z >= two.position.z &&
        two.position.z + two.size.z >= one.position.z;
    // collision only if on both axes
    return collisionX && collisionY && collisionZ;
}  

Mesh aModel::generateBoundingBoxMesh(AABB aabb, glm::vec4 color) {

    std::vector<Vertex> vertices;
    std::vector<glm::vec3> vert;

    glm::vec3 vertex_1 = glm::vec3(aabb.position.x, aabb.position.y, aabb.position.z + aabb.size.z);
    glm::vec3 vertex_2 = glm::vec3(aabb.position.x + aabb.size.x, aabb.position.y, aabb.position.z + aabb.size.z);
    // glm::vec3 vertex_2 = glm::vec3(right_most_point, top_most_point, front_most_point);
    glm::vec3 vertex_3 = glm::vec3(aabb.position.x + aabb.size.x, aabb.position.y - aabb.size.y, aabb.position.z + aabb.size.z);
    glm::vec3 vertex_4 = glm::vec3(aabb.position.x, aabb.position.y - aabb.size.y,  aabb.position.z + aabb.size.z);

    glm::vec3 vertex_5 = glm::vec3(aabb.position.x, aabb.position.y - aabb.size.y,  aabb.position.z);
    glm::vec3 vertex_6 = glm::vec3(aabb.position.x + aabb.size.x, aabb.position.y - aabb.size.y, aabb.position.z);
    glm::vec3 vertex_7 = glm::vec3(aabb.position.x + aabb.size.x, aabb.position.y, aabb.position.z);
    glm::vec3 vertex_8 = glm::vec3(aabb.position.x, aabb.position.y, aabb.position.z);

    vert.push_back(vertex_1);
    vert.push_back(vertex_2);
    vert.push_back(vertex_3);
    vert.push_back(vertex_4);
    vert.push_back(vertex_5);
    vert.push_back(vertex_6);
    vert.push_back(vertex_7);
    vert.push_back(vertex_8);

    for (glm::vec3 vect : vert) {
        
        Vertex vertex;
        vertex.position = vect;
        vertex.normal = glm::vec3(0.0f, 1.0f, 0.0f);


        if(vect == aabb.position) {
            vertex.color = color + glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
        } else {
            vertex.color = color;
        }
    
        vertex.texUV = glm::vec2(1.0f, 1.0f);
        vertices.push_back(vertex);
    }

    std::vector<GLuint> indices = {
        0, 1, 2, 3,
        0, 7, 6, 1,
        1, 2, 5, 6,
        6, 1, 0, 7,
        7, 6, 5, 4,
        4, 7, 0, 3
    };

    std::vector<Texture> textures;

    return Mesh(vertices, indices, textures, false);
    
}

void aModel::ApplyGravity() {
    glm::vec3 ground = glm::vec3(0.0f, -50.0f, 0.0f);

    if (apply_gravity) {
        if (position.y >= ground.y) {
            position.y -= 0.1f;
        }       
    }
   
}


unsigned int TextureFromFile2(const char* path, const std::string& directory, bool gamma)
{
    std::string filename = std::string(path);
    filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    std::cout << "Texture: " << filename << std::endl;


    int width, height, nrComponents;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "aTexture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}