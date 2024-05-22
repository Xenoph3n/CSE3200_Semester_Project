#ifndef BUILDING_H
#define BUILDING_H


#include"aMesh.h"
#include"aModel.h"
#include<glad/glad.h>
#include<vector>
#include<iostream>
#include<glm/glm.hpp>
#include"Shader.h"
#include"aCamera.h"
#include<filesystem>

namespace fs = std::filesystem;


struct Object {
    std::vector<aMesh> meshes;
    std::vector<float> shininess;
};

class Building {
    public:
        bool update = false;
        Object meshes;
        std::vector<AABB> aabbs;
        std::vector<aModel> models;
        std::vector<std::string> file_paths;
        
        void get_file_list(const std::string folder_path);

        void render(Shader &shader, 
                    aCamera &camera, 
                    float screen_width, 
                    float screen_height,
                    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f),
                    glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
                    float rotation_in_degrees = 0.0f
                    );
        void render_model(  Shader &shader, 
                            std::string file_path, 
                            glm::mat4 projection, 
                            glm::mat4 view, 
                            glm::mat4 model, 
                            glm::vec3 light_color,
                            glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f),
                            glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
                            float rotation_in_degrees = 0.0f
                        );
        void draw(
            Shader &shader,
            aCamera &camera,
            float screen_width,
            float screen_height,
            glm::mat4 model, 
            glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f),
            glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
            float rotation = 0.0f,
            glm::vec3 rotation_axis = glm::vec3(0.0f, 1.0f, 0.0f)

            );
    private:
        bool endsWith(const std::string& str, const std::string& suffix);
};
   
#endif