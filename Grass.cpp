#include "Grass.h"

void Grass::DrawSingle(Mesh grass, Shader &shader, glm::vec3 position, glm::mat4 model, int index) {

        float randomNumber;

        shader.Activate();
        model = glm::translate(model, position);
        shader.setMat4("model", model);
        grass.Draw(shader, false);


        randomNumber = getRandomNumber(1, 30);
        
        // std::cout << randomNumber << "\n";

        model = glm::rotate(model, glm::radians((float) orientations[index].s1), glm::vec3(0.0f, -1.0f, 0.0f));
        shader.setMat4("model", model);
        // shader.setVec4("lightColor", lightColor);
        grass.Draw(shader, false);

        model = glm::rotate(model, glm::radians((float) -orientations[index].s1), glm::vec3(0.0f, -1.0f, 0.0f));
        shader.setMat4("model", model);
        grass.Draw(shader, false);

        randomNumber = getRandomNumber(30, 60);

        // std::cout << randomNumber << "\n";
        
        model = glm::rotate(model, glm::radians((float) orientations[index].s2), glm::vec3(0.0f, -1.0f, 0.0f));
        shader.setMat4("model", model);
        grass.Draw(shader, false);

        model = glm::rotate(model, glm::radians((float) -orientations[index].s2), glm::vec3(0.0f, -1.0f, 0.0f));
        shader.setMat4("model", model);
        grass.Draw(shader, false);

        randomNumber = getRandomNumber(60, 90);
        // std::cout << randomNumber << "\n";

        model = glm::rotate(model, glm::radians((float) orientations[index].s3), glm::vec3(0.0f, -1.0f, 0.0f));
        shader.setMat4("model", model);
        grass.Draw(shader, false);

        model = glm::rotate(model, glm::radians((float) -orientations[index].s3), glm::vec3(0.0f, -1.0f, 0.0f));
        shader.setMat4("model", model);
        grass.Draw(shader, false);
}

void Grass::generateRandomNumbers(int m, int n) {
    GridOrientation orientation;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++ ) {
            int s1 = getRandomNumber(1, 30);
            int s2 = getRandomNumber(30, 60);
            int s3 = getRandomNumber(60, 90);   

            orientation.s1 = s1;
            orientation.s2 = s2;
            orientation.s3 = s3;
            
            orientations.push_back(orientation);
        }
    }
}

void Grass::DrawGrid(Mesh grass, Shader &shader, glm::vec3 position, glm::mat4 model) {
    glm::vec3 pos = position;
    glm::mat4 local_model = model;
    int index = 0;
    float offset = 0;
    for(int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            pos.z += 10.0f;
            shader.Activate();
            // shader.setMat4("model", local_model);
            shader.setMat4("model[" + std::to_string(index) + "]", glm::translate(local_model, glm::vec3(offset, 0.0f, 0.0f)));
            // shader.setVec3("offsets[" + std::to_string(index) + "]", glm::vec3(offset , 0.0f, 0.0f));   
            // DrawSingle(grass, shader, pos, model, index);
            // DrawSingle(grass, shader, glm::vec3(pos.x, pos.y, pos.z + 0.3), model, index);
            // std::cout << pos.x << "\n";
            index++;
            offset += 1.0f;
        }
        pos.z = position.z;
        pos.x += 2.0f;
    }

    grass.Draw(shader, false, true);
}

// Function to generate a random number
int Grass::getRandomNumber(int start, int stop) {
    // Define a random number generator engine
    static std::random_device rd;
    static std::mt19937 gen(rd());
    // Define a distribution (for example, between 0 and 100)
    std::uniform_int_distribution<int> distribution(start, stop);
    // Generate and return a random number
    return distribution(gen);
}

// Function to generate a random floating-point number
double Grass::getRandomFloat() {
    // Define a random number generator engine
    static std::random_device rd;
    static std::mt19937 gen(rd());
    // Define a distribution (for example, between 0 and 1)
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    // Generate and return a random floating-point number
    return distribution(gen);
}