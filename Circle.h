#ifndef CIRCLE_H
#define CIRCLE_H

#include <glm/glm.hpp>
#include <math.h>
#include <iostream>
#include "Vertex.h"
#include <vector>
#include <glad/glad.h>
#include "Collision.h"

class Circle {
    public:
        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;
        Collision collision;

        float radius;

        // std::vector<Texture> textures;

        void calculate(
            glm::vec3 center_position, 
            float angle_in_degrees, 
            float radius,
            glm::vec4 color
        );
};

#endif