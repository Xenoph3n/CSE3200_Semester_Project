#ifndef WORLD_BOUNDARY_H
#define WORLD_BOUNDARY_H

#include <glm/glm.hpp>
#include <vector>
#include <glad/glad.h>
#include "Collision.h"
#include <vector>
#include "Vertex.h"
#include <math.h>

class WorldBoundary {
    
    
    public:
        float radius_size = 200.0f;
        
        float size_x = 0.0f;
        float size_y = 0.0f;
        float size_z = 0.0f;

        float y_offset;
        float z_offset;
        std::vector<AABB> aabbs;
        std::vector<Vertex> vertices;
        
        void calculateWorldAABBs();
};

#endif