#ifndef CIRCLE_H
#define CIRCLE_H

#include <glm/glm.hpp>
#include <math.h>
#include <iostream>

class Circle {
    public:
        
        void calculate(glm::vec3 center_position, float angle_in_degrees, float radius);
};

#endif