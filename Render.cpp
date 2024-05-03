#include "Render.h"


// Render::Render(Shader &shader, aCamera &camera) {
//     ourCamera = camera;
// }

void Render::get_file_list(const std::string folder_path) {

    // Iterate over all files in the folder
    for (const auto& entry : std::filesystem::directory_iterator(folder_path)) {
        // Check if the entry is a regular file
        if (std::filesystem::is_regular_file(entry.path())) {
            std::string path = entry.path().string();
            if (endsWith(path, ".obj")) {
                file_paths.push_back(path);
            }
            
        } 
    }

    for (std::string file_path : file_paths) {
        std::cout << file_path << "\n";
    }
}

void Render::render(Shader &shader, aCamera &camera, float screen_width, float screen_height) {
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)screen_width / (float) screen_height, 0.1f, 2000.0f);
    glm::mat4 view = camera.GetViewMatrix();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene

    glm::vec3 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    for (std::string file_path : file_paths)
    {
        render_model(shader, file_path, projection, view, model, lightColor);
    }
    
}

void Render::render_model(Shader &shader, std::string file_path, glm::mat4 projection, glm::mat4 view, glm::mat4 model, glm::vec3 light_color) {
    aModel object(file_path, false);

    shader.Activate();
    
    shader.setMat4("projection", projection);
    shader.setMat4("view", view);
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
    shader.setMat4("model", glm::translate(model, glm::vec3(0.0f,2.0f,0.0f)));
    shader.setVec4("lightColor", light_color);
    
    object.Draw(shader);
}

bool Render::endsWith(const std::string& str, const std::string& suffix) {
    if (str.length() < suffix.length())
        return false;
    return str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0;
}