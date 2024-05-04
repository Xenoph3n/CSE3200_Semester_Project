#include "Grass.h"

void Grass::DrawSingle(Mesh grass, Shader &shader, glm::vec3 position, glm::mat4 model) {
    
        shader.Activate();
        model = glm::translate(model, position);
        shader.setMat4("model", model);
        grass.Draw(shader, false);

        model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, -1.0f, 0.0f));
        shader.setMat4("model", model);
        // shader.setVec4("lightColor", lightColor);
        grass.Draw(shader, false);

        model = glm::rotate(model, glm::radians(-30.0f), glm::vec3(0.0f, -1.0f, 0.0f));
        shader.setMat4("model", model);
        grass.Draw(shader, false);

        model = glm::rotate(model, glm::radians(60.0f), glm::vec3(0.0f, -1.0f, 0.0f));
        shader.setMat4("model", model);
        grass.Draw(shader, false);

        model = glm::rotate(model, glm::radians(-60.0f), glm::vec3(0.0f, -1.0f, 0.0f));
        shader.setMat4("model", model);
        grass.Draw(shader, false);

        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
        shader.setMat4("model", model);
        grass.Draw(shader, false);

        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
        shader.setMat4("model", model);
        grass.Draw(shader, false);
}

void Grass::DrawGrid(Mesh grass, Shader &shader, glm::vec3 position, glm::mat4 model) {
    glm::vec3 pos = position;
    for(int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            pos.z += 0.5f;
            DrawSingle(grass, shader, pos, model);
        }
        pos.z = position.z;
        pos.x += 0.5f;
    }
}