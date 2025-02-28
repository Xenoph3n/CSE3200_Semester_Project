#include "Building.h"

void Building::get_file_list(const std::string folder_path) {

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

}

void Building::render(Shader &shader, aCamera &camera, float screen_width, float screen_height, glm::vec3 scale, glm::vec3 translation, float rotation_in_degrees) {
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)screen_width / (float) screen_height, 0.1f, 2000.0f);
    glm::mat4 view = camera.GetViewMatrix();

    glm::mat4 model = glm::mat4(1.0f);
    glm::vec3 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    for (std::string file_path : file_paths)
    {
        render_model(
            shader, 
            file_path, 
            projection, 
            view, 
            model, 
            lightColor, 
            scale,
            translation,
            rotation_in_degrees
        );
    }
    
}

void Building::render_model(Shader &shader, std::string file_path, glm::mat4 projection, glm::mat4 view, glm::mat4 model, glm::vec3 light_color, glm::vec3 scale, glm::vec3 translation, float rotation_in_degrees) {
    aModel object(file_path, false);
    AABB aabb = object.collision.calculateBoundingBox();

    aabbs.push_back(aabb);

    models.push_back(object);

    shader.Activate();
    
    shader.setMat4("projection", projection);
    shader.setMat4("view", view);
    model = glm::scale(model, scale);	
    shader.setMat4("model", glm::translate(model, translation));
    shader.setVec4("lightColor", light_color);

    std::string WINDOW = "window";
    std::string CHAIR = "chair";
    std::string RAILING = "railing";

    float shiny_value = 1.0f;
    if (file_path.find(WINDOW) != std::string::npos) {
        shiny_value = 200.0f;
    } 

    if (file_path.find(CHAIR) != std::string::npos) {
        shiny_value = 100.0f;
    }

    if (file_path.find(RAILING) != std::string::npos) {
        shiny_value = 200.0f;
    }
     
    for (aMesh mesh :  object.meshes) {
        meshes.meshes.push_back(mesh);
        meshes.shininess.push_back(shiny_value);
    }
}

void Building::draw(Shader &shader, aCamera &camera, float screen_height, float screen_width, glm::mat4 model, glm::vec3 scale, glm::vec3 translation, float rotation, glm::vec3 rotation_axis

) {
    for (unsigned int i = 0; i < meshes.meshes.size(); i++) {

        shader.Activate();
        glm::mat4 local_model = model;
        glm::mat4 view = camera.GetViewMatrix();

        local_model = glm::translate(local_model, glm::vec3(0.0f, 0.0f, 0.0f));
        local_model = glm::scale(local_model, scale);	
        local_model = glm::rotate(local_model, glm::radians(rotation), rotation_axis);
        local_model = glm::translate(local_model, translation);
        
        shader.setMat4("model", local_model);    
        // glm::vec4 aabb_position = glm::vec4(aabbs[i].position.x, aabbs[i].position.y, aabbs[i].position.z, 1.0f);

        shader.setMat4("view", view);
        shader.setFloat("shininess", meshes.shininess[i]);
        meshes.meshes[i].Draw(shader);
        shader.setMat4("model", glm::mat4(1.0f));
    }
    update = true;
}

bool Building::endsWith(const std::string& str, const std::string& suffix) {
    if (str.length() < suffix.length())
        return false;
    return str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0;
}