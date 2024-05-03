#ifndef RENDER_H
#define RENDER_H


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

class Render {
    public:
        std::vector<std::string> file_paths;
        void get_file_list(const std::string folder_path);
        void render(Shader &shader, aCamera &camera, float screen_width, float screen_height);
        void render_model(Shader &shader, std::string file_path, glm::mat4 projection, glm::mat4 view, glm::mat4 model, glm::vec3 light_color);
    private:
        bool endsWith(const std::string& str, const std::string& suffix);
};
   
#endif