#include "Cricketers.h"

Cricketers::Cricketers() {
    field_man = aModel("./animations/guy_object.obj", false);
}

void Cricketers::generate_positions(float field_radius, glm::vec4 pitch_bounds) {

    // while (positions.size() < 12)
    // {
        // float position_x = getRandomNumber(0, field_radius);
        // float position_z = getRandomNumber(0, field_radius);

        // if  (    sqrt(pow(position_x, 2) + pow(position_z, 2)) < (float) field_radius && 
        //     !(  position_x > pitch_bounds.x && position_x < pitch_bounds.z &&
        //         position_z > pitch_bounds.y && position_z < pitch_bounds.w)
        // ) {
        //     int indicator = getRandomNumber(0, 3);
        //     glm::vec3 random_position;
        //     switch (indicator)
        //     {
        //     case 0:
        //         random_position = glm::vec3(position_x, -50.0f, position_z);
        //         break;
        //     case 1:
        //         random_position = glm::vec3(position_x, -50.0f, -position_z);
        //         break;
        //     case 2:
        //         random_position = glm::vec3(-position_x, -50.0f, -position_z);
        //         break;
        //     default:
        //         random_position = glm::vec3(-position_x, -50.0f, position_z);
        //         break;
        //     }

            
        //     if (random_position.z < 0.0f) {

        //         float a_magnitude = 1.0f;
        //         float b_magnitude = sqrt(pow(random_position.x, 2) + pow(random_position.z, 2));
        //         float a_dot_b = glm::dot(glm::vec2(random_position.x, random_position.z), glm::vec2(0.0f, 1.0f));

        //         float angle = acos(a_dot_b / (a_magnitude * b_magnitude));             
        //         rotations.push_back(glm::radians(180.0f));
        //     } else {

        //         float a_magnitude = 1.0f;
        //         float b_magnitude = sqrt(pow(random_position.x, 2) + pow(random_position.z, 2));
        //         float a_dot_b = glm::dot(glm::vec2(random_position.x, random_position.z), glm::vec2(0.0f, -1.0f));

        //         float angle = acos(a_dot_b / (a_magnitude * b_magnitude));             
        //         rotations.push_back(glm::radians(0.0f));
        //     }
        //     positions.push_back(random_position);
        // } 

        
             
    // }

    for (glm::vec3 position : positions) {
            if (position.z < 0.0f) {

                float a_magnitude = 1.0f;
                float b_magnitude = sqrt(pow(position.x, 2) + pow(position.z, 2));
                float a_dot_b = glm::dot(glm::vec2(position.x, position.z), glm::vec2(0.0f, -1.0f));

                float angle = acos(a_dot_b / (a_magnitude * b_magnitude));             
                std::cout << "Random Position" << "( x: " << position.x << ", y: " << position.y << ", z: " << position.z << ")" << std::endl;
                std::cout << "Less Angle" << angle << "\n";


                if(position.x > 0.0f) {
                    rotations.push_back((glm::radians(0.0f) - angle));
                } else {
                    rotations.push_back((glm::radians(0.0f) + angle));

                }
         
            } else {

                float a_magnitude = 1.0f;
                float b_magnitude = sqrt(pow(position.x, 2) + pow(position.z, 2));
                float a_dot_b = glm::dot(glm::vec2(position.x, position.z), glm::vec2(0.0f, 1.0f));

                float angle = acos(a_dot_b / (a_magnitude * b_magnitude));             
                std::cout << "Random Position" << "( x: " << position.x << ", y: " << position.y << ", z: " << position.z << ")" << std::endl;
                std::cout << "More Angle" << angle << "\n";
            
                // glm::radians(180.0f - angle)


                if(position.x > 0.0f) {
                    rotations.push_back((glm::radians(180.0f) + angle));
                } else {
                    rotations.push_back((glm::radians(180.0f) - angle));

                }
            }
    }
    
}

void Cricketers::get_batter_starting_positions(glm::vec4 pitch_bounds) {

    batter_1_position = glm::vec3(pitch_bounds.x, -50.0f, 0.0f);
    batter_2_position = glm::vec3(pitch_bounds.z, -50.0f, 0.0f);

    std::cout << "Batter Position" << "( x: " << batter_1_position.x << ", y: " << batter_1_position.y << ", z: " << batter_1_position.z << ")" << std::endl;
    std::cout << "Batter Position" << "( x: " << batter_2_position.x << ", y: " << batter_2_position.y << ", z: " << batter_2_position.z << ")" << std::endl;

}

void Cricketers::print_random_positions() {
    int i = 0;
    for(glm::vec3 position : positions) {
        std::cout << "Random Position" << "( x: " << position.x << ", y: " << position.y << ", z: " << position.z << ")" << std::endl;
         std::cout << "Rotaion" << rotations[i]  << std::endl;
         i++;
    }
}

void Cricketers::draw(Shader& shader, glm::mat4 view, glm::mat4 projection) {
    shader.Activate();
    shader.setMat4("projection", projection);
    shader.setMat4("view", view);

    glm::mat4 model;

    for(int i = 0; i < positions.size(); i++) {
        model = glm::mat4(1.0f);

        // rotations[i] += 0.1f;

        model = glm::translate(model, positions[i]);

        if (rotations[i] == 0.0f) {
            model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
        } 
        model = glm::rotate(model, rotations[i], glm::vec3(0.0f, 1.0f, 0.0f));

        shader.setMat4("model", model);
        field_man.Draw(shader);
    }
    
    model = glm::mat4(1.0f);
    model = glm::translate(model, batter_1_position);
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    shader.setMat4("model", model);
    field_man.Draw(shader);

    model = glm::mat4(1.0f);
    model = glm::translate(model, batter_2_position);
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    shader.setMat4("model", model);
    field_man.Draw(shader);
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