#include "Grass.h"

void Grass::DrawSingle(Mesh grass, Shader &shader, glm::vec3 position, glm::mat4 model) {

        float randomNumber;

        shader.Activate();
        model = glm::translate(model, position);
        shader.setMat4("model", model);
        grass.Draw(shader, false);

        /* initialize random seed: */
        srand (time(NULL));

        /* generate secret number between 1 and 10: */
        randomNumber = rand() % 30 + 1;
        
        // std::cout << randomNumber << "\n";

        model = glm::rotate(model, glm::radians((float) randomNumber), glm::vec3(0.0f, -1.0f, 0.0f));
        shader.setMat4("model", model);
        // shader.setVec4("lightColor", lightColor);
        grass.Draw(shader, false);

        model = glm::rotate(model, glm::radians((float) -randomNumber), glm::vec3(0.0f, -1.0f, 0.0f));
        shader.setMat4("model", model);
        grass.Draw(shader, false);

        /* initialize random seed: */
        srand (time(NULL));

        /* generate secret number between 1 and 10: */
        randomNumber = rand() % 60 + 30;

        // std::cout << randomNumber << "\n";
        
        model = glm::rotate(model, glm::radians((float) randomNumber), glm::vec3(0.0f, -1.0f, 0.0f));
        shader.setMat4("model", model);
        grass.Draw(shader, false);

        model = glm::rotate(model, glm::radians((float) -randomNumber), glm::vec3(0.0f, -1.0f, 0.0f));
        shader.setMat4("model", model);
        grass.Draw(shader, false);

        /* initialize random seed: */
        // srand (time(NULL));

        /* generate secret number between 1 and 10: */
        randomNumber = rand() % 90 + 60;
        
        // std::cout << randomNumber << "\n";

        model = glm::rotate(model, glm::radians((float) randomNumber), glm::vec3(0.0f, -1.0f, 0.0f));
        shader.setMat4("model", model);
        grass.Draw(shader, false);

        model = glm::rotate(model, glm::radians((float) -randomNumber), glm::vec3(0.0f, -1.0f, 0.0f));
        shader.setMat4("model", model);
        grass.Draw(shader, false);
}

void Grass::DrawGrid(Mesh grass, Shader &shader, glm::vec3 position, glm::mat4 model) {
    glm::vec3 pos = position;
    for(int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            srand (time(NULL));
            int randomNumber = rand() % 5 + 1;
            // std::cout << "Random float" << randomNumber << "\n";
            pos.z += (float) randomNumber/10;
            DrawSingle(grass, shader, pos, model);
        }
        pos.z = position.z;
        pos.x += 0.5f;
    }
}