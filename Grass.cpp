#include "Grass.h"

void Grass::DrawSingle(Mesh grass, Shader &shader, glm::vec3 position, glm::mat4 model, int index) {

        float randomNumber;

        shader.Activate();
        model = glm::translate(model, position);
        shader.setMat4("model", model);
        grass.Draw(shader, false);


        randomNumber = getRandomNumber(1, 30);
        
        model = glm::rotate(model, glm::radians((float) orientations[index].s1), glm::vec3(0.0f, -1.0f, 0.0f));
        shader.setMat4("model", model);
        grass.Draw(shader, false);

        model = glm::rotate(model, glm::radians((float) -orientations[index].s1), glm::vec3(0.0f, -1.0f, 0.0f));
        shader.setMat4("model", model);
        grass.Draw(shader, false);

        randomNumber = getRandomNumber(30, 60);

        
        model = glm::rotate(model, glm::radians((float) orientations[index].s2), glm::vec3(0.0f, -1.0f, 0.0f));
        shader.setMat4("model", model);
        grass.Draw(shader, false);

        model = glm::rotate(model, glm::radians((float) -orientations[index].s2), glm::vec3(0.0f, -1.0f, 0.0f));
        shader.setMat4("model", model);
        grass.Draw(shader, false);

        randomNumber = getRandomNumber(60, 90);

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
            shader.setMat4("model[" + std::to_string(index) + "]", glm::translate(local_model, glm::vec3(offset, 0.0f, 0.0f)));
            index++;
            offset += 1.0f;
        }
        pos.z = position.z;
        pos.x += 2.0f;
    }

    grass.Draw(shader, false, true);
}

void Grass::setUpModels(Shader &shader) {
    shader.Activate();
     for (int j = 0; j < n; j++) {
        for(int i = 0; i < n; i++) {
            glm::mat4 smodel = glm::mat4(1.0f);
            glm::vec3 q1 = glm::vec3(position.x, position.y, position.z);
            glm::vec3 q2 = glm::vec3(position.x, position.y, -position.z);
            glm::vec3 q3 = glm::vec3(-position.x, position.y, -position.z);
            glm::vec3 q4 =  glm::vec3(-position.x, position.y, position.z);
            int s1;
            int s2;

            if (sqrt(pow(q1.x, 2) + pow(q1.z, 2)) < (float) n / 2 && 
                !(   q1.x > pitch_bounds.x && q1.x < pitch_bounds.z &&
                    q1.z > pitch_bounds.y && q1.z < pitch_bounds.w
                )
            ) {
                smodel = glm::translate(smodel, q1);
                models.push_back(smodel);

                s1 = getRandomNumber(1, 90);
                smodel = glm::rotate(smodel, glm::radians((float) s1), glm::vec3(0.0f, -1.0f, 0.0f));
                models.push_back(smodel);

                smodel = glm::rotate(smodel, glm::radians((float) -s1), glm::vec3(0.0f, -1.0f, 0.0f));
                models.push_back(smodel);

                s2 = getRandomNumber(1, 90);
                smodel = glm::rotate(smodel, glm::radians((float) s2), glm::vec3(0.0f, -1.0f, 0.0f));
                models.push_back(smodel);

                smodel = glm::rotate(smodel, glm::radians((float) -s2), glm::vec3(0.0f, -1.0f, 0.0f));
                models.push_back(smodel);

            }

            if (sqrt(pow(q2.x, 2) + pow(q2.z, 2)) < (float) n / 2 &&
                !(   q2.x > pitch_bounds.x && q2.x < pitch_bounds.z &&
                    q2.z > pitch_bounds.y && q2.z < pitch_bounds.w
                )
            ) {
                smodel = glm::translate(glm::mat4(1.0f), q2);
                models.push_back(smodel);

                s1 = getRandomNumber(1, 90);
                smodel = glm::rotate(smodel, glm::radians((float) s1), glm::vec3(0.0f, -1.0f, 0.0f));
                models.push_back(smodel);

                smodel = glm::rotate(smodel, glm::radians((float) -s1), glm::vec3(0.0f, -1.0f, 0.0f));
                models.push_back(smodel);

                s2 = getRandomNumber(1, 90);
                smodel = glm::rotate(smodel, glm::radians((float) s2), glm::vec3(0.0f, -1.0f, 0.0f));
                models.push_back(smodel);

                smodel = glm::rotate(smodel, glm::radians((float) -s2), glm::vec3(0.0f, -1.0f, 0.0f));
                models.push_back(smodel);
            }

            if (sqrt(pow(q3.x, 2) + pow(q3.z, 2)) < (float) n / 2 && 
                !(  q3.x > pitch_bounds.x && q3.x < pitch_bounds.z &&
                    q3.z > pitch_bounds.y && q3.z < pitch_bounds.w
                )
            ) {
                smodel = glm::translate(glm::mat4(1.0f), q3);
                models.push_back(smodel);

                s1 = getRandomNumber(1, 90);
                smodel = glm::rotate(smodel, glm::radians((float) s1), glm::vec3(0.0f, -1.0f, 0.0f));
                models.push_back(smodel);

                smodel = glm::rotate(smodel, glm::radians((float) -s1), glm::vec3(0.0f, -1.0f, 0.0f));
                models.push_back(smodel);

                s2 = getRandomNumber(1, 90);
                smodel = glm::rotate(smodel, glm::radians((float) s2), glm::vec3(0.0f, -1.0f, 0.0f));
                models.push_back(smodel);

                smodel = glm::rotate(smodel, glm::radians((float) -s2), glm::vec3(0.0f, -1.0f, 0.0f));
                models.push_back(smodel);

            }

            if (sqrt(pow(q4.x, 2) + pow(q4.z, 2)) < (float) n / 2 &&
                !(  q4.x > pitch_bounds.x && q4.x < pitch_bounds.z &&
                    q4.z > pitch_bounds.y && q4.z < pitch_bounds.w
                )
            ) {
                smodel = glm::translate(glm::mat4(1.0f), q4);
                models.push_back(smodel);

                s1 = getRandomNumber(1, 90);
                smodel = glm::rotate(smodel, glm::radians((float) s1), glm::vec3(0.0f, -1.0f, 0.0f));
                models.push_back(smodel);

                smodel = glm::rotate(smodel, glm::radians((float) -s1), glm::vec3(0.0f, -1.0f, 0.0f));
                models.push_back(smodel);

                s2 = getRandomNumber(1, 90);
                smodel = glm::rotate(smodel, glm::radians((float) s2), glm::vec3(0.0f, -1.0f, 0.0f));
                models.push_back(smodel);

                smodel = glm::rotate(smodel, glm::radians((float) -s2), glm::vec3(0.0f, -1.0f, 0.0f));
                models.push_back(smodel);
            }

            position.z += 0.5f;

        }
        position.z = 0.0f;
        position.x += 0.5f;
    }
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