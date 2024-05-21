#include "Cricketers.h"

Cricketers::Cricketers() {
    field_man = aModel("./animations/guy_object.obj", false);
}

void Cricketers::generate_positions(float field_radius, glm::vec4 pitch_bounds) {

   
    while (positions.size() < 12)
    {
        float position_x = getRandomNumber(0, field_radius);
        float position_z = getRandomNumber(0, field_radius);

        if  (    sqrt(pow(position_x, 2) + pow(position_z, 2)) < (float) field_radius && 
            !(  position_x > pitch_bounds.x && position_x < pitch_bounds.z &&
                position_z > pitch_bounds.y && position_z < pitch_bounds.w)
        ) {
            int indicator = getRandomNumber(0, 3);
            glm::vec3 random_position;
            switch (indicator)
            {
            case 0:
                random_position = glm::vec3(position_x, -50.0f, position_z);
                break;
            case 1:
                random_position = glm::vec3(position_x, -50.0f, -position_z);
                break;
            case 2:
                random_position = glm::vec3(-position_x, -50.0f, -position_z);
                break;
            default:
                random_position = glm::vec3(-position_x, -50.0f, position_z);
                break;
            }
            
            positions.push_back(random_position);
        } 
    }
    
}

void Cricketers::get_batter_starting_positions(glm::vec4 pitch_bounds) {

    float center_position_z = abs(pitch_bounds.y - pitch_bounds.w) / 2;

    batter_1_position = glm::vec3(pitch_bounds.x, -50.0f, center_position_z);
    batter_2_position = glm::vec3(pitch_bounds.z, -50.0f, center_position_z);
}

void Cricketers::print_random_positions() {
    for(glm::vec3 position : positions) {
        std::cout << "Random Position" << "( x: " << position.x << ", y: " << position.y << ", z: " << position.z << ")" << std::endl;
    }
}

void Cricketers::draw(Shader& shader, glm::mat4 view, glm::mat4 projection) {
    shader.Activate();
    shader.setMat4("projection", projection);
    shader.setMat4("view", view);

    for(glm::vec3 position : positions) {
        glm::mat4 model = glm::mat4(1.0f);

        model = glm::translate(model, position);
        shader.setMat4("model", model);
        field_man.Draw(shader);
    }
}

// Function to generate a random number
int Cricketers::getRandomNumber(int start, int stop) {
    // Define a random number generator engine
    static std::random_device rd;
    static std::mt19937 gen(rd());
    // Define a distribution (for example, between 0 and 100)
    std::uniform_int_distribution<int> distribution(start, stop);
    // Generate and return a random number
    return distribution(gen);
}