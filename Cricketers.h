#ifndef CRICKETERS_H
#define CRICKETERS_H

#include <vector>
#include <glm/glm.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <random>
#include <math.h>
#include <iostream>
#include "aModel.h"
#include "Shader.h"

class Cricketers {
    public:

        aModel field_man;
        
        Cricketers();

        std::vector<glm::vec3> positions;
        glm::vec3 batter_1_position;
        glm::vec3 batter_2_position;
        
        void generate_positions(float field_radius, glm::vec4 pitch_bounds);
        void get_batter_starting_positions(glm::vec4 pitch_bounds);
        int getRandomNumber(int start, int stop);
        void print_random_positions();
        void draw(Shader& shader, glm::mat4 view, glm::mat4 projection);
};

#endif