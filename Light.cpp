#include "Light.h"

Light::Light() {
    stadium_light = aModel("./stadium/single/light.obj", false);
}

void Light::draw(Shader& shader, glm::mat4 view, glm::mat4 projection) {
    
    shader.Activate();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
    
    shader.setMat4("model", model);
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);

    stadium_light.Draw(shader);
}