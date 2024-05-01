#include "Circle.h"

void Circle::calculate(glm::vec3 center_position, float angle_in_degrees, float radius) {

    int number_of_sections = floor(360.0f / angle_in_degrees);
    int number_of_sections_per_quadrant = number_of_sections / 4;

    glm::vec3 positions[number_of_sections + 1];
    unsigned int indices[number_of_sections * number_of_sections_per_quadrant];

    std::cout << number_of_sections << "\n";

    float x = center_position.x;
    float y = center_position.y + radius;
    
    positions[0] = glm::vec3(x, y, 0.0f);
    
    for (int i = 1; i <= number_of_sections_per_quadrant; i++) {
        if (angle_in_degrees < 90.0f) {
            x = center_position.x + glm::sin(glm::radians(angle_in_degrees)) * radius;
            y = center_position.y + glm::cos(glm::radians(angle_in_degrees)) * radius;

            positions[i] = glm::vec3(x, y, 0.0f);
            
            angle_in_degrees += angle_in_degrees;

        } else {
            x = center_position.x + radius;
            y = center_position.y;

            positions[i] = glm::vec3(x, y, 0.0f);
        } 
    }   

    for (int i = 1; i < number_of_sections_per_quadrant; i++) {
        
        glm::vec3 quad_2 = glm::vec3(positions[i].x, center_position.y - positions[i].y, 0.0f);
        glm::vec3 quad_3 = glm::vec3(center_position.x - positions[i].x, center_position.y - positions[i].y, 0.0f);
        glm::vec3 quad_4 = glm::vec3(center_position.x - positions[i].x, positions[i].y, 0.0f);

        positions[number_of_sections_per_quadrant + i] = quad_2;
        positions[number_of_sections_per_quadrant * 2 + i] = quad_3;
        positions[number_of_sections_per_quadrant * 3 + i] = quad_4;
        std::cout << "hello..." << "\n";    
    }

    x = center_position.x;
    y = center_position.y - radius;
    positions[number_of_sections_per_quadrant * 2] = glm::vec3(x, y, 0.0f);

    x = center_position.x - radius;
    y = center_position.y;
    positions[number_of_sections_per_quadrant * 3] = glm::vec3(x, y, 0.0f);

    positions[number_of_sections] = center_position;

    for (int i = 0; i < number_of_sections + 1; i++) {
        std::cout << "(" << positions[i].x << "," << positions[i].y << "," << positions[i].z << ")" << "\n";
    }

    int count = 0;
    for (int i = 0; i < number_of_sections * number_of_sections_per_quadrant; i+=number_of_sections_per_quadrant) {
        indices[i] = number_of_sections;
        
        if (count + 1 != number_of_sections) {
            indices[i + 1 ] = count;
            indices[i + 2] = count + 1; 
        } else {
            indices[i + 1 ] = count;
            indices[i + 2] = 0; 
        }
        count +=1;
    }
    
}