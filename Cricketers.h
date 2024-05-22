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

        std::vector<glm::vec3> positions = {
            glm::vec3(-51.0f, -50.0f, 67.0f), // --
            glm::vec3(-35.0f, -50.0f, -94.0f), // --
            glm::vec3(-37.0f, -50.0f, -27.0f), // --
            glm::vec3(67.0f, -50.0f, -21.0f), // --
            glm::vec3(149.0f, -50.0f, -45.0f), // --
            glm::vec3(-137.0f, -50.0f, -96.0f), // --
            glm::vec3(-134.0f, -50.0f, 120.0f), // --
            glm::vec3(110.0f, -50.0f, -76.0f), // --
            glm::vec3(-43.0f, -50.0f, 149.0f), // --
            glm::vec3(-40.0f, -50.0f, 45.0f),
            glm::vec3(132.0f, -50.0f, 60.0f), // ++
            glm::vec3(-98.0f, -50.0f, 118.0f)
        };

        std::vector<float> rotations;

        glm::vec3 batter_1_position;
        glm::vec3 batter_2_position;
        
        void generate_positions(float field_radius, glm::vec4 pitch_bounds);
        void get_batter_starting_positions(glm::vec4 pitch_bounds);
        int getRandomNumber(int start, int stop);
        void print_random_positions();
        void draw(Shader& shader, glm::mat4 view, glm::mat4 projection);
};

#endif