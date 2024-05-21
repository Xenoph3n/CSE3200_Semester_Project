#include "WorldBoundary.h"

void WorldBoundary::calculateWorldAABBs() {

    glm::vec3 q1_point = glm::vec3(radius_size, 0.0f, radius_size);
    glm::vec3 q2_point = glm::vec3(-radius_size, 0.0f, radius_size);
    glm::vec3 q3_point = glm::vec3(-radius_size, 0.0f, -radius_size);
    glm::vec3 q4_point = glm::vec3(radius_size, 0.0f, -radius_size);

    std::vector<glm::vec3> points;
    points.push_back(q1_point);
    points.push_back(q2_point);
    points.push_back(q3_point);
    points.push_back(q4_point);

    AABB aabb; 

    aabb.position = q3_point + glm::vec3(0.0f, 0.0f, 0.0f);
    aabb.size = glm::vec3(radius_size * 2, 50.0f, 0.0f);
    aabbs.push_back(aabb);  

    aabb.position = q2_point + glm::vec3(0.0f, 0.0f, 0.0f);
    aabb.size = glm::vec3(radius_size * 2, 50.0f, 0.0f);
    aabbs.push_back(aabb);  
    
    aabb.position = q4_point + glm::vec3(0.0f, 0.0f, 0.0f);
    aabb.size = glm::vec3(0.0f, 50.0f, radius_size * 2);
    aabbs.push_back(aabb);  

    aabb.position = q3_point + glm::vec3(0.0f, 0.0f, 0.0f);
    aabb.size = glm::vec3(0.0f, 50.0f, radius_size * 2);
    aabbs.push_back(aabb);  
    
}
