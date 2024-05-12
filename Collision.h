#ifndef COLLISION_H
#define COLLISION_H

#include <glm/glm.hpp>
#include <vector>
#include <math.h>
#include "Mesh.h"

struct AABB {
    glm::vec3 position;
    glm::vec3 size;
};

class Collision {
    public: 

    
        float right_most_point = 0.0f;
        float left_most_point = 0.0f;
        float top_most_point = 0.0f;
        float bottom_most_point = 0.0f;
        float front_most_point = 0.0f;
        float back_most_point = 0.0f;

        AABB aabb;

        void processVertices(glm::vec3 vector);
        AABB calculateBoundingBox();
        bool CheckCollision(AABB &one, AABB &two); // AABB - AABB collision
        bool CheckCollisionY(AABB &one, AABB &two); // AABB - AABB collision
        bool CheckMassCollision(AABB &one, std::vector<AABB> static_objects);
        bool CheckMassCollisionY(AABB &one, std::vector<AABB> static_objects);
        Mesh generateBoundingBoxMesh(AABB aabb, glm::vec4 color);


};

#endif