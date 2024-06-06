#include "Circle.h"

void Circle::calculate(glm::vec3 center_position, float angle_in_degrees, float radius, glm::vec4 color) {

    Circle::radius = radius;
    
    int number_of_sections = floor(360.0f / angle_in_degrees);
    int number_of_sections_per_quadrant = number_of_sections / 4;

    glm::vec3 positions[20];
    unsigned int ind[200];

    float x = center_position.x;
    float z = center_position.z + radius;
    
    positions[0] = glm::vec3(x, 0.0f, z);
    
    for (int i = 1; i <= number_of_sections_per_quadrant; i++) {
        if (angle_in_degrees < 90.0f) {
            x = center_position.x + glm::sin(glm::radians(angle_in_degrees)) * radius;
            z = center_position.z + glm::cos(glm::radians(angle_in_degrees)) * radius;

            positions[i] = glm::vec3(x, 0.0f, z);
            
            angle_in_degrees += angle_in_degrees;

        } else {
            x = center_position.x + radius;
            z = center_position.z;

            positions[i] = glm::vec3(x, 0.0f, z);
        } 
    }   

    for (int i = 1; i < number_of_sections_per_quadrant; i++) {
        
        glm::vec3 quad_2 = glm::vec3(positions[i].x, 0.0f, center_position.z - positions[i].z);
        glm::vec3 quad_3 = glm::vec3(center_position.x - positions[i].x, 0.0f, center_position.z - positions[i].z);
        glm::vec3 quad_4 = glm::vec3(center_position.x - positions[i].x, 0.0f, positions[i].z);

        positions[number_of_sections_per_quadrant * 2 - i] = quad_2;
        positions[number_of_sections_per_quadrant * 4 - i] = quad_4;

        positions[number_of_sections_per_quadrant * 2 + i] = quad_3;
    }

    x = center_position.x;
    z = center_position.z - radius;
    positions[number_of_sections_per_quadrant * 2] = glm::vec3(x, 0.0f, z);

    x = center_position.x - radius;
    z = center_position.z;
    positions[number_of_sections_per_quadrant * 3] = glm::vec3(x, 0.0f, z);

    positions[number_of_sections] = center_position;

    unsigned int count = 0;
    for (int i = 0; i < number_of_sections * number_of_sections_per_quadrant; i+=number_of_sections_per_quadrant) {
        // ind[i] = number_of_sections;
        indices.push_back(number_of_sections);

        if (count + 1 != number_of_sections) {
            indices.push_back(count);
            indices.push_back(count + 1); 
        } else {
            indices.push_back(count);
            indices.push_back(0);
        }

        count +=1;
    }

    for (int i = 0; i <= number_of_sections; i++) {
        Vertex vertex;

        vertex.position = positions[i];
        collision.processVertices(vertex.position);
        vertex.color = color; 
        vertex.normal = glm::vec3(0.0f, 1.0f, 0.0f);
        vertex.texUV = glm::vec2(positions[i].x, positions[i].z);
    
        vertices.push_back(vertex);
    }

}